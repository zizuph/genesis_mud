/*
 * /d/Gondor/mordor/ungol/tower/stdtower.c
 *
 * This is the standard file of the tower at Citith Ungol and includes of
 * some functions to use let people in the tower at Cirith Ungol hear when
 * people walk in this tower.
 *
 * Another nice feature is that with make_the_room() several random add_items
 * are defined. Obviously, if you want to redefine them you will have to call
 * make_the_room first ;-) The defined add_items are:
 * - wall walls
 * - floor ground
 * - stone stones
 * - torch torches stand stands bracket brackets "torch stand" "torch stands"
 *   torchstand torchstands
 * - ceiling
 * - girder girders
 * - light
 * - nail nails (sometimes)
 * - sign signs (sometimes, if defined also with add_cmd_item for read)
 * - pile garbage refuse (sometimes)
 * - niche niches opening openings (sometimes)
 * - footstep footsteps (sometimes)
 *
 * The following add_cmd_items are added to this room
 * - light torch(es) all
 * - extinguish torch(es) all
 *
 * Call "no_torch" to get no add_item of torch
 * Call "no_add_items" to get no add_items at all
 *
 * /Mercade, 24 September 1993
 *
 * Revision History:
 *
 *    Toby, 10th-Sept-2007: Added terrain.h
 */

inherit "/d/Gondor/common/room"; /* includes time */

#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include <macros.h>

#define TOWER_DOOR  UNGOL_DIR + "tower/towerdoor"
#define TOWER_TORCH MORDOR_DIR + "obj/torchstand"
#define TOWER_ORC   MORDOR_DIR + "npc/towerorc"
#define WHIP        MORDOR_DIR + "obj/whip"

#define ORC_ENTRANCE_MESSAGES                         \
    ({ " enters the room, searching for indruders.",  \
       " steps out of one of the niches.",            \
       " suddenly looms up from the gloom.",          \
       " arrives from an adjecent room.",             \
       " comes in, attracted by the noise you make.", \
       " runs in, crying: ghash blan tark!",          \
       " rushes in, brandishing his weapons."         \
    })
/*
 * Ghash = fire          (old orcish word)
 * blan  = to            (not an old orcish word *grin*)
 * tark  = man of Gondor (old orcish word)
 */

/*
 * Global variable
 */
int add_no_torch_in_this_room = 0;     /* no add_item of torch here */
int add_no_add_items_in_this_room = 0; /* no add_items at all here  */

/*
 * This function will do a random add_item to get different wall descriptions
 */
void
add_item_wall()
{
    switch(random(4))
    {
    case 0:
        add_item( ({ "wall", "walls" }),
            BSN("The walls of this tower are make of stone and they are " +
            "quite thick. They are quite smooth, making the the rooms sound " +
            "hollow."));
        return;
    case 1:
        add_item( ({ "wall", "walls" }),
            BSN("The walls are dark and there are several openings in " +
            "walls, where orcs can hide or chests might be found."));
        add_item( ({ "niche", "niches", "opening", "openings" }),
            BSN("Most of the niches here are empty, but in one you see a " +
            "chest."));
        add_item( ({ "chest", "chests" }),
            BSN("The chest you see in one of the openings is empty."));
        return;
    case 2:
        add_item( ({ "wall", "walls" }),
            BSN("Except from some signs you don't see much special on the " +
            "walls surrounding you."));
        add_item( ({ "sign", "signs" }),
            BSN("On the sign you see some writing in the an old language."));
        add_cmd_item( ({ "sign", "signs" }), ({ "read" }),
            BSN("One of the signs reads: Ugluk u bagronk sha pushdug " +
            "bubhosh skai. It doesn't make much sense to you. You are not " +
            "that skilled in the black speech also known as the orc tongue."));
        return;
    case 3:
    default:
        add_item( ({ "wall", "walls" }),
            BSN("The walls feel remarkably smooth. Long ago, the men of " +
            "Gondor made this tower to guard against the evil forces of the " +
            "nameless One and they made the walls very thick."));
        return;
    }
}

