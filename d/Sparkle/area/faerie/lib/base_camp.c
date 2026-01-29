/*
 * Base file for orc camp in Faerie
 * By Finwe, August 2004
 */

#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/room";
inherit S_LIB_CLOCK;
inherit COMMON_BASE;

void create_camp_room() {}
void set_add_mountain();
//int up_tree();
//void down_tree();

// tower_num is assignedin the room that leads into a tower or exits out to the camp
string tower_num = "Bad tower num. Please report this to a wizard.";


public void
create_room()
{
    setuid(); 
    seteuid(getuid());

    create_camp_room();
    reset_faerie_room();

    s_item_sky_outside();

    set_add_mountain();

    add_prop(ROOM_S_MAP_FILE, "faerie_map.txt");

    add_item(({"conifer", "conifer trees", "conifers", "evergreen",
            "evergreen tree", "evergreen trees", "evergreens", "fir",
            "fir tree", "fir trees", "firs", "tall evergreen tree",
            "tall evergreen trees", "tall fir tree", "tall fir trees",
            "tall trees", "trees"}),
        "The trees are huge and stand in the distance. They surround the camp " +
        "and muffle the sounds of the orcs.\n");

    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room

}

/*
 * Function name : set_add_mountain
 * Description   : adds descr of mountains in the forest
 */
void set_add_mountain()
{
    add_item(({"mountain", "mountains"}),
        "The mountains are extremely tall. The tallest peaks are hidden " +
        "in the clouds and are snow capped. The lesser peaks of the " +
        "mountains are jagged and covered by trees. \n");
    add_item(({"peaks", "mountain peaks"}),
        "The mountain peaks are jagged and various sizes. The tallest " +
        "peaks are buried in the clouds while the lesser ones are " +
        "draped with trees.\n");
    add_item(({"snow"}),
        "It is white and covers the tallest peaks of the mountains. " +
        "It glistens in the light.\n");
    add_item(({"tallest peaks"}),
        "They are jagged and are hidden in the clouds. They look bare " +
        "except for the snow on them.\n");
    add_item(({"lesser peaks", "lesser peak", "shorter peaks", "shorter peak",
            "short peak", "short peaks"}),
        "They are shorter, but still tall. These peaks are jagged and " +
        "appear to have trees growing on them. The tallest ones are " +
        "crowned with snow.\n");
    add_item(({"peaks", "mountain peaks"}),
        "They are hard to see with the trees moving about. " +
        "Nonetheless, some snowcapped tops can be seen as well " +
        "as some buried in the clouds.\n");
}

/*
 * Function name : set_add_tower
 * Description   : adds descr of watchtowers
 */
void set_add_tower()
{
    add_item(({"tower", "watch tower", "watchtower"}),
        "It is tall and overlooks the camp. From it orcs can keep watch out for enemies. The tower is made of logs crudely lashed together with leather.\n");
    add_item(({"logs"}),
        "They are long and lashed together by strips of animal hide. The logs look roughly cut from the nearby forest.\n");
    add_item(({"ladder", "ladders"}),
        "They are simply made of logs tied together and lead up to the " +
        "watchtower.\n");
    add_item(({"animal hide", "strips", "hide", "hides", "animal hides"}),
        "They strips of animal hide are thick pieces of leather. They tie " +
        "the logs together and hold the watchtower together.\n");
}
/*
 * Function name : set_add_camp
 * Description   : adds descr of camp vs watchtowers
 */
void set_add_camp()
{
    add_item(({"stumps", "tree stumps"}),
        "They are twisted remains of trees that once grew in the camp. " +
        "They were ripped and shredded by orcs who live here.\n");
    add_item(({"tents", "tent"}),
        "They are different sizes and all look to be in poor condition. " +
        "The tents are scattered around the tent and offer some shelter " +
        "for the orcs who live here.\n");
    add_item(({"debris", "garbage", "refuse", "trash"}),
        "It's a mixture of trash the orcs have thrown away. It lies " +
        "in piles around the camp and trampled underfoot in the mud.\n");
    add_item(({"ground", "dirt", "mud", "track", "trail", "path", "road"}),
        "The ground is dark and dirty, and covered in mud. Debris and " +
        "trash lie in heaps around the camp, and buried in the mud.\n");
}


void set_in_tower()
{
    add_item(({"walls"}),
        "The walls are made of roughly hewn logs and held together with braided leather. They look sturdy and have probably been standing for years.\n");
    add_item(({"floor", "ground"}),
        "The ground is dirty and made of logs cut in half with the flat sides up. Debris lies scattered around, a lot of it pushed to the walls as the orcs race through the tower.\n");
    add_item(({"leather"}),
        "It is thick strips of animal hide and braided together to hold the walls together. The leather is dried and durable looking.\n");
    add_item(({"logs"}),
        "They are various sizes and rough looking. Some stand vertical and make up the walls. Others have been cut in half with the flat sides up for the floors.\n");
    add_item(({"ceiling"}),
        "It is made of roughly hewn logs.\n");
    add_item(({"ladder"}),
        "It is simply made of logs tied together, providing a way to travel through the tower.\n");

}

string camp_desc1(string str)
{
    return short() + ". " + s_desc_sky_outside_sky() + "Tents are scattered " +
        "around the camp. They are shabby looking and different sizes. The " +
        "dirty path runs in all directions of the camp. Ground into the " +
        "path is all kinds of debris. " + str + "\n";
}

string camp_desc2(string str)
{
    return short() + ". " + s_desc_sky_outside_sky() + "The path is " +
        "well trodden by countless feet. Buried in the mud are all kinds " +
        "of debris. Tents are on either sides of the path. Broken trees " +
        "stand scattered through the camp. " + str + "\n";
}

string camp_desc3(string str)
{
    return short() + ". " + s_desc_sky_outside_sky() + "The dirty path " +
        "winds past broken trees and stumps. The mud is full of debris " +
        "ground into by countless feet. Dirty tents stand in the distance. " +
        str + "\n";
}

string camp_desc4(string str)
{
    return short() + ". " + s_desc_sky_outside_sky() + "Tents line the " +
        "path, which wanders through the camp and past broken trees. The " +
        "path is a morass of filth and debris. It smells terrible. " +
        str + "\n";
}

string camp_desc5(string str)
{
    return short() + ". " + s_desc_sky_outside_sky() + "Broken trees and " +
        "stumps are scattered around the camp. They look like they were " +
        "torn apart by the orcs that live here. Mud and debris are everywhere. " +
        "The trail runs throughout the camp and looks well traveled. " +
        str + "\n";
}

string tower_desc(string str)
{
    return short() + ". " + str + "\n";
}


/* adds shortcuts for tower entrance/exits 
 *
 * Fixing shortcuts, because NPC's are taking them.
 * Aeg 2010
 */
 
//tower entrances
void add_tower_entr()
{
    add_exit(OC_DIR + tower_num, "in",0,1,1);
    add_exit(OC_DIR + tower_num, "tower",0,1,1);
}


// tower exits
void add_tower_exit()
{
    add_exit(OC_DIR + tower_num, "o",0,1,1);
}

