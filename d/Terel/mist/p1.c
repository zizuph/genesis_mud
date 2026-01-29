/* /d/Terel/mist/p1.c
 *
 *
 * Nerull, 2016
 *
 */

#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>
#include "/d/Terel/include/Terel.h";

inherit STDROOM;

#define ROOM_TELL_TIMER  200.0

string short_descriptor;
string long_descriptor;

int room_tells = 0;
int roomalarm = 0;



/*
* Function name: block_player()
* Description  : blocks a player from going a certain direction.
*/
int
block_player()
{
    write("That direction heads into some dense mist. You decide "
        +"to stay here for now.\n");

    return 1;
}


/*
* Function name: local_room_tells()
* Description  : As described - local tells.
*/
int
local_room_tells()
{
    if (room_tells == 0)
    {
        return 1;
    }

    object *plays;
    plays = FILTER_PLAYERS(all_inventory(this_object()));

    string  room_tell_message = one_of_list(({
        "You hear howls in the distance.",
        "You see movement in the woods around you.",
        "The mist swirls around the trees.",
    }));

    tell_room(this_object(), room_tell_message + "\n");

    if (sizeof(plays) > 0)
    {
        set_alarm(ROOM_TELL_TIMER, 0.0, &local_room_tells());

        return 1;
    }

    roomalarm = 0;

    return 1;
}


/*
 * Function name: create_sva_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_room()
{
    seteuid(getuid());

    set_short("You are at the edge of the Silver Forest.");

    set_long("You are at the edge of the Silver Forest. To the southeast you "
        +"see the road between the trees while the path leads deeper into the "
        +"forest to northwest. The area here is occupied with swirling mist. You "
        +"notice a trail of blood on the ground.\n");

    add_item(({ "path", "ground" }), "You look at the ground and "
        +"notice the path continues to northwest and southeast through the "
        +"grass.\n");

	add_item(({ "blood", "trail"}), "You notice marks of blood in the "
        +"grass leaving a distinct trail leading further to the northwest.\n");

    add_item(({ "wood", "woods", "forest", "forests"}), "There are giant "
        +"pine trees all around you, accompanied with various foliage and "
        +"bushes in all directions.\n");

    add_item(({ "swirly mist", "mist"}), "The mist emanates from the grass as "
        +"if it were burning, but it's very chilly and moves about unnaturally.\n");


    add_exit(DOMAIN_DIR + "mist/p2",   "northwest");
    add_exit(RIBOS_DIR + "roads/road_06",   "southeast");

    // Activate local roomtells.
    room_tells = 1;

    reset_room();
}


/*
 * Function name: reset_room()
 * Description  : Resets the room
 */
void
reset_room()
{

}


/*
* Function name: init()
* Description  :
*/
void
init()
{

    if (interactive(this_player()))
    {
        if (roomalarm == 0)
        {
            set_alarm(10.0, 0.0, &local_room_tells());

            roomalarm = 1;
        }
    }

    ::init();
}

