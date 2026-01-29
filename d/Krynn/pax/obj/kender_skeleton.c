/*
   kender_skeleton.c
   -----------------

   Coded ........: 95/05/09
   By ...........: Jeremiah

   Latest update : 95/05/09
   By ...........: Jeremiah

   Kender skeleton, with the Gem -- used to open the entrance to Sla mori.

*/

inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

int gem_found = 0;  /* 0 = gem NOT found yet */

void
create_object()
{
   set_name(({"skeleton", "kender skeleton"}));
   set_short("small skeleton");
   set_long("@@long_descr");

   add_adj("small");

   add_item("hair", "What is left of the hair on the skeleton, is still " +
            "arranged in a topknot.\n");

   add_item(({"pouch", "pouches", "bag", "bags"}), "These are all more " +
            " or less rotted away, probably cause of the moist air " +
            " down here. They are all empty.\n");

   add_item("hand", "@@hand_descr");
   
   add_prop(OBJ_I_NO_GET, 1);
   add_prop(OBJ_I_NO_GIVE, 1);

   seteuid(getuid(TO));
}


string
long_descr()
{
   string ret_str =  "This is a small skeleton. It looks like the " +
                     "skeleton of a child. A few half rotted pouches " +
                     "and bags are hanging at the skeleton. Some of " +
                     "the hair is still there, arranged in a topknot. " +
                     "You realize, that this must be a kender skeleton.";

   if(!gem_found)
      ret_str += " One of the small skeletal hands seems to be clutching " +
                 "something.";

   ret_str += "\n";

   return ret_str;
}


string
hand_descr()
{
   if(gem_found)
      return "There's is nothing special about it. It is just " +
              "a small skeletal hand.\n";

   gem_found = 1;
   tell_room(E(TO), QCTNAME(TP) + " opens the small skeletal hand " +
             "of the skeleton, and retrieves a small green gem.\n", TP);
   clone_object(POBJ + "gem")->move(TP);
   return "You open the small skeletal hand, and find a small green " +
          "gem. You gently take the gem from the skeletal hand.\n";
}
