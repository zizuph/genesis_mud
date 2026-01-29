/*
   prison_key.c
   ------------

   Coded ........: 95/05/04
   By ...........: Jeremiah

   Latest update : 95/05/04
   By ...........: Jeremiah

   Key for the prison cells in the lower parts of Pax Tharkas.

*/


inherit "/std/key";
#include "/d/Krynn/pax/local.h"

create_key() 
{
   ::create_key();
   set_name("key");
   set_short("iron key");
   set_adj("iron");
   set_long("This is a rather large iron key. It looks solid, " +
            "ordinary and well used.\n");
   
   set_key(PRISON_KEY);
}
