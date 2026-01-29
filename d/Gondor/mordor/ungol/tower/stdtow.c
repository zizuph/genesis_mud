/*
 * /d/Gondor/mordor/ungol/tower/stdtower.c
 *
 * This is the standard file of the tower at Citith Ungol and includes of
 * some functions to use let people in the tower at Cirith Ungol hear when
 * people walk in this tower.
 *
 * If you want walking to echo in this room, you have to call the function
 * init_echo_walking();
 *
 * Currently however, to help lazy wizards, initialization is done
 * automatically!
 *
 * /Mercade, 27-06-1993
 */

inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"
#include "/sys/filter_funs.h"

#define DEPTH               5
/* SS_HEARING is defined in /d/Gondor/defs.h */
#define MAX_WITHOUT_HEARING 3
#define MIN_HEARING         25
#define ROOM_I_ECHO_WALKING "_room_i_echo_walking"
#define TOWER_DOOR          UNGOL_DIR + "/tower/towerdoor"
#define TORCH_OBJECT        MORDOR_DIR + "/obj/torchstand"

/*      HEAR_NO_SEARCH   0 is tested as well, so don't start with 0 */
#define HEAR_NO_SAY      1
#define HEAR_CLOSING     2
#define HEAR_MOVING_AWAY 3
#define HEAR_NEITHER     4

object *arr_rooms;  /* all rooms within hearing distance from this room */
int *arr_distance;  /* the distance from this room to the other rooms   */

object *rooms_to_tell;  /* the rooms to tell about the walking */
int *distance_to_tell;  /* the distances to the rooms to tell  */
int *direction_to_tell; /* like the HEAR_ defines above        */

/*
 * Prototypes
 */
void init_echo_walking();

/*
 * This function is to be called when you setup the room.
 */
void
make_the_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    init_echo_walking();

}

object
make_door(string other_room, string direction)
{
    object door;

    door = clone_object(TOWER_DOOR);
    door->make_the_door(other_room, direction);
    door->move(TO);

    return door;
}

void
make_torch()
{
    clone_object(TORCH_OBJECT)->move(TO);
    return;
}

/*
 * This function builds an array (arr_rooms) with all rooms that lay within
 * DEPTH rooms from this very room. The array arr_distance will also be built
 * and will contain the distance from this room the each room in arr_rooms.
 */
void
find_neighbour_rooms(object search_room, int depth)
{
    int i;
    string *next_rooms;
    object next_room;

    next_rooms = (string *)search_room->query_exit_rooms();

    for (i = 0; i < sizeof(next_rooms); i ++)
    {
        /* I guess every call should work at long as it doesn't exist! */
        call_other(next_rooms[i], "so_I_hope_this_funcion_does_not_exist");
        next_room = find_object(next_rooms[i]);
        if (member_array(next_room, arr_rooms) == -1)
        {
            if (next_room->query_prop(ROOM_I_ECHO_WALKING))
            {
                arr_rooms += ({ next_room });
                arr_distance += ({ depth });
                if (depth < DEPTH)
                {
                    find_neighbour_rooms(next_room, (depth ++));
                }
            }
        }
    }
}

/*
 * Tell "player" that something moves in "direction" in a room that is
 * "distance" away from him. You need to have hearing skills to hear something
 * in a distance or to hear the direction someone is moving in.
 */
void
tell_player_about_walking(object player, int distance, int direction,
    object walker)
{
    int hearing_skill;
    string str;

    if (distance == 0)
    {
        if (walker->query_wiz_level())
        {
            walker->catch_msg(BSN("Since you are a wizard, you have learned " +
                "to walk stealthily, so noone will hear you enter or leave " +
                "a room whether you are invis or not. You can be heard from " +
                "a distance though."));
        }
        else
        {
            if (direction == HEAR_CLOSING)
            {
                player->catch_msg(BSN("You hear someone entering the room."));
            }
            else
            {
                player->catch_msg(BSN("You hear someone leaving the room."));
            }

            /* Check for sneaking into a room and then tell him that he is
               heard but not seen? */
        }

        return;
    }

    hearing_skill = (int)player->query_skill(SS_HEARING);

    if (distance >= MAX_WITHOUT_HEARING)
    {
        if (hearing_skill < MIN_HEARING)
        {
            return;
        }

        str = "In the distance you faintly hear footsteps, echoing against " +
            "the walls of this tower. ";
    }
    else
    {
        str = "Not far away you hear footsteps, echoing against the walls " +
            "of this tower. ";
    }

    if ((!direction) || (direction == HEAR_NO_SAY))
    {
        return;
    }

    if ((direction == HEAR_NEITHER) || (hearing_skill < MIN_HEARING))
    {
        str += "Someone is moving, but you cannot tell whether he is " +
            "closing in on you or moving away from you.";
    }
    else
    {
        if (direction == HEAR_MOVING_AWAY)
        {
            str += "From the sound you deduce that someone is moving away " +
                "from you.";
        }
        else
        {
            str += "From the sound you deduce that someone is closing in " +
                "on you.";
        }
    }

    if (hearing_skill < MIN_HEARING)
    {
        str += " If you would have better trained ears, you might have been " +
            "be able to make more out of the sounds you hear.";
    }

