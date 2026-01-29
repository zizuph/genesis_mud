/*
   Diamond. Street W#1.

   w1.c
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
    add_my_desc("You are standing in the western corner of Diamond " +
	"City. The road continues northeast or southeast into the " +
	"city, or west through the Western Corridor.\n");

    AI(({"western corridor","Western Corridor","corridor","west"}),
	"This corridor is the western entrance and exit of Diamond City.\n");
        
    AE(DIROOM + "w2", "west", 0);
    AE(DIROOM + "nw2", "northeast", 0);
    AE(DIROOM + "sw2", "southeast", 0);
}
