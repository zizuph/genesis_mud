/*
   Wayreth tower base.

   tower_base.c
   -------------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : 16/08/27
   By ...........: Arman

*/

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <composite.h>

#define RESET  "reset_tower_room"

inherit WAYOUTROOM;

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_wayreth_room()
{
    call_other(TO, RESET);
}

void
create_tower_room() { }

void
create_wayreth_room()
{

    add_prop(ROOM_M_NO_TELEPORT, "Something prevents you " +
        "from teleporting.\n");
    add_prop(ROOM_M_NO_SCRY, "Powerful magical illusionary mists " +
        "frustrate your ability to scry your target.\n");

    create_tower_room();
}

void
expel_non_test_participant(object ob)
{

    tell_object(ob, "Mists suddenly form around you, and you find " +
        "yourself suddenly elsewhere.");
    tell_room(E(ob), "Mists form around " +QTNAME(ob) + ", and " +HE(ob)+ 
        " slowly fades away.\n", ({ ob }) );

    ob->move_living("M", "/d/Krynn/wayreth/tower/foretower", 1, 0);
    tell_room(E(ob), QCTNAME(ob)+ " suddenly appears before you!\n", 
        ({ ob }) );

    return;
}

void
check_test_participant(object ob)
{
    if((WOHS_MANAGER->query_started_wohs_test() != ob->query_real_name()) 
        && !ob->query_wiz_level())
    {
        DEBUG("Manager: " +WOHS_MANAGER->query_started_wohs_test()+ 
            ", name: " +ob->query_real_name());
        set_alarm(0.5, 0.0, &expel_non_test_participant(ob));
        return;
    }
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(!ob->query_humanoid())
    {
        return;
    }

    if(ob->query_npc())
    {
        return;
    }

    set_alarm(1.0, 0.0, &check_test_participant(ob));
}

public int
check_new_time(string str)
{

    if(environment(this_player())->query_prop(ROOM_I_INSIDE))
    {
        write("Being inside and cannot study the sky, you cannot " +
            "estimate the time precisely.\n");
        return 1;
    }

    write("For some reasons the celestials seem a bit strange to you " +
        "and you struggle to estimate the time. If you didn't know " +
        "better, you'd think they were positioned how they would have " +
        "been pre-Cataclysm!\n");
   return 1;
}


public void
init()
{
    ::init(); 
    add_action("check_new_time", "time"); 
}
