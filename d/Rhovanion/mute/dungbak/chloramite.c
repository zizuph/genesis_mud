inherit "/std/object";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>
void
create_object() {
   set_name("stone");
   set_adj("crusted");
   set_adj("dirty");
   set_long("This is an odd stone indeed, especially considering " +
      "it was cut out from the stomach of a giant, constrictor " +
      "snake.  It is crusted over with all manner of filth and " +
      "goo.  It could use some cleaning.\n");
   add_prop(OBJ_I_VALUE, 1);
   add_prop(OBJ_I_WEIGHT, 600);
   add_prop(OBJ_I_VOLUME, 350);
}
void
init()
{
   ::init();
   add_action("part_clean","clean");
}
int
part_clean(string str) {
   notify_fail("Clean what?\n");
   if (!str)
      return 0;
   if (str !="stone")
      return 0;
   {
      write("You clean the stone up the best you can.\n");
      say(QCTNAME(this_player()) + " cleans a stone.\n");
      this_object()->remove_adj("crusted");
      this_object()->remove_adj("dirty");
      this_object()->set_adj("spotted");
      this_object()->set_adj("black");
      this_object()->set_long("This uncommon stone is a " +
         "White Chloramite.  It is embedded with small round nodules of " +
         "black stone giving it a unique appearance.  If it were " +
         "cut it might be worth quite a bit of money to a collector.\n");
      this_object()->add_prop(OBJ_I_VALUE, 1500);
      return 1;
   }
}
