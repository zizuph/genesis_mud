/*
 * /d/Shire/moria/eastgate/std/base.c
 *
 * This is the base room for the eastern parts of Moria.
 *
 * Rogon did lots of wonderful stuff in the western part of
 * Moria which was first opened decades ago, but quite
 * frankly, his stuff probably worked great for him but it
 * is a mess for me to go through. So... I'm not going to
 * use it.
 *
 * Varian - April, 2020
 *
 */

#include "../defs.h"

inherit EG_STD + "room";

inherit "/d/Gondor/common/lib/room_tell";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <macros.h>

#define LVL1 "You are on the first level inside Moria."

void set_items_passage();
void set_items_chamber();
void set_items_mine();
void set_items_window();
void set_items_firsthall();

/*
 * Function name:        create_eg_room
 * Description  :        Use create_eg_room() to make rooms in the
 *                       eastern parts of Moria which use 
 *                       information from this file
 */
void create_eg_room() 
{
}

nomask void create_eastgate_room() 
{
    /*gmcp_room_id = ""*/
    create_eg_room();

    add_item( ({"moria", "dwarrowdelf", "khazad dum", "khazad-dum",
            "hadhodrond", "the dwarrowdelf", "casarrondo",
            "phurunargian", "black chasm", "the black chasm",
            "black pit", "the black pit"}),
        "@@moria@@");

    reset_room();
}

/*
 * Function name:        set_items_passage
 * Description  :        Items added to passages in the eastern
 *                       parts of Moria when you include the line
 *                       set_items_passage(); in the room.
 *                       *** MUST DESCRIBE ROOM LONG DESCRIPTION IN
 *                       A STRING DEFINED AS DESC!!! ***
 */
void
set_items_passage()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_S_DARK_LONG,
                "You are in one of the dark passages which tunnel " +
                "through Moria.\n");

    add_item( ({"hallway", "corridor", "hall", "here", "passage", 
            "tunnel"}),
        "@@desc@@");
}
/* set_items_passage */

/*
 * Function name:        set_items_chamber
 * Description  :        Items added to chamber rooms in the eastern
 *                       parts of Moria when you include the line
 *                       set_items_chamber(); in the room.
 *                       *** MUST DESCRIBE ROOM LONG DESCRIPTION IN
 *                       A STRING DEFINED AS DESC!!! ***
 */
void
set_items_chamber()
{
    add_item( ({"room", "here", "chamber"}),
        "@@desc@@");
}
/* set_items_chamber */

/*
 * Function name:        set_items_mine
 * Description  :        Items added to mining rooms in the eastern
 *                       parts of Moria when you include the line
 *                       set_items_mine(); in the room.
 *                       *** MUST DESCRIBE ROOM LONG DESCRIPTION IN
 *                       A STRING DEFINED AS DESC!!! ***
 */
void
set_items_mine()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -3);
    add_prop(ROOM_S_DARK_LONG,
                "You are somewhere in the dark mines of Moria, " +
                "it is too dark here to see anything.\n");

    add_item( ({"room", "here", "mine"}),
        "@@desc@@\n");
}
/* set_items_mine */


/*
 * Function name:        set_items_window
 * Description  :        Items added to rooms with windows in the eastern
 *                       parts of Moria when you include the line
 *                       set_items_window(); in the room.
 *                       MUST BE THE LAST SET DECLARED IN THE ROOM!!!
 */
void
set_items_window()
{
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    add_item( ({"outside", "sky"}),
        "Looking through the open windows, you can see the outisde.\n");
}
/* set_items_window */

/*
 * Function name:        set_items_firsthall
 * Description  :        Items added to rooms in the first hall
 *                       of Moria when you include the line
 *                       set_items_firsthall(); in the room.
 */
void
set_items_firsthall()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_S_DARK_LONG,
                "You are somewhere in the First Hall of Moria, " +
                "however the light from the windows does not " +
                "reach this far.\n");

    add_item( ({"gate", "main gate", "east gate"}),
        "The east gate is here.\n");
    add_item( ({"statue", "statues", "broken statue",
            "broken statues"}),
        "@@statue_first@@");
    add_item( ({"relief", "reliefs", "broken relief",
            "broken reliefs"}),
        "@@relief_first@@");
}
/* set_items_firsthall */



/*
 * Function name:        moria
 * Description  :        Description of Moria
 */
string
moria()
{
    string moria_desc = "";

    if (this_player()->query_skill(SS_MORIA_LORE) > 98)
        moria_desc += "You are in Khazad-dum, the Dwarrowdelf, " +
        "greatest of all dwarven mansions. Now it is simply known as " +
        "the Black Pit, or as it is translated in the elven " +
        "tongue - Moria.\n\nDurin the Deathless himself delved deep " +
        "in the Misty Mountains, carving out dozens of great halls. " +
        "They spread across the seven levels above the First Hall " +
        "(where Durin began building Khazad-dum) and the seven " +
        "deeps which were below these halls formed the heart of the " +
        "greatest and wealthiest city Middle-Earth has ever known.\n" +
        "\nIt was here that the dwarves found Mithril, and mining " +
        "too deep, in their greed they also awoke Durin's Bane which " +
        "slew the dwarves and destroyed the city. These are its " +
        "ruins, and any who enter and wander the ancient halls must " +
        "beware.";
    else
        moria_desc += "What?";
    return (moria_desc + "\n");
}
/*moria*/

/*
 * Function name:        relief_first
 * Description  :        Statue description
 */
string
relief_first()
{
    string relief_desc = "Carved into the very walls of ";

    if (this_player()->query_skill(SS_MORIA_FIRST & SS_MORIA_LORE) > 99)
        relief_desc += "the First Hall ";
    else
        relief_desc += "this ancient hall ";

    relief_desc += "you see the remains of beautiful, polished " +
        "reliefs. Masterful images of ";

    if (this_player()->query_skill(SS_MORIA_FIRST & SS_MORIA_LORE) > 99)
        relief_desc += "Khazad-dum in its days of glory, Durin's " +
        "folk enjoying their riches before the fall. ";
    else
        relief_desc += "large chambers filled with dwarves are " +
        "depicted clearly here. ";

    relief_desc += "Yet the reliefs are broken and scarred now, " +
        "much of their beauty lost forever.";

    return (relief_desc + "\n");
}
/*relief_first*/

/*
 * Function name:        statue_first
 * Description  :        Statue description
 */
string
statue_first()
{
    string statue_desc = "Several statues, once magnificent and " +
        "beautiful, line the walls of ";

    if (this_player()->query_skill(SS_MORIA_FIRST & SS_MORIA_LORE) > 99)
        statue_desc += "the First Hall ";
    else
        statue_desc += "this ancient hall ";

    statue_desc += "in broken, scarred pieces. The statues were ";

    if (this_player()->query_skill(SS_MORIA_FIRST & SS_MORIA_LORE) > 99)
        statue_desc += "depicting Durin's folk, the Lords of " +
        "Khazad-dum, yet ";
    else
        statue_desc += "depicting what you think might be some " +
        "dwarves, but it is hard to tell and ";

    statue_desc += "now they are forever descrated.";

    return (statue_desc + "\n");
}
/*statue_first*/