/*
   Diamond. Street SW#1.

   sw1.c
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
    add_my_desc("A bank is open to the southwest, with a sign " +
	"hanging in front of it. The street continues to the " +
	"southeast and to the northwest, where it leads to the " +
	"western corner of the city.\n");
    AI(({"bank","sw"}),
	"The bank lies to the southwest, and, contrary " +
	"to popular gnomish policies, this bank is open all " +
	"day _and_ all night, for who knows when these drunken " +
	"citizens might need cash for more drink.\n");
    AI("sign","The sign has a depiction of coins and diamonds " +
	"filling a safe upon it.\n");
        
    AE(DIROOM + "w1", "northwest", 0);
    AE(DIROOM + "bank", "southwest", 0);
    AE(DIROOM + "sw2", "southeast", 0);
}
