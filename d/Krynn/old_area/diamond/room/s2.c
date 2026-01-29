/*
   Diamond. Street S#2.

   s2.c
   -----------
   Coded ........: April 1997
   By ...........: Kentari
   
   Latest update : April 1997
   By........... : Kentari

*/

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit OUT_BASE;

public void
create_dim_room()
{
    set_short("Southern Corridor of Diamond City");
    set_long("");
    add_my_desc("You stand in the Southern Corridor of Diamond City. " +
	"The walls of the city loom above you, their sturdiness " +
	"a tribute to the builders. To the west are the city board " +
	"rooms, and to the east is the registration office. " +
	"South takes you outside the walls of Diamond City. " +
	"The city lies to the north, but you need to be registered " +
	"to enter. Remember: No violence will be tolerated within " +
	"the walls of Diamond City!\n"); 

    AI(({"southern corridor","Southern Corridor","corridor"}),
	"Yup, thats where you're standing!\n");
    AI(({"north","force","mystical force"}),
	"Though you can't tell what it is, something by the northern " +
	"exit makes the hairs on the back of your neck stand up.\n");
        
    AE(DIROOM + "board", "west", 0);
    AE(DIROOM + "s1", "north", 0);
    AE(DIROOM + "register", "east", 0);
    AE(DIROOM + "s3", "south", 0);
}  
