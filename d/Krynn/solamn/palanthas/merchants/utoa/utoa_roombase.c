/* 
 * The base indoor room for the skeleton infested area underneath the
 * Tower of Arms in Palanthas. It was an old crypt now awakened and is
 * intended to serve as a good-aligned killing ground counter to the
 * Tower of Arms itself.
 *
 * Mortis 10.2014
 */
#pragma strict_types

#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../../local.h"
#include CLOCKH

/* Inherit the Ansalon room */
inherit R_FILE
inherit TDIR + "smell_world";

#define CREATE "create_palan_room"
#define RESET  "reset_palan_room"

public void init();
public int do_smell(string arg);
public string add_long();

string dsmell = "The air is dusty here, old, and stale. ";

/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

/*
 * This function is called from the main Krynn room. It checks
 * whether or not the room should be reset.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
    {
        return 1;
    }
    return 0;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    call_other(TO, CREATE);
    ITEM(({"floor", "floors", "ceiling", "wall", "walls", "ground"}), "The "
    + "walls, floor, and ceiling are ancient, grey stone. Covered in dust, "
    + "rivulets of water have stained sections of the stone with a reddish "
    + "brown hue.\n");

    ITEM(({"grey stone", "ancient stone", "stone", "crypt"}), "The ancient, "
    + "grey stone is bedrock for this region. The rough chiseling and low "
    + "ceilings are consistent with crypts made five centuries ago.\n");
    ITEM(({"opened stone coffins", "stone coffins", "coffins", "urns",
        "burial urns", "piles", "bone piles"}), "Coffins of dusty stone, "
    + "some opened and empty, line the place amidst burial urns and piles "
    + "of old, dusty bones.\n");

    add_prop(ROOM_S_DARK_LONG, "A pitch-black, dark crypt.\n");
    add_prop(ROOM_S_DARK_MSG, "It is too pitch-black dark to");
    add_prop(ROOM_I_LIGHT, 0);
    
    set_tell_time(90);
    add_tell("@@get_tells@@" + "\n");

    add_smell("vampire", dsmell + "Your heightened sense of smell detects "
    + "the ancient dust is from human and elven bone permeating this "
    + "place.");
    add_smell("morgul", dsmell + "The ancient dust smells like that from "
    + "decaying bones.");

    add_smell("human", dsmell + "A hint of fear begins to fill your "
    + "nostrils.");
    add_smell("elf", dsmell + "The area reeks of decay and fear like "
    + "a crypt.");
    add_smell("goblin", dsmell + "Not bad for goblin whoopie.");
    add_smell("dwarf", dsmell + "It smells like a crypt.");
    add_smell("hobbit", dsmell + "It stinks down here frankly.");
    add_smell("gnome", dsmell + "The dust appears to be from bone, "
    + "perhaps human or elven or human and elven. Yes, this is likely a "
    + "crypt, and a disturbed one at that.");
    add_smell("minotaur", dsmell + "The smell of old human bones floods "
    + "your senses.");
    add_smell("halfhuman", dsmell + "It smells like a crypt, maybe for "
    + "humans.");
    add_smell("halfelf", dsmell + "It smells like a crypt, maybe for elves.");
    add_smell("orc", dsmell + "The smell of old, decayed manflesh is strong "
    + "here. They must dump their dead here.");
    add_smell("hobgoblin", dsmell + "This is crypt air, human and elven crypt "
    + "air.");
    add_smell("kender", dsmell + "It does not smell sweet here. Maybe "
    + "old bones or old people.");
    add_smell("drow", dsmell + "Nor'ilgghu! It's a human and elven crypt and "
    + "smells disturbed by undead..");
    add_smell("noldor", dsmell + "The dust is likely from human and elven "
    + "bone, and you detect the scent of undeath.");

    /* CMD("area", "smell", "@@smell_world"); */
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_room_tells();
    }
}

public void
init()
{
    ::init();  /* vitally important! never forget this line! */

    add_action(do_smell, "smell");
    add_action(do_smell, "sniff");
    add_action(do_smell, "inhale"); /* a few different verbs, same effect*/
} /* init */

/*
 * Function name:        add_long
 * Description  :        Random string to customize /utoa rooms
 * Returns      :        string to add onto room description using this base.
 */
public string
add_long()
{
    string mylong = one_of_list(({"Empty stone coffins", "Open stone "
    + "coffins", "Burial urns", "Scattered piles of bones"}));
    mylong += " line the place.\n";

    return mylong;
}

/*
 * Function name:        do_smell
 * Description  :        allow the player to smell the air
 * Arguments    :        string arg - the commands following the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_smell(string arg)
{
    if (strlen(arg) && !parse_command(arg, ({}),
        "[the] 'air' / 'here' / 'area' [of] [the] [city]"))
    {
        return 0; /* the player used syntax we don't agree with */
    }

    /*
     * Note: The above if statement searches for combinations of the
     *       syntax in quotes. Statementes in [] are optional, statements
     *       in '' are required, with / acting as "or" statements. Thus,
     *       we can handle a vast number of combinations, including, but
     *       not limited to:
     *
     *       air
     *       the air
     *       the air of the city
     *       here
     *       area
     *       etcetera
     *
     *       Of course, we have also made possible odd combinations such
     *       as:
     * 
     *       here the
     *       the area city
     *       etcetera
     *
     *       But a small price to pay for being user friendly. :-)
     */


    smell_world(this_player());
    return 1;
} /* do_smell */

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}

string
get_tells()
{
    string utoatell;

    utoatell = one_of_list(({"A rivulet of water streams briefly down the "
    + "wall.",
      "\"Drip.\"",
      "The clack of bone on stone echoes about the walls from somewhere "
    + "closeby.",
      "\"Gruuhhhh...\"",
      "The collapse of a pile of bones resounds throughout the area.",
      "You hear the clump of a heavy footstep echoing about the walls "
    + "from somewhere " + one_of_list(({"nearby.", "above.", "below."})),
      "A small piece of stone clatters briefly nearby.",
      "The floor groans and cracks below you momentarily.",
      "Dust swirls up suddenly.",
      "\"Clump... clump... clump...\"",
      "The scurrying of hundreds of tiny clawed feet nearby echoes about the "
    + "walls.",
      "A fetid breeze gusts for a moment bringing with it the smell of "
    + one_of_list(({"rot", "death", "ancient dust", "wet stone", "blood "
    + "throat-choking dust", "sour filth"})) + ".",
      "A dusty breeze chokes your throat.",
      "\"Goom!\"",
      "You hear a " + one_of_list(({"male", "female"})) + " voice scream "
    + "nearby.",
      "The cool, dry breeze brings with it a low moan.",
      "The sound of claws screeching across stone echoes about from "
    + "closeby."}));

    return utoatell;
}
