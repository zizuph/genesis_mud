/*
   Diamond. Street SW#2.

   sw2.c
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
    add_my_desc("A collection store is open to the southwest, with a sign " +
	"hanging in front of it. The street continues to the " +
	"northwest and to the southeast, where it leads to the " +
	"southern corner of the city.\n");
    AI(({"collection store","store","sw"}),
	"A place for travellers to sell their goods, this store buys " +
	"weapons and armours. It does not sell anything, as this is a " +
	"peacful city and doesn't wish to promote violence here.\n");
    AI("sign","This sign shows an adventurer with no clothes on, " +
	"but with a handful of coins and a smile.\n");
        
    AE(DIROOM + "sw1", "northwest", 0);
    AE(DIROOM + "collect", "southwest", 0);
    AE(DIROOM + "s1", "southeast", 0);
}
