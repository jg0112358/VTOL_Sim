function sumSqDiff = sumOfSquaresOfDifferences(matrix1, matrix2)
    % Check if the dimensions of the matrices match
    if ~isequal(size(matrix1), size(matrix2))
        error('Matrices must be of the same size.');
    end
    
    % Compute the element-wise differences
    differences = matrix1 - matrix2;
    
    % Square the differences
    squaredDifferences = differences .^ 2;
    
    % Sum all the squared differences
    sumSqDiff = sum(squaredDifferences(:));
end