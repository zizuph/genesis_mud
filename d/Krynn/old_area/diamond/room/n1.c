/*
   Diamond. Street N#1.

   n1.c
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
    add_my_desc("You are standing in the northern corner of Diamond " +
	"City. The road continues southwest or southeast into the " +
	"city, or north through the Northern Corridor.\n");

    AI(({"northern corridor","Northern Corridor","corridor","north"}),
	"This corridor is the northern entrance and exit of Diamond City.\n");
        
    AE(DIROOM + "n2", "north", 0);
    AE(DIROOM + "nw1", "southwest", 0);
    AE(DIROOM + "ne1", "southeast", 0);
}
