/* Created By Stevenson */
/* Magnifying Lens used to melt the ice block holding dragon */
   inherit "/std/object";
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <stdproperties.h>
#include <macros.h>

inherit PLAINS_O + "icy_objects_base";
create_object() {
   set_name("lens");
   add_name("mag_lens");
   set_short("magnifying lens");
   set_adj("mangifying");
   set_long("You see a magnifying lens which could be useful for "
	+ "focusing light or for peeking through. " +
	"At first you assumed the lens was made of glass, but " +
	"now that you look closely you realize it's made of ice!\n");
   
   add_prop(OBJ_I_VOLUME, 75);
   add_prop(OBJ_I_WEIGHT, 50);
   add_prop(OBJ_I_VALUE, 20);
	make_me_meltable();
}

init() {
   ::init();
   ADA("peek");
}

int peek(string str) {
   if ((str=="lens")||(str=="through lens")) {
      write("Everything seems much bigger.\n");
      say(QCTNAME(TP)+ " holds a strange piece of glass up to "
         + TP->query_possessive() + " face and makes "
         + TP->query_possessive() + " eye grow larger.\n");
      return 1;
   }
   NF("what?");
   return 0;
}
