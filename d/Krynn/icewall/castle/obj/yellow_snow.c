/* Yellow snow created by Stevenson */

inherit "/std/food";
#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
inherit PLAINS_O+"icy_objects_base";

object poison;

create_food()
{
   set_name("snow");
   add_name("pee");
   add_name("patch");
   set_short("patch of yellow snow");
   set_adj("yellow");
   set_long("You see some yellow snow. Are you sure you should eat it?\n");
   set_amount(5);
   make_me_meltable();
}

consume_text(object * arr, string vb) {
   write("Your intestines tell you that you've just made a mistake!\n");
   say(QCTNAME(TP)+" eats some yellow snow and looks "
      + "suddenly ill.\n");
   
   
   seteuid(getuid());
   poison = clone_object(ICE_CAST_O+"snow_poison");
   poison->move(TP);
   poison->start_poison();
}
