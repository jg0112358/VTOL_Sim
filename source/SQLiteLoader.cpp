/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            main.cpp                                                        *
 * Purpose:         To create a simulated model of my VTOL aircraft for data-gen    *
 * Description:     This script is intended to take the flow5 simulation op-points, *
 *                  and combine them with basic vector mechanics and simulation of  *
 *                  the motor and propellers, and the battery to create a discrete- *
 *                  time state-space model of the VTOL aircraft. It is expected that*
 *                  this will not be a perfect representation of the aircraft, but  *
 *                  will be sufficient.                                             *
 ***********************************************************************************/
 
/*********************************** INCLUDES **************************************/
//Libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <sqlite3.h>

//Internal Headers

/************************************ GLOBALS **************************************/
const std::string airfoils[] = {"18deg_down","05deg_down","Neutral","05deg_up","18deg_up"};
const double controlSurfaceAngles[5] = {-18,-5,0,5,18};
const int numFoils = 5;

/***************************** FUNCTIONS DEFINITIONS********************************/

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

/*===========================================================================
 * Function:        main
 * Arguments:       int argc - Number of command line arguments 
                    char *argv[] - Array of command line arguments 
 * Returns:         int - 0 on success, 1 on fail
 * Description:     main function
 */
int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char* data = "Callback function called";

    int errorCount =0;


    /* Open database */
    rc = sqlite3_open("flow5Data.db", &db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stdout, "Opened database successfully\n");
    }

    /* Create SQL statement */
   sql = "CREATE TABLE FLOW5DATA("  
      "ID INT PRIMARY   KEY         NOT NULL," 
      "LEFT             REAL        NOT NULL," 
      "RIGHT            REAL        NOT NULL," 
      "ELEVATOR         REAL        NOT NULL," 
      "RUDDER           REAL        NOT NULL,"
      "ALPHA            REAL        NOT NULL,"
      "CLIFT            REAL        NOT NULL,"
      "CDRAG            REAL        NOT NULL,"
      "CSIDEFORCE       REAL        NOT NULL,"
      "CROLL            REAL        NOT NULL,"
      "CPITCH           REAL        NOT NULL,"
      "CYAW             REAL        NOT NULL );";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }

    std::string masterfolder = "/Users/jamesguest/Documents/UBC/540 - Data-Driven Modelling/Project/flow5_XML_analysis/output/plane_scripted_run/Planes";
    int ID =0;
    double LEFT, RIGHT, ELEVATOR, RUDDER, ALPHA, CLIFT, CDRAG, CSIDEFORCE, CROLL, CPITCH, CYAW;
    std::ostringstream sql_stream;

    bool repeatsymmetry = false;
    int asymmetryCount = 0;
    int validRowCount = 0;
    int repeatedLines = 0;
    int totalFiles = 0;

    sqlite3_stmt *stmt;
    const char *sql_INSERT = "INSERT OR REPLACE INTO FLOW5DATA (ID, LEFT, RIGHT, ELEVATOR, RUDDER, ALPHA, CLIFT, CDRAG, CSIDEFORCE, CROLL, CPITCH, CYAW) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";


    for(int ruddIndex = 0; ruddIndex < numFoils; ruddIndex++){
        for(int elevIndex = 0; elevIndex < numFoils; elevIndex++){
            for(int LAilIndex = 0; LAilIndex < numFoils; LAilIndex++){
                for(int RAilIndex = 0; RAilIndex < numFoils; RAilIndex++){
                    //Skip over symmetric cases
                    if (RAilIndex < LAilIndex)
                    {
                        continue;
                    }
                    if (RAilIndex != LAilIndex){
                        repeatsymmetry = true;
                        asymmetryCount ++;
                        
                    }
                    
                    // Set folder name to identify plane geometry
                    std::string filePath = masterfolder + "/Rud_" + airfoils[ruddIndex] 
                                                        + "_Elev_" + airfoils[elevIndex] 
                                                        + "_LAil_" + airfoils[LAilIndex] 
                                                        + "_RAil_" + airfoils[RAilIndex] 
                                                        + "_xml"
                                            + "/T1-20_0 m_s-TriUniform-ThinSurf_xml.csv";

                    //Try opening the csv file
                    std::ifstream file(filePath); // File still has a .csv extension
                    std::string line;
                    if (!file.is_open()) {
                        std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
                        std::cout << "Called file path: " << filePath << "\n";
                        std::cerr << "Error opening file!" << std::endl;
                        return 1;
                    } else {
                        // std::cout << "\n Successfully opened file: " << filePath << "\n";
                        totalFiles++;
                    }

                    bool validRowFound = false;

                    
                    // Process the file line by line
                    while (std::getline(file, line)) {
                        std::istringstream iss(line);
                        std::string firstToken;

                        // Get the first non-space token to determine if the row is valid
                        iss >> firstToken;

                        // Check if the first token is a number (or row starts with space and then a number)
                        if (!firstToken.empty() && (std::isdigit(firstToken[0]) || (firstToken[0] == '-' && std::isdigit(firstToken[1]) ) ) ) {
                            validRowFound = true; // Found a valid row
                            validRowCount++;
                            if (repeatsymmetry){ repeatedLines++;}
                        }

                        if (validRowFound) {
                            std::vector<double> extractedNumbers;
                            double value;
                            int columnIndex = 0; // Track the column index for specific extraction

                            // Reset the stringstream to process the row fully
                            iss.clear();
                            iss.seekg(0);

                            // Extract specific numbers (e.g., column 2 and column 4)
                            while (iss >> value) {
                                // Extract specific column values (column 2, 4, 5, 8, 9, 12, 13)
                                if (columnIndex == 1 || columnIndex == 3 || columnIndex == 4 || columnIndex == 7 || columnIndex == 8 || columnIndex == 11 || columnIndex == 12) { // Columns are zero-based indexed
                                    extractedNumbers.push_back(value);
                                }
                                columnIndex++;
                            }

                            ALPHA = extractedNumbers[0];
                            CLIFT = extractedNumbers[1];
                            CDRAG = extractedNumbers[2];
                            CSIDEFORCE = extractedNumbers[3];
                            CPITCH = extractedNumbers[4];
                            CROLL = extractedNumbers[5];
                            CYAW = extractedNumbers[6];
                            
                            LEFT = controlSurfaceAngles[LAilIndex];
                            RIGHT = controlSurfaceAngles[RAilIndex];
                            ELEVATOR = controlSurfaceAngles[elevIndex];
                            RUDDER = controlSurfaceAngles[ruddIndex];
                            
                            // Prepare the statement
                            rc = sqlite3_prepare_v2(db, sql_INSERT, -1, &stmt, 0);
                            if (rc != SQLITE_OK) {
                                fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
                                return 1;
                            }

                            // Bind values and execute the statement for each row    
                            sqlite3_bind_int(stmt, 1, ID);
                            sqlite3_bind_double(stmt, 2, LEFT);
                            sqlite3_bind_double(stmt, 3, RIGHT);
                            sqlite3_bind_double(stmt, 4, ELEVATOR);
                            sqlite3_bind_double(stmt, 5, RUDDER);
                            sqlite3_bind_double(stmt, 6, ALPHA);
                            sqlite3_bind_double(stmt, 7, CLIFT);
                            sqlite3_bind_double(stmt, 8, CDRAG);
                            sqlite3_bind_double(stmt, 9, CSIDEFORCE);
                            sqlite3_bind_double(stmt, 10, CROLL);
                            sqlite3_bind_double(stmt, 11, CPITCH);
                            sqlite3_bind_double(stmt, 12, CYAW);   



      
                            /* Execute SQL statement */
                            rc = sqlite3_step(stmt);
                            if (rc != SQLITE_DONE) {
                                fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
                                errorCount ++;
                            }
                        

                            // reset row validation
                            sqlite3_reset(stmt);  // Reset the statement for the next execution
                            validRowFound = false;
                            ID++;

                            if (repeatsymmetry){
                                ALPHA = extractedNumbers[0];
                                CLIFT = extractedNumbers[1];
                                CDRAG = extractedNumbers[2];
                                CSIDEFORCE = -1 * extractedNumbers[3];
                                CPITCH = extractedNumbers[4];
                                CROLL = -1 * extractedNumbers[5];
                                CYAW = -1 * extractedNumbers[6];
                                
                                LEFT = controlSurfaceAngles[RAilIndex];
                                RIGHT = controlSurfaceAngles[LAilIndex];
                                ELEVATOR = controlSurfaceAngles[elevIndex];
                                RUDDER = -1 * controlSurfaceAngles[ruddIndex];
                                
                                // Prepare the statement
                                rc = sqlite3_prepare_v2(db, sql_INSERT, -1, &stmt, 0);
                                if (rc != SQLITE_OK) {
                                    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
                                    return 1;
                                }

                                // Bind values to the statement   
                                sqlite3_bind_int(stmt, 1, ID);
                                sqlite3_bind_double(stmt, 2, LEFT);
                                sqlite3_bind_double(stmt, 3, RIGHT);
                                sqlite3_bind_double(stmt, 4, ELEVATOR);
                                sqlite3_bind_double(stmt, 5, RUDDER);
                                sqlite3_bind_double(stmt, 6, ALPHA);
                                sqlite3_bind_double(stmt, 7, CLIFT);
                                sqlite3_bind_double(stmt, 8, CDRAG);
                                sqlite3_bind_double(stmt, 9, CSIDEFORCE);
                                sqlite3_bind_double(stmt, 10, CROLL);
                                sqlite3_bind_double(stmt, 11, CPITCH);
                                sqlite3_bind_double(stmt, 12, CYAW);   

        
                                /* Execute SQL statement */
                                rc = sqlite3_step(stmt);
                                if (rc != SQLITE_DONE) {
                                    fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
                                    errorCount ++;
                                }
                            

                                // reset row validation
                                sqlite3_reset(stmt);  // Reset the statement for the next execution
                                validRowFound = false;
                                ID++;
                            }

                            
                        }
                    }
                    repeatsymmetry = false;
                    file.close();
                }
            }
        }
    }

    sqlite3_finalize(stmt);
    
    sqlite3_close(db);

    std::cout << "\n\n THERE WERE " << errorCount << " ERRORS IN THIS RUN, OUT OF "<< ID << " LINES LOADED\n";
    std::cout << " Number of Assymetrical Mirrored Files: " << asymmetryCount <<std::endl;
    std::cout << " Total Number of Files: " << totalFiles <<std::endl;
    std::cout << " Number of Valid Lines: " << validRowCount <<std::endl;
    std::cout << " Number of Mirrored Lines: " << repeatedLines <<std::endl;

    return 0;
}




