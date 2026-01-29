/*
 * File:    hall_lower_north.c
 * Creator: Cirion, 1998.05.02
 * Purpose: Entrance hall to the monks guild
 */
#pragma strict_types
#pragma strict_types

// since this is a guild room, save the binary of the file
// to facilitate quick loading after reboots
#pragma save_binary

#include "defs.h"
#include <language.h>
#include <composite.h>

inherit ROOMBASE;

string fresco_desc();

void
create_room ()
{
    set_short("great hall north");
    set_long("Two great pillars of luminous green nephrite "
        + "frame the massive double wooden doors that "
        + "open to the outside. The high ceiling of "
        + "this hall is made from a lattice of dark "
        + "metal, through which pale sunlight filters "
        + "and forms dappled patterns upon the floor. "
        + "Square tiles of rough stone make up the floor, "
        + "arranged with great precision. The hall continues "
        + "to the south. Through a wide archway "
        + "to the west, you can see many shelves lined "
        + "with tomes and scrolls. A narrower doorway "
        + "in the eastern wall opens onto a large spiral "
        + "stairwell that extends up and out of sight. "
        + "Inset into the east and west walls are tall "
        + "empty niches. "
        + fresco_desc()
        + living_view("hall_lower_south", " Standing in the south "
        + "great hall, "
        + "you see ", ".", "")
        + "\n");
    add_prop(ROOM_I_INSIDE, 1);


    add_item(({"pillar","pillars"}),"The pillars are enormous, "
        + "reaching up to the "
        + "grand heights of the ceiling. They are "
        + "made from nephrite, a "
        + "common, dull green jade, and their "
        + "polished surface is "
        + "unadorned.\n"
        + VBFC_SAY("looks up at the grand nephrite pillars.\n"));
    add_item(({"ceiling","lattice"}),"The ceiling high above your "
        + "head is made from "
        + "a dark iron lattice, allowing pale "
        + "sunlight to filter through and "
        + "make dappled patterns of yellow and "
        + "white on the cold stone floor.\n"
        + VBFC_SAY("peers up at the lattice that makes up the ceiling.\n"));
    add_item(({"floor","tile","tiles","ground","stone"}),"The "
        + "square tiles "
        + "that make up the floor are rough stone, "
        + "fitted together evently "
        + "and with great care. The stone, although "
        + "rough, is worn down "
        + "by the passage of many feet over the years.\n"
        + VBFC_SAY("stoops down to examine the stone tiles "
        + "that make up the floor.\n"));
    add_item(({"archway","library","west"}),"To the west is a wide stone archway, "
        + "composed of the same rough stone that makes up the floor. The arch is "
        + "is adorned with bas relief images of books and scrolls. Through the "
        + "archway you can see a large library, whose shelves are populated "
        + "with scrolls and tomes.\n"
        + VBFC_SAY("peers east through the archway.\n"));
    add_item(({"tomes","scrolls","tome","scroll","book","books",
        "shelves","shelf"}),"You cannot make out any details of the library "
        + "from here.\n");
    add_item(({"door","doorway"}),
        "It is a massive, curved wooden arch that leads out "
        + "to the windy lawn to the north. Its frame appears "
        + "to have once held strong doors, long since "
        + "removed.\n");

    add_cmd_item(({"stone","stones","tile","tiles","ground"}),
        ({"touch","feel"}),
        "The stones of the floor are smooth with the passage of many feet.\n"
        + VBFC_SAY("reaches down and touches the stone tiles.\n"));

    WIZINFO("This room is the entrance hall to the monks guild.\n");

    // where, command
    add_exit("hall_lower_south", "south");
    add_exit("library", "west");
    add_exit("stair_lower", "east");
    add_exit("lawn_ne", "north");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("south", "You pass along the great hall, "
        + "your footfalls making "
        + "no noise on the smooth stone underfoot.\n");
    ENTRANCE_MSG("east", "You walk out of the stairwell "
        + "into the great hall.\n");
    ENTRANCE_MSG("west", "You pass through the archway "
        + "into the great hall.\n");
    ENTRANCE_MSG("north", "You enter the great hall.\n");

    // when someone arrives, we tell people in WHERE MESSAGE
    VIEW_ENTRANCE("hall_upper_north", "You see movement through "
        + "the grille floor in the great hall below.\n");

    m_clone_here(MONK_NPC + "regliak");
}

string
fresco_desc()
{
    string *names;
    int     i;
    string  str;
    string  *descs = ({});

    names = m_list_council_members();

    if(sizeof(names) <= 0)
        str = "The walls are grey and unadorned.";
    if(sizeof(names) == 1)
        str = "There is a single coloured fresco on the east wall.";
    else
        str = "There are " + LANG_WNUM(sizeof(names)) + " colourful "
            + "frescos between the "
            + "niches along the east and west walls.";


    for(i = 0; i < sizeof(names); i++)
    {
        descs += ({ m_query_council_desc(names[i]) });

        add_item(({ "fresco", names[i],
            capitalize(names[i]), ("fresco " + (i + 1)),
            (LANG_WORD(i + 1) + " fresco") }),
            "It is a colorful fresco, depicting "
            + m_query_council_desc(names[i]) + ".\nBelow the "
            + "fresco is inscribes in light etching: "
            + capitalize(names[i]) + ".\n");
    }

    if (sizeof (descs) > 0)
        add_item ("frescos", "There are " + LANG_WNUM(sizeof(names))
            + " frescos adorning the wall, showing the images of "
            + COMPOSITE_WORDS (descs) + ".\n");

    return str;
}

