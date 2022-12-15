const int REQUIRED_BITS = 20;

void formattedNumToBinary(long long x){
    const char separator    = ' ';
    const int numWidth      = 4;
    const int tableWidth = (REQUIRED_BITS + 1) * (numWidth + 1);

    for(int i = 0; i < tableWidth; i++)
        cerr << '_';
    cerr << endl;

    cerr << right << setw(numWidth + 1) << '|';
    for(int i = REQUIRED_BITS - 1; i >= 0; i--){
        cerr << right << setw(numWidth) << setfill(separator) << i << '|';
    }
    cerr << endl;

    for(int i = 0; i < tableWidth; i++)
        cerr << '-';
    cerr << endl;

    cerr << left << setw(numWidth) << setfill(separator) << x << '|';
    for(int i = REQUIRED_BITS - 1; i >= 0; i--){
        cerr << right << setw(numWidth) << setfill(separator);
        if((x & (1ll << i)))
            cerr << 1;
        else
            cerr << 0;
        cerr << '|';
    }
    cerr << endl;

    for(int i = 0; i < tableWidth; i++)
        cerr << '-';
    cerr << endl;
}

#ifndef BeruboIV
    #define formattedNumToBinary(x) 42;
#endif