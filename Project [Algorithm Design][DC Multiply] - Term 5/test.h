// Program Test:

cout << "\n " << "1100 + 1010 = " << addString("1100","1010");
cout << "\n " << "1100 - 1010 = " << subString("1100","1010");
cout << "\n " << "0000 - 0000 = " << subString("0000","0000");
cout << "\n " << "1100 * 1010 = " << multiply("1100","1010");
cout << "\n " << "0011 * 1110 = " << multiply("0011","1110");
cout << "\n " << "1111 * 1111 = " << multiply("1111","1111");

cout << "\n " << "SHL<1101,3> = " << shlString("1101",3);

cout << "\n " << "ISBINARY<4> = " << isBinary("4");
cout << "\n " << "ISDECIMAL<124> = " << isDecimal("124");
cout << "\n " << "ISDECIMAL<12G4> = " << isDecimal("12G4");

cout << "\n " << "NORMALIZE<000010111010> = " << normalizeBinary("000010111010");
cout << "\n " << "NORMALIZE<00000> = " << normalizeBinary("00000");
cout << "\n " << "NORMALIZE<0> = " << normalizeBinary("0");
cout << "\n " << "NORMALIZE<1> = " << normalizeBinary("1");
cout << "\n " << "NORMALIZE<NULL> = " << normalizeBinary("");

cout << "\n " << "POWER2BIN<5> = " << power2bin_first(5);
cout << "\n " << "POWER2BIN<5> = " << power2bin_second(5);
cout << "\n " << "POWER2BIN<-8> = " << power2bin_first(-8);


cout << "\n " << "DECIMAL2BIN<12> = " << decimal2bin("12");
cout << "\n " << "DECIMAL2BIN<20> = " << decimal2bin("20");
