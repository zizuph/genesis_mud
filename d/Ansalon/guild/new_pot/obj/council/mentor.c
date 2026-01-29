/* Stralle @ Genesis 010605
 *
 * The council position "mentor"
 */

#pragma strict_types

inherit "/std/object";

inherit "/d/Ansalon/guild/new_pot/lib/council/pilgrimhood";
inherit "/d/Ansalon/guild/new_pot/lib/council/cleric_promotion";
inherit "/d/Ansalon/guild/new_pot/lib/council/training";
inherit "/d/Ansalon/guild/new_pot/lib/council/absence";
inherit "/d/Ansalon/guild/new_pot/lib/council/delegate";
inherit "/d/Ansalon/guild/new_pot/lib/council/enemies";

#include "../../guild.h"
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("mentor_council_object");
    set_long("This is not suppose to be seen. In the unlikely event " +
        "that you do, please pretend that you did not.\n");
    
    set_no_show();
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
}

mapping
query_cmdlist()
{
    return query_pilgrimhood_commands() +
           query_cleric_promotion_commands() +
           query_training_commands() +
           query_absence_commands() +
           query_enemies_commands() +
           query_delegate_commands();
}

void
add_mentor_commands()
{
    mapping smap = query_cmdlist();
    string *arr = m_indices(smap);
    int x = -1, size = sizeof(arr);
    
    while (++x < size)
        add_action(smap[arr[x]], arr[x]);
}

void
init()
{
    ::init();
    
    add_mentor_commands();
}
