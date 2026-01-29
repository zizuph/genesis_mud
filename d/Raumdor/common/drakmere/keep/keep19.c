/* Sarr */
#include "defs.h"
inherit KEEP_ROOM;

object door;

void
create_room()
{
    ::create_room();

    set_short("Inside a large vault");
    set_long(
      "You are in windowless, featureless room clearly intended for the " +
      "storage of valuables.\n");

    add_prop(ROOM_I_HIDE, 90);
    add_prop(ROOM_M_NO_TELEPORT, "The vault seems to be magically protected " +
      "against entering or leaving by means other than the door.\n");
    door = clone_object(KEEP_OBJ_DIR + "vault_door_inside");
    door->move(TO,1);
    MONEY_MAKE_PC(random(5) + 1)->move(TO);
    MONEY_MAKE_GC(random(20) + 5)->move(TO);
    MONEY_MAKE_SC(random(100) + 20)->move(TO);

    // Let's just do one of these, for now. 
    clone_object(KEEP_OBJ_DIR + "raumdor_map")->move(TO);
}

/* This gets called from the other side when no players present. We make sure
 * there are none here either before resetting.
 */
void
reset_vault()
{
    if (sizeof(FILTER_PLAYERS(INV(TO))))
        return;

    door->do_close_door();
    door->query_other_door()->do_close_door();
    door->do_lock_door();
    door->query_other_door()->do_lock_door();
    MONEY_MAKE_PC(random(2))->move(TO);
    MONEY_MAKE_GC(random(5) + 1)->move(TO);
    MONEY_MAKE_SC(random(20) + 5)->move(TO);
}
