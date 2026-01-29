/*
 * Base room for Cair Andros
 *
 * Varian - 2016
 *
 */

#include "../defs.h"

inherit ANORIEN_STD_DIR + "room";
inherit "/d/Gondor/common/lib/room_tell";

#include <macros.h>
#include "/d/Gondor/anorien/std/descriptors.c"

void set_items_fort();
void set_items_river();

/*
 * Function name:        create_ca_room
 * Description  :        Use create_ca_room() to make Cair Andros rooms that
 *                       use information from this file
 */
void create_ca_room() 
{
}

nomask void create_anorien_room() 
{

    create_ca_room();
/*
 * Function name:        add_tell - used when inheriting 
 *                       "/d/Gondor/common/lib/room_tell";
 * Description  :        Gives some atmosphere by providing some 'sounds'
 *                       in the room in a similar manner to echo
 */
        add_tell("Dark grey clouds pass in front of the " + 
            VBFC("sun_moon") + ", temporarily blocking out the " +
            VBFC("light_type") + " that is cast down upon the fortress.\n");
        add_tell("The " + VBFC("daylight_desc") + " sparkles down upon the " +
            "river in the distance, dancing across the surface.\n");
        add_tell("As some clouds part in the sky, bright " + VBFC("light_type") 
            + " from the " + VBFC("day_desc") + " " + VBFC("sun_moon") + 
            " spreads out across the battlements.\n");
        add_tell("A gentle breeze rises from the river, sweeping over " +
            "the fort as it follows the river south.\n");
        add_tell("Far off to the east, the " + VBFC("daylight_desc") +
            " reveals a flock of birds, swooping and diving over the " +
            "forests of Ithilien.\n");
        add_tell("A cool breeze rips through the crenellations of the " +
            "parapet and swirls off down the river.\n");
        add_tell("Just beyond the walls of the fort, you can see the " +
            VBFC("light_type") + " sparkling as it dances on the " +
            "surface of the river.\n");
        add_tell("A swirling wind follows the sparkling surface of the " +
            "Anduin River, causing the tall grasses that line the banks " +
            "to bend and sway in the breeze.\n");
        add_tell("The dull roar of the river echoes across the land " +
            "as the rushing waters tumble through the lands of Gondor.\n");
        add_tell("A small flock of birds chase each other, swooping and " +
            "diving all across the grassy fields that stretch out to the " +
            "west.\n");
        add_tell("A gentle breeze ripples through the tall grasses of " +
            "Anorien that roll across the western horizon, causing them to " +
            "bend and sway with each gust.\n");
        add_tell("Far to the east, you see an eagle soaring in the " + 
            VBFC("daylight_desc") + " around jagged peaks of Ephel " +
            "Duath, the Mountains of Shadow, that rise up meancingly " +
            "in the distance.\n");
        add_tell("The winds rustles through the dense forests of Ithilien " +
            "that line the eastern bank of the river.\n");
        add_tell("A thunderous echo falls down the river from the north, " +
            "where the mouths of the Entwash empty into the Anduin.\n");
        add_tell("A small boat floats down the river, passing near the " +
            "western banks of the river as it continues its journey south.\n");
        add_tell("A small boat floats down the river, passing near the " +
            "eastern banks of the river as it continues its journey south.\n");
        add_tell("A large brown stag slips out of the trees on the " +
            "eastern banks of the river, before bounding away after " +
            "taking a drink of water.\n");
        add_tell("A large, silver fish jumps high out of the sparkling " +
            "waters of the Anduin, landing again with a loud splash.\n");
        add_tell("A large, brown fish jumps high out of the sparkling " +
            "waters of the Anduin, landing again with a loud splash.\n");
        add_tell("A small, silver fish jumps high out of the sparkling " +
            "waters of the Anduin, landing again with a loud splash.\n");
        add_tell("A horde of tiny flies start buzzing around your face, " +
            "biting at your bare flesh.\n");
        add_tell("A horde of tiny flies start buzzing around your face, " +
            "biting at your bare flesh.\n");
        add_tell("A horde of tiny flies start buzzing around your face, " +
            "biting at your bare flesh.\n");
        add_tell("A brightly coloured dragonfly zips past, chasing down " +
            "some of the insects for a quick meal.\n");
        add_tell("A brightly coloured dragonfly zips past, chasing down " +
            "some of the insects for a quick meal.\n");
        add_tell("A small bird settles atop the fortress walls nearby, " +
            "before taking flight again after a short rest.\n");
        add_tell("You spot some movement on the eastern bank, deep within " +
            "the shadows of Ithilien's forest.\n");
        add_tell("A flight of swallows dance in the air before taking " +
            "shelter in the forest of Ithilien.\n");
        add_tell("A small flight of swallows dance in the air before taking " +
            "shelter in the trees on the eastern bank.\n");
        add_tell("A large flight of swallows dance in the air before taking " +
            "shelter in the oak trees growing tall and proud in Ithilien.\n");
        add_tell("On the western bank, dozens of tiny butterflies " +
            "flutter across the grassy fields of Anorien in a parade of " +
            "bright colours.\n");
        add_tell("On the western bank, a handful of large butterflies " +
            "flutter across the grassy fields of Anorien in a parade of " +
            "bright colours.\n");
        add_tell("On the western bank, a kaleidoscope of butterflies " +
            "flutter across the grassy fields of Anorien in a parade of " +
            "bright colours.\n");
        add_tell("From the dark depths of Ithilien to the east, you hear " +
            "the long mournful howling of a wolf.\n");
        add_tell("A graceful group of white swans swim slowly across the " +
            "surface of the river near the east bank.\n");
        add_tell("The droning chirp of crickets echoes across the river " +
            "from the fields of Anorien on the western bank.\n");
/*
 * Function name:        set_tell_time
 * Description  :        Provides time increments between tells
 */
        set_tell_time(random(400) + 70);
}
/*
 * Function name:        enter_inv
 * Description  :        Needed to start the room tells
 */
