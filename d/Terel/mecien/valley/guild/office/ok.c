/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/key";

#include <macros.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO this_object()
#define TP this_player()

public void
init()
{
   ::init();
   add_action("back", "return");
}

public int
back(string str)
{
   object lib = find_living("herilnas");
   
   notify_fail("Return what?\n");
   if (!str || !id(str)) return 0;
   
   if (lib) {
       TO->move(lib);
       TP->catch_msg("The " + short() + " has returned to its keeper.\n");
   } else {
       TP->catch_msg("The " + short() + " cannot return at this time.\n");
   }
   return 1;
}

public void
create_key()
{
   ::create_key();

   set_adj("old");
   add_adj("silver");
   add_name("orator_key");

   set_long("An old silver key.\n");

   set_key(9832);
}
