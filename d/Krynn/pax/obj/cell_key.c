/*
   prison_key.c
   ------------

   Coded ........: 95/05/21
   By ...........: Jeremiah

   Latest update : 95/05/21
   By ...........: Jeremiah

   Key for the prison cell on the ground of Pax Tharkas.

*/


inherit "/std/key";
#include "/d/Krynn/pax/local.h"

create_key() 
{
   ::create_key();
   set_name("key");
   set_short("key");
   set_adj("slender");
   set_long("This is a slender iron key. It looks solid, " +
            "but it's terribly filthy.\n");
   
   set_key(CELL_KEY);
}
