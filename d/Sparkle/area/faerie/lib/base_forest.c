/*
 * Base file for forests in Faerie
 * By Finwe, August 2004
 */

#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/room";
inherit S_LIB_CLOCK;
inherit COMMON_BASE;

int room_num;

// room exits when climbing up or down.
string  tree_down_rm, 
        tree_up_rm;

// defines if the room have up or down exits.
int tree_down_flag = 0,
    tree_up_flag = 0;

void create_forest_room() {}
//int up_tree();
//void down_tree();
 
   
public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "faerie_map.txt");
    reset_room();
    set_short("A forest trail");


    create_forest_room();
    reset_faerie_room();
    s_item_sky_outside();
 
    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
 
}
 
string forest_desc1(string str)
{
    return short() + ". @@s_desc_sky_outside_sky@@The forest " +
    "is thick with tall trees. They reach to the sky. A small road " +
    "disappears into the deep shadow-filled forest. Bushes and shrubs " +
    "grow along the path. " + str + "\n";
}

string forest_desc2(string str)
{
    return short() + ". @@s_desc_sky_outside_sky@@You stand on " +
    "a small road in the middle of a dark fir forest. The road disappears " +
    "into the forest. Tall fir trees block your view of the sky above " +
    "and of the sides of the road. " + str + "\n";
}

string forest_desc3(string str)
{
    return short() + ". @@s_desc_sky_outside_sky@@A cool breeze " +
    "blows past you and the forest thins a little here. In the distance " +
    "grow tall trees. Scattered around, young firs grow in scattered " +
    "groups of the forest. A small road runs through the forest. " + 
    str + "\n";
}

string forest_desc4(string str)
{
    return short() + ". @@s_desc_sky_outside_sky@@You stand " +
    "in the middle of a dark fir forest. A narrow road, surrounded by " +
    "bushes and shrubs, runs into the forest. " + str + "\n";
}

string forest_desc5(string str)
{
    return short() + ". @@s_desc_sky_outside_sky@@You are somewhere " +
    "in a dark forest. The road wanders into the forest and is surrounded " +
    "by tall fir trees. A cool breeze blows past you. " + str + "\n";
}

/* 
 * Descriptions for road between Sparkle and faerie
 */

string mt_desc1(string str)
{
    return short() + ". @@s_desc_sky_outside_sky@@The forest is " +
    "thick and full of ancient fir trees. It spreads out in all directions, " +
    "preventing you from leaving the track that runs through it. " + str + "\n";
}

string mt_desc2(string str)
{
    return short() + ". " + s_desc_sky_outside_sky() +  "The track winds " +
    "its way around huge fir trees. They are ancient looking and make " +
    "up the forest here. Wildflowers grow alongside the road. " + str + "\n";
}

string mt_desc3(string str)
{
    return short() + ". @@s_desc_sky_outside_sky@@Huge fir trees " +
    "grow everywhere and make up the forest. They are ancient looking and " +
    "reach to the sky. They block your way except for the track that " +
    "winds between the trees. " + str + "\n";
}

string mt_desc4(string str)
{
    return short() + ". @@s_desc_sky_outside_sky@@A cool breeze " +
    "blows through the forest. Huge, dark firs surround the track. " +
    "The air smells of evergreens and wildflowers. " + str + "\n";
}

string mt_desc5(string str)
{
    return short() + ". @@s_desc_sky_outside_sky@@Wildflowers " +
    "grow in scattered groups alongside the track and in the forest. " +
    "Huge trees make up the forest, which spreads out in all directions. " + 
    str + "\n";
}

string mt_desc6(string str)
{
//    return short() + ". " + s_desc_sky_outside_sky() + "Mountains rise " +
//    "around you in the forest. They are tall and jagged, with their " +
    return short() + ". @@s_desc_sky_outside_sky@@Through the forest " +
    "you can see mountains rise around you. They are tall and jagged, with " +
    "their highest peaks buried in the clouds. The shorter peaks are covered " +
    "with trees, but the highest ones seem bare except for the snow on them. " + 
    str + "\n";
}

string mt_desc7(string str)
{
    return short() + ". @@s_desc_sky_outside_sky@@The air is " +
    "cooler here in the mountains. The trees rise in the distance as " +
    "they climb the sides of the mountains. The tallest peaks touch " +
    "the clouds and are crowned with snow. " + str + "\n";
}
string mt_desc8(string str)
{
    return short() + ". @@s_desc_sky_outside_sky@@Wildflowers " +
    "grow along the track. They provide color in the mountains and the " +
    "tree-covered mountain peaks. A cool breeze blows through the huge fir " +
    "trees, full of forest scents and sounds of the trees. " + str + "\n";
}

string mt_desc9(string str)
{
    return short() + ". @@s_desc_sky_outside_sky@@The mountain " +
    "peaks glisten in the light as they touch the sky. They are jagged " +
    "looking and are carpeted with a large forest of huge firs. " + str + "\n";
}

string mt_desc10(string str)
{
    return short() + ". @@s_desc_sky_outside_sky@@This small clearing is " +
    "covered by rocks and large boulders among the trees. You see the steep " +
    "rise of a tree-covered mountain before you to the northwest." + str + "\n";
}

/*
 * Function name : set_pine_branches
 * Description   : adds descr pine branches
 */
void set_pine_branches()
{
    add_item(({"branches"}),
        "They are large and rough looking. They spread out and hang " +
        "down slightly. The ends fork and are covered with needles.\n");
    add_item(({"needles", "pine needles"}),
        "They are thin, scaly leaves of conifer trees. The needles " +
        "are long and green.\n");
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
    add_item(({"track", "trail", "path", "road"}),
        "It is a used trail that wanders through the forest. It looks " +
        "well used and is probably travelled by merchants and other " +
        "travellers. Wildflowers and bushes grow alongside the track.\n");
/*
    add_item(({"clouds"}),
        "They are white and puffy, and move slowly across the sky. " +
        "Many of them surround the highest peaks, perpetually hiding " +
        "the peaks from your view.\n");
*/
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
 * Function name : set_add_valley
 * Description   : adds descr of valley between Sparkle and Faerie
 */
void set_add_valley()
{
    set_add_mountain();
    add_item(({"valley"}),
        "It is a relatively long, narrow ravine in the mountains. Tall " +
        "trees grow in the valley, which is also dotted with bushes and " +
        "wildflowers.\n");    
}

/*
 * Function name : set_add_oak_trees
 * Description   : adds descr of oak trees.
 */
void set_add_oak_trees()
{
    add_item(({"oak trees", "oak tree", "oaks"}),
        "These are tall, ancient trees. Their large branches reach " +
        "outward and up to the sky and are covered with a multitude " +
        "of emerald green leaves. They grow in groups scattered among " +
        "the fir trees.\n");
    add_item(({"oak leaves", "oak leaf"}),
        "The leaves are long and emerald green. On both sides of the " +
        "leaves are three or four large rounded edges. The top of the " +
        "leaves have a large round edge.\n");
    add_item(({"oak branches"}),
        "They reach outward and up to the sky. They are large and " +
        "covered with many emerald green leaves.\n");
    add_item(({"oak trunk", "oak trunks"}),
        "The tree trunks are tall and and very large. Branches at the " +
        "top reach outward and are covered with many leaves.\n");
    
}

/*
 * Function name : set_conifer_trees
 * Description   : adds descr of conifers
 */
void set_conifer_trees()
{
    add_item(({"conifer", "conifer trees", "conifers", "evergreen", 
            "evergreen tree", "evergreen trees", "evergreens", "fir", 
            "fir tree", "fir trees", "firs", "tall evergreen tree", 
            "tall evergreen trees", "tall fir tree", "tall fir trees", 
            "tall trees", "trees"}),
        "The firs are huge with thick branches that spread out and " +
        "form a canopy above you. The ground beneath these majestic " +
        "trees is covered in a soft carpet of brown, dried needles. " +
        "The trees fill the sky and block out much of the light, forming " +
        "a canopy above you.\n");
    add_item(({"young trees", "young evergreens", "young fir trees", 
            "young fir tree", "young evergreen tree", "young evergreen", 
            "young fir"}),
        "These are young trees, struggling to grow in the forest. " +
        "Nonetheless, they look healthy growing beneath the other trees.\n");
    set_pine_branches();    
}

/*
 * Function name : set_add_forest_debris
 * Arguments     : str: none
 * Description   : adds standard items to all rooms.
 */
void set_add_forest_debris()
{
    add_item(({"ground", "forest debris", "debris", 
            "forest's floor", "floor", "down"}),
        "Beneath the trees, the ground is littered with dead branches, " +
        "pine needles, and some fallen trees.\n");
    add_item(({"fallen leaves", "dead leaves"}),
        "You see a mat of both fresh and dead leaves covering the " +
        "ground. Poking out of them are dead branches, some " +
        "plants, stones, and other signs of a living forest.\n");
    add_item(({"fallen branches", "dead branches", "dead branch"}),
        "They are broken and lie scattered across the ground. " +
        "Some look like they just fell from the trees. They lie " +
        "on the ground in various stages of decomposition.\n");
    add_item(({"twig", "twigs"}),
        "They are small branches, lying scattered across the " +
        "forest's floor.\n");
    add_item(({"fallen trees", "fallen tree", "dead trees", 
        "dead tree"}),
        "Some fallen trees lie rotting under a blanket of fallen " +
        "leaves, branches, and forest debris.\n");
    add_item(({"log", "logs", "rotting log", "rotting logs"}),
        "The rotting logs are in various forms of decomposition. " +
        "Some are hollowed out and appear to be homes for " +
        "woodland animals.\n");
    add_item(({"hollow logs", "hollow log"}),
        "The logs are rotting and hollowed out. Most of them " +
        "are partially buried in the ground or under the forest " +
        "debris.\n");
    add_item(({"dead pine needles", "dead pine needle", 
            "dead needles", "dead needle"}),
        "These are brown and dry, and lie piled under the trees in " +
        "the forest.\n");
    add_item(({"carpet", "soft carpet"}),
        "It is a layer of needles. Over time, they have fallen from " +
        "the trees and accumulated beneath the trees.\n");
}

/*
 * Function name : set_down_trees
 * Description   : adds descr of down below trees
 */
void set_down_trees()
{    add_item(({"thick trees", "thick tree"}),
        "They are ancient and giant in size. Their tops reach " +
        "to the sky and dwarf the trees below them.\n");
    add_item(({"plants", "woodland plants"}),
        "Besides trees, a diverse number of plants grow in the " +
        "forest. Flowers and bushes grow everywhere, somewhat " +
        "hampering your travel blocking your view.\n");
    add_item(({"bushes", "shrubs"}),
        "Bushes of different color and sizes grow everywhere. " +
        "Some are thick and block your view while others are " +
        "thin and spindly.\n");
    add_item(({"moss", "mosses"}),
        "Moss can be seen growing on logs, rocks, on trees, and " +
        "under the trees in patches. It is healthy and a deep " +
        "green. Some patches of moss are so large that bumps " +
        "can be seen under them.\n");
    add_item(({"lichen", "lichens"}),
        "Lichen can be seen on some rocks and trees. It is grey " +
        "and white colored. Some are simple while others are " +
        "large and fan shaped\n");
    add_item(({"flowers", "wild flowers", "wildflowers"}),
        "Various wild flowers are growing about the forest, " +
        "scattered about among the forest's floor. They are " +
        "white, yellow, pink, and other bright colors. They " +
        "add color to the forest and sway in the breezes.\n");
    add_item(({"canopy"}),
        "It is made up of tops of tall trees that block your view of " +
        "the sky. It is irregularly shaped, but still allows some light " +
        "to filter into the forest.\n");
    add_item(({"forest"}),
        "The forest is large and stretches in all directions. " +
        "Tall trees grow everywhere. Some have fallen over and block " +
        "paths in the forest while others grow tall and block the " +
        "sky above. Fallen branches, pine needles, and other " +
        "debris cover the forest's floor. Light slants through the " +
        "trees.\n");
    add_item(({"undergrowth", "underbrush"}),
        "Dense bushes grow under the trees, making travel " +
        "through the forest difficult and obscuring your way.\n");
    set_add_forest_debris();
    set_add_all_track();

}

/*
 * Function name : 
 * Description   : adds descr of 
 */
void set_up_trees()
{
    add_item(({"tree"}),
        "The tree is tall and ancient looking. The branches spread out around " +
        "you from the trunk, blocking most of your view.\n");
    add_item(({"trunk"}),
        "The trunk is wide with branches extending from it. The bark is " +
        "rough and very old looking.\n");
    add_item(({"bark"}),
        "This is the outer skin of the tree. It is grey colored, rough, " +
        "and very old looking.\n");

}


/*
 * Function name : set_add_bees
 * Description   : adds descr of bees in the trees and forest
 */
void set_add_bees()
{
    add_item(({"bees", "honeybees"}),
        "They are large black and yellow insects. They have large wings " +
        "and buzz around the tree.\n");

}

/*
 * Function     : reset_room
 * Description  : processes things that should reset approx every
 *                30 minutes.
 * Arguments    : none
 * Returns      : nothing
 */
void
reset_room()
{
    object hive;
    
    hive = present("hive", this_object());
    if (objectp(hive))
    {
        hive->reset_hive();
    }
}
