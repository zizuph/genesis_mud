/*
   Diamond. Street NE#1.

   ne1.c
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
    add_my_desc("A public tavern opens to the northeast, with " +
	"a sign hanging in front of it. The street continues to the " +
	"southeast and to the northwest, where it leads to the " +
	"northern corner of the city.\n");
    AI(({"tavern","golden keg tavern","ggt","ne"}),
	"The main tavern for Diamond City, the Golden Keg serves all " +
	"types of drink for the common traveller. Though the food " +
	"selection is minimal and not very good, most people don't " +
	"come for their appetite, but rather their thirst.\n");
    AI("sign","The sign depicts a golden keg held on the shoulders of " +
	"a strong man.\n");

    AE(DIROOM + "ne2", "southeast", 0);
    AE(DIROOM + "tavern", "northeast", 0);
    AE(DIROOM + "n1", "northwest", 0);
}
