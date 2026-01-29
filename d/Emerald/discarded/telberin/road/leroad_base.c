/*
 * Base road file to chapel, starts at xroad of Telberin
 * By Finwe
 * February 1997
 */
 
inherit "/std/room";
#include "/d/Emerald/defs.h"
#include "../default.h"
 
void create_road();
string road_desc();
 
void create_room()
{
    add_prop(OBJ_I_CONTAIN_WATER,1);
    set_short("A forest road");
    set_long(road_desc());
    add_item( ({"animals", "animal"}),
        "Peering into the distance, you see various woodland " +
        "creatures darting between the trees and across the field.\n");
    add_item( "bushes",
        "Most of the bushes are wild undergrowth. Other " +
        "bushes are wild berries, and edible plants. Travelling " +
        "through the bushes is difficult and not worth the effort.\n");
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
    add_item ( ({"road", "down", "ground"}),
        "You notice that the road is hard packed dirt. Grasses " +
        "grow on it where traffic hasn't worn it away. It is " +
        "generally free of twigs and debris from constant use " +
        "by travellers. Growing next to the path are wildflowers " +
        "and bushes.\n");
    add_item("brook",
        "A gentle brook bubbles along the side of the road. It " +
        "flows from the lake and into the forest. The water is " +
        "clear and looks refreshing. You can easily see the " +
        "bottom of the brook.\n");
    add_item( ({"bottom of brook", "bottom of the brook", 
            "brook bottom"}),
        "The bottom of the brook is covered with rounded rocks " +
        "and pebbles. Brightly coloured fish lazily swim by.\n");
    add_item ( ({"cup", "cups", "silver cup", "silver cups" }),
        "These lovely little cups are made of pure silver. They " +
        "are simple but beautiful. They shine brightly in the " +
        "sun. The cups sit on a rack that stands along side " +
        "the brook. They are placed here for travellers to get a " +
        "drink of water.\n");
    add_item( ({"cup rack", "rack"}),
        "The rack stands along side the brook. It is made from " +
        "polished mahogany and looks very sturdy. The rack has " +
        "many hooks with silver cups hanging from it.\n");
 
    create_road();
}
 
create_road()
{
}
 
string
road_desc()
{
    switch(random(3))
    {
        case 0:
        return "   You are walk along the northern edge of " +
            "the great forest. Many trees grow along the " +
            "southern edge of the road with a few scattered " +
            "north of you. They rise tall into the sky creating " +
            "a shaded canopy across the road here. The road is " +
            "well used by travellers. A great field spreads out " +
            "in all directions north of here. ";
        break;
        case 1:
        return "   You walk along a worn road. It cuts through a " +
            "large field but skirts the Great Emerald forest. It " +
            "runs east and west. Scattered " +
            "tall trees grow here. Their foilage shades the road " +
            "here. A gentle breeze blows past you. It cools you " +
            "and and smells of the forest. A slow moving brook " +
            "follows the road. It flows from the lake and into " +
            "the forest. ";
        break;
        case 2:
        return "   The road wanders here as it goes under the " +
            "tall trees of the forest. The trees block your view " +
            "of the field north of here. Sunlight shines through " +
            "the trees and warms your body with its gentle rays. " +
            "It feels good. Woodland animals scamper through the " +
            "forest. "; 
        break;
        default:
        return "   The road is quiet and relaxing here as it " +
            "wanders along the southern edge of the field. Deep " +
            "wagon tracks run along the outside of the road. " +
            "South is the northern edge of the forest. The trees " +
            "that grow south of here are large and reach to the " +
            "sky. They offer some shade.  A bubbling brook flows " +
            "past you as it heads into the forest. ";
        break;
     }
}

init()
{
   ::init();
   
    add_action("drink_it",    "drink");
}
drink_it(string s)
{
   if(s=="water" || s=="water from brook")
       {
           TP->catch_msg("You take a silver cup from the hook, " +
               "fill it with water from the brook and get a " +
               "drink. You place the cup back on the hook.\n" +
               "You feel refreshed.\n");
           say(QCTNAME(TP)+" gets a drink of water from the brook.\n");
           TP->drink_soft(100);
            return 1;
        }
    else
            NF("Drink what?\n");
}
