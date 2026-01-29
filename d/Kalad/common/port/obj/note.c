inherit "/std/scroll";
#include "/d/Kalad/defs.h"
#include <stdproperties.h>
/* by Antharanos */
void
create_scroll()
{
    set_name("note");
    add_name("bloody_quest_note");
    set_adj("bloody");
    set_long("A small note covered with drops of blood. There is writing "+
      "on it.\n");

    add_prop(OBJ_I_VALUE,1);
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 40);

    set_file("/d/Kalad/common/port/obj/note");
}
