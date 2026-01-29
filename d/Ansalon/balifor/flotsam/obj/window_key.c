/*
*    Key for treasure chest in quest in Flotsam
*/
#include "/d/Ansalon/balifor/flotsam/local.h"
inherit "/std/key";
inherit "/lib/keep";

void
create_key() 
{
   ::create_key();
   set_name("wire");
   set_short("hooked piece of wire");
   set_pshort("hooked pieces of wire");
   set_adj("hooked");
   add_adj("piece of");
   set_long("This strange piece of wire is long and " +
      "hooked at one end. You wonder what it could be " +
      "used for?\n");
   
   set_key(BOGUS_KEY);
}
