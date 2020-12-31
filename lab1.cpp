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

private:
	byte** matrix = nullptr;
	vec2 matrixSize{0, 0};
	byte min = 100;
	byte max = 200;
	bool filled = false;

	void copyOnRightDiagonals(byte* row) {
		
		return;
	}
	void handleAnswer(short answer) {
		short x = (short) matrixSize.x;
		short y = (short) matrixSize.y;
		byte* row = new byte[x * y];
		
		switch (answer) {
		case 1:
			copyOnRightDiagonals(row);
			break;
		case 2:
			// copyOnLeftDiagonals(row);
			break;
		case 3:
			// copyInSpiralFromCenter(row);
			break;
		case 4:
			// copyInSpiralFromFirst(row);
			break;
		}
		delete [] row;
		return;
	}
	void renderMenu() {
		std::cout << "1. Копировать по правым диагоналям, начиная с правого верхнего эл-а" << std::endl;
		std::cout << "2. Копировать по левым диагонялаям, начиная с левого верхнего эл-а" << std::endl;
		std::cout << "3. Копировать по спирали, начиная с центрального эл-а" << std::endl;
		std::cout << "4. Копировать по спирали, начиная с левого эл-а" << std::endl;
		std::cout << ":: Your answer: ";
		short answer;
		std::cin >> answer;
		std::cout << std::endl;
		handleAnswer(answer);
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
		matrix = new byte*[n];
		for (byte i = 0; i < n; i++) matrix[i] = new byte[m];
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
			for (byte j = 0; j < matrixSize.y; j++) {
				matrix[i][j] = std::rand() % (max - min) + min;
			}
		}
		filled = true;
		return true;
	}
	bool printMatrixData() {
		// matrix size
		std::cout << "size: " << (int) matrixSize.x;
	       	std::cout << " x " << (int) matrixSize.y << std::endl;
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
		for (byte i = 0; i < matrixSize.x; i++) {
			for (byte j = 0; j < matrixSize.y; j++) {
				std::cout << (int) matrix[i][j] << " ";
			}
			for (byte j = 0; j < 1; j++) std::cout << std::endl;
			for (byte j = 0; j < matrixSize.y; j++) std::cout << "=== ";
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
	app.createMatrix(10, 10);
	app.fillMatrix();
	// app.printMatrixData();
	std::cout << "A matrix has been created just now!" << std::endl;
	std::cout << std::endl;
	app.printMatrix();
	std::cout << std::endl;
	app.runApp();
	app.deleteMatrix();
	return 0;
}
