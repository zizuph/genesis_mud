inherit "/std/object";
#include "/d/Rhovanion/defs.h"
void
create_object() {
   set_name("rag");
   set_adj("cloth");
   set_adj("old");
   set_long("This is an old cleaning rag.  You " +
      "could probably still use it to clean things!\n");
   add_prop(OBJ_I_VALUE, 1);
   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 200);
}
void
init()
{
   ::init();
   add_action("part_clean","clean");
}
int
part_clean(object obj) {
   notify_fail("Clean what?\n");
   if (!obj)
      return 0;
   if(present(obj, TP))
      {
      write("You clean up the " + obj + " with your old " +
         "cloth rag.\n");
      say(QCTNAME(TP) + " cleans up the " + obj + " with " +
         "the old cloth rag.\n");
      return 1;
   }
   write("Clean what?\n");
   return 1;
}
