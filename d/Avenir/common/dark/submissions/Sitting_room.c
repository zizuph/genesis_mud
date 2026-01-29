/*
 * File:          /d/Avenir/common/dark/submissions/Sitting_room.c
 * Creator:       Caw
 * Date:          Fri Mar  5 01:38:17 1999
 * Note:          This room was auto-generated using
 *                the room creator module inherited by
 *                /d/Avenir/common/dark/mon/foreman#35855
 * Comments:      
 *                This is in response to a idea report I put in
 *                concerning an informal sitting room for in
 *                the Halls of the Union of Shadow Warriors.
 *                The table should be a container similar to
 *                that in the case room. Perhaps with a bowl
 *                that could hold foodstuffs, and goblets such
 *                as those used in the case rooms table as
 *                well. And a pitcher of water, and perhaps
 *                another of a fruit or berry punch and
 *                goblets. That can be filled with water from
 *                the astuary like the goblets, but can hold
 *                much more and be used to refill the goblets.
 *                The pitcher with punch is for those who want
 *                something with more flavor then water but
 *                dislike kahve, perhaps Goatfeathers could
 *                sell the same thing and we could refill the
 *                pitcher there. Or perhaps the table could
 *                also be used to play games, there is a card
 *                game called Lansquenet. Which would be
 *                fitting for its name come from the same
 *                source that some of our titles come from.
 *                And of course the cushions can be sat in
 *                like those in Goatfeathers. The black tile
 *                could be used to open another hidden
 *                entrance should one ever be needed for
 *                adding a secret room. If you feel this room
 *                doesn't fit in the Halls feel free to use it
 *                elsewhere, Perhaps a hunting lodge on the
 *                holm.
 */
#include "defs.h"
inherit "/std/room";

void
create_room ()
{
    set_short("Sitting room");
    set_long("This room is softly lit with dimly glowing crystal "
        + "veins that streak the walls and ceiling. The "
        + "walls are unworked, but they has a soft look to "
        + "them as if the rough edges have been removed with "
        + "water. The ceiling is rather low, being just a "
        + "little over the head of an average sized elf. The "
        + "floor  nearly disorients you at first it seems to "
        + "be that you are floating above a bank of gray "
        + "mists, but then you realize that the floor is "
        + "indeed stone and quite solid.  Several soft "
        + "cushions are scattered about the floor, most are "
        + "centered about a low table in the center of the "
        + "room.\n");

    add_item(({"walls"}),
        "The walls are a dark flat gray stone that seem to "
        + "absorb the light helping keep the room to a "
        + "comfortable light level for relaxing. They "
        + "haven't been worked except by nature giving them "
        + "an irregular but soft surface.\n");
    add_item(({"ceiling"}),
        "There isn't truly a ceiling as the walls simply "
        + "arch around and merge with one another creating a "
        + "natural dome. The lowness of it creates a "
        + "comfortable feel when combined with the other "
        + "features of the room.\n");
    add_item(({"floor","mist","mists"}),
        "This floor is a marvel, it appear as if you are "
        + "floating on a bank of mists. The effect has been "
        + "created by carefully arranging millions of small "
        + "gray tiles of various shades of gray.\n");
    add_item(({"crystal","crystals"}),
        "Thin veins of a dull glowing crystal illuminate "
        + "this cavern with a soft indigo colored light.\n");
    add_item(({"tiles"}),
        "You notice one tile near the back corner is "
        + "completely black and circular, it's the only "
        + "non-gray tile on the whole floor.\n");
    add_item(({"black tile"}),
        "This tile is located near the rear of the room and "
        + "is cut from obsidian into a perfect circle.\n");
    add_item(({"cushions"}),
        "Crafted from black webcloth and filled with an "
        + "unknown substance that's soft but firm, these "
        + "cushions make for comfortable seating.\n");
    add_item(({"table"}),
        "The table is carved from a single piece of wood "
        + "and lacquered in shades of gray to blend with the "
        + "floor. It sits low to the floor on  four legs "
        + "that are intricately carved.\n");
    add_item(({"legs"}),
        "The legs of the table appear to be slaves crouched "
        + "down supporting the table on their backs.\n");
    add_item(({"slaves"}),
        "The slaves are on their knees each facing out from "
        + "the corner that they support. They appear to have "
        + "a look of pride on their face.\n");
    add_cmd_item(({"tile","circle"}),
        ({"push","press","mash"}),
        "You push the tile but nothing happens.\n");
    add_cmd_item(({"crystal","crystals"}),
        ({"touch","feel"}),
        "The crystals are smooth and cool.\n");


}
