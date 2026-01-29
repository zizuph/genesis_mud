/* Created By Stevenson */
/* The Ball you give to Puppy */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
inherit "/std/object";
#include "/sys/stdproperties.h"

init() {
   ADA("bounce");
   ::init();
}

int bounce(string str) {
   if (str != "ball") {
      NF("Bounce what?\n");
      return 0;
   }
   write("You try to bounce the ball but end up "
      + "chasing it as it rolls away.\n");
   say(QCTNAME(TP)+" drops a ball and chases it as it rolls "
      + "away.\n");
   return 1;
}

create_object() {
   set_name("ball");
   set_short("red ball");
   set_long("You see a very chewed on, slobbered on, "
      + "not so bouncy ball.\n");
   set_adj("red");
   add_name("puppy_ball");
   
   add_prop(OBJ_I_VOLUME, 100);
   add_prop(OBJ_I_WEIGHT, 75);
}
/* how do I differentiate this from any ball */
   
