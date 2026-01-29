
/*
 * st5.c
 * Main street of the town of haven
 * Tibbit, 4 March 1998
 *
 */

#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

inherit HAVENBASE;

#define MINIMUM_SPELLCRAFT 39

void
create_haven()
{
    add_my_desc(
        "This is the southern end of the town of Haven. "+
        "The main street heads north from here, passing through "+
        "the center of town. Two modest wooden homes are "+
        "just east and west of here. "+
        "To your northeast is a building, largely hidden from view " +
        "by oak trees and a high stone wall. A small sign has been " +
        "attached above the door to the building.\n");

    add_exit(HROOM+"st4","north");
    add_exit(HROOM+"mageware_shop","northeast","@@enter_shop");
    add_exit(HROOM+"home2","west");
    add_exit(HROOM+"home1","east");

    add_item(({"town","city","haven"}),
        "The town of Haven is not very large, but the townspeople "+
        "seem to be doing all right for themselves.\n");
    add_item(({"street","main street"}),
        "The one major street of Haven heads north from here.\n");
    add_item(({"hall","town hall"}),
        "Near the center of Haven "+
        "stands a simple town hall, made from unfinished wood. "+
        "It is just off to the north of here.\n");
    add_item(({"home","homes"}),
        "A few simple wooden homes stand along Haven's main road, "+
        "especially at this, the southern end of the town.\n");
    add_item(({"temple"}),
        "The temple of the Seekers, the religious men who handle the "+
        "affairs of this town, is the mightiest building in "+
        "Haven. Made from wood and from brick which must have been "+
        "imported from a respectable distance, the large building "+
        "is painted entirely white, and stands out as the tallest, "+
        "most noticeable thing in the town.\n");
    add_item(({"building","shop","mageware shop"}),
        "Hidden largely from view by oak trees and a high stone wall " +
        "is a building with a small sign attached above the door that " +
        "looks like the image of a huge white eye with a black pupil " +
        "and a red iris.\n");
    add_item(({"sign","small sign","eye","huge white eye","white eye",
               "black pupil","red iris"}),"@@exa_sign"); 
    add_item(({"trees","oak trees"}),
        "Oak trees largely hide a building to your northeast.\n");
    add_item(({"wall","high stone wall","stone wall","garden",
        "well-tended garden"}),"Surrounding the building to your " +
        "northeast is a high stone wall. Looking over it, you see " +
        "a well-tended garden.\n");

}

int
enter_shop()
{
    write("You step in to the darkness of Lemuel's Mageware shop.\n");
    return 0;
}

string
exa_sign()
{
    if(this_player()->query_skill(SS_SPELLCRAFT) > MINIMUM_SPELLCRAFT)
    {
      return "Upon the sign is the symbol of a huge white eye with a " +
        "black pupil and a red iris. Being skilled in spell lore, you " +
        "recognise this as the Night of the Eye - " +
       "a symbol of that singular event where the three moons of magic " +
       "align. It is also a symbol to alert practitioners of magic that " +
       "within this building can be purchase mageware equipment.\n";
    }
      return "Upon the sign is the symbol of a huge white eye with a " +
        "black pupil and a red iris. You are not sure what that means.\n";
}


