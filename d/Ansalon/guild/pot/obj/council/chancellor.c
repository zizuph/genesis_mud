/* Stralle @ Genesis 010605
 *
 * The council position "chancellor"
 *
 * Revisions:
 *   Lucius, Sep 2016: Renamed "herbmanager" to "chancellor"
 *
 */
#pragma strict_types

inherit "/std/object";

inherit "/d/Ansalon/guild/pot/lib/council/honourifics";
inherit "/d/Ansalon/guild/pot/lib/council/herbaccess";
inherit "/d/Ansalon/guild/pot/lib/council/enemies";
inherit "/d/Ansalon/guild/pot/lib/council/absence";
inherit "/d/Ansalon/guild/pot/lib/council/delegate";

#include "../../guild.h"
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("chancellor_council_object");
    set_long("This is not supposed to be seen. In the unlikely event " +
        "that  you do, please pretend that you did not.\n");
    
    set_no_show();
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
}

mapping
query_cmdlist()
{
    return query_honourifics_commands() +
           query_herbaccess_commands() +
           query_enemies_commands() +
           query_absence_commands() +
           query_delegate_commands();
}

void
add_chancellor_commands()
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
    
    add_chancellor_commands();
}
