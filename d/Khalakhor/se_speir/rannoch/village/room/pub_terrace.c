/* File         : /d/Khalakhor/se_speir/rannoch/village/room/pub_terrace.c
 * Creator      : Darragh@Genesis
 * Date         : 00-11-04      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "room.h"
inherit "/d/Khalakhor/std/room";

void
create_add_items()
{
    add_item(({"lake","loch","loch rannoch","lake rannoch","rannoch",
               "inlet"}),
               "This narrow highland lake is surrounded by mountains "
             + "on its east and south side. On its north and west "
             + "sides the hills are covered in forest. You see a few "
             + "boats out there on the lake.\n");
    add_item(({"boat","boats","fishing boat","fishing boats"}),
               "The boats within sight are small and narrow, some "
             + "with sails. The rest are either further out "
             + "on the lake or docked in the village.\n");
    add_item(({"mountain","mountains","range","mountain range","spine",
               "peaks","peak"}),
               "The mountains rises up from the carpet of forest "
             + "like a great spine on the eastern shoreline of the "
             + "lake, and continuing on its southern end. There it "
             + "diminishes into craggy rock formations and finally "
             + "evens out into the western hills. The northern end "
             + "can not be seen from here, as it continues far "
             + "away northeast.\n");
    add_item(({"village"}),
               "You see nothing of the village itself, except the "
             + "walkway down below.\n");
    add_item(({"terrace"}),
               "The terrace you stand on is definitely more recently "
             + "built than the rest of the pub. Care has been taken to "
             + "protect the terrace against any rain or fierce winds, "
             + "and also it is built in a way that does only allow view "
             + "of the lake and surrounding landscape, and the walkway "
             + "below. A few long tables with benches are neatly "
             + "arranged here.\n");
    add_item(({"walkway","walkways","planks"}),
               "Jutting out from the cliff wall below you, you see "
             + "the walkway about twelve feet down below. It runs "
             + "along the whole shoreline, twisting and winding its "
             + "way upward. At this place is where it is at its most "
             + "southern point. It is constructed of thick wooden planks "
             + "and looks very reliable.\n"); 
    add_item(({"hills","hill"}),
               "All the way west from the lake, the hills continue "
             + "on, as far as you can see. The nearest hilltop looks "
             + "as if it is completely devoid of any vegetation.\n");
    add_item(({"woods","forest","trees","woodlands","carpet","vegetation"}),
               "The forest grows everywhere possible, on the mountain "
             + "slopes as well as the hillsides of the west all the "
             + "way down to the shoreline.\n");
    add_item(({"shoreline"}),
               "You will need to specify which shoreline you "
             + "wish to examine.\n");
    add_item(({"west shoreline","western shoreline","strip",
               "narrow strip","western shore","western shore"}),
               "The west shoreline of the lake is lined with a narrow "
             + "strip of bare land, before the forest takes over "
             + "and continues on westward up on the hills.\n");
    add_item(({"north shoreline","northern shoreline",
               "north shore","northern shore"}),
               "You are unable to see the northern end of the lake, "
             + "due to the terrace wall blocking your view west.\n");
    add_item(({"east shoreline","eastern shoreline","wall of rock",
               "rock wall","east shore","eastern shore"}),
               "With the mountains drawing themselves up high "
             + "above the lake, casting their reflections onto it, "
             + "the only shoreline there is is just a merciless "
             + "wall of rock.\n");
    add_item(({"south shoreline","southern shoreline",
               "south shore","southern shore"}),
               "The shape of the lake does not allow much of a "
             + "southern shoreline, and the distance makes it hard "
             + "to discern any details. The lake should have its outlet "
             + "there, in the form of another river.\n");
    add_item(({"reflection","reflections","images","image"}),
               "The mountains on the east side of the lake casts "
             + "their reflection onto the surface of the lake, "
             + "creating an illusion of even greater height.\n");
    add_item(({"cliff","cliffs","cliffside","cliffsides","rocks"}),
               "From the eastern bank of the river the land rises "
             + "steeply into hills, joining up with the mountains "
             + "further east. This makes the northern shoreline "
             + "into high cliffsides, a perilous place "
             + "to venture with risk of falling down on the "
             + "sharp rocks far below.\n");
    add_item(({"hilltop","top of the hill","summit","hill summit",
               "nearest hilltop"}),
               "You see no details from this distance, although "
             + "there is something there at the top of the hill.\n");
    add_item(({"pub"}),
               "Looking in through the door you see very little, "
             + "due to the dark interior of the pub.\n");
    add_item(({"furniture","table","tables","long table","long tables",
               "bench","benches","long bench","long benches"}),
               "The furniture out here consists only of a few long "   
             + "wooden tables nailed to the floor and north wall "
             + "along with equally long benches on either side. "
             + "They look rather new, and reletively clean. Most "
             + "of the benches are occupied by customers.\n");
    add_item(({"wall","walls","wooden wall","wooden walls","north wall",
               "northern wall","south wall","southern wall","west wall",
               "western wall","east wall","eastern wall"}),
               "You are surrounded by wooden walls, the north one "
             + "holding the entrance leading back to the pub. The "
             + "south is only waist-high, to allow a sitting customer "
             + "a fine view of the lake and walkway. The west and east "
             + "walls are flat and uninteresting, intended to block off "
             + "your view of the rest of the village. Some flowers "
             + "have been planted in boxes hanging on the south wall.\n");
    add_item(({"floor","floorboards","planks","wooden planks","wooden plank"}),
               "The floor is made of wooden planks, and mostly covered "
             + "by a large, striped rug.\n");
    add_item(({"rug","carpet"}),
               "The rug is striped with grey and white, placed there in "
             + "an effort to keep the floor a bit warmer.\n");
    add_item(({"box","boxes","flower box","flower boxes","box of flowers",
               "boxes of flowers","flowers"}),
               "To add some homely feeling to the terrace, flowers have "
             + "been planted in long wooden boxes hanging on the outside "
             + "of the south wall. They are simple flowers in many "
             + "colours, planted firmly in dark soil.\n");
    add_item(({"soil","dirt"}),
               "The soil is dark and moist, perfect conditions for "
             + "the flowers to grow in.\n");
    add_item(({"customer","customers","people","patron","patrons"}),
               "Some of the tables are occupied by people eating "
             + "and drinking, some gazing out at the lake and its "
             + "surroundings.\n");
    add_item(({"door","doorway","entrance"}),
               "The doorway leading into the pub is narrow, and "
             + "the door seems to be open all the time.\n");
    add_item(({"roof","ceiling"}),
               "The roof over the terrace is slanting southwards, and "
             + "made of wooden rafters covered with thick thatch "
             + "to ward off any rain or bird droppings.\n");
    add_item(({"rafter","rafters","wooden rafter","wooden rafters"}),
               "The thatch of the roof is supported by a a row of "
             + "thick wooden rafters.\n");
    add_item(({"thatch"}),
               "Made of thick reeds and straw along with bark and "
             + "grass, the thatch looks strong enough to keep any "
             + "rain out.\n");

    add_exit(ROOM + "pub.c","north");
}
void
create_room_tells()
{
    add_tell(({"You hear the clinking of glasses and plates from the pub.\n",
               "You sense the smell of fried fish from the pub.\n", 
               "A villager walks by on the walkway below.\n",
               "A villager walks by on the walkway below.\n",
               "A child runs by on the walkway below, chased by "
             + "another child.\n",
               "A child runs by on the walkway below, chased by "
             + "a group of other children.\n",
               "You hear a roar of laughter from within the pub.\n",
               "A man arrives from the north, and takes a seat at "
             + "a nearby table.\n",
               "A man holding a mug and a plate of food arrives from "
             + "the north, and takes a seat at a table.\n",
               "A man rises from his seat, burps loudly, and leaves north.\n",
               "A man falls off his seat, stands up, and leaves north.\n",
               "A young woman arrives from the north, loads her tray "
             + "with dirty plates and mugs, and leaves north.\n",
               "Someone sighs happily.\n",
               "The flowers sway slightly in the breeze.\n",
               "An icy breeze sweeps in from the lake.\n",
               "A fresh breeze sweeps through the terrace.\n",
               "You hear the cries of birds from the lake.\n",}));
}
public void
create_khalakhor_room()
{
    set_short("On the pub terrace");
    set_long("You are standing on a wide terrace, built outside the pub "
           + "high above the lake. The view of the lake and its surroundings "
           + "is superb. Below the terrace you can see the walkway, "
           + "and even further down the water itself. The "
           + "terrace is covered by a roof to fend of any rain, and a "
           + "few tables and benches are available for any costumer who "
           + "feels the need of enjoying the view while eating and "
           + "drinking.\n");

    create_add_items();

    set_tell_time(350);
    create_room_tells();
}

