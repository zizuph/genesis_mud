/*
   Diamond. Street NE#2.

   ne2.c
   -----------
   Coded ........: April 1997
   By ...........: Kentari
   
   Latest update : April 1997
   By .......... : Kentari

*/

#include "../local.h"

inherit STREET;

public void
create_street()
{
    add_my_desc("A party hall lies to the northeast, with " +
	"a sign hanging in front of it. The street continues to the " +
	"northwest and to the southeast, where it leads to the " +
	"eastern corner of the city.\n");
    AI(({"party hall","hall","party","ne"}),
	"This decorated party hall is where people can come to throw " +
	"a party for whatever purpose they wish, for a cost of course.\n"); 
    AI("sign","The sign is full of balloons and confetti, with " +
	"streamers hanging off of it.\n");

    AE(DIROOM + "e1", "southeast", 0);
    AE(DIROOM + "pubparty", "northeast", 0);
    AE(DIROOM + "ne1", "northwest", 0);
}
