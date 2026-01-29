/*
 * Base file for outdoor rooms of Green Oak in Faerie
 * By Finwe, August 2004
 */

#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/room";
inherit S_LIB_CLOCK;
inherit COMMON_BASE;

void create_town_room() {}

int room_num;

string read_sign(string str);
void set_add_trees();

public void
create_room()
{

    add_prop(ROOM_S_MAP_FILE, "faerie_map.txt");
    set_short("Along the Village Road in Green Oaks");

    create_town_room();
    reset_faerie_room();
    add_item(({"white stone", "white blocks of stone", "white block of stone",
            "stone", "white stones", "white stone blocks", "stones"}),
        "The white blocks of stone are used in both the buildings and " +
        "the road. Those that are are set into the ground are smooth " +
        "from constant use and age.\n");
    add_item(({"town", "village", "green oaks"}),
        "This is the elven town of Green Oaks. It is set in a forest of " +
        "oak trees. Roads criss-cross through the town past buildings.\n");

    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
    s_item_sky_outside();
    set_add_trees();

}


string forest_desc1()
{
    return s_desc_sky_outside_sky() + "The forest is thick with tall " +
    "trees. They reach to the sky. A small road disappears into the deep " +
    "shadow-filled forest. Bushes and shrubs grow along the path.\n";
}

/******************************************************************************
 * Main routines for describing areas
 ******************************************************************************/

/*
 * Function name : set_add_trees
 * Description   : adds descr of trees in Green Oaks
 */
void set_add_trees()
{
    add_item(({"trees", "oak trees", "oaks", "ancient trees",
            "ancient oak trees", "tall trees", "tall ancient trees",
            "tall, ancient trees", "oak"}),
        "These are tall, ancient trees. Their large branches reach " +
        "outward and up to the sky and are covered with a multitude " +
        "of emerald green leaves. The trees are expertly cared for " +
        "and pruned to retain their regal shape.\n");
    add_item(({"branches", "tree branches"}),
        "The tree branches are very large and expertly pruned. They " +
        "reach outward and upward to form a loose umbrella shape. The " +
        "branches are covered with many leaves.\n");
    add_item(({"tree bark", "bark"}),
        "The bark is unusually smooth. It is dark gray without any " +
        "visible ridges.\n");
    add_item(({"trunk", "trunks", "tree trunk", "tree trunks"}),
        "The tree trunks are tall and and very large. Branches at " +
        "the top reach outward and are covered with many leaves.\n");
    add_item(({"leaf", "leaves", "oak leaf", "oak leaves"}),
        "The leaves are long and emerald green. On both sides of the " +
        "leaves are three or four large rounded edges. The top of " +
        "the leaves have a large round edge.\n");
}


/*
 * Function name : set_add_road
 * Description   : adds descr for the roads in Green Oaks
 */
void set_add_road()
{

    add_item(({"road", "ground", "street", "avenue"}),
        "The road is paved with wide, smooth flagstones. They are " +
        "irregularly shaped, and some are large enough to reach " +
        "across the road. The stones are set together with only " +
        "hairline cracks between them. Some ruts are worn into the " +
        "surface of the stones. Tall oak trees line the road.\n");
    add_item(({"flagstones", "wide flagstones", "smooth flagstones"}),
        "The flagstones are smooth and set into the ground. Their " +
        "irregular shapes create unique patterns in the road. Faint " +
        "hairline cracks are visible where the stones have been set " +
        "next to each other. Slight ruts can be seen in the flagstones, " +
        "probably from centuries of wear by wagons.\n");
    add_item(({"wagon ruts", "ruts"}),
        "They are slight grooves in the stones from wagons rolling " +
        "across the flagstones.\n");
    add_item(({"cracks", "hair line cracks", "hairline cracks",
            "seams", "crack"}),
        "These cracks are where each stone has been place in " +
        "the road and they rest next to each other. The seams are " +
        "barely visible.\n");
    add_item(({"shapes", "irregular shapes", "irregularly shaped flagstones",
            "patterns"}),
        "These are flagstones that are in unnatural shapes and sizes. " +
        "The majority of them are squares and rectangulars. They fit " +
        "together tightly with barely any seams.\n");
}

/*
 * Function name : set_add_park
 * Description   : adds descr park around fountain
 */
