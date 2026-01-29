/*
 * The remains of the player after they betray the Elementals.
 *
 * Copied from old worshippers guild.
 *
 * Modified by Petros, April 2014
 */

#include <stdproperties.h>
#include "defs.h"

inherit "/std/food";

public string enemy_race = "unknown";

public void
create_food()
{
    set_name("blob");
    add_name("remains");
    add_name("smouldering remains");
    set_short("smouldering remains");
    set_long("It is a smouldering pile of remains of @@query_race@@ origin.\n");
    set_amount(125);
}

public string
query_race()
{
    return enemy_race;
}

public void
set_race(string str)
{
    enemy_race = str;
}
