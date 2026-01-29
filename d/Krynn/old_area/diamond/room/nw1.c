/*
   Diamond. Street NW#1.

   nw1.c
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
    add_my_desc("A unique type of pub is open to the northwest, with " +
	"a sign hanging in front of it. The street continues to the " +
	"southwest and to the northeast, where it leads to the " +
	"northern corner of the city.\n");
    AI(({"pub","crystal clairvoyance pub","ccp","nw"}),
	"A unique type of pub, the Crystal Clairvoyance Pub serves " +
	"only non-alcoholic drinks for those who choose to keep " +
	"their thoughts clear and mind as sharp as possible.\n");
    AI("sign","The sign has a painting of a head with a twinkling " +
        "crystal within it.\n");

    AE(DIROOM + "nw2", "southwest", 0);
    AE(DIROOM + "pub", "northwest", 0);
    AE(DIROOM + "n1", "northeast", 0);
}
