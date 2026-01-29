/*  /d/Faerun/phlan/rooms/innkit.c
*
*   By Tharizdun, 2021
* 
*/

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "defs.h"

inherit BASE_PHLAN_INDOOR;


void
create_phlan_room()
{
    set_long("Kitchen of the Cracked Crown Inn.\n"
        +"The kitchen is busy! Several stoves and an open flame grill are"
        +" along one wall with stovepipe vents ascending through the"
        +" ceiling. Another corner has a large icebox. Chef's tools and"
        +" various pots and pans hang from pegs on the walls. Delicious"
        +" smells assail your senses enticing you to try everything, but"
        +" you quickly realize you are just getting in the way back here."
        +" The archway in the north wall leads back to the inn.\n");
    
    set_short("Inn kitchen");
    
        
    add_item(({"walls", "wall"}),
        "The walls are not as decorative as those in the dining room."
        +" They are plain reddish slate that seem chosen specifically"
        +" for their ease in cleaning. Wooden pegs are mounted to hang"
        +" chef's tools and utensils.\n");

    add_item(({"slate", "tile", "tiles"}),
        "The slate tiles have a reddish color. They look frequently"
        +" scrubbed.\n");

    add_item(({"floor", "ground"}),
        "The floor is also of reddish slate. It has a slight angle"
        +" towards a depression in the center with a large brass"
        +" drain.\n");

    add_item(({"depression", "drain", "brass drain"}),
        "The slight concavity of the floor acts as a funnel towards this"
        +" six in circular brass drain. It is designed to aid in cleaning"
        +" as mop water can easily be sluiced towards and down the drain"
        +" at the end of the day.\n");

    add_item(({"stove", "stoves", "oven", "ovens"}),
        "The large wood-fired cast iron stoves have both cooking surfaces"
        +" and an oven for baking. Various pots and pans with wonderful"
        +" food combinations simmer on each.\n");

    add_item(({"ceiling"}),
        "The ceiling is wood with stains from wood smoke. Stovepipes acting"
        +" as exhaust vents ascend to and through the ceiling.\n");

    add_item(({"stovepipe", "exhaust", "vent", "vents", "stovepipes"}),
        "Tin stovepipes expand to funnel-like collectors immediately"
        +" above the stoves and grill. The stovepipes vent smoke from"
        +" the stoves and grill out through the ceiling keeping the air"
        +" relatively smoke free.\n");

    add_item(({"grill", "grills"}),
        "The grill consists of a brick structure with a removable ash"
        +" pan on the bottom, a suspended grate for the firewood, and"
        +" a cooking grill on the top. The fire smells of apple wood."
        +" The grilling surface is blackened metal that has seen a lot"
        +" of wire-brushing.\n");
        
    add_item(({"icebox"}),
        "A large wooden box with blocks of ice, used to keep raw"
        +" ingredients fresh. It smells faintly of fish and seafood.\n");

    add_item(({"archway"}),
        "An archway in the northern wall leads back to the main room"
        +" of the inn.\n");

    add_item(({"tools", "tool", "chef's tools", "utensil", "utensils"}),
        "The tools of the trade for a good chef. You see kitchen knives,"
        +" spoons, spatulas, scrapers, whisks, ladels, cutting boards"
        +" serving forks, tongs and many other things too numerous to"
        +" look at individually hang from the pegs in the walls.\n");    
        
    add_item(({"pot", "pots", "pan", "pans", "pots and pans"}),
        "Cast iron and tin pots and pans of all shapes and sizes hang"
        +" from the pegs in the walls.\n");    

    add_item(({"peg", "pegs"}),
        "Well used wooden pegs are mounted in almost every wall surface"
        +" to hang tools, utensils, pots and pans.\n");

    add_item(({"smell", "smells"}),
        "The smells of baking bread, simmering bisque and grilled fish"
        +" fill the air making you hope your meal is ready soon.\n");         

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "inn", "north");
}


void
reset_faerun_room()
{
    set_searched(0);
}