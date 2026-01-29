/* One of the quest objects for the Union entrance quest
 * Cirion 050296
 */
inherit "/std/object";
#include <stdproperties.h>
#include "questob.h"

void create_object()
{
    set_name("ashes");
    add_name(({"pile","handful","ash"}));
    add_name(QUEST_OB_NAME);
    set_adj(({"blue","powdery"}));
    set_short("small handful of bluish ashes");
    set_long("It is pile of light blue ashes, very fine and "
      +"soft. They almost feels warm.\n");

    add_prop(QUEST_OB, 4);
    add_prop(OBJ_I_VALUE, 2);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 2);
    add_prop(OBJ_M_NO_BUY, "@@remove@@");
}

mixed remove()
{
    set_alarm(0.1, 0.0, remove_object);
    return "What was that?\n";
}
