#include "../defs.h"

inherit RHOVANION_STD_DIR + "room";
inherit "/d/Gondor/common/lib/herbsearch";
inherit RHOVANION_DIR + "mirkwood/std/warning";
inherit "/d/Gondor/common/lib/room_tell";

#include <macros.h>

void

create_room()
{
    set_short("Base of the Carrock");
    set_long("You are standing atop a great rock, essentially a hill of "+
        "stone, which stands tall and pround in the middle of the Anduin " +
        "river. This eyot is known as the Carrock, and it is well known " +
        "in the Wilderland for miles around, often seen as some last " +
        "outpost of the nearby Misty Mountains whose rugged peaks tower " +
        "high across the western horizon. On either side of the great " +
        "river, a deep valley runs down in slopes filled with a tall " +
        "green grass, small copses of oak and elm, and the occasional " +
        "jagged collection of broken boulders. Far to the east, a great " +
        "forest spreads out across the eastern horizon, marking the " +
        "boundary of the legendary Mirkwood forest. A small path of " +
        "flat, black stones lead from this rocky island to the eastern " +
        "bank of the river while a small cave opens up to the west.\n");

    add_item(({"grasses", "grass", "ground", "field", "fields", "green grass",
            "yellowish grass", "yellow grass", "yellow-green grass"}),
        "The deep valley is full of a tall, yellow-green grass which seems " +
        "to sway in the wind with every breeze which blows past.\n");
    add_item(({"rock", "hill", "stone", "carrock", "hill of stone",
            "great rock"}),
        "This is the Carrock, a massive stone island which stands tall " +
        "in the middle of the Anduin river.\n");
    add_item(({"island", "eyot"}),
        "The Carrock is a small island, otherwise known as an eyot, which " +
        "stands in the middle of this deep valley as the great Anduin " +
        "river loops around its base.\n");
    add_item(({"wilderland", "land"}),
        "You are in the Wilderland, far away from civilization, surrounded " +
        "by the remote Misty Mountains to the west and the dangerous " +
        "Mirkwood forest to the east.\n");
    add_item(({"mountains", "misty mountains"}),
        "Rising high above the foothills below, their jagged peaks piercing " +
        "the clouds above, the legendary Misty Mountains are both " +
        "majestic and intimidating at once.\n");
    add_item(({"peak", "peaks", "snow", "cloud", "clouds", "tips", "tip"}),
        "The peaks of the Misty Mountains are jagged and covered in snow, " +
        "yet the very tips are lost in the ever-present clouds which hang " +
        "above the mountains, granting them their name.");
    add_item(({"river", "great river", "anduin river", "anduin", "water"}),
        "A massive river spreads itself wide as it cuts through the " +
        "Wilderland, leaving a deep valley behind as it runs down from the " +
        "north on its journey south towards the sea. The river loops itself " +
        "around the Carrock, the blue water swirling and splashing " +
        "against the rock.\n");    
    add_item(({"valley", "vale", "vale of the anduin", "slopes"}),
        "This deep valley, known more famously as the Vale of the Anduin " +
        "follows the great river as it carves and cuts a path " +
        "through the Wilderland on its journey southward.\n"); 
    add_item(({"hill", "hills", "foothill", "foothills"}),
        "Rugged foothills leap up away from the valley that surrounds " +
        "you, growing by leaps and bounds into the massive peaks of the " +
        "majestic Misty Mountains.\n"); 
    add_item(({"boulder", "broken boulders", "broken boulder", "boulders"}),
        "Dozens of massive boulders, jagged and broken, lay scattered " +
        "around the Vale of the Anduin, as if carelessly discarded by " +
        "some littering giant.\n");
    add_item(({"trees", "tree"}),
        "You can see many trees from atop the Carrock. The deep valley " +
        "which surrounds you has many pockets of elms and oaks, while " +
        "far to the east the massive Mirkwood forest lines the top of " +
        "the valley across the entire eastern horizon.\n");
    add_item(({"oak", "oaks"}),
        "Small groves of oak trees are scattered across the vale, while " +
        "endless black oak trees fill the legendary Mirkwood forest.");
    add_item(({"elm", "elms"}),
        "Tall and slender, dozens of elm trees cast their shade across " +
        "the valley in small groves.");     
    add_item(({"grove", "groves"}),
        "Dozens of groves of trees dot the broken slopes of the deep " +
        "valley which surrounds you. Mostly consisting of tall elms and " +
        "oaks, these groves provide an abundance of shade and shelter.");
    add_item(({"forest", "mirkwood", "mirkwood forest", "black oak", 
            "black oaks"}),
        "Countless lines of tall, black oak trees cover the eastern " +
        "horizon, standing at the top of the slopes of the valley. This " +
        "is the legendary, and infamous, Mirkwood forest.");
    add_item(({"leaf", "leaves", "green leaf", "green leaves"}),
        "You cannot make out any individual leaves on the many trees at " +
        "this distance, but the lush greeness is abundantly obvious.");
    add_item(({"step", "steps", "stair", "stairs"}),
        "Carved into the side of the Carrock itself, a winding set of " +
        "steps lead up to the top of the rocky island.");
    add_item(({"path", "stones", "flat stones", "black stones"}),
        "These black stones are rather flat, and rise up just about the " +
        "surface of the water. There seems to be a line of them, winding a " +
        "path from the the Carrock to the eastern bank of the Anduin " +
        "river.\n");
    add_item(({"bank", "east bank", "river bank", "eastern bank"}),
        "This is the other side of the river, covered in tall green grass " +
        "and connected by a path of flat, black stones in the river.");
    add_item(({"cave", "small cave", "dark cave"}),
        "There is a small, dark cave mouth which opens up to the west. The " +
        "cave itself actually appears surprisingly dry, giving it " +
        "a wholesome sort of appearance. The floor appears to be lined " +
        "with thousands of round pebbles.");
    add_item(({"pebble", "pebbles", "round pebbles", "round pebble"}),
        "There are thousands of small, round pebbles which are surprisingly " +
        "dry and lining the floor of the cave to the west.");
    add_item(({"mouth", "opening", "edge", "edges"}),
        "The mouth of the cave is not very large, but the edges are smooth " +
        "and rounded.\n");


    add_exit(VALE_DIR + "cave2", "west",0,2,0);
    add_exit(VALE_DIR + "carrock", "up",0,2,0);
    add_exit(VALE_DIR + "valen8w7", "east","@@path@@",2,0);

}

int
path()
{
write("You carefully make your way across the path of flat stones " +
    "to reach the eastern bank of the Anduin river.\n");
return 0;
}