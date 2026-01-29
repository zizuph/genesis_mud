/* /d/Terel/mist/cab_1.c
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

int picture = 0;

// Search-stuff
int searched_here = 0;
object found_item = 0;


/*
* Function name: do_search()
* Description  : When someone searches a certain item.
*/
string do_search(object searcher, string str)
{
	if (str == "beam" || str == "beams" ||
		str == "wooden beams" || str == "wooden poles" ||
		str == "poles")
	{
		if (searched_here > 0)
		{
			return "";
		}

		searched_here++;

		string item = one_of_list(({
			"wep/rlyehian_axe",
		}));

		tell_room(this_object(), QCTNAME(this_player()) + " finds "
			+ "something behind one of the wooden beams.\n",this_player());

		//found_item = clone_object(MAR + item);
		//found_item->move(this_object());

		return "You find a " + found_item->short()
		+ " behind one of the wooden beams.\n";
	}

	return "";
}



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
        "A speck of dust lands on your nose.",
        "The wooden boards creak as you move on them.",
        "You sense a draft from the roof.",
        "The old dusty picture shimmers for a brief moment.",
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


int change_picture()
{
    picture = picture + 1;

    if (picture >= 4)
    {
        picture = 0;
    }

    return 1;
}



/*int exa_picture(string str)
{
    if (str == "picture" || str == "dusty picture"
        || str == "old dusty picture")
    {
        switch(picture)
        {
            case 0:
            write("The old dusty picture shows a ghastly skeletal "
                +"face of a woman dressed in white.\n");
            break;

            case 1:
            write(".\n");
            break;

            case 2:
            write(".\n");
            break;

            case 3:
            write(".\n");
            break;

            return 1;

        }
    }

    return 0;
}*/

string exa_picture()
{
    switch(picture)
    {
        case 0:
        return "The old dusty picture shows a ghastly skeletal "
            +"face of a woman dressed in white.\n";

        case 1:
        return "The old dusty picture shows a ghastly skeletal "
            +"face of a woman dressed in white.\n";

        case 2:
        return "The old dusty picture shows a ghastly skeletal "
            +"face of a woman dressed in white.\n";

        case 3:
        return "The old dusty picture shows a ghastly skeletal "
            +"face of a woman dressed in white.\n";
    }

    return "The old dusty picture shows a ghastly skeletal "
        +"face of a woman dressed in white.\n";
}



int do_picture(string str)
{
    if (str == "picture" || str == "dusty picture"
        || str == "old dusty picture")
    {
        return 1;
    }

    return 0;
}

/*
 * Function name: create_sva_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_room()
{
    seteuid(getuid());

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    set_short("You are inside an old wooden cabin.");

    set_long("You are inside an old wooden cabin. There are strewn "
        +"about pieces of wood and fragments of old furniture all over "
        +"the place. The room is almost entirely barren for anything "
        +"else except for an old dusty picture on the north wall.\n");

    add_item(({ "picture", "dusty picture", "old dusty picture" }), exa_picture);

	add_item(({ "blood", "trail"}), "You notice marks of blood in the "
        +"grass leaving a distinct trail leading further to the northwest.\n");

    add_item(({ "swirly mist", "mist"}), "The mist emanates from the grass as "
        +"if it were burning, but it's very chilly and moves about unnaturally.\n");


    //add_exit(DOMAIN_DIR + "mist/cab_1",   "enter");
    add_exit(DOMAIN_DIR + "mist/p2",   "out");

    // Activate local roomtells.
    room_tells = 0;

    set_alarm(60.0, 60.0, &change_picture());

    reset_room();
}


/*
 * Function name: reset_room()
 * Description  : Resets the room
 */
void
reset_room()
{
    // Resets the searchable item
    if (random(2) == 0)
	{
		searched_here = 0;
		found_item = 0;
	}
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

     add_action(do_picture, "touch");
     add_action(exa_picture, "examine");
}

