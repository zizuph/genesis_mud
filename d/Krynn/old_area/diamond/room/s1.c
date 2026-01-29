/*
   Diamond. Street S#1.

   s1.c
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
    add_my_desc("You are standing in the southern corner of Diamond " +
	"City. The road continues northwest and northeast into the " +
	"city, north across the bridge to the keep of the Diamond " +
	"Drunkards Club, or south through the Southern Corridor.\n");

    AI(({"bridge","north"}),
	"The bridge spans the Crystal Waters Tributary and leads to " +
	"the entrance of the keep. Along the bridge are intricately " +
	"crafted railings of a silvery metal.\n");
    AI(({"railings","metal","intricate railings"}),
	"Though you can't make out the metal of which it was made, " +
	"the craftsmanship of the patterns is exquisite.\n");
    AI(({"southern corridor","Southern Corridor","corridor","south"}),
	"This corridor is the southern entrance and exit of " +
	"Diamond City, and also is the path to the Board rooms " +
	"and Registration office.\n");
        
    AE(DIROOM + "sw2", "northwest", 0);
    AE(DIROOM + "entrance", "north", 0);
    AE(DIROOM + "se2", "northeast", 0);
    AE(DIROOM + "s2", "south", 0);
}  
