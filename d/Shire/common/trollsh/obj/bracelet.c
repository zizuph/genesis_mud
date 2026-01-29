inherit "/std/object";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"

create_object()
{
    set_name("bracelet");
    add_name("_gollin_bracelet_");
    set_pname("bracelets");
    set_pshort("old silver bracelets");
   set_adj(({"old","silver"}));
    set_long(
    "This is an old silver bracelet, tarnished by the humidity "+
   "of some dark dank place. "+
    "The size of the bracelet would indicate that it only fit a very "+
   "small creature.\n");

    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VALUE, 290);
}

void
init()
{
    ::init();
   add_action("do_rub","rub",0);
   add_action("do_rub","clean",0);
}
int
do_rub(string str)
{
   if (str != "bracelet")
   {
     write("Rub what?\n");
   return 0;
   }

write("You rub the bracelet and discover an engraving--the "+
   "letter G!\n");
     return 1;
}
