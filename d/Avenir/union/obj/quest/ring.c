/* One of the quest objects for the Union entrance quest
 * Cirion 050296
 */
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include "questob.h"

void create_armour()
{
    set_name("ring");
    add_name(QUEST_OB_NAME);
    set_adj(({"dull","obsidian"}));
    set_short("dull obsidian ring");
    set_long("It is a small and heavy ring, made for a "
      +"slender finger.\n");

    add_prop(QUEST_OB, 6);
    add_prop(OBJ_I_VALUE, 12);
    add_prop(OBJ_I_WEIGHT, 96);
    add_prop(OBJ_I_VOLUME, 66);
    add_prop(OBJ_M_NO_BUY, "@@remove_this@@");

    set_default_armour(2, A_R_FINGER);
}

mixed remove_this()
{
    set_alarm(0.1, 0.0, remove_object);
    return "What was that?\n";
}
