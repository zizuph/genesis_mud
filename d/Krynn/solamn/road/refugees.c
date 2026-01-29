/* Aridor, 08/98 */

#include "local.h"

inherit ROOM_BASE

void
create_road_room()
{
    if (LOAD_ERR(ROAD_OBJECT))
    {
        write("Bug! please report immediately.\n");
	return;
    }
 
    set_short("@@my_short@@");
    set_long("@@my_long@@");
    
    add_item(({"people", "refugees"}), "@@refugee_desc@@");
    add_item(({"grass"}), "The grass grows well in the " +
        "rich soil of Solamnia.\n");
    add_item(({"shrub", "shrubs", "tree", "trees"}), "The shrubs and " +
        "trees have a peculiar slanted look to them, due to the heavy " +
        "winds that blow across the open plains.\n");
    add_item(({"plains", "plains of solamnia"}), "Spreading out before " +
        "you as far as the eye can see are the Eastern Plains of " +
        "Solamnia.\n");

    add_exit("", "west", "@@enter_map:" + ROAD_OBJECT + "|R@@",6,1);
    add_exit("", "east", "@@enter_map:" + ROAD_OBJECT + "|R@@",6,1);
    add_exit("", "south","@@enter_map:" + ROAD_OBJECT + "|R@@",6,1);
    add_exit("", "north","@@enter_map:" + ROAD_OBJECT + "|R@@",6,1);  
}

/* Are there refugees here? OLD: Yes, if the occupying army is a DragonArmy.
 * Yes, if the occupying army is evil aligned.
 * No, otherwise.
 */

int
refugees_there()
{
    string occ_army = ARMYMASTER->army_in_area("Eastern Solamnian Plains");
    return ARMYMASTER->army_alignment(occ_army) < 0;
    /*return wildmatch("*Dragon Army*", occ_army);*/
}

string
my_short()
{
    if (refugees_there())
        return "At a refugee camp";

    return "A clearing on the plains";
}

string
my_long()
{
    if (refugees_there())
        return "This is a clearing on the Plains of Solamnia. A " +
            "number of people have gathered here. They look tired, " +
            "worn and frightened.\n";

    return "This is a clearing on the Plains of Solamnia. It is " + 
        "an open place covered with grass and surrounded by some " +
        "shrubs and trees.\n";
}

string
refugee_desc()
{
    if(refugees_there())
        return "These people look dirty and tired. Most of them " +
            "have a frightened look in their eyes.\n";

    return "The plains are rather desolate now.\n";
}

