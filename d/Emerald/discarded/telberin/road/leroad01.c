/*
 * LEROAD01.c
 * This is the road to leah
 * - Alaron February 10, 1997
 */
 
#include "../default.h"
#include "/d/Emerald/defs.h"
 
inherit "/std/room";
 
void
create_room()
{
    set_short("A forest road");
    set_long("   You are walking along a narrow, winding, " +
        "peaceful forest road. The tall, lush green trees tower " +
        "over the road, creating a calming shade which casts " +
        "soft shadows across the hard packed dirt and grass. " +
        "Thick, deep wagon ruts line either side of the road " +
        "where many a traveller, merchant or royal caravan have " +
        "passed through here. The road continues its shaded " +
        "course through the wood to the west and broadens to a " +
        "crossroads to the east.\n\n");
 
    add_item("crossroads",
        "The crossroads are where three major roads of Emerald " +
        "meet. It seems to be quite busy from here.\n");
    add_item( ({"animals", "animal"}),
        "Peering into the distance, you see various woodland " +
        "creatures darting between the trees and across the field.\n");
    add_item( "bushes",
        "Most of the bushes are wild undergrowth. Other " +
        "bushes are wild berries, and edible plants. Travelling " +
        "through the bushes is difficult and not worth the effort.\n");
    add_item( "road",
        "You notice that the road is smooth and worn. It is " +
        "free of twigs and debris from constant use by " +
        "travellers. Growing next to the path are wildflowers " +
        "and bushes.\n");
    add_item(({ "wildflowers", "flowers"}),
        "Many of wild flowers are brightly colored and native " +
        "to foothills. You see columbine, shooting stars, " +
        "poppies, daisies, and other bright flowers.\n");
    add_item( "trees",
        "Most of the trees here are primarily deciduous trees " +
        "like maples, birches, and willows. The prominent trees " +
        "growing here are poplars. Under the trees is a carpet of " +
        "dead twigs, leafs and other forest debris. Some " +
        "scraggly grasses grow under the trees.\n");
    add_item(({ "grass", "grasses"}),
        "The grass waves in the breeze as it covers the field here. " +
        "oddly enough, it is cut short by the numerous animals that " +
        "live on it. Some scraggly grass grows under the trees " +
        "alongside the shore.\n");
    add_item( "field", 
        "The field stretches in all directions. It ends as it reaches " +
        "the foothills. Sometimes you see deer grazing.\n");
    add_item( "bark",
        "The bark of the trees is varied and weathered. On some " +
        "trees, it is white and beautiful while on other trees, it " +
        "is dark brown and sculptured by the elements.\n");
    add_item( "trunks",
        "Some of the trunks are tall and slender, others are " +
        "forked, and some are even knarled and aged by the elements. " +
        "Most, though, rise tall into the sky creating a canopy " +
        "from the sun.\n");
    add_item( "sun",
        "Sunlight can be seen through the trees. On the field, though, " +
        "it is almost glaring.\n");
    add_item("leaves",
        "Some dead leaves lie under the trees. Some are fresh " +
        "and green while others are brown and half decomposed. " +
        "They offer shelter and food for the forest's animals.\n");
    add_item( "twigs",
        "A few dead twigs lie under the trees. They are in " +
        "different forms of decompsoing. Some are rotten and " +
        "soft, others are freshly fallen, and others are moss " +
        "covered.\n");
    add_item( "canopy",
        "As you look up, you notice the canopy is thick " +
        "with leaves and branches. They block most of the " +
        "sunlight, creating a cool area here in the fields.\n");
    add_item( "field",
        "The field spreads out from the road and heads north " +
        "to the mountains and foothills.\n");
    add_item( "mountains",
        "The mountains are rugged looking, and rise before you " +
        "to the north. They are rocky and quite formidable and " +
        "seem dark and forbidding. It has been said that crossing " +
        "them is nearly impossible but some travellers have " +
        "supposedly done it. The tops of the mountains are capped " +
        "with snow.\n");
    add_item(({ "hills", "foothills"}),
        "The foothills sit at the base of the mountains. They " +
        "are covered with thick brush and brambles. Plenty of " +
        "trees cover the foothills but thin at the base of " +
        "the mountains.\n");
    add_item( "brambles",
        "The brambles are thorny plants and grow in clumps " +
        "across the foothills. You see pyracanthas, hawthorns, " +
        "blackberries, and other thorny plants growing on the " +
        "hills. They make travelling through the foothills " +
        "difficult.\n");
    add_item( "bushes",
        "Most of the bushes are wild undergrowth. Other " +
        "bushes are wild berries, and edible plants. Travelling " +
        "through the bushes is difficult and not worth the effort.\n");
 
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);
 
    add_exit( LROAD + "xroad", "east");
    add_exit( LROAD + "leroad02", "west");
 
}