void
enter_inv(object ob, object from)
{
    start_room_tells();
    ::enter_inv(ob, from);
}
/*
 * Function name:        set_items_fort
 * Description  :        Items added to Cair Andros rooms when you include the 
                         line set_items_fort(); 
 *                       Use for all rooms atop the fort on Cair Andros
 */
void
set_items_fort()
{
    add_item(({"horizon", "horizons"}),
        "There is a lot of land around you out here, which horizon did " +
        "you want to examine?\n");
    add_item(({"west", "western horizon"}),
        "The rolling plains of Anorien stretch out across the western " +
        "horizon, stretching all the way to the borders of Rohan.\n");
    add_item(({"southwest", "southwestern horizon"}),
        "The rolling plains of Anorien stretch out to the southwest, " +
        "reaching all the way to the feet of Ered Nimrais, the White " +
        "Mountains.\n");
    add_item(({"northwest", "northwestern horizon"}),
        "Your eyes follow the Anduin river to the northwest, where the " +
        "many mouths of the Entwash flood the great river.\n");
    add_item(({"north", "northern horizon"}),
        "Your eyes follow the Anduin river to the north where it is " +
        "surrounded by miles of soggy swampland.\n");
    add_item(({"east", "eastern horizon"}),
        "Staring across the Anduin to the east, you see the rolling lands " +
        "of Ithilien, occasionally broken up with dense forests, all " +
        "sitting beneath the ominous gaze of the Mountains of Shadow.\n");
    add_item(({"southeast", "southeastern horizon"}),
        "The rolling hills of Ithilien become more frequently forested " +
        "to the southeast, all laying under the sinister eye of the " +
        "Mountains of Shadow that march across the entire eastern " +
        "horizon.\n");
    add_item(({"northeast", "northeastern horizon"}),
        "The rolling plains of Ithilien stretch out to the north, framed " +
        "by the Mountains of Shadow to the east and an endless sprawl " +
        "of swampland to the north.\n");
    add_item(({"south", "southern horizon"}),
        "The Anduin river cuts through the land to the south, running " +
        "towards the ruins of Osgiliath and the sea that lays beyond.\n");
    add_item(({"up", "sky"}),
        "High above your head, the " + VBFC("sun_moon") + " casts the " +
        "glow of " + VBFC("light_type") + " on the mighty walls of the " +
        "fortress that surround you.\n");
    add_item(({"down", "ground", "floor"}),
        "Below your feet are the massive stone blocks that have been used " +
        "to build the fortress.\n");
    add_item(({"river", "anduin", "bank", "banks", "waters", "great river"}),
        "This is the great river Anduin, whose legendary waters cut through " +
        "the lands of Middle-Earth for hundreds of miles, before emptying " +
        "out into the sea far to the south.\n");
    add_item(({"east bank", "eastern bank"}),
        "Sprawling along the eastern bank of the Anduin, the hills of " +
        "Ithilien are filled with forests and woods.\n");
    add_item(({"west bank", "western bank"}),
        "The rolling plains of Anorien flow across the land on the " +
        "western bank of the Anduin.\n");
    add_item(({"grasses", "grass", "ground", "field", "fields", "green grass"}),
        "The plains of Anorien are filled with fields of tall green " +
        "grass that stretch out to the west as far as the eye can see.\n");
    add_item(({"hill", "hills", "plains", "rolling plains", "anorien"}),
        "Hundreds of gentle hills rise and dip slightly across the " +
        "fields of Anorien.\n");
    add_item(({"flower", "flowers", "wildflower", "wildflowers"}),
        "Scattered all across the fields of Anorien, colourful wildflowers " +
        "make a brilliant splash across a carpet of tall green grass.\n");
    add_item(({"insect", "insects"}),
        "There seems to be an endless amount of insects in this part of " +
        "the world, mostly little bitemes that are buzzing around " +
        "everywhere.\n");
    add_item(({"biteme","bitemes", "fly", "flies"}),
        "These small flies are apparently looking for some nice juicy " +
        "flesh to bite! The are incredibly annoying.\n");
    add_item(({"fort","fortress","fortifications","stone fort","stone",
            "stone fortress","stone fortifications","tall fortifications",
            "tall stone fort","tall stone fortifications","tall fort",
            "tall fortress","tall stone fortress"}),
        "You are standing atop the tall stone fortress that guards the " +
        "fords which cross the Anduin at Cair Andros. The view from " +
        "up here allows you to scan the land for many miles in all " +
        "directions.\n");
    add_item(({"stone","stones","stone block","stone blocks"}),
        "The entire fortress appears to have been made from massive stone " +
        "blocks, precisely cut and fit in a very sturdy formation.\n");
    add_item(({"crenellation","merlon","merlons"}),
        "All along the rampart, crenallations divide the merlons, allowing " +
        "the soldiers here to launch arrows through the narrow openings " +
        "and attack any invading force.\n");
    add_item(({"rampart","parapet","wall"}),
        "All around the perimeter of the fort, a tall rampart has been " +
        "built to overlook the fords across the Anduin. This parapet " +
        "has tall stone merlons, with crenellations for the soldiers " +
        "use.\n");
    add_item(({"swallow","swallows"}),
        "Dozens of swallows dip and dive through the air, casually flying " +
        "on both sides of the river.\n");
    add_item(({"bird","birds"}),
        "The air around the river is filled with many different birds of " +
        "all colours and sizes, singing merrily in the comfort of the " +
        "wilderness.\n");
    add_item(({"dragonfly","dragonflies"}),
        "Zipping around, you can see the occasional colourful dragonfly " +
        "looking for a quick meal amongst all of the small flies that " +
        "are buzzing nearby.\n");
    add_item(({"crickets","cricket", "grasshopper", "grasshoppers"}),
        "The fields on either side of the river appear to be filled with " +
        "the droning chirp of crickets and grasshoppers.\n");
    add_item(({"butterfly","butterflies"}),
        "From your view atop the fortress here, you occassionally see " +
        "a colourful parade of butterflies bounce through the air along " +
        "the banks of the river.\n");
    add_item(({"ithilien"}),
        "Stretching out to the east, the contested lands of Ithilien " +
        "are filled with rolling hills filled with pockets of dense " +
        "woods. It is commonly known that the forces of Mordor and " +
        "Gondor each claim the land as their own, fighting bitterly " +
        "for its possession.\n");
    add_item(({"culumalda", "culumalda trees", "golden tree", "golden trees"}),
        "Unique to the lands of Ithilien, you can see the occasional grove " +
        "of golden Culumalda trees. Their peaceful beauty helps you forget " +
        "that Ithilien is now a land of war, at least for a few moments.\n");
    add_item(({"tree","trees"}),
        "The lands around you are filled with pockets of trees, from the " +
        "smaller groves that dot the rolling plains of Anorien to the " +
        "dense woods that gather in the hills of Ithilien.\n");
    add_item(({"oak", "oaks"}),
        "There are many oak trees to be found on both sides of the " +
        "river, growing tall, strong and proud.\n");
    add_item(({"elm", "elms"}),
        "There are groves of slender elm trees which grow on both sides " +
        "of the river.\n");
    add_item(({"fir", "firs"}),
        "The dark green of fir trees can be seen on both sides of the " +
        "Anduin as the trees gather in thick groves.\n");
    add_item(({"grove","groves"}),
        "From your perch high in the air, atop this stone fortress, " +
        "you can see countless groves of trees inhabiting the lands on " +
        "both sides of the Anduin. Groves of oak, elm, fir and even " +
        "culumalda trees can be seen from here.\n");
    add_item(({"fish","silver fish", "brown fish"}),
        "You cannot see any fish right at this moment, but occasionally " +
        "you will see one jumping in the Anduin river.\n");
    add_item(({"forest","forests", "woods", "wood"}),
        "There are dark woods which fall across the eastern bank of the " +
        "river, tucked in amongst the hills which stretch across the " +
        "lands of Ithilien.\n");
    add_item(({"wolf","wolves"}),
        "You cannot see any wolves right now, but you know they are " +
        "undoubtedly concealed within the shadowy woods that populate " +
        "the hills of Ithilien.\n");
    add_item(({"eagle","eagles"}),
        "Occassionally you will see an eagle, far in the distance, " +
        "flying high over Ithilien against the backdrop of the Mountains " +
        "of Shadow.\n");
    add_item(({"deer", "stag", "stags", "buck", "bucks"}),
        "Occasionally, you are able to see some deer as they exit the " +
        "woods of Ithilien to drink at the river bank.\n");
    add_item(({"white mountains", "ered nimrais"}),
        "Far away to the south and west, you are able to catch a glimpse " +
        "of the snow-capped peaks of the White Mountains.\n");
    add_item(({"mountain", "mountains"}),
        "There are mountains visible across many parts of the horizon, " +
        "most prominently the Mountains of Shadow to the east and the " +
        "White Mountains to the southwest.\n");
    add_item(({"mordor", "morgul", "minas morgul"}),
        "Hidden somewhere in the ominous depths of the Mountains of " +
        "Shadow, lays the dark city of Minas Morgul, and the might " +
        "of Mordor beyond.\n");
    add_item(({"mountains of shadow", "ephel duath"}),
        "The Mountains of Shadow dominate the horizon to the east, almost " +
        "appearing to watch the lands of Ithilien with a vigilant eye, " +
        "as if searching for enemies to crush.\n");
    add_item(({"gondor"}),
        "You are in the northern reaches of the lands of Gondor, an ancient " +
        "land of men whose influence once reached to almost every " +
        "corner of Middle-Earth.\n");
    add_item(({"rohan"}),
        "The lands of Rohan can be found to the west of Gondor, where " +
        "the green fields have bred a nation of horsemen.\n");
    add_item(({"minas tirith", "citadel", "wall", "rammas echor", "tower",
            "tower of guard"}),
        "Far to the south, a massive wall has been raised around the " +
        "farms which surround the legendary city of Minas Tirith. Minas " +
        "Tirith itself has rings of walls which surround a citadel which " +
        "sits perched on the eastern edge of the White Mountains.\n");
    add_item(({"osgiliath", "ruins"}),
        "Far to the south, a ruined city of broken walls and bridges " +
        "is visible as it attempts to span the rushing waters of the " +
        "Anduin. Osgiliath was once a great city, the heart of Gondor.\n");
    add_item(({"entwash", "mouths", "mouths of the entwash"}),
        "Far to the north, the sluggish waters of the Entwash flow from " +
        "west to east, before splitting into the mouths which flood " +
        "the Anduin and every visible piece of land nearby, creating " +
        "vast swamps that stretch for miles.\n");
    add_item(({"snow", "snow-capped peaks", "peaks", "peak"}),
        "Many of the mountains visible in the distance reach so high " +
        "into the sky, their peaks have been capped with the white of " +
        "snow.\n");
    add_item(({"swamp", "swampland", "marsh", "marshes", "fens", "nindalf",
        "wetwang"}),
        "Miles upon endless miles of swampland covers the land east " +
        "of the Anduin, opposite the flooding waters which spill out " +
        "of the mouths of the Entwash. The bulk of these fens are " +
        "known as the Nindalf, or the Wetwang as it is sometimes " +
        "named in the Westron tongue. The northeastern edge of the " +
        "Nindalf is known as the Dead Marshes.\n");
}
/*
 * Function name:        set_items_river
 * Description  :        Items added to Cair Andros rooms when you include the
 *                       line et_items_river(); 
 *                       Use for all fort rooms on the island of Cair Andros
 *                       that overlook the Anduin
 */
void
set_items_river()
{
    add_item(({"island", "cair andros"}),
        "You are standing atop the rampart of a fortress on the island " +
        "of Cair Andros in Gondor. The island is rather long, and filled " +
        "with all manner of trees on the north end. All around you, the " +
        "powerful waters of the Anduin River flow past, on their way " +
        "south to empty out into the sea.\n");
    add_item(({"fort","fortress","fortifications","stone fort","stone",
            "stone fortress","stone fortifications","tall fortifications",
            "tall stone fort","tall stone fortifications","tall fort",
            "tall fortress","tall stone fortress"}),
        "You are standing atop a tall stone fortress, behind the parapet " +
        "which overlooks the rushing waters of the Anduin river which " +
        "flow around the island of Cair Andros. The view from up here " +
        "is astounding, allowing you to see for many miles in every " +
        "direction.\n");
    add_item(({"ford", "river", "anduin", "bank", "banks", "waters",
            "great river", "water"}),
        "The Anduin River flows around the island here, just beyond the " +
        "walls of the fort. Two fords are visible nearby, connecting " +
        "the island to both the east and west banks of the great river. " +
        "These fords are certainly the reason for this fortress being " +
        "here, as you imagine it would be impossible to move an army " +
        "across a river of this size normally.\n");
}