//     /* Create SQL statement */
//    sql = "SELECT * from FLOW5DATA";

//    /* Execute SQL statement */
//    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   
//    if( rc != SQLITE_OK ) {
//       fprintf(stderr, "SQL error: %s\n", zErrMsg);
//       sqlite3_free(zErrMsg);
//    } else {
//       fprintf(stdout, "Operation done successfully\n");
//    }


// if (repeatsymmetry){
                            //     ALPHA = extractedNumbers[0];
                            //     CLIFT = extractedNumbers[1];
                            //     CDRAG = extractedNumbers[2];
                            //     CSIDEFORCE = -1 * extractedNumbers[3];
                            //     CPITCH = extractedNumbers[4];
                            //     CROLL = -1 * extractedNumbers[5];
                            //     CYAW = -1 * extractedNumbers[6];
                                
                            //     LEFT = controlSurfaceAngles[RAilIndex];
                            //     RIGHT = controlSurfaceAngles[LAilIndex];
                            //     ELEVATOR = controlSurfaceAngles[elevIndex];
                            //     RUDDER = -1 * controlSurfaceAngles[ruddIndex];
                                

                            //     /* Create SQL statement */
                            //     sql_stream << "INSERT OR REPLACE INTO FLOW5DATA (\"ID\", \"LEFT\", \"RIGHT\", \"ELEVATOR\", \"RUDDER\", \"ALPHA\","
                            //         << "\"CLIFT\", \"CDRAG\", \"CSIDEFORCE\", \"CROLL\", \"CPITCH\", \"CYAW\") VALUES ("
                            //         << ID << ", "
                            //         << LEFT << ", "
                            //         << RIGHT << ", "
                            //         << ELEVATOR << ", "
                            //         << RUDDER << ", "
                            //         << ALPHA << ", "
                            //         << CLIFT << ", "
                            //         << CDRAG << ", "
                            //         << CSIDEFORCE << ", "
                            //         << CROLL << ", "
                            //         << CPITCH << ", "
                            //         << CYAW << ");";

                            //     const char* sql = sql_stream.str().c_str();
                            //     /* Execute SQL statement */
                            //     rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
                                
                                
                            //     if( rc != SQLITE_OK ){
                            //         fprintf(stderr, "\n ###########SQL error: %s\n", zErrMsg);
                            //         std::cout << "Error issued for: " << "\"";
                            //         fprintf(stdout, sql);
                            //         std::cout << "\"\n";
                            //         std::cout << "Error while parsing: " << filePath << std::endl;
                            //         std::cout << "Error inside if(repeatsymmetry) \n";
                            //         errorCount ++;
                            //     } else {
                            //         // fprintf(stdout, sql);
                            //         // std::cout<<"\n";
                            //     }

                            //     // reset row validation
                            //     sql_stream.str(" ");
                            //     sql_stream.clear();
                            //     validRowFound = false;
                            //     ID++;
                                
                            // }

