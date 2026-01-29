/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/caves/grotto.c
 *
 *  This room was carved out by Formandil's elves to be used as a hidden
 *  storage area. Many things were kept here for dire circumstances
 *  in case the main reserves were destroyed or depleted. Maeltar
 *  fashioned symbols here for his own mysterious purposes.
 *
 *  Copyright (c) June 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void        create_del_rimmon();
public string      display_shape(int emblem);
public int         do_stuff(int arg);
public void        init();


/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room
 */
public void
create_del_rimmon()
{
    set_short("a small chamber carved in the rock");
    set_long("In a small chamber carved in the rock. This roughly"
      + " rectangular chamber appears to have once been a storage"
      + " room. Wooden racks line the western wall, where a few"
      + " old and rusted armaments yet remain. Large barrels rest along"
      + " the base of the wall to the north, and a row of low shelves"
      + " rest against the southern wall. A passageway leads east"
      + " into a dark chamber.\n");

    add_item( ({ "here", "chamber", "small chamber", "store room",
                 "room", "area", "storage room", "storage chamber"}),
        "This room appears to have been used many hundreds of years"
      + " ago as a storage chamber.\n");
    add_item( ({ "rack", "racks", "wooden rack", "wooden racks" }),
        "The wood which the racks are made of has bent and split"
      + " in many places from the passing of time. The shape of the"
      + " racks suggest that they were built to house weapons and"
      + " armour of various shapes and sizes. A few forgotten spears"
      + " yet stand idle in their slots. A thick coat of dust lies"
      + " undisturbed on the surface of the racks.\n");
    add_item( ({ "wood" }),
        "The racks, barrels, and shelves are all comprised of wood.\n");
    add_item( ({ "weapon", "weapons", "armament", "armaments",
                 "rusted weapon", "rusted armament", "rusted armaments",
                 "spear", "spears", "forgotten spear",
                 "forgotten spears" }),
        "A number of spears stand forgotten in the rack along the"
      + " west wall. Their shafts look old and brittle, and their"
      + " tips horribly rusted. Though certainly of little use, they"
      + " suggest the function that this room may have served at one"
      + " time, long ago.\n");
    add_cmd_item( ({ "spear", "spears", "weapon", "weapons" }),
                  ({ "get", "take", "search" }),
        "You pull one of the spears from its slot in the wooden rack,"
      + " and immediately notice how feeble a weapon it is, having stood"
      + " uncared for for countless years in this room. Figuring it"
      + " would be a waste of space to carry such a thing around, you"
      + " return it to its resting place.\n");
    add_item( ({ "slot", "slots" }),
        "Most of the slots in the rack are empty, though a few spears"
      + " seem to have been left behind.\n");
    add_item( ({ "rust", "tip", "tips", "tip of the spear",
                 "spear tip", "spear tips", "tips of the spears" }),
        "The tips of the spears are heavily corroded with rust, which"
      + " would make them nearly useless for any kind of defense.\n");
    add_item( ({ "shaft", "shafts", "spear shaft", "spear shafts",
                 "shaft of the spear", "shafts of the spears" }),
        "The shafts of the spears are warped with age, and look as"
      + " if they would break if one were to attempt to use them.\n");
    add_item( ({ "dust", "thick coat of dust", "coat of dust",
                 "thick dust" }),
        "Thick dust lies on everything in this room. It does not look"
      + " as if anyone has visited these confines for hundreds of"
      + " years.\n");
    add_item( ({ "west", "west wall", "western wall",
                 "wall to the west" }),
        "The western wall is flat and fairly smooth, obviously having"
      + " been carved by living hands. Wooden racks line its surface.\n");
    add_item( ({ "wall", "walls" }),
        "The walls of this chamber are flat and fairly smooth. Clearly,"
      + " this room was carved by living hands. There appear to be"
      + " shapes carved into the walls to the north and south.\n");
    add_item( ({ "north", "north wall", "northern wall", 
                 "wall to the north" }),
        "The northern wall is somewhat smoother than most of the other"
      + " surfaces in this room. A shape has been cunningly carved into"
      + " the stone surface there, just above a row of barrels which"
      + " line the base of the wall.\n");
    add_item( ({ "barrel", "barrels", "row", "row of barrels",
                 "wooden barrel", "wooden barrels", "large barrel",
                 "large barrels", "large wooden barrel",
                 "large wooden barrels" }),
        "A long row of wooden barrels lines the base of the northern"
      + " wall here. Most of the barrels are without lid, and yet a"
      + " few remain closed.\n");
    add_item( ({ "lid", "lids", "barrel lid", "barrel lids",
                 "lid of the barrels", "lids of the barrels" }),
        "A few of the barrels are sealed with lids which are covered"
      + " with a thick layer of dust.\n");
    add_cmd_item( ({ "barrel", "barrels", "lid", "lids", "barrel lids",
                     "barrel lids", "wooden barrel", "wooden barrels" }),
                  ({ "open", "lift", "search" }),
        "Moving to more closely inspect the barrels, you remove the"
      + " lids from those which are sealed. All are empty, save one,"
      + " which seems to have become a home to a large family of"
      + " spiders.\n");
    add_item( ({ "spider", "spiders", "family", "large family",
                 "family of spiders", "large family of spiders",
                 "arachnid", "arachnids" }),
        "One of the barrels here is completely filled with spiders."
      + " Perhaps this is due to a recent hatching.\n");
    add_item( ({ "south", "south wall", "southern wall",
                 "wall to the south" }),
        "The southern wall is somewhat smoother than most of the other"
      + " surfaces in this room. A shape has been cunningly carved into"
      + " the surface there, just above a low line of shelves which rest"
      + " along the base of the wall.\n");
    add_item( ({ "shelf", "shelves", "line of shelves",
                 "wooden shelf", "wooden shelves" }),
        "The wooden shelves which line the southern wall are mostly"
      + " empty, except for the odd pile of dirt or forgotten tool."
      + " More than anything else, they now contain a great deal of"
      + " dust.\n");
    add_item( ({ "dirt", "pile", "pile of dirt", "dirt pile" }),
        "The dirt on the shelves is odd, considering that there is"
      + " no dirt at all on the floor of this chamber. Perhaps the"
      + " shelf once housed digging tools.\n");
    add_item( ({ "tool", "odd tool", "hammer", "rusted hammer",
                 "old hammer" }),
        "A single hammer lies on the shelves. It does not seem to"
      + " have survived well through the years, and looks as if it"
      + " would break upon a single stroke. It is covered with rust.\n");
    add_cmd_item( ({ "hammer", "rusted hammer", "old hammer", "tool" }),
                  ({ "get", "take", "use" }),
        "You pick up the hammer and quickly realize that it has"
      + " outlived its usefulness. You doubt that it would survive even"
      + " a single use without being destroyed. You place it back on"
      + " the shelf.\n");
    add_item( ({ "east", "passage", "passageway" }),
        "A passageway leads out of this chamber to the east. Its shape"
      + " suggests that it was carved out of the rock by living hands.\n");
    add_item( ({ "chamber to the east", "dark chamber to the east",
                 "grotto", "dark chamber" }),
        "A dark chamber lies to the east, connected to this room by a"
      + " passageway. Little can be seen from here of what lies in"
      + " that room.\n");
    add_item( ({ "floor", "ground", "down" }),
        "The floor of this chamber is rough, but even. It appears to have"
      + " been carved from the rock and leveled for walking ease. It"
      + " is covered by a thick layer of dust.\n");
    add_item( ({ "ceiling", "roof", "up" }),
        "The ceiling of this cave is roughly hewn from the rock. It is"
      + " basically flat, though has not been carved with the level of"
      + " care which went into the floor of this chamber.\n");
    add_item( ({ "stone", "rock", "stones", "rocks", 
                 "rock of the cliffs", "rock of the cliff" }),
        "The entire chamber has been carved out of the rock of the"
      + " cliffs.\n");
    add_item( ({ "shape", "shapes" }),
        "Shapes have been carved into the surface of both the northern"
      + " and southern walls. The north shape is above a row of barrels,"
      + " and looks different from the south shape, which is above a"
      + " line of shelves.\n");


    FIX_EUID

    add_item( ({ "north shape", "northern shape",
                 "shape on the north wall",
                 "shape on the northern wall" }), &display_shape(1));
    add_item( ({ "south shape", "southern shape",
                 "shape on the south wall",
                 "shape on the southern wall" }), &display_shape(2));
    add_item( ({ "figure", "figures", "tiny figure", "tiny figures",
                 "tiny carved figure", "tiny carved figures",
                 "hand", "hands" }),
        "Tiny figures have been carved into the rock beneath the shapes"
      + " on the walls to the north and south. The figures are in the"
      + " shape of a hand on both walls, and yet there is some"
      + " difference between the two.\n");
    add_item( ({ "finger", "fingers" }),
        "The fingers of the two figures are different from one another."
      + " The hand on the northern wall has its fingers pointing up,"
      + " while the hand on the southern wall has its fingers pointing"
      + " down.\n");
    add_item( ({ "north figure", "north hand", "northern figure",
                 "northern hand", "hand on the north wall",
                 "figure on the north wall" }),
        "The figure beneath the shape on the northern wall is of"
      + " a tiny hand with its fingers pointing up.\n");
    add_item( ({ "south figure", "south hand", "southern figure",
                 "southern hand", "hand on the south wall",
                 "figure on the south wall" }),
        "The figure beneath the shape on the southern wall is of"
      + " a tiny hand with its fingers pointing down.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    add_exit(DELRIMMON_DIR + "lakeside/caves/grotto_pool", "east");

    set_no_exit_msg( ({ "southeast", "south", "southwest", "west",
                        "northwest", "north", "northeast" }),
        "The walls of the chamber block your progress in that"
      + " direction.\n");
} /* create_del_rimmon */


/*
 * Function name:        display_shape
 * Description  :        show the player the shape which corresponds
 *                       to the emblem code they have been assigned.
 *                       Both the north and the south outpost shapes
 *                       are displayed using this function.
 * Arguments    :        int emblem - 1: the northern outpost code,
 *                                    2: the southern outpost code.
 * Returns      :        string - the shape displayed in text
 */
public string
display_shape(int emblem)
{
    int    combo;
    string   txt;

    txt = "The wall has a shape scratched into its surface.\n\n\n\n";

    MANAGER->assign_emblem_codes(this_player());

    if (emblem == 1)
    {
        combo = MANAGER->query_emblem_1(this_player());
    }

    else
    {
        combo = MANAGER->query_emblem_2(this_player());
    }

    switch(combo)
    {
        case 170:
            txt +=
              "          *********************\n"
            + "          *                   *\n"
            + "          *                   *\n"
            + "          *                   *\n"
            + "          *                   *\n"
            + "          *                   *\n"
            + "          *                   *\n"
            + "          *                   *\n"
            + "          *                   *\n"
            + "          *                   *\n"
            + "          *********************\n\n\n\n";
            break;
        case 85:
            txt +=
              "                    *\n"
            + "                  *   *\n"
            + "                *      **\n"     
            + "              **         **\n"
            + "            **             **\n"
            + "          **                 *\n" 
            + "         *                     *\n" 
            + "       *                         *\n"
            + "         *                     *\n" 
            + "           *                 **\n"
            + "            **             **\n"
            + "              **         **\n"
            + "                **      *\n"     
            + "                  *   *\n"
            + "                    *\n\n\n\n";
            break;
        case 41:
            txt +=
              "                    *\n"
            + "                   ***\n"
            + "                  ** **\n"       
            + "                 **   **\n"
            + "                 *     *\n"
            + "                *       *\n"
            + "               **       **\n"
            + "              **         **\n"     
            + "             **           **\n"
            + "             *             *\n"
            + "            *               *\n"
            + "           **               **\n"
            + "          *********************\n\n\n\n";
            break;
        case 82:
            txt +=
              "                             **\n"
            + "                         *****\n"
            + "                     ****   *\n"
            + "                 ****      **\n"
            + "            *****         **\n"
            + "       *****             **\n"         
            + "        **              **\n"
            + "          **           **\n"
            + "            **         *\n"
            + "              **      **\n"
            + "                **   **\n"            
            + "                  ****\n"
            + "                    *\n\n\n\n";
            break;
        case 164:
            txt +=
              "          ***\n"                   
            + "          *   ****\n"
            + "          *        ***\n"
            + "          *            ****\n"
            + "          *                 ***\n"
            + "          *                     **\n"
            + "          *                 ***\n"
            + "          *            ****\n"
            + "          *        ***\n"
            + "          *   ****\n"
            + "          ***\n\n\n\n"; 
            break;
        case 73:
            txt +=
              "                    *\n"
            + "                  ****\n"
            + "                **   **\n"
            + "              **      **\n"
            + "            **         *\n"
            + "          **           **\n"
            + "        **              **\n"
            + "       *****             **\n"
            + "            *****         **\n"
            + "                 ****      **\n"
            + "                     ****   *\n"
            + "                         *****\n"
            + "                             **\n\n\n\n";
            break;
        case 146:
            txt +=
              "          *********************\n"
            + "           **               **\n"
            + "            *               *\n"
            + "             *             *\n"
            + "             **           **\n"
            + "              **         **\n"
            + "               **       **\n"
            + "                *       *\n"
            + "                 *     *\n"
            + "                 **   **\n"
            + "                  ** **\n"
            + "                   ***\n"
            + "                    *\n\n\n\n";
            break;
        case 37:
            txt +=
              "                   *\n"
            + "                  ****\n"
            + "                 **   **\n"           
            + "                **      **\n"
            + "                *         **\n"
            + "               **           **\n"
            + "              **              **\n"
            + "             **             *****\n"
            + "            **         *****\n"
            + "           **      ****\n"
            + "           *   ****\n"
            + "          *****\n"
            + "         **\n\n\n\n";
            break;
        case 74:
            txt +=
              "                            ***\n"
            + "                       ****   *\n"
            + "                   ***        *\n"
            + "              ****            *\n"
            + "          ***                 *\n"
            + "       **                     *\n"
            + "          ***                 *\n"
            + "              ****            *\n"
            + "                   ***        *\n"
            + "                       ****   *\n"
            + "                            ***\n\n\n\n";
            break;
        case 148:
            txt +=
              "          **\n"                
            + "           *****\n"
            + "            *   ****\n"
            + "            **      ****\n"
            + "             **         *****\n"
            + "              **             *****\n"
            + "               **              **\n"
            + "                **           **\n"
            + "                 *         **\n"
            + "                 **      **\n"
            + "                  **   **\n"
            + "                   ****\n"
            + "                    *\n\n\n\n";
            break;
        case 138:
            txt +=
              "          *********************\n"
            + "            **                *\n"
            + "              **              *\n"
            + "                **            *\n"
            + "                  **          *\n"
            + "                    **        *\n"
            + "                      **      *\n"
            + "                        **    *\n"
            + "                          **  *\n"
            + "                            ***\n"
            + "                              *\n\n\n\n";  
            break;
        case 162:
            txt +=
              "          *********************\n"
            + "          *                **\n"
            + "          *              **\n"
            + "          *            **\n"
            + "          *          **\n"
            + "          *        **\n"          
            + "          *      **\n"
            + "          *    **\n"
            + "          *  **\n"
            + "          ***\n"
            + "          *\n\n\n\n";  
            break;
        case 168:
            txt +=
              "          *\n"
            + "          ***\n"
            + "          *  **\n"
            + "          *    **\n"
            + "          *      **\n"
            + "          *        **\n"              
            + "          *          **\n"
            + "          *            **\n"
            + "          *              **\n"
            + "          *                **\n"
            + "          *********************\n\n\n\n";
            break;
        case 42:
            txt +=
              "                              *\n"
            + "                            ***\n"
            + "                          **  *\n"
            + "                        **    *\n"
            + "                      **      *\n"
            + "                    **        *\n"
            + "                  **          *\n"
            + "                **            *\n"
            + "              **              *\n"
            + "            **                *\n"
            + "          *********************\n\n\n\n";
            break;
        default:
            txt += "ERROR: Please bugreport this to Gorboth.\n";
    } /* switch(combo) */

    return txt + "You notice a tiny figure carved beneath the shape.\n";
} /* display_shape */


/*
 * Function name:        do_stuff
 * Description  :        allow the player to try to mess with the"
 *                       shapes for Red Herring effect (?)
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
do_stuff(string arg)
{
    string *names = ({
        "shape",
        "shapes",
        "north shape",
        "northern shape",
        "shape on the north wall",
        "shape on the northern wall",
        "north wall",
        "northern wall",
        "wall to the north",
        "wall",
        "walls",
        "south shape",
        "southern shape",
        "shape on the south wall",
        "shape on the southern wall",
        "south wall",
        "southern wall",
        "wall to the south",
        "west wall",
        "western wall",
        "wall to the west",
                    }); /* we want to be syntax friendly */


    if (!strlen(arg))
    {
        notify_fail(CAP(QVB) + " what?\n");
        return 0;
    }
    arg = LOW(arg);

    if (!parse_command(arg, ({}),
        "[the] %p", names))
    {
        return 0;      /* bad arg */
    }

    if (!CAN_SEE_IN_ROOM(TP))
    {
        NFN0("You cannot see well enough to try that.");
    }

    if (names[0] == "shape" || names[0] == "shapes" ||
        names[0] == "wall"  || names[0] == "walls")
    {
        write("Which of them do you wish to " + QVB + "?\n");
        return 1;
    }

    if (QVB == "pull")
    {
        WRITE("You attempt to pull the "+names[0]+", but it does not"
            + " yield any obvious finger holds.");
        return 1;
    }

    if (QVB == "turn")
    {
        WRITE("There does not seem to be any way to turn the "
            + names[0] + ".");
        return 1;
    }

    if (QVB == "push" || QVB == "press")
    {
        WRITE("You give the "+names[0]+" a solid push, but it does"
            + " not budge.");
        return 1;
    } /* if (QVB == "push") */

    return 0; /* shouldn't ever happen */
} /* do_stuff */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_stuff, "push");
    add_action(do_stuff, "press");
    add_action(do_stuff, "pull");
    add_action(do_stuff, "turn");
} /* init */
