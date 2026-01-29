/*
 * This file file contains all the common items Thalandrone
 * such as houses, arches, bridges, etc.. 
 * This way these routines aren't  spread over several files 
 * and makes maintaining these routines much easier.
 *
 * To use any of these routines, this file must be inherited 
 * by the base file, then simply call the routine(s) within 
 * the room definition.
 *
 * Example:

    void
    create_road_room()
    {

        set_add_houses("They are two storied and made of brick " +
            "and appear well kept. ");
    }
    
 * To pass nothing to the routine, simply pass "" in place of text.
 * By Finwe, July 2001
 */
 
#include "/d/Shire/cypress/sys/defs.h"
#include "local.h"
inherit AREA_ROOM;
inherit "/cmd/std/command_driver";
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>


/*
 * Each of these variables defines the respective
 * set_ routine within this file. To create a new 
 * routine, define it here.
 */

static string add_all_rooms = "",
              add_trees = "",
              add_forest_debris = ""
              ;


/*
 * Function name : set_add_all_rooms
 * Arguments     : str: none
 * Description   : adds standard items to all rooms.
 */
void set_add_all_rooms()
{
    add_item(({"stone blocks", "white stone blocks"}),
        "The white stone blocks are hewn of white marble. They " +
        "are very large and perfectly square. Some are used to " +
        "make the avenues that criss-cross while polished stone " +
        "blocks are used to make the countless buildings of the " +
        "city.\n");
    add_item(({"gardens",}),
        "They surround various buildings and are of different " +
        "sizes. They are works of art showing the skills of the " +
        "elves.\n"); 
    add_item(({"ivy", "ivies"}),
        "The ivy is ancient and grows over the buildings. " +
        "Despite its age, it looks very young and healthy.\n");
    add_item(({"ivy leaf", "ivy leaves"}),
        "The leaves of the ivy vary in shape. They are heart, " +
        "curly, fan, bird's foot, typical shaped leaves. Some " +
        "of the plants have green and white leaves which " +
        "contrast with the rest of the plants and buildings.\n");
    add_item(({"ancient trees"}),
        "The ancient trees appear to be the oldest living plant. " +
        "They are giant whose crowns seem hidden in the sky. " +
        "Their branches stretch out, shading everything beneath " +
        "them. In the very ancent trees, lights twinkle above.\n");
    add_item(({"lights", "twinkling lights"}),
        "The twinkling lights shine from high in the ancient trees.\n");
    add_item(({"forest", "woods", "ancient forest", "ancient woods"}),
        "The ancient forest surrounds the city of Thalandrone. " +
        "It is ancient looking and seems to be the ancestral " +
        "home of elves. Various trees of different ages grow in " +
        "the forest, from young saplings to ancient trees. They " +
        "all look cared for and in perfect health.\n");
    add_item(({"saplings", "new trees", "young trees"}),
        "The saplings are recently planted. They look healthy " +
        "and perfect.\n");
    add_item(({"trees", "tree"}),
        "The trees of the forest is made up of many different " +
        "trees. The most common are beech, maple, and oak. Many " +
        "of them look ancient, as if they have been cared for by " +
        "the elves for many millenia. Some of the trees are so " +
        "large that they house homes within their branches.\n");
    add_item(({"ancient oak trees", "ancient oaks", "oak trees", "oak"}),
        "The ancient oak trees tower over everything in " +
        "Thalandrone. Their branches are ancient and covered " +
        "with large, green, serrated leaves. Their trunks are " +
        "gray and white in color and very thick.\n");
    add_item(({"ancient beech trees", "ancient beech", 
            "beech trees", "beech"}),
        "The trees are tall and ancient looking. They are " +
        "covered with a multitude of green leaves that rustle in " +
        "the wind. Their trunks are smooth and large, silver " +
        "colored, and surprisingly smooth looking.\n");
    add_item(({"ancient maples", "ancient maple trees", 
            "maple trees", "maples"}),
        "The ancient maple trees are giants in the forest. Their " +
        "trunks are large with age, and rough looking. Their " +
        "large branches grow out and upwards and are covered " +
        "with many large, green leaves.\n");
    add_item(({"fountains", "fountain"}),
        "The fountains are lovely and full of a life all their " +
        "own. Each are a work of art and are diverse in their " +
        "shape and styles. Some are multi-level bowls with water " +
        "that pours over their edges into large bowls. Other " + 
        "fountains are basins with water spraying up. Still " + 
        "other fountains imitate brooks with water bubbling over " +
        "stones. They all contribute to the relaxing musical " +
        "sounds that fill Thalandrone.\n");
}

