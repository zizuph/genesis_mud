/*
 * pimp.c
 *
 * Used in nyreese/red_bordell.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include "/d/Genesis/homes/relation.h"

string *ss;

void
create_monster()
{
    set_name("baihurk");
    set_living_name("baihurk");
    set_race_name("goblin");
    add_name("goblin");
    add_name("pimp");
    set_long("He is dressed in rather fancy clothes.\n");

    default_config_npc(35);
    ss = ({});
}

int
query_knight_prestige()
{
    return 112;
}

/* Is this used for anything? FIXA
void
make_a_note(object o)
{
    object a;

    if (QUERY_HAS_RELATION_OF_TYPE(ob->query_real_name(), "marriage"))
    {
        restore_object(ROKEDIR + "log/pimp");
        if (member_array(o->query_real_name(), ss) < 0)
        {
            ss += ({o->query_real_name()});
            save_object(ROKEDIR + "log/pimp");
        }
    }
}
*/
