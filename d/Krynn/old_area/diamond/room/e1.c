/*
   Diamond. Street E#1.

   e1.c
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
    add_my_desc("You are standing in the eastern corner of Diamond " +
	"City. The road continues northwest or southwest into the " +
	"city, or east through the Eastern Corridor.\n");

    AI(({"eastern corridor","Eastern Corridor","corridor","east"}),
	"This corridor is the eastern entrance and exit of Diamond City.\n");
        
    AE(DIROOM + "e2", "east", 0);
    AE(DIROOM + "ne2", "northwest", 0);
    AE(DIROOM + "se1", "southwest", 0);
}
