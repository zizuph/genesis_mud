#include "defs.h"

#define PARALYZE_OBJECT_PATH OBJ_DIR + "paralyze"

object
paralyze(object player, string type = "default", int time = 20)
{
    object paralyze;
    paralyze = clone_object(PARALYZE_OBJECT_PATH);
    paralyze->set_remove_time(time);
    paralyze->set_paralyze_type(type);
    paralyze->move(player, 1);
    player->add_attack_delay(time, 1);
    return paralyze; 
}

object *
get_paralyzed(object player, string type = 0)
{

    return OBJ_IN_ARRAY(PARALYZE_OBJECT_PATH, INV(player));
}

int
is_paralyzed(object player)
{
    if (sizeof(get_paralyzed(player)))
        return 1;
    return 0;
}
