#include "calculator.h"
bool success = true;
int main() {
	success = RunCalculatorCycle();
	success ? return 0 : return 1;
}