void set_add_park()
{

    add_item(({"park"}),
        "The park is surrounded by tall oak trees, which give the town " +
        "its name. A broad street runs through it and decorated with " +
        "boxes of flowers.\n");
    add_item(({"flower boxes", "boxes of flowers", "boxes"}),
        "The flower boxes are round and oversized. They are overflowing " +
        "with a wide variety of flowers. The boxes are situated around " +
        "the park, providing splashes of color.\n");
    add_item(({"flowers"}),
        "The flowers are different sizes and shapes. They are a tapestry " +
        "of color and textures, and grow in the flower boxes. Their " +
        "sweet fragrance drifts through the park, creating a relaxing " +
        "atmosphere.\n");
    add_item(({"wisteria"}),
        "These are long, vining plants that grow up and over the trellis. " +
        "It has long, drooping clusters of white and pink flowers. They " +
        "gracefully hang over the sides of the trellis.\n");
    add_item(({"trellis", "arbor"}),
        "This is a sturdy, open latticework to support vining plants. It " +
        "is tall and covered with growing wisteria. In the center of " +
        "the arbor is an opening to allow visitors to pass through it.\n");
    add_item(({"latticework", "lattice work", "lattice"}),
        "These are thin strips of wood, arranged in a criss-crossed " +
        "pattern, forming an open wall. \n");
    add_item(({"strips of wood", "wood strips"}),
        "These are long strips of wood about a hand's width. They are " +
        "arranged diagonally in a diamond pattern to form the latticework " +
        "of the trellis.\n");
    add_item(({"broad street"}),
        "It runs through the park and is lined with trees and flower " +
        "boxes. Like the other streets, it is paved with flagstones.\n");
    add_item(({"plants"}),
        "They are flowers growing in boxes and trees growing throughout " +
        "the park.\n");
    add_item(({"opening"}),
        "It's a large archway set into the latticework. The openings " +
        "allow you to enter the park or leave it by passing beneath " +
        "the wisteria growing over it.\n");
}

/*
 * Function name : set_add_designs
 * Description   : adds descr of designs in stonework
 */
void set_add_designs()
{

    add_item(({"designs", "design", "exquisite designs", "exquisite design"}),
        "They are ornamental figures carefully carved into the stone. " +
        "The designs are too beautiful to be described, but seem to " +
        "resemble trees, flowers, animals, and other natural beauties " +
        "revered by elves.\n"); 
        
}

/*
 * Function name : set_add_plain_bldg
 * Description   : adds descr of plain stone buildings
 */
void set_add_plain_bldg(string str)
{
    add_item(({"building", "stone building"}),
        "The building is made of stone and decorated with exquisite " +
        "designs which seem to make the building appear alive. " +
        str + "\n");
    set_add_designs();
}

/*
 * Function name : set_add_plain_bldg
 * Description   : adds descr of multiple plain stone buildings
 */
void set_add_plain_bldgs(string str)
{
    add_item(({"buildings", "stone buildings", "stone building", "building"}),
        "The buildings are made of stone. They are smooth looking and " +
        "carved with exquisite designs, making the buildings seem alive. " +
        str + "\n");
    set_add_designs();

}

/*
 * Function name : set_add_forest
 * Description   : adds descr of forest surrounding Green Oaks
 */
void set_add_forest()
{
    add_item(({"forest"}),
        "It is made up of ancient oak trees and surrounds the town. The " +
        "forest is vast and stretches out in every direction.\n");
    add_item(({"edge of town", "southern perimeter", "northern perimeter",
            "eastern perimeter", "western perimeter", "perimeter",
            "edge of forest"}),
        "It is made up of ancient oak trees. They surround the town " +
        "and stretch in all directions away from Green Oaks.\n");
}


string read_sign(string str)
{
    return "On the sign you read: " +
    "'" + str + "'.\n";
}


/*
 * Function name : set_add_sign
 * Description   : adds descr of sign on door
 */
void set_add_sign(string str)
{
    add_item("sign", "It is a rectangular sign hanging above the door. " +
        "Some writing is painted on the sign.\n");
    add_item(({"writing"}),
        "The writing is painted onto the sign. It is exquisite and flowing, " +
        "in the style of elves.\n");
    add_item(({"door"}),
        "It is a wide archway set into the building. A sign hangs above it.\n");
    add_cmd_item("sign", "read", &read_sign(str));

}

/*
 * Function name:	random_noise
 * Description	:	write a random noise
 * Returns	:	int -- non-zero if noises should continue,
 *				zero if they should stop
 */
public int
random_noise()
{
    tell_room(TO, ({
	"An elf walks past you.\n",
	"A traveller wanders past you.\n",
	"You hear faint silvery laughter in the distance.\n",
	"A cool breeze blows past you.\n",
	"Sweet fragrance wafts past you.\n",
    "The trees move gently in the breeze.\n",
    })[random(6)] );
    return 1;
} /* random_noise */
