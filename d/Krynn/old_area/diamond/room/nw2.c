/*
   Diamond. Street NW#2.

   nw2.c
   -----------
   Coded ........: April 1997
   By ...........: Kentari
   
   Latest update : April 1997
   By........... : Kentari

*/

#include "../local.h"

inherit STREET;

public void
create_street()
{
    add_my_desc("A post office is open to the northwest, with a sign " +
	"hanging in front of it. The street continues to the " +
	"northeast and to the southwest, where it leads to the " +
	"western corner of the city.\n");
    AI(({"post","post office","po","nw"}),
	"The post office is where you can send mail to anyone " +
	"in the realms, free of charge no less!\n");
    AI("sign","The sign has a picture of an envelope in front a " +
        "map.\n");

    AE(DIROOM + "w1", "southwest", 0);
    AE(DIROOM + "mail", "northwest", 0);
    AE(DIROOM + "nw1", "northeast", 0);
}
