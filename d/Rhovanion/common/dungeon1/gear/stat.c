inherit "/std/object";
#include "/d/Rhovanion/defs.h"
void
create_object() {
   set_name("statuette");
   set_adj("wooden");
   set_adj("silver-enlaid");
   set_long("This is a small statuette approximately one foot tall " +
      "made out of a wood so well sanded and stained with such a " +
      "deep, rich " +
      "dark color as to make the variety unrecognizable.  For all you know " +
      "it could be made out of pine.  The statue itself is a carving of " +
      "a man in flowing garb strumming some sort of stringed instrument.  " +
      "The accoutrements of the man are set with silver as is the " +
      "instrument he plays.  This is probably worth something.\n");
   add_prop(OBJ_I_VALUE, 1000);
   add_prop(OBJ_I_WEIGHT, 900);
   add_prop(OBJ_I_VOLUME, 1100);
}
