// Signed int to char[]

int charToInt(char c) {
	switch (c) {
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	default:
		return -1;
	}
}

void intToStr(char *buffer, int num) {
	int negative = 0;
	if (num < 0) {negative = 1; num *= -1;}

	int rem = 1;
	int length = 0;
	if (num < 10) {
		rem = 10;
	} else {
		int testLen = num;
		while (testLen != 0) {
			testLen /= 10;
			rem *= 10;
			length++;
		}
	}

	// TODO: "length" to be used for
	// perfect char[] size

	int resultC = 0;
	if (negative) {
		resultC++;
		buffer[0] = '-';
	}

	while (rem != 1) {
		buffer[resultC] = (num % rem / (rem / 10)) + '0';
		rem /= 10;
		resultC++;
	}

	buffer[resultC] = '\0';
}

int strToInt(char *string, int *error, int length) {
	*error = 0;
	int c = 0;
	int negative = 0;
	if (string[0] == '-') {
		negative = 1;
		c++;
	}

	int result = 0;
	while (c < length) {
		result *= 10;
		int tryInt = charToInt(string[c]);
		if (tryInt == -1) {
			*error = -1;
			result += 0;
		} else {
			result += tryInt;
		}

		c++;
	}

	if (negative) {
		result *= -1;
	}

	return result;
}
