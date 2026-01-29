// ROOM:  Dome - trail, middle
//        DOME_ROOMS + trail02

    /*  Calia Domain

        HISTORY
        1998-09-06 Created by Khon.

        PURPOSE
        This is the middle of a small trail leading up to
        the mountain plateau.

        AREA HISTORY
        This used to be a small road, but lack of maintainance
        has reduced it to a trail. It's still in use, however.
    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room.c";

#include "defs.h"
#include <stdproperties.h>
// ROOM DEFINITION

void
create_room()
{

    /* DESCRIPTION */

    set_short("Middle of pleasure trail");

    set_long("To be determined.\n");

    /* ITEMS */

    add_item(({"forest", "tree", "trees"}),
        "This is a faint trail running east-west through the " +
        "great forest. The trees grow thick and tall, mostly " +
        "oak and other hardwoods. Bushes and vines make it hard " +
        "to travel anywhere off the trail.\n");

    add_item(({"underbrush"}), 
        "Bushes, vines, tall grass, ferns and moss all grow " +
        "densely here. Small game and birds seem plentiful.\n");

    add_item(({"bushes", "bush"}), 
        "Numerous species of bush thrive here, competing for " +
        "the nutrient rich soil. Some of the larger bushes " +
        "resemble small trees themselves. Many are covered with " +
        "vines, most have thorns.\n");

    add_item(({"ferns", "fern"}), 
        "Ferns of all shapes and sizes grow here, their green " +
        "fronds shading the ground and moving slightly in any " +
        "breeze.\n");

    add_item(({"mosses", "moss"}), 
        "Spongy mosses of all colours cover the ground and many " +
        "trees. Moist and filled with stems and mushrooms, they " +
        "are a tiny world in themselves, filled with insect " +
        "life.\n");
 
   add_item(({"vines", "vine"}), 
        "Vines here are plentiful and widely varied. They wind " +
        "around trees and even bushes, clinging tightly and " +
        "perhaps even strangling thier hosts. One of the more " +
        "common creepers is a dark green plant, with five " +
        "leaves and beautiful red blossoms speckled with black" +
        ".\n");

   /* TELLS */

     set_tell_time(80);

     add_tell("You hear the wind rustle through the leaves.\n");
     add_tell("A chill mountain breeze blows against you.\n");
     add_tell("You hear the faint sound of falling rocks.\n");

    /* EXITS */

    add_exit("trail01", "southwest", 0, 20);
    add_exit("trail03", "east", 0, 25);

    /* PROPERTIES */

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_HIDE, 10);

    }