/*
 * This function will do a random add_item to get different floor descriptions
 */
void
add_item_floor()
{
    switch(random(3))
    {
    case 0:
        add_item( ({ "floor", "ground" }),
            BSN("You are standing on a stone floor. It is dusty and there " +
            "is some garbage or refuse. You see nothing of particular " +
            "interest in the pile of garbage"));
        add_item( ({ "pile", "refuse", "garbage" }),
            BSN("You don't see anything interesting in the garbage. The " +
            "orcs that live here might be slobs, but they don't throw away " +
            "anything useful."));
        return;
    case 1:
        add_item( ({ "floor", "ground" }),
            BSN("Looking at the dusty floor you see footprints in all " +
            "directions. The orcs that live hear don't clean up this place " +
            "on a regular basis."));
        add_item( ({ "footprint", "footprints" }),
            BSN("The footprints only reveal to you that many people, " +
            "probably orcs, walked here."));
        return;
    case 2:
    default:
        add_item( ({ "floor", "ground" }),
            BSN("The floor is made of dark stones and is rather dusty."));
        return;
    }
}

/*
 * This function will do a random add_item to get different stone descriptions
 */
void
add_item_stone()
{
    switch(random(3))
    {
    case 0:
        add_item( ({ "stone", "stones" }),
            BSN("The stones yield no information if you look at them " +
            "closely. They are smooth yet dark."));
        return;
    case 1:
        add_item( ({ "stone", "stones" }),
            BSN("Looking closely at the stones you see that even though " +
            "they are all shaped capriciously they are carved in such a way " +
            "that they fit exactly without cement between them."));
        return;
    case 2:
    default:
        add_item( ({ "stone", "stones" }),
            BSN("They are just normal dark stones and you see a lot of " +
            "them."));
        return;
    }
}

/*
 * This function will do a random add_item to get different torch descriptions
 */
void
add_item_torch()
{
    if (add_no_torch_in_this_room)
    {
        return;
    }

    switch(random(3))
    {
    case 0:
        add_item( ({ "torch", "torches", "stand", "stands", "bracket",
            "brackets", "torch stand", "torch stands", "torchstand",
            "torchstands" }),
            BSN("Several torches are in brackets, secured to the wall. They " +
            "shed some light on the dark walls surrounding you."));
        return;
    case 1:
        add_item( ({ "torch", "torches", "stand", "stands", "bracket",
            "brackets", "torch stand", "torch stands", "torchstands",
            "torchstands" }),
            BSN("This dark and gloomy place is illuminated slightly by " +
            "several torches that flare in their stands. The torch stands " +
            "stands are mounted to the wall with large nails."));
        add_item( ({ "nail", "nails" }),
            BSN("They are used to secure the torch stands to the wall."));
        return;
    case 2:
    default:
        add_item( ({ "torch", "torches", "stand", "stands", "bracket",
            "brackets", "torch stand", "torch stands", "torchstand",
            "torchstands" }),
            BSN("At the walls you see some torches in brackets. They give " +
            "little light in this dark place, but enough for you to see."));
        return;
    }
}

/*
 * This function will do a random add_item to get ceiling description.
 */
void
add_item_ceiling()
{

/* adds ceiling, girder(s) */

}

/*
 * This function is to be called when you setup the room.
 */
void
make_the_room()
{
    if (!add_no_add_items_in_this_room)
    {
        add_item_wall();
        add_item_floor();
        add_item_stone();
        add_item_torch();
        add_item_ceiling();
    }

    add_item("light",
        "Yes, indeed there is light in this room. You might even see something " +
        "here.\n");

    set_terrain(TERRAIN_SHADOWS | TERRAIN_COLD | TERRAIN_ROCK);

    add_prop(ROOM_I_INSIDE, 1); /* You are inside the tower    */
    add_prop(ROOM_I_LIGHT, 0);  /* it is dark inside the tower */
    add_prop(OBJ_S_WIZINFO,
        "This tower has a nice feature. If you walk here, other people " +
        "that are within hearing distance will hear you walking. In " +
        "addition the stairs are developed like a winding staircase. If " +
        "you go northeast, you descend the stairs, if you go northwest you " +
        "up (if you are in a room with the stairs).\n");

    seteuid(getuid(this_object()));
}

