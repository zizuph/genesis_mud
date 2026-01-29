#include <filter_funs.h>

/**
 * This function is only here until we get the /secure/simul_efun_tell_roombb
 * function fixed to allow exclusion of other livings than this player.
 */
void
my_tell_roombb(mixed room, mixed str, object from_player = this_player(),
               object* exclude_livings = ({}))
{
    object *objs;

    if (!room)
    {
        return;
    }
    
    if (stringp(room) && !(room = find_object(room)))
    {
        return;
    }
    
    objs = FILTER_LIVE(all_inventory(room)) - ({ from_player })
                                            - exclude_livings;
    objs = FILTER_CAN_SEE_IN_ROOM(objs);
    objs = FILTER_IS_SEEN(from_player, objs);
    objs->catch_msg(str, from_player);
}
