inherit "/std/receptacle";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
void
create_container()
{
   set_name("corpse");
   set_adj("smashed");
   set_adj("rotting");
   set_long("This is the corpse of what appears to be some hapless gnome who ran into a little bit of bad luck in this end of the caverns.  Judging by the extreme decay of his body you guess he's been here for months.\n");
   add_prop(OBJ_I_VALUE, 0);
   add_prop(CONT_I_WEIGHT, 22000);
   add_prop(CONT_I_VOLUME, 20000);
   add_prop(CONT_I_MAX_WEIGHT, 100000);
   add_prop(CONT_I_MAX_VOLUME, 100000);
   set_alarm(0.0,0.0,"get_axe");
}
get_axe() {
   object ob1;
   seteuid(getuid());
   return (clone_object("/d/Rhovanion/common/dungeon1/gear/b_axe.c"))
   ->move(TO);
}
