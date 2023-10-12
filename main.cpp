#include "Network.h"
#include "define.h"

int main() {
	Network n("network_data.csv");
	n.saveFile("network_data2.csv");
	//n.loadFile();
	return 0;
}