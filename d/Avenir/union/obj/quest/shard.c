/* One of the quest objects for the Union entrance quest
 * Cirion 050296
 */
inherit "/std/object";
#include <stdproperties.h>
#include "questob.h"

void create_object()
{
    set_name("shard");
    add_name(QUEST_OB_NAME);
    set_adj(({"black","obsidian","stone","sharp"}));
    set_short("long black shard");
    set_long("It is a long shard of jet black stone, "
      +"sharp and glimmering with a malicious gleam.\n");
    add_cmd_item("shard",({"feel", "touch"}),
      "It is sharp, and feels very hot.\n");

    add_prop(QUEST_OB, 1);

    add_prop(OBJ_I_VALUE, 4);
    add_prop(OBJ_I_WEIGHT, 11);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_M_NO_BUY, "@@remove@@");
}

mixed remove()
{
    set_alarm(0.1, 0.0, remove_object);
    return "What was that?\n";
}
