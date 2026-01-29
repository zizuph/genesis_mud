/* Stralle @ Genesis 010605
 *
 * The council position "leader"
 */

#pragma strict_types

inherit "/std/object";

inherit "/d/Ansalon/guild/new_pot/lib/council/high_priest_promotion";
inherit "/d/Ansalon/guild/new_pot/lib/council/council";
inherit "/d/Ansalon/guild/new_pot/lib/council/punishment";
inherit "/d/Ansalon/guild/new_pot/lib/council/initiation";
inherit "/d/Ansalon/guild/new_pot/lib/council/training";
inherit "/d/Ansalon/guild/new_pot/lib/council/spells";
inherit "/d/Ansalon/guild/new_pot/lib/council/honourifics";
inherit "/d/Ansalon/guild/new_pot/lib/council/absence";
inherit "/d/Ansalon/guild/new_pot/lib/council/delegate";
inherit "/d/Ansalon/guild/new_pot/lib/council/enemies";

#include "../../guild.h"
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("leader_council_object");
    set_long("This is not supposed to be seen. In the unlikely event " +
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
    return query_high_priest_promotion_commands() +
           query_council_commands() +
           query_punishment_commands() +
           query_initiation_commands() +
           query_training_commands() +
           query_spells_commands() +
           query_honourifics_commands() +
           query_enemies_commands() +
           query_absence_commands() +
           query_delegate_commands();
}

void
add_leader_commands()
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
    
    add_leader_commands();
}
