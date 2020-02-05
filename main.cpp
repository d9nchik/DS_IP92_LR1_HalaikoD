#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


void getGraf(int &n, int &m, vector<vector<int>> &heights, int answer);

vector<vector<int>> getMatrixAdjacency(int n, vector<vector<int>> &heights);

vector<vector<int>> getMatrixIncidence(int n, vector<vector<int>> &heights);

void showMatrix(vector<vector<int>> matrix);

vector<int> getDegreeOfVecticles(vector<vector<int>> matrixOfInc);

void showIsolated(vector<int> degrees);


int main() {
    cout << "Launch part 1 or 2: ";
    int part;
    cin >> part;
    switch (part) {
        case 1: {
            int n, m;
            vector<vector<int>> heights;
            getGraf(n, m, heights, part);


            vector<vector<int>> matrixOfAdjacency = getMatrixAdjacency(n, heights);
            cout << "Matrix of adjacency: " << endl;
            showMatrix(matrixOfAdjacency);

            vector<vector<int>> matrixOfInc = getMatrixIncidence(n, heights);
            cout << "Matrix of incidence: " << endl;
            showMatrix(matrixOfInc);

            vector<int> degrees = getDegreeOfVecticles(matrixOfInc);
            showIsolated(degrees);
        }
            break;
        case 2: {
            int n, m;
            vector<vector<int>> heights;
            getGraf(n, m, heights, part);
        }
            break;
        default:
            cout << "Your answer is incorrect!";
    }

    return 0;
}

void getGraf(int &n, int &m, vector<vector<int>> &heights, int answer) {
    string path;
    switch (answer) {
        case 1:
            path = R"(C:\Users\danga\CLionProjects\DS_IP92_LR1_HalaikoD\orgrafi.txt)";
            break;
        case 2:
            path = R"(C:\Users\danga\CLionProjects\DS_IP92_LR1_HalaikoD\disorgrafi.txt)";
            break;
        default:
            cout << "Something has gone wrong!";
            exit(1);
    }
    ifstream orGrafI(path, ios::in);
    orGrafI >> n >> m;
    for (int i = 0; i < m; ++i) {
        vector<int> temp;
        int a, b;
        orGrafI >> a >> b;
        temp.push_back(a);
        temp.push_back(b);
        heights.push_back(temp);
    }
    orGrafI.close();
    for (int i = 0; i < m; ++i) {
        cout << heights[i][0] << " " << heights[i][1] << endl;
    }
}

vector<vector<int>> getMatrixAdjacency(int n, vector<vector<int>> &heights) {
    vector<vector<int>> matrix;
    for (int i = 0; i < n; ++i) {
        vector<int> temp;
        temp.reserve(n);
        for (int j = 0; j < n; ++j) {
            temp.push_back(0);
        }
        matrix.push_back(temp);
    }
    for (auto &height : heights) {
        matrix[height[0] - 1][height[1] - 1] = 1;
        matrix[height[1] - 1][height[0] - 1] = 1;
    }
    return matrix;
}

void showMatrix(vector<vector<int>> matrix) {
    cout << " \\ ";
    for (int k = 0; k < matrix[0].size(); ++k) {
        cout << k + 1 << " |";
    }
    cout << endl;
    for (int i = 0; i < matrix.size(); ++i) {
        cout << i + 1 << " |";
        for (int j : matrix[i]) {
            cout << j << " |";
        }
        cout << endl;
    }
}

vector<vector<int>> getMatrixIncidence(int n, vector<vector<int>> &heights) {
    vector<vector<int>> matrix;
    for (int i = 0; i < n; ++i) {
        vector<int> temp;
        temp.reserve(heights.size());
        for (int j = 0; j < heights.size(); ++j) {
            temp.push_back(0);
        }
        matrix.push_back(temp);
    }

    for (int k = 0; k < heights.size(); ++k) {
        matrix[heights[k][0] - 1][k] = 1;
        matrix[heights[k][1] - 1][k] = 1;
    }
    return matrix;
}

vector<int> getDegreeOfVecticles(vector<vector<int>> matrixOfInc) {
    vector<int> degree;
    cout << "Degree of Vecticles:" << endl;
    for (int i = 0; i < matrixOfInc.size(); ++i) {
        int summa = 0;
        for (int j : matrixOfInc[i]) {
            summa += j;
        }
        degree.push_back(summa);
        cout << i + 1 << " - " << summa << endl;
    }

    bool isUniform = true;
    for (int k = 1; k < degree.size(); ++k) {
        if (degree[0] != degree[k]) {
            isUniform = false;
            break;
        }
    }

    if (isUniform) {
        cout << "Graf is uniform. Degree " << degree[0];
    }
    return degree;
}

void showIsolated(vector<int> degrees) {
    cout << "Do you want to watch isolated?(1 for yes, 0 for no): ";
    int answer;
    cin >> answer;
    if (answer) {
        cout << "Hanging points: ";
        for (int i = 0; i < degrees.size(); ++i) {
            if (degrees[i] == 1)
                cout << i + 1 << " ";
        }
        cout << endl << "Isolated points: ";
        for (int i = 0; i < degrees.size(); ++i) {
            if (degrees[i] == 0)
                cout << i + 1 << " ";
        }
    }
}
