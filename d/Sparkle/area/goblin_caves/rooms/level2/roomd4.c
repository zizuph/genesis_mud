/*
 * Shaman area entrance 
 * Boreaulam, Nov 2012
 */
#include "defs.h"
#pragma strict_types

inherit L2_BASE_ROOM;

/*
 * Function name:        create_room
 * Description  :        creates room
 */
void
create_room()
{
    ::create_room();

    set_short("Small cave");
    set_long("This small cave is really more of an alcove, as it is not very " +
        "deep at all. Judging by a large pile of rubble which has been left " +
        "against the eastern wall, it is entirely possible that the goblins " +
        "have not finished opening up a new cave here just yet. The rest " +
        "of the walls and ceiling are rather featureless, save for a single " +
        "torch which has been mounted on the wall. An irregular shaped " +
        "opening leads out west, back to the larger cavern.\n\n");

    add_item(({"rubble", "stone rubble", "debris", 
               "pile", "small stones", "stones"}),
        "There is a lot of stone rubble left in a large pile here, as if " +
        "the goblins who have been " +
        "expanding these caves have not quite finished everything " +
        "just yet. There does not appear to be anything in the pile " +
        "aside from a whole lot of small stones.\n");
    add_item(({"hole", "small opening", "small hole"}),
        "This is a small hole, half covered by the rubble and just large " +
        "enough to squeeze past. It digs through the eastern wall " +
        "and down even deeper through the grey stone of the " +
        "mountain.\n");
    add_item(({"opening", "irregular opening"}),
        "There is an irregular shaped opening in the wall which leads back " +
        "out into the larger cavern you came from originally.\n");
    add_item(({"lake", "underground lake", "wide lake"}),
        "Barely visible through the opening in the northern wall is " +
        "the wide underground lake which fills the middle of the " +
        "cavern outside.\n");
    add_item(({"cavern", "large cavern", "larger cavern"}),
        "When you look through the opening in the north wall, you can " +
        "see a large cavern with a wide lake in the middle of it.\n");
    add_item(({"caves", "caverns"}),
        "You are in a large series of caves and caverns that tunnel " +
        "deep beneath the mountains.\n");
    add_item(({"floor", "down"}),
        "The grey, stone floor here is quite rough and uneven, jagged " +
        "pieces of stone rubble seem to be scattered everywhere.\n");
    add_item(({"wall", "walls"}),
        "The walls here are made of the same grey stone as everything " +
        "else in these caves. A single torch has been mounted on the " +
        "southern wall to provide some light.\n");
    add_item(({"south wall", "southern wall"}),
        "The dull grey stone of the southern wall has been roughly chiseled, " +
        "and the debris has apparently been left behind, piled up against " +
        "the eastern wall. A small torch has been mounted here, providing " +
        "a little bit of light.\n");
    add_item(({"north wall", "northern wall"}),
        "The dull grey stone of the northern wall has been roughly chiseled, " +
        "and the debris has apparently been left behind, piled up against " +
        "the eastern wall.\n");
    add_item(({"east wall", "eastern wall"}),
        "The dull grey stone of the eastern wall has been roughly chiseled, " +
        "and the debris has apparently been left behind, piled up against " +
        "this wall.\n");
    add_item(({"west wall", "western wall"}),
        "The dull grey stone of the western wall has been roughly chiseled, " +
        "and the debris has apparently been left behind, piled up against " +
        "the eastern wall. There is an irregular shapen opening in this " +
        "wall which leads back into the larger cavern outside.\n");
    add_item(({"ceiling", "up"}),
        "The dull grey stone of the ceiling has been roughly chiseled, " +
        "obviously worked by hand to expand what was probably a " +
        "naturally existing cave at first.\n");
    add_item(({"torch", "torches"}),
        "A small torch has been mounted on the southern wall, helping to " +
        "provide a little bit of light here.\n");
    add_item(({"stone", "grey stone", "granite"}),
        "This dull grey stone is the very bones of the mountains you are " +
        "currently beneath. This granite is very hard, but in many places " +
        "it appears that several industrious goblins have chiseled away " +
        "at the walls and ceilings to make these caves more habitable.\n");

    add_exit("roomd3", "west");

    add_prop(OBJ_S_SEARCH_FUN, "do_search");

} /* create_room */

/*
 * Function name:        init
 * Description  :        on init hook
 */
void
init()
{
    ::init();
    add_action("enter", "enter", 0);
} /* init */

/*
 * Function name:        do_search
 * Description  :        allow the player to search things in the room
 * Arguments    :        object pl  - the player object,
 *                       string arg - what the player tried to search
 * Returns      :        int 1 - success, 0 - failure
 */
public string
do_search(object pl, string arg)
{
    if (member_array(arg,
        ({ "rubble", 
           "rubble", 
           "small rubble", 
           "small rubble", 
           "small stones", 
           "stones", 
           "debris",
           "small stone rubble", 
           "small stone rubble"}) ) == -1)
    {
        return "Your search reveals nothing special.\n";
    }

    return "You find a small hole opening up in the east wall.\n";

} /* do_search */

/*
 * Function name:        enter
 * Description  :        enters into roomg
 */
int
enter(string s)
{
    if (!strlen(s))
    {
        notify_fail("Enter what?\n");
        return 0;
    }

    if (!parse_command(s, ({}),
        "[in] [into] [to] [the] [small] 'hole' [in] [the] [east]"
      + " [wall]"))
    {
        notify_fail("What are you trying to enter? The hole?\n");
        return 0;
    }

    set_dircmd("hole");
    TP->move_living("into the hole", ROOMS_DIR + "level2/shaman_entrance");
    return 1;
} /* enter */
