#include "hungarianoper.h"

Eigen::Matrix<float, -1, 2, Eigen::RowMajor> HungarianOper::Solve(const DYNAMICM &cost_matrix)
{
    
    //把cost_matrix矩阵复制到matrix中
        
    int rows = cost_matrix.rows();
    int cols = cost_matrix.cols();
    Matrix<double> matrix(rows, cols);    //新建矩阵matrix
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            matrix(row, col) = cost_matrix(row, col);
        }
    }
    
    //Munkres get matrix;
    Munkres<double> m;
    m.solve(matrix);

    //
    std::vector<std::pair<int, int>> pairs;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int tmp = (int)matrix(row, col);
            if (tmp == 0) pairs.push_back(std::make_pair(row, col));
        }
    }
    
    //写入indices矩阵
    int count = pairs.size();
    Eigen::Matrix<float, -1, 2, Eigen::RowMajor> re(count, 2);
    for (int i = 0; i < count; i++) {
        re(i, 0) = pairs[i].first;
        re(i, 1) = pairs[i].second;
    }
    return re;
}//end Solve;
