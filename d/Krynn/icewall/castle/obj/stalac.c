/* a stalactite that breaks apart to reveal a surprise */
/* created for Icewall by Stevenson */

#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
inherit "/std/object";

init() {
   ADD("kablooy","kick");
   ADD("kablooy","smash");
   ADD("kablooy","hit");
   ADD("kablooy","break");
   ::init();
}

create_object() {
   set_name(({"stalactite", "_stalactite_"}));
   set_short("stalactite");
   set_long("The stalactite is about 5 feet in diameter and juts "
      + "down from the ceiling to a height of 7 feet.\n");
   
   add_prop(OBJ_I_NO_GET,1);
   seteuid(getuid());
}

int kablooy(string arg) {
   NF("Do what?\n");
   if (arg == "stalactite" || arg == "the stalactite") {
      write("You somehow manage to hit the stalactite in its weak spot.\n");
      say(QCTNAME(TP)+" smashes the stalactite.\n");
      set_alarm(2.0,0.0,"smash");
      return 1;
   }
   return 0;
}

smash() {
   tell_room(E(TO),"The stalactite begins to quiver and crumbles into "
      + "a pile of dust.\n");
   (clone_object(ICE_CAST_O+"dust"))->move(E(TO));
   write("Something big hit you on the head.\n");
   (clone_object(ICE_CAST_O+"diamond"))->move(TP);
   TO->remove_object();
}
