/* /d/Terel/mist/p2.c
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

    set_short("You are outside a wooden cabin in the Silver Forest.");

    set_long("You are next to a wooden cabin somewhere in "
        +"the Silver Forest. The area here is occupied with swirling mist that "
        +"crawls up the walls of the cabin, and you "
        +"notice a trail of blood on the ground leading to the entrance.\n");

    add_item(({ "path", "ground" }), "You look at the ground and "
        +"notice the path continues to northwest and southeast through the "
        +"grass.\n");

    add_item(({ "wood", "woods", "forest", "forests"}), "There are giant "
        +"pine trees all around you, accompanied with various foliage and "
        +"bushes in all directions.\n");

	add_item(({ "blood", "trail"}), "You notice marks of blood in the "
        +"grass leaving a distinct trail leading further to the northwest.\n");

    add_item(({ "mist"}), "The mist creeps about just a few inches "
        +"above the ground and around the cabin.\n");

    add_item(({ "cabin", "wooden cabin", "window", "windows"}), "It's an "
        +"old but rather large "
        +"wooden cabin. Strangely, it has no windows, but the door-less "
        +"entrance gaps at you like an open maw.\n");

    add_item(({ "entrance", "door", "doorway"}), "The entrance of the "
        +"cabin is missing a door. The shadows from within gives it "
        +"an eerie appearance of a gaping maw.\n");

    add_item(({ "swirly mist", "mist"}), "The mist emanates from the grass as "
        +"if it were burning, but it's very chilly and moves about unnaturally.\n");


    add_exit(DOMAIN_DIR + "mist/cab_1",   "enter");
    add_exit(DOMAIN_DIR + "mist/p1",   "southeast");

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