    player->catch_msg(BSN(str));

    return;
}

/*
 * This function tells all players within hearing distance about the fact that
 * someone is walking in his surrounding.
 */
void
tell_rooms_about_walking(object walker)
{
    int i, j;
    object *inv_room;

    for (i = 0; i < sizeof(rooms_to_tell); i ++)
    {
        inv_room = FILTER_LIVE(all_inventory(rooms_to_tell[i]));

        for (j = 0; j < sizeof(inv_room); j ++)
        {
            if ((!inv_room[j]->query_npc()) && (inv_room[i] != walker))
            {
                tell_player_about_walking(inv_room[j], distance_to_tell[i],
                    direction_to_tell[i], walker);
            }
        }
    }

    return;
}

/*
 * Adds two arrays to eachother, making sure that only one instance of each
 * element ends up in the conjunction.
 */
object *
add_arrays(object *arr1, object *arr2)
{
    int i;

    for (i = 0; i < sizeof(arr2); i ++)
    {
        if (member_array(arr2[i], arr1) == -1)
        {
            arr1 += ({ arr2[i] });
        }
    }

    return arr1;
}

/*
 * Get the distance between room_from and room_tell (if room_from doesn't
 * echo walking, the maximum distance is used.
 */
int
get_distance_to_room(object room_from, object room_tell)
{
    if (room_from->query_prop(ROOM_I_ECHO_WALKING))
    {
        return (int)room_from->query_distance_to_room(room_tell);
    }

    return (DEPTH + 1);
}

/*
 * This function takes the room someone leaves and the room someone enters
 * and tries to compose a third array (direction_to_tell) which should contain
 * whether this "someone" is moving towards you, away from you or staying at
 * equal distance.
 */
void
update_rooms_to_tell(object room_from, object room_to)
{
    object *other_rooms;
    int i;
    int diff_distance;

    if (!arr_rooms)
    {
/*
 * Maybe it is nicer to make the function invisible to the wizards, as long
 * as they include this file
 *
        write(BSN("Please make a bugreport in this room, saying that the " +
            "wizard responsible for this room should call the following " +
            "function to this room: init_echo_walking();"));
 */
        TO->init_echo_walking();
    }

    if (room_from == TO)
    {
        if (room_to->query_prop(ROOM_I_ECHO_WALKING))
        {
            other_rooms = (object *)room_to->get_arr_rooms();
        }
        else
        {
            other_rooms = ({ });
        }
    }
    else
    {
        if (room_from->query_prop(ROOM_I_ECHO_WALKING))
        {
            other_rooms = (object *)room_from->get_arr_rooms();
        }
        else
        {
            other_rooms = ({ });
        }
    }

    direction_to_tell = ({ });
    rooms_to_tell = add_arrays(arr_rooms, other_rooms);
    distance_to_tell = arr_distance;

    for (i = 0; i < sizeof(rooms_to_tell); i ++)
    {
        diff_distance = (get_distance_to_room(room_from, rooms_to_tell[i]) -
            get_distance_to_room(room_to, rooms_to_tell[i]));
        if (!diff_distance)
        {
            direction_to_tell += ({ HEAR_NEITHER });
        }
        else
        {
            if (diff_distance > 0)
            {
                direction_to_tell += ({ HEAR_CLOSING });
            }
            else
            {
                direction_to_tell += ({ HEAR_MOVING_AWAY )};
            }
        }
    }

    return;
}

/*
 * If you leave a room, that is heard!
 */
void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (living(ob))
    {
        ob->catch_msg(BSN("When you move, you make some sounds that echo " +
            "against the walls or the tower."));
        update_rooms_to_tell(TO, to);
        tell_rooms_about_walking(ob);
    }

    return;
}

/*
 * If you enter a room, that is heard as well! You only hear an arrival if
 * that isn't handled from the room you came from.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!from)
    {
        return;
    }

    if ((living(ob)) && (!from->query_prop(ROOM_I_ECHO_WALKING)))
    {
        ob->catch_msg(BSN("When you move, you make some sounds that echo " +
            "against the walls of the tower."));
        update_rooms_to_tell(from, TO);
        tell_rooms_about_walking(ob);
    }

    return;
}

/*
 * Initializes some global variables and sets the property involved.
 */
void
init_echo_walking()
{
    add_prop(ROOM_I_ECHO_WALKING, 1);

    arr_rooms = ({ TO });
    arr_distance = ({ 0 });
    find_neighbour_rooms(TO, 1);

    return;
}

/*
 * Called from another room to enquire about the rooms that are within hearing
 * distance from this room.
 */
object *
get_arr_rooms()
{
    if (!arr_rooms)
    {
        TO->init_echo_walking();
    }

    return arr_rooms;
}

/*
 * Called from another room to enquire about the distance between this room and
 * the room that the listener is in.
 */
int
query_distance_to_room(object room)
{
    int i;

    if (!arr_rooms)
    {
        TO->init_echo_walking();
    }

    i = member_array(room, arr_rooms);

    if (i != -1)
    {
        return arr_distance[i];
    }

    return (DEPTH + 1);
}