/*
 * Add some commands to the player.
 */
void
init()
{
    ::init();

    if (!add_no_torch_in_this_room)
    {
        add_action("try_to_access_torch", "light");
        add_action("try_to_access_torch", "extinguish");
    }
}

/*
 * Make it impossible to handle the torch
 */
int
try_to_access_torch(string str)
{
    if ((str != "all") && (str != "torch") && (str != "torches"))
    {
        NFN0(CAP(query_verb()) + " what ?");
    }

    NFN0("The torchstands are mounted too high on the wall. You cannot " +
        "reach the torch in it.");
}

/*
 * Call this function if you don't want to have add_items of a torch in this
 * room, for instance if it is a prison or a terrace/lookout
 */
void
no_torch()
{
    remove_item("torch");
    add_no_torch_in_this_room = 1;
}

/*
 * Call this function to block all add_items in the room, for instance when
 * you define the terrace/lookout.
 */
void
no_add_items()
{
    add_no_add_items_in_this_room = 1;
}

/*
 * Function name: compute_door_id
 * Description  : The doors require a unique name that only the doors on
 *                either side of the door has. This function is used to
 *                compute such a unique name from the filename of this room
 *                and the filename of the other room on the other side of the
 *                door.
 * Arguments    : other_room (string) - the filename of the other room
 * Returns      : string - the composed door id string.
 */
string
compute_door_id(string other_room)
{
    if (other_room > MASTER)
    {
        return other_room + " " + MASTER;
    }

    return MASTER + " " + other_room;
}

/*
 * Function name: make_door
 * Description  : This function is used to add a door to the room.
 * Arguments    : other_room (string) - the other room file
 *                direction  (string) - the direction to get to the other room
 *                door_number (int)   - the number of the door. Can either be
 *                                      1 or 2 (determining the key)
 * Returns      : object - the objectpointer to the door
 */
object
make_door(string other_room, string direction, int door_number)
{
    string door_id_string = compute_door_id(other_room);
    object door;

    FIX_EUID;

    door = clone_object(TOWER_DOOR);
    door->make_the_door(door_id_string, other_room, direction, door_number);
    door->move(TO);

    return door;
}

/*
 * Call this function to get a torch in this room.
 */
void
make_torch()
{
    no_torch(); /* Do not get an add_item torch here. */

    FIX_EUID;

    clone_object(TOWER_TORCH)->move(TO);
}

/*
 * Function name: make_orc
 * Description  : This function adds an orc to the room and gives a random
 *                entrance message.
 * Arguments    : strength (int) - the average stats of the orc
 *                whip (int) - set to 1 to give the orc a whip
 * Returns      : object - the objectpointer to the orc.
 */
varargs object
make_orc(int strength, int whip)
{
    object orc;

    FIX_EUID;

    orc = clone_object(TOWER_ORC);
    orc->make_the_orc(strength, whip);
    TELL_ROOM(TO, orc, ONE_OF_LIST(ORC_ENTRANCE_MESSAGES), orc);
    orc->move(TO);

    return orc;
}

/*
 * the filter fun, used in query_living_orcs()
 */
int
living_orc(object ob)
{
     return ((ob->id("orc")) && (living(ob)));
}

/*
 * Call this query if you want to know whether there are orcs alive in this
 * room. If there is a living orc, you will get the objectpointer to one orc.
 */
object
query_living_orc()
{
    object *obs = filter(all_inventory(TO), "living_orc", TO);

    if (sizeof(obs))
    {
        return obs[0];
    }

    return 0;
}
