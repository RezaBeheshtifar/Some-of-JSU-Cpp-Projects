familyTree FT;

FT.birth("ali","","",'M',{""},1);
FT.birth("zahra","","",'F',{""},2);
FT.marriage("ali","zahra",{""});
FT.birth("mehdi","ali","zahra",'M',{""},3);
FT.birth("roya","","",'F',{""},4);
FT.marriage("ali","roya",{""});
FT.birth("maryam","ali","zahra",'F',{""},5);
FT.birth("yas","ali","roya",'M',{""},6);
FT.death("ali",{""});
FT.birth("ebi","","",'M',{""},7);
FT.marriage("ebi","roya",{""});
FT.birth("sara","ebi","roya",'F',{""},8);
FT.marriage("mehdi","sara",{""});

FT.birth("elyas","mehdi","sara",'M',{""},9);

return FT;
