/* One of the quest objects for the Union entrance quest
 * Cirion 050296
 */
inherit "/std/object";
#include <stdproperties.h>
#include "questob.h"

void create_object()
{
    set_name("sliver");
    add_name(QUEST_OB_NAME);
    set_adj(({"long","dark"}));
    set_short("dark sliver of gemstone");
    set_long("It is a long sliver of some strange and "
      +"dark gemstone. It seems to emanate cold and "
      +"a sense of dread.\n");
    add_cmd_item("sliver",({"feel", "touch"}),
      "It is sharp, and feels quite cold.\n");

    add_prop(QUEST_OB, 2);
    add_prop(OBJ_I_VALUE, 94);
    add_prop(OBJ_I_WEIGHT, 11);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_M_NO_BUY, "@@remove@@");
}

mixed remove()
{
    set_alarm(0.1, 0.0, remove_object);
    return "What was that?\n";
}
