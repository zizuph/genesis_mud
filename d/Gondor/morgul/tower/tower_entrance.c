/*
 * The entrance to the Tower of Minas Morgul
 *
 * Created: Olorin, 10-jan-1994
 *
 */
#pragma strict_types

inherit "/d/Gondor/morgul/tower/tower.c";

#include <filter_funs.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"

#define ENTERING_TOWER 0
#define LEAVING_TOWER  1

public void    reset_room();

static object  Mage;

void
create_morgul_tower_room()
{
    set_extra_long("The darkness is so deep that your light source hardly " +
        "illuminates the walls of the hall. To the southwest the hall " +
        "continues into the tower. ");

    set_room_type("wide hall");
    set_level(0);

    add_exit(MORGUL_DIR + "city/mmr3", "northeast", 0, 1, 1);
    add_exit(TOWER_DIR  + "guard_0se", "southeast", 0, 1);
    add_exit(TOWER_DIR  + "tower_0ne", "southwest", 0, 1);
    add_exit(TOWER_DIR  + "guard_0nw", "northwest", 0, 1);

    add_walls();
    add_roof();
    add_floor();
    add_item(({"hall","passage"}), BSN(
        "This wide hall seems to be the entrance hall of the Tower. " +
        "To the northeast is the outer gate, and the hall continues to " +
        "the southwest into the Tower."));

    clone_object(TOWER_DIR + "doors/outergate_in")->move(TO);

    (TOWER_DIR + "guard_0se")->load_me();
    (TOWER_DIR + "guard_0nw")->load_me();

    add_prop(ROOM_I_NO_CLEANUP, 1); // To prevent gate relocking

    reset_room();
}

void
enter_inv(object ob, object from)
{
    object *mage;
    string  msg;

    ::enter_inv(ob, from);

    if (!objectp(ob) || !living(ob) || !objectp(from))
        return;

    if (file_name(from) != (MORGUL_DIR + "city/mmr3"))
        return;

    if (IS_MORGUL_MAGE(ob) || ob->query_wiz_level())
        return;

    mage = FILTER_LIVE(all_inventory(find_object(TOWER_DIR + "guard_0se")));
    if (sizeof(mage))
    {
        mage->give_alarm(ob, ENTERING_TOWER);
        msg = "from the room to the left";
    }

    mage = FILTER_LIVE(all_inventory(find_object(TOWER_DIR + "guard_0nw")));
    {
        mage->give_alarm(ob, ENTERING_TOWER);
        if (strlen(msg))
            msg += " and ";
        else
            msg += "";
        msg += "from the room to the right";
    }

    set_alarm(0.5, 0.0, &ob->catch_msg("You feel the watchful eyes of someone "
      + msg+".\n"));
}

void
leave_inv(object ob, object to)
{
    object *mage;

    ::leave_inv(ob, to);

    if (!objectp(ob) || !living(ob) || !objectp(to))
        return;

    if (file_name(to) != (MORGUL_DIR + "city/mmr3"))
        return;

    if (IS_MORGUL_MAGE(ob) || ob->query_wiz_level())
        return;

    mage = FILTER_LIVE(all_inventory(find_object(TOWER_DIR + "guard_0se")));
    if (sizeof(mage))
        mage->give_alarm(ob, LEAVING_TOWER);

    mage = FILTER_LIVE(all_inventory(find_object(TOWER_DIR + "guard_0nw")));
    if (sizeof(mage))
        mage->give_alarm(ob, LEAVING_TOWER);
}

public void
reset_room()
{

/*
    Mage = clone_npc(Mage, MAGES_DIR + "npc/morandir");
*/

}
