/* One of the quest objects for the Union entrance quest
 * Cirion 050296
 */
inherit "/std/object";
#include <stdproperties.h>
#include "questob.h"

void create_object()
{
    set_name("ball");
    add_name(QUEST_OB_NAME);
    set_adj(({"sphere","round", "tiny", "blue"}));
    set_short("tiny blue ball");
    set_long("A tiny ball of dark blue stone.\n");
    add_cmd_item("ball",({"feel", "touch"}),
      "It is round and smooth.\n");

    add_prop(QUEST_OB, 3);
    add_prop(OBJ_I_VALUE, 14);
    add_prop(OBJ_I_WEIGHT, 11);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_M_NO_BUY, "@@remove@@");
}

mixed remove()
{
    set_alarm(0.1, 0.0, remove_object);
    return "What was that?\n";
}
