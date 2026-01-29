// ROOM:  Dome - Plateau, northern
//        DOME_ROOMS + plateau01

    /*  Calia Domain

        HISTORY
        1998-09-06 Created by Khon.

        PURPOSE
        This is the front end of the plateau upon which the
        pleasure dome resides. It has extensive gardens,
        plants chosen for thier beauty or perfumes to please
        the senses.

        AREA HISTORY
        This used to be a defensive position to resist attack,
        but the hedonists have long since torn down the 
        defensive works to plant this beautiful garden.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

// ROOM DEFINITION

void
create_room()
{

    /* DESCRIPTION */

    set_short("Plateau in the mountains");

    set_long("This is the northern end of small plateau in " +
        "the mountains. Brightly colored flowers of all kinds " +
        "draw the eye here, and exotic smells fill the air. " +
        "Groves of blossoming trees providing shade and " +
        "border flower-filled clearings. Dominating the scene " +
        "is a huge copper dome, green with verdigris. Obviously " +
        "old, the dome is in good repair and its gates are " +
        "open. The plateau ends north and east in sheer " +
        "mountain walls. It continues to the south, and a " +
        "trail leads down the cliff to the west.\n");

    /* ITEMS */

    add_item(({"dome", "copper dome"}),
        "Rising over fifteen meters into the air, this " +
        "impressive dome shaped building is made of fitted " +
        "copper plates. Huge double gates make up the front " +
        "entrance. Stained green with age, the dome is " +
        "majestic rather than rundown in appearance.\n");

    add_item(({"gate", "gates", "entrance", "double doors"}),
        "Two copper gates guard the entrance to the dome. " +
        "Over a foot thick, each two meters wide and three " +
        "meters high, these doors look unpenetrable without " +
        "seige equipment. They are currently open.\n");

    add_item(({"plateau", "ledge"}),
        "This a plateau, a clearing on a ledge in the side of " +
        "the mountains.\n");

    add_item(({"copper", "copper plates", "plates"}),
        "The dome has been built with carefully fitted " +
        "copper plates. The copper is dark coloured and " +
        "streaked with green from exposure to the air.\n");

    add_item(({"streaks", "green streaks", "verdigris"}),
        "The copper is dark coloured and streaked with " +
        "green from exposure to the air.\n");

    add_item(({"tree", "trees", "grove", "groves"}),
        "Poignant smells drift from briliantly blossoming " +
        "trees. Flawless in appearance, these trees are a " +
        "marvelous banquet for the eyes and nose. " +
        "Leafy branches provide pleasant shade, the trees " +
        "are spaced providing a continuous covered path " +
        "while ensuring the branches of one tree never touch " +
        "the branches of another.\n");

    add_item(({"shade", "suncover"}),
        "Pleasant shade is provided by the trees thick " +
        "folliage, connecting the groves and clearings " +
        "of the garden.\n");

    add_item(({"clearing", "clearings"}),
        "Low hedges combine with the groves of trees form " +
        "natural clearings in the garden, shaded and " +
        "smelling of flowers.\n");

    add_item(({"hedge", "hedges", "low hedges"}),
        "Close inspection of the hedges reveals them to be " +
        "low walls of stone totally overgrown with mosses, " +
        "flowers and grasses.\n");

    add_item(({"stone", "blocks"}),
        "The hedges are made of large blocks of hard stone, " +
        "similiar to those used to construct castle walls " +
        "and fortifications. Each block is one by one by " +
        "two meters in dimension, and the wall is made of single " +
        "blocks placed side by side. They have been here a " +
        "long time, and completely overgrown with " +
        "vegetation.\n");

    add_item(({"blossom", "blossoms"}),
        "Briliantly coloured flowers blossom on the trees. " +
        "Red, pink and white blossoms contrast pleasantly " +
        "with green leaves.\n");

    add_item(({"leaf", "leaves"}),
        "The leaves of the plants here are various shades " +
        "of healthy green.\n");

    add_item(({"flower", "flowers"}),
        "Reds, greens, blues and yellows mix with all shades " +
        "black and white to produce a vivid display of " +
        "coloured flowers. There are hundreds of varieties, " +
        "each with its own distinctive perfume.\n");

    add_item(({"mountains", "walls", "mountain walls"}), 
        "Sheer and formidable, the mountain walls to the " +
        "east and south are too smooth and steep to climb.\n");
 
    add_item(({"cliff", "cliffs"}), 
        "Sheer and formidable, the cliffs to the west are " +
        "too smooth and steep to climb save for a single " +
        "narrow trail leading down.\n");

    add_item(({"trail"}), 
        "A narrow trail leads down the otherwise impassable " +
        "cliffs to the west. There seems to be no other way " +
        "on or off the plateau.\n");

   /* TELLS */

     set_tell_time(80);

     add_tell("You hear the faint whinny of a horse.\n");
     add_tell("A chill mountain breeze blows against you.\n");
     add_tell("You hear a faint sound of falling rocks.\n");

    /* EXITS */

    add_exit("trail03", "west", 0, 05);
    add_exit("plateau02", "south", 0, 01);
    add_exit("entrance", "east", 0, 01);

    /* PROPERTIES */

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_HIDE, 10);

    }
