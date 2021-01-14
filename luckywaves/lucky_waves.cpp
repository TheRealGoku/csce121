#include <iostream>

using std::cin; 
using std::cout; 
using std::endl;

int main()
{
	int length_of_sequence=0;
	cout << "Enter sequence length: " << endl;
	cin >> length_of_sequence;

	int length_of_longest_lucky_waves=1; //Record the length of the longest lucky waves in the sequence read so far.
	int length_of_the_latest_lucky_wave=1; //Record the length of the lucky wave closest to the end of the sequence read so far.
	
	/*TODO:Read a number from the input sequence and update the above two
	variables. Repeat this until all numbers are read.
	Write your code below this line.**/
	int current;
	cin >> current;
	int last = current;
	int cnt = 1;
	for (int i = 0; i < length_of_sequence; i++) {
		if (current > last) {
			cnt++;
			if (cnt > length_of_longest_lucky_waves) {
				length_of_longest_lucky_waves = cnt;
			}
		}
		else {
			if (cnt > length_of_longest_lucky_waves) {
				length_of_longest_lucky_waves = cnt;
			}
			cnt = 1;
		}
		if (i + 1 != length_of_sequence) {
			last = current;
			cin >> current;
		}	
	}


	cout<<length_of_longest_lucky_waves<<endl; //Output the length of the longest lucky waves.
	return 0;
}
