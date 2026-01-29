/* One of the quest objects for the Union entrance quest
 * Cirion 050296
 */
inherit "/std/object";
#include <stdproperties.h>
#include "questob.h"

void create_object()
{
    set_name("stone");
    add_name(({"cube","rock"}));
    add_name(QUEST_OB_NAME);
    set_adj(({"small","heavy","rectangular"}));
    set_short("small green cube");
    set_long("It is a tiny cube made from a hard, "
      +"green gemstone. Long thin lines of dull "
      +"grey vein the sides.\n");

    add_prop(QUEST_OB, 5);
    add_prop(OBJ_I_VALUE, 192);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 66);
    add_prop(OBJ_M_NO_BUY, "@@remove@@");
}

mixed remove()
{
    set_alarm(0.1, 0.0, remove_object);
    return "What was that?\n";
}