/*
 * Function name : set_add_trees
 * Arguments     : str: none
 * Description   : adds standard items to all rooms.
 */
void set_add_trees()
{
    add_item(({"ancient trees"}),
        "The ancient trees appear to be the oldest living plant. " +
        "They are giant whose crowns seem hidden in the sky. " +
        "Their branches stretch out, shading everything beneath " +
        "them.\n");
    add_item(({"forest", "woods", "ancient forest", "ancient woods"}),
        "The ancient forest surrounds the garden. " +
        "Various trees of different ages grow in " +
        "the garden from young saplings to ancient trees. They " +
        "all look cared for and in perfect health.\n");
    add_item(({"saplings", "new trees", "young trees"}),
        "The saplings are recently planted. They look healthy " +
        "and perfect.\n");
    add_item(({"trees", "tree"}),
        "The trees of the forest are made up of many different " +
        "species. The most common are beech, maple, and oak. Many " +
        "of them look ancient, as if they have been cared for by " +
        "the elves for many millenia.\n");
    add_item(({"ancient oak trees", "ancient oaks", "oak trees", "oak"}),
        "The ancient oak trees tower over everything in " +
        "the forest. Their branches are ancient and covered " +
        "with large, green, serrated leaves. Their trunks are " +
        "gray and white in color and very thick.\n");
    add_item(({"ancient beech trees", "ancient beech", 
            "beech trees", "beech"}),
        "The trees are tall and ancient looking. They are " +
        "covered with a multitude of green leaves that rustle in " +
        "the wind. Their trunks are smooth and large, silver " +
        "colored, and surprisingly smooth looking.\n");
    add_item(({"ancient maples", "ancient maple trees", 
            "maple trees", "maples"}),
        "The ancient maple trees are giants in the forest. Their " +
        "trunks are large with age, and rough looking. Their " +
        "large branches grow out and upwards and are covered " +
        "with many large, green leaves.\n");
    add_item(({"branches", "branch"}),
        "The branches of the trees are of various sizes, ranging " +
        "from very thick and ancient to young and thing. They " +
        "are covered with leaves, which often rustle in the wind.\n");
}

/*
 * Function name : set_add_trees
 * Arguments     : str: none
 * Description   : adds standard items to all rooms.
 */
void set_add_forest_debris()
{
    add_item(({"ground", "forest debris", "debris", 
        "forest's floor", "floor", "down"}),
        "Beneath the trees, the ground is littered with dead branches, pine needles, and some fallen trees.\n");
    add_item(({"fallen leaves", "dead leaves"}),
        "You see a mat of both fresh and dead leaves covering the " +
        "ground. Poking out of them are dead branches, some " +
        "plants, stones, and other signs of a living forest.\n");
    add_item(({"fallen branches", "dead branches", "dead branch"}),
        "They are broken and lay scattered across the ground. " +
        "Some look like they just fell from the trees. They lay " +
        "on the ground in various stages of decomposition.\n");
    add_item(({"twig", "twigs"}),
        "They are small branches, laying scattered across the " +
        "forest's floor.");
    add_item(({"fallen trees", "fallen tree", "dead trees", 
        "dead tree"}),
        "Some fallen trees lay rotting under a blanket of fallen " +
        "leaves, branches, and forest debris.\n");
    add_item(({"log", "logs", "rotting log", "rotting logs"}),
        "The rotting logs are in various forms of decomposition. " +
        "Some are hollowed out and look to be homes for " +
        "woodland animals.\n");
    add_item(({"hollow logs", "hollow log"}),
        "The logs are rotting and hollowed out. Most of them " +
        "are partially buried in the ground or under the forest " +
        "debris.\n");

}