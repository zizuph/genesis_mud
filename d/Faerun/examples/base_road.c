/*
 * Base Room for Halflings Settlement
 * -- Finwe, October 2015
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit FAERUN_OUTDOOR_BASE;

//fruit file names
#define FRUIT_NAMES ({"blueberries", "golden_apple", "green_apple", "green_grapes", "strawberry"})

// fruit vars
int fruit_count = 0;

void
create_road()
{
}

void
create_faerun_room()
{
    setuid(); 
    seteuid(getuid());
    
    ::create_faerun_room();
//    add_prop(ROOM_S_MAP_FILE,"highroad_map.txt");

    extraline = "Room description goes here.";

    set_short("A small village road");
//    set_long(short() + ". " + extra_line + "\n");
    create_road();
}

/*
 * Function name : add_road
 * Description   : adds descr of the village road
 */
void add_road()
{
    add_item(({"road", "down", "ground"}),
        "The road is wide and made from packed dirt. It winds through " +
        "the village.\n");
    add_item(({"up", "sky"}),
        TIME_DESC_ROOM + "\n");

//    add_room_tell("A halfling passes by you.");
//    add_room_tell("Some halfling children run by, laughing as they pass you.");
//    add_room_tell("A halfling watches you intently.");

}

/*
 * Function name : add_path
 * Description   : adds descr of the path leading to the village
 */
void add_path()
{
    add_item(({"path", "trail", "down", "ground"}),
        "It is a narrow ribbon of trampled grass. The path doesn't look " +
        "like much more than a trail and appears to be little used.\n");
    add_item(({"trampled grass"}),
        "The grass lays flat agaisnt the ground. It is well hidden and " +
        "blends in with the grasslands.\n");
    add_item(({"up", "sky"}),
        TIME_DESC_ROOM + "\n");
    
}

/*
 * Function name : add_grasslands
 * Description   : adds descr of the grasslands
 */
void add_grasslands()
{
    add_item(({"grasslands"}),
        "They are a large, rolling area covered in tall grass. A few " +
        "trees dot the land. The grass is tall and golden colored. Seed " +
        "heads are visible on some the taller grases.\n");
    add_item(({"seed heads", "seed head"}),
        "They are long and full of grass seeds. Some of the vertical " +
        "heads are bent over and others are straight and sway in the breeze.\n");
    add_item(({"bushes"}),
        "They are all sizes and shapes, and grow scattered everywhere. " +
        "They are low plants with many branches that spread outward.\n");
    add_item(({"trees"}),
        "They are scattered across the grasslands. They are tall and " +
        "mature, and provide shade beneath them.\n");
}

/*
 * Function name : add_buildings
 * Description   : adds descr of buildings and houses
 */
void add_buildings()
{
    add_item("planks",
        "The planks are thick and made of smooth wood. They fit neatly " +
        "into place with very small cracks.\n");
    add_item(({"buildings", "building"}),
        "They line the streets and are made of wood planks. The buildings " +
        "seem very sturdy and well crafted. Most of the buildings have " +
        "peaked roofs and vary in height from one to two stories.\n");

    add_item(({"house", "houses"}),
        "The houses are sturdy and made of smooth planks of wood. They " +
        "line the street and look sturdy. The houses are weathered have " +
        "peaked roofs \n");
    add_item(({"roofs", "roof", "peaked roofs", "peaked oof"}),
        "The roofs of the buildings are peaked and covered with wooden " +
        "shingles.\n");
    add_item("eaves",
        "The eaves extend from each roof by about an arm's length. They " +
        "provide protection to anyone standing beneath them.\n");
    add_item(({"shingles", "wood shingles", "wood shingle"}),
        "The wooden shingles cover the roof in an overlapping pattern. They " +
        "are made from rough cut lumber and protect the house from the " +
        "elements.\n"); 
    add_item(({"chimney", "chimnies"}),
        "The chimnies are made from stone and concrete. They run up the " +
        "side of some houses. Each chimney is wide at the base and then " +
        "become narrow about two thirds of the way up the houses.\n");

    add_room_tell("A halfling comes out and sweeps their front porch clean.");
    add_room_tell("Someone runs out of a house and down the street.");
    add_room_tell("A dog runs up to you and barks excitedly. Then it runs off.");
}

/*
 * Function name : add_trees
 * Description   : adds descr of trees along the road
 */
void add_trees()
{
    add_item(({"trees"}),
        "They are tall maple trees growing alongside the road. They shade " +
        "the road and buildings beneath them.\n");
    add_item(({"maple trees", "maple tree"}),
        "They are tall and symmetrical. The tree trunks are gray with long, " +
        "upright branches. Green leaves cover the branches and rustle in " +
        "the breeze.\n");
    add_item(({"trunk", "trunks", "tree trunks", "tree trunk"}),
        "The tree trunks are ancient looking and rough. Branches grow " +   
        "outward from the tree trunks.\n");
    add_item(({"leaves"}),
        "The leaves are large and green with three to five lobes. They cover " +
        "the branches and rustle in the breeze.\n");
}

/*
 * Description   : adds descr of trees along the road
 */
void add_gardens()
{
    add_item(({"garden", "gardens"}),
        "They are cultivated areas around the buildings and houses. " +
        "Flowers, bushes, and some fruit trees grow in the gardens. " +
        "Trellisses are set against walls and are covered with vines. " +
        "The plants are lush and aromatic, and add look well tended.\n");
    add_item(({"flowers"}),
        "They are colorful and fill the gardens surrounding the " +
        "buildings. They are all colors and shapes, and sway in the " +
        "breeze.\n");
    add_item(({"bushes"}),
        "They are low plants with many branches that grow up from the " +
        "ground. The bushes are well cared for, and are all different " +
        "sizes. Flowers and fruit cover the bushes.\n");
    add_item(({"fruit trees"}),
        "They are tall and grow in the gardens. The fruit trees are " +
        "bushy and hide the houses behind them. They are laden with " +
        "fruit which glisten in the light.\n");
    add_item(({"trellis", "trellises"}),
        "They are square grid of wooden poles and set in gardens around " +
        "the houses. The trellises are strong looking and covered with " +
        "vines.\n");
    add_item(({"vines"}),
        "They are woody stemed plants growing on the trellises in the " +
        "garden. The vines are healthy looking and full of leaves, " +
        "flowers, and fruit.\n");

}
// pick fruit
int
pick_fruit(string str)
{
    object fruit;
    string fruit_file = ONE_OF_LIST(FRUIT_NAMES);
    string fruit_short = "";
    
    if((str == "fruit"))
    {
        if (fruit_count == 3)
        {
            write("It looks like all the fruit has been picked.\n");
            return 1;
        }
          setuid();
          seteuid(getuid());
          fruit = clone_object(FRUIT_DIR + fruit_file);
          fruit->move(this_player(), 1);

        write("You reach out and pick " + fruit->short() + " from a " +
        "nearby garden.\n");
        say(QCTNAME(TP) + " picks some fruit from a nearby garden.\n");
        fruit_count = fruit_count + 1;
        return 1;
    }
    return 0;
}