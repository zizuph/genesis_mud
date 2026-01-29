#include "../defs.h"

inherit RHOVANION_STD_DIR + "room";
inherit "/d/Gondor/common/lib/herbsearch";
inherit RHOVANION_DIR + "mirkwood/std/warning";
inherit "/d/Gondor/common/lib/room_tell";

#include <macros.h>

void

create_room()
{
    set_short("Atop the Carrock");
    set_long("You are standing atop a great rock, essentially a hill of "+
        "stone, which stands tall and pround in the middle of the Anduin " +
        "river. This eyot is known as the Carrock, and it is well known " +
        "in the Wilderland for miles around, often seen as some last " +
        "outpost of the nearby Misty Mountains whose rugged peaks tower " +
        "high across the western horizon. On either side of the great " +
        "river, a deep valley runs down in slopes filled with a tall " +
        "green grass, small copses of oak and elm, and the occasional " +
        "jagged collection of broken boulders. Far to the east, a great " +
        "forest spreads out in an ocean of green leaves. This is the " +
        "legendary Mirkwood forest, where legends tell of black oak " +
        "trees which drink up any scrap of light, leaving travellers " +
        "blind to the perils and dangers hidden within. The middle of " +
        "the carrock is flat, and on the east side, a series of steps " +
        "carved into the stone lead down towards the river.\n");

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
        "far to the east the massive Mirkwood forest has countless trees " +
        "which create an ocean of green across the eastern horizon.\n");
    add_item(({"oak", "oaks"}),
        "Small groves of oak trees are scattered across the vale, while " +
        "endless black oak trees fill the legendary Mirkwood forest.\n");
    add_item(({"elm", "elms"}),
        "Tall and slender, dozens of elm trees cast their shade across " +
        "the valley in small groves.\n");     
    add_item(({"grove", "groves"}),
        "Dozens of groves of trees dot the broken slopes of the deep " +
        "valley which surrounds you. Mostly consisting of tall elms and " +
        "oaks, these groves provide an abundance of shade and shelter.\n");
    add_item(({"forest", "mirkwood", "mirkwood forest", "black oak", 
            "black oaks"}),
        "Countless lines of tall, black oak trees cover the eastern " +
        "horizon, their leafy heads creating a green ocean that your " +
        "eyes cannot see the end of. Legends talk of Mirkwood forest, " +
        "but always tales of danger and peril.\n");
    add_item(({"leaf", "leaves", "green leaf", "green leaves"}),
        "You cannot make out any individual leaves on the many trees at " +
        "this distance, but the lush greeness is abundantly obvious.\n");
    add_item(({"step", "steps", "stair", "stairs"}),
        "Carved into the side of the Carrock itself, a winding set of " +
        "steps lead down towards the river below.\n");
    add_item(({"flat", "flat place", "flat space"}),
        "The middle of the Carrock is quite smooth and flat, a comfortable " +
        "place to stand and relax without fear of tripping or falling.\n");

    add_exit(VALE_DIR + "cave1", "down",0,2,0);

}

void
init()
{
::init();
add_action("do_relax","relax");
}
int
do_relax(string str)
{
    if(!str)
    {
        notify_fail("Relax where? On the Carrock?\n");
        return 0;
    }
    if((str != "carrock")  && (str != "Carrock") && (str != "on the carrock")
        && (str != "on the Carrock") && (str != "on carrock")
        && (str != "on Carrock"))
    { 
        ("Relax where? On the Carrock?\n");
        return 1;
    }
    write("You stand tall on the flat space in the middle of the " +
        "Carrock, instinctively spreading your arms out wide to feel " +
        "the cool breeze as it curls past.\n\nSlowly your eyes close as the " +
        "land speaks to you. The rushing sound of the river crashes around " +
        "the base of the Carrock, reciting its tale of a " +
        "long journey towards the wild, untamed sea.\n\nThe wind whistling " +
        "down from the Misty Mountains whispers of the slow, unstoppable " +
        "passag of time.\n\nThis is all set to the gentle music which echoes " +
        "around the vale, as if Eru granted a special hymn to the many birds " +
        "whose song somehow mix and mingle into one beautiful and complex " +
        "harmony.\n");
    SAYBB(" eyes close as they spread their arms wide open as if to " +
        "embrace the whistling wind.\n");
    return 1;
}