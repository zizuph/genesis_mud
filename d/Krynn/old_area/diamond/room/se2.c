/*
   Diamond. Street SE#2.

   se2.c
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
    add_my_desc("A supply store is open to the southeast, with a sign " +
	"hanging in front of it. The street continues to the " +
	"northeast and to the southwest, where it leads to the " +
	"southern corner of the city.\n");
    AI(({"supply store","store","supply","se"}),
	"This is a place where you can buy containers to hold your " +
	"various drinks and other miscallaneous items.\n");
    AI("sign","This sign depicts someone with one leg up on a keg and " +
	"grinning while drinking double-fisted, that is with a bottle " +
	"in each hand.\n");
        
    AE(DIROOM + "se1", "northeast", 0);
    AE(DIROOM + "shop", "southeast", 0);
    AE(DIROOM + "s1", "southwest", 0);
}
