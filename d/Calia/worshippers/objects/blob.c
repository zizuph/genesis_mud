
 /* Smouldering corpse leftovers by Jaacar */

inherit "/std/food";
#include <stdproperties.h>
#include "defs.h"

string enemy_race = "unknown";

create_food()
{
    set_name("blob");
    add_name("remains");
    add_name("smouldering remains");
    set_short("smouldering remains");
    set_long("It is a smouldering pile of remains of @@query_race@@ origin.\n");
    set_amount(125);
}

query_race()
{
    return enemy_race;
}

set_race(string str)
{
    enemy_race = str;
}
