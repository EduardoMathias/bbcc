#include "elem.h"

Nave inicializaNave(int x, int y){
	Nave NovaNave = {
		" /^\\ ", "MMMMM", x, y
	};
	return NovaNave;
}
Alien inicializaAlien1(int x,int y){
	Alien Alien1 = {
		" A ","AMA","/X\\", x, y, 1};
	return Alien1;
}
Alien inicializaAlien2(int x,int y){
	Alien Alien2 = {
	     ".v_v.","}WMW{"," / \\ ", x, y, 1};
       return Alien2;
}
Alien inicializaAlien3(int x, int y){
	Alien Alien3 = {
		" nmn ", "dbMdb", "_/-\\_", x, y, 1};
	return Alien3;
}
Barreira inicializaBarreira(int x, int y){
	Barreira NovaBarreira = {
		"M", x, y, 0
	};
	return NovaBarreira;
}

Missel inicializaMissel(int x, int y){
    Missel NovoMissel ={
        "|",x,y,0
    };
    return NovoMissel;
}

Missel inicializaMisselAlien(int x, int y){
    Missel NovoMisselAlien = {
        "$", x,y,0
    };
    return NovoMisselAlien;
}