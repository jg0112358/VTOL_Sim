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


    for(int ruddIndex = 0; ruddIndex < numFoils; ruddIndex++){
        for(int elevIndex = 0; elevIndex < numFoils; elevIndex++){
            for(int LAilIndex = 0; LAilIndex < numFoils; LAilIndex++){
                for(int RAilIndex = 0; RAilIndex < numFoils; RAilIndex++){
                    //Skip over symmetric cases
                    if (RAilIndex < LAilIndex)
                    {
                        continue;
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
                        std::cout << "\n Successfully opened file: " << filePath << "\n";
                    }

                    bool validRowFound = false;

                    
                    // Process the file line by line
                    while (std::getline(file, line)) {
                        std::istringstream iss(line);
                        std::string firstToken;

                        // Get the first non-space token to determine if the row is valid
                        iss >> firstToken;

                        // Check if the first token is a number (or row starts with space and then a number)
                        if (!firstToken.empty() && (std::isdigit(firstToken[0]) || (firstToken[0] == '-' && std::isdigit(firstToken[1])))) {
                            validRowFound = true; // Found a valid row
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
                            

                            /* Create SQL statement */
                            sql_stream << "INSERT OR REPLACE INTO FLOW5DATA (ID, LEFT, RIGHT, ELEVATOR, RUDDER, ALPHA,"
                                << "CLIFT, CDRAG, CSIDEFORCE, CROLL, CPITCH, CYAW) VALUES ("
                                << ID << ", "
                                << LEFT << ", "
                                << RIGHT << ", "
                                << ELEVATOR << ", "
                                << RUDDER << ", "
                                << ALPHA << ", "
                                << CLIFT << ", "
                                << CDRAG << ", "
                                << CSIDEFORCE << ", "
                                << CROLL << ", "
                                << CPITCH << ", "
                                << CYAW << ");";

                            const char* sql = sql_stream.str().c_str();
                            /* Execute SQL statement */
                            rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
                            
                            
                            if( rc != SQLITE_OK ){
                                fprintf(stderr, "\n ###########SQL error: %s\n", zErrMsg);
                                std::cout << "Error issued for: " << "\"";
                                fprintf(stdout, sql);
                                std::cout << "\"\n";
                                errorCount ++;
                            } else {
                                fprintf(stdout, sql);
                                std::cout<<"\n";
                                // std::cout << "Records created for: " << "INSERT OR REPLACE INTO FLOW5DATA (ID, LEFT, RIGHT, ELEVATOR, RUDDER, ALPHA,"
                                // << "CLIFT, CDRAG, CSIDEFORCE, CROLL, CPITCH, CYAW) VALUES ("
                                // << ID << ", "
                                // << LEFT << ", "
                                // << RIGHT << ", "
                                // << ELEVATOR << ", "
                                // << RUDDER << ", "
                                // << ALPHA << ", "
                                // << CLIFT << ", "
                                // << CDRAG << ", "
                                // << CSIDEFORCE << ", "
                                // << CROLL << ", "
                                // << CPITCH << ", "
                                // << CYAW << "); \n";
                            }

                            // reset row validation
                            sql_stream.str("");
                            sql_stream.clear();
                            validRowFound = false;
                            ID++;
                        }
                    }

                    file.close();
                }
            }
        }
    }

    
    sqlite3_close(db);

    std::cout << "\n\n THERE WERE " << errorCount << " ERRORS IN THIS RUN \n";

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

