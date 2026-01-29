#include "defs.h"

object
paralyze(object player, int time = 20)
{
    object paralyze;
    paralyze = clone_object(COMMON_OBJ_DIR + "paralyze");
    paralyze->set_remove_time(time);
    paralyze->move(player, 1);
    player->add_attack_delay(time, 1);
    return paralyze; 
}

int
is_paralyzed(object player)
{
    if (present("_raumdor_paralyze_object", player))
        return 1;
    return 0;
}
