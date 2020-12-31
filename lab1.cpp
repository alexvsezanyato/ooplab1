#include <iostream>
#include <ctime>
#include <cstdlib>

class App {
public:
	virtual void runApp() = 0;
	virtual void pauseApp() = 0;
};

class MatrixApp : App {
public:
	using byte = unsigned char;
	struct vec2{ byte x; byte y; };
    struct direction{ bool horisotal; bool right; };

private:
	byte** matrix = nullptr;
	vec2 matrixSize{0, 0};
	byte min = 100;
	byte max = 200;
	bool filled = false;

	bool copyOnRightDiagonals(byte* row) {
        vec2 size = matrixSize;
        vec2 start{0, 0};
        short index = 0;
        short i = start.y, j = start.x;

        // start is a start point
        // (the cell where we start from)
		while (start.x < size.x && start.y < size.y) {
            while (j >= 0 && i < size.y) {
                short range = (short) size.x * (short) size.y;

                if (range - 1 < index) {
                    std::cout << "You're out of range!" << std::endl;
                    std::cout << range << " " << i << " " << j << std::endl;
                    return false;
                }
                row[index] = matrix[i][j];
                // std::cout << (short) matrix[i][j] << " ";
                // std::cout << "matrix[" << i << "][" << j << "] = " << matrix[i][j] << std::endl;
                // std::cout << std::endl;
                index++;
                i++;
                j--;
            }
            // if x is max, increment y
            // (the next diagonal - another start point)
            // (top left => bottom right)
            if (start.x < size.x - 1) start.x++;
            else start.y++;
            j = start.x;
            i = start.y;
        }
		return true;
	}
    bool copyOnLeftDiagonals(byte* row) {
        vec2 size = matrixSize;
        vec2 start{(byte) (size.x - 1), 0};
        short index = 0;
        short i = start.y, j = start.x;

        // start is a start point
        // (the cell where we start from)
		while (start.x >= 0 && start.y < size.y) {
            while (i < size.y && j < size.x) {
                short range = (short) size.x * (short) size.y;

                if (range - 1 < index) {
                    std::cout << "You're out of range!" << std::endl;
                    std::cout << range << " " << i << " " << j << std::endl;
                    return false;
                }
                row[index] = matrix[i][j];
                // std::cout << (short) matrix[i][j] << " ";
                // std::cout << "matrix[" << i << "][" << j << "] = " << matrix[i][j] << std::endl;
                // std::cout << std::endl;
                index++;
                i++;
                j++;
            }
            // if x is max, increment y
            // (the next diagonal - another start point)
            // (top left => bottom right)
            if (start.x > 0) start.x--;
            else start.y++;
            j = start.x;
            i = start.y;
        }
		return true;
    }
	bool copyInSpiral(byte* row, bool reverse) {
        vec2 size = matrixSize;
        bool** marked = new bool*[size.y];
        for (int i = 0; i < size.y; i++) marked[i] = new bool[size.x];
        bool horisontal = true;
        bool next = true;
        short index;
        if (reverse) index = (size.x * size.y) - 1;
        else index = 0;

        for (short i = 0; i < size.y; i++) {
            for (short j = 0; j < size.x; j++) {
                marked[i][j] = false;
            }
        }

        for (short i = 0, j = 0; !marked[i][j];) {
            if (i >= size.y || j >= size.x || i < 0 || j < 0) {
                std::cout << "You're out of range!" << std::endl;
                std::cout << "Direction: ";
                if (horisontal) std::cout << "horisontal ";
                else std::cout << "vertical ";
                if (next) std::cout << "right";
                else std::cout << "left";
                std::cout << std::endl;
                std::cout << "i: " << i << "; j: " << j << std::endl;
                return false;
            }    
            row[index] = matrix[i][j];
            marked[i][j] = true;
            if (reverse) index--;
            else index++;
            // std::cout << matrix[i][j] << " ";
            // check the direction
            if (horisontal) {
                // to the right, out of range => down
                if (next) if (j >= size.x - 1 || marked[i][j + 1]) {
                    horisontal = false;
                    next = true;
                } else;

                // to the left, out of range => up
                else if (!next) if  (j <= 0 || marked[i][j - 1]) {
                    horisontal = false;
                    next = false;
                }
            } else {
                // down, out of range => to the left
                if (next) if (i >= size.y - 1 || marked[i + 1][j]) {
                    horisontal = true;
                    next = false;
                } else;

                // up, out of range => to the right
                else if (!next) if (i <= 0 || marked[i - 1][j]) {
                    horisontal = true;
                    next = true;
                }
            }
            
            // next cell
            if (horisontal) {
                if (next) j++;
                else j--;
            } else {
                if (next) i++;
                else i--;
            }
        }
		return true;
	}
    void printRow(byte* row, short size) {
        std::cout << "Row: ";

        for (int i = 0; i < size; i++) {
            std::cout << (short) row[i] << " ";
        }
        std::cout << std::endl;
        return;
    }
	bool handleAnswer(short answer) {
	    short x = (short) matrixSize.x;
		short y = (short) matrixSize.y;
		byte* row = new byte[x * y];
        bool result = true;
        bool done = false;

		switch (answer) {
		case 1:
			done = copyOnRightDiagonals(row); 
            if (!done) result = false;
            // printRow(row, x * y);
			break;
		case 2:
			done = copyOnLeftDiagonals(row);
            if (!done) result = false;
            // printRow(row, x * y);
			break;
		case 3:
			done = copyInSpiral(row, false);
			if (!done) result = false;
            // printRow(row, x * y);
			break;
		case 4:
            done = copyInSpiral(row, true);
            if (!done) result = false;
            // printRow(row, x * y);
			break;
        case 5:
            createAndPrintRandomRows(10);
            result = false;
            break;
		}
		delete [] row;
		return result;
	}
	void renderMenu() {
		std::cout << "1. Копировать по правым диагоналям, начиная с правого верхнего эл-а" << std::endl;
		std::cout << "2. Копировать по левым диагонялаям, начиная с левого верхнего эл-а" << std::endl;
		std::cout << "3. Копировать по спирали, начиная с центрального эл-а" << std::endl;
		std::cout << "4. Копировать по спирали, начиная с левого эл-а" << std::endl;
		std::cout << "5. Создать и распечатать двумерный массив с произвольной длиной строк" << std::endl;
		std::cout << ":: Your answer: ";
		
        short answer;
		std::cin >> answer;
		std::cout << std::endl;
		bool result = handleAnswer(answer);
        
        if (result) std::cout << "Copied";
        else std::cout << "Not copied";

        std::cout << std::endl;
		return;
	}
    short getRandom(short from = 0, short to = 100) {
        short randomNumber;
        randomNumber = std::rand() % (to - from) + from;
        return randomNumber;
    }
    void createAndPrintRandomRows(short rowsNumber) {       
        byte** data = new byte*[rowsNumber];
        short dataMax = 2;
        short dataMin = 12;

        // alloc mem
        for (short i = 0; i < rowsNumber; i++) {
            short rowLength = getRandom(dataMin, dataMax);
            data[i] = new byte[rowLength];
            data[i][0] = rowLength;
        }

        // fill cells
        for (short i = 0; i < rowsNumber; i++) {
            for (short j = 1; j < data[i][0]; j++) {
                data[i][j] = getRandom(10, 99);
            }
        }

        // print cells
        for (short i = 0; i < rowsNumber; i++) {
            for (short j = 1; j < data[i][0]; j++) {
                std::cout << (short) data[i][j] << " ";
            }
            std::cout << "(" << (short) data[i][0] << ")";
            std::cout << std::endl;
        }

        // free mem
        for (short i = 0; i < rowsNumber; i++) delete [] data[i];
        delete [] data;
        std::cout << std::endl;
        return;
    }
public:
	void runApp() override {
		if (matrix == nullptr) createMatrix();
		if (!filled) fillMatrix();
		renderMenu();


		return;
	}
	bool createMatrix(byte n = 200, byte m = 200) {
		if (matrix != nullptr) return false;
		matrixSize = {n, m};
		matrix = new byte*[m];
		for (byte i = 0; i < n; i++) matrix[i] = new byte[n];
		return true;
	}
	bool deleteMatrix() {
		if (matrix == nullptr) return false;
		for (byte i = 0; i < matrixSize.y; i++) delete [] matrix[i];
	    delete [] matrix;
		matrix = nullptr;
		filled = false;
		return true;
	}
	bool fillMatrix() {
		if (matrix == nullptr) {
			std::cout << "You must create matrix before!" << std::endl;
			std::cout << "Use MatrixApp::createMatrix()" << std::endl;
			return false;
		}
		for (byte i = 0; i < matrixSize.x; i++) {
		}
		for (byte i = 0; i < matrixSize.x; i++) {
			for (byte j = 0; j < matrixSize.y; j++) {
				matrix[i][j] = std::rand() % (max - min) + min;
			}
		}
		filled = true;
		return true;
	}
	bool printMatrixData() {
		// matrix size
		std::cout << "size: " << (int) matrixSize.y;
	    std::cout << " x " << (int) matrixSize.x << std::endl;
		// is the matrix nullptr?
		std::cout << "nullptr: ";
		if (matrix == nullptr) std::cout << "yes";
		else std::cout << "no";
		std::cout << std::endl;
		// is some array of the matrix nullptr?
		// ..
		return true;
	}
	bool printMatrix() {
		if (matrix == nullptr) {
			std::cout << "You must create matrix before!" << std::endl;
			std::cout << "Use MatrixApp::createMatrix()" << std::endl;
			return false;
		}
		if (!filled) {
			std::cout << "You must fill matrix before!" << std::endl;
			std::cout << "Use MatrixApp::fillMatrix()" << std::endl;
			return false;
		}
		for (byte i = 0; i < matrixSize.y; i++) {
			for (byte j = 0; j < matrixSize.x; j++) {
				std::cout << (int) matrix[i][j] << " ";
			}
			for (byte j = 0; j < 1; j++) std::cout << std::endl;
			for (byte j = 0; j < matrixSize.x; j++) std::cout << "=== ";
			std::cout << std::endl;
		}
		return true;
	}
	void pauseApp() override {
		// do nothing on pause
		return;
	}
	MatrixApp(vec2 size) {
		createMatrix(size.x, size.y);
		return;
	}
	MatrixApp() {
		// do nothing by default
		return;
	}
	~MatrixApp() {
		if (matrix == nullptr) deleteMatrix();
		return;
	}
};

int main() {
	MatrixApp app;
	app.createMatrix(5, 5);
	app.fillMatrix();
	// app.printMatrixData();
	std::cout << "A matrix has been created just now!" << std::endl;
	// std::cout << std::endl;
	// app.printMatrix();
	std::cout << std::endl;
	app.runApp();
	app.deleteMatrix();
    return 0;
}
