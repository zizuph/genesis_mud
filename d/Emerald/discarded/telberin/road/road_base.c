/* Master room for the forest of Rohim
* Created 19 April, 1995 by Mayhem, Liege of Emerald
*/
inherit "/std/room";
#include "/d/Emerald/defs.h"
 
void create_road();
string road_desc();
 
void create_room()
{
    set_short("A lake side road");
    set_long(road_desc());
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
    add_item( "road",
        "You notice that the road is smooth and worn. It is " +
        "free of twigs and debris from constant use by " +
        "travellers. Growing next to the path are wildflowers " +
        "and bushes.\n");
    add_item(({ "wildflowers", "flowers"}),
        "Many of the wild flowers are brightly colored and native " +
        "to foothills. You see columbine, shooting stars, " +
        "poppies, daisies, and other bright flowers.\n");
    add_item( "lake",
        "The lake is so big you can't see across it. The " +
        "water is deep blue and alive with life. Fish jump " +
        "occasionally in the distance, kingfishers skim the " +
        "surface as they catch their meals, waterfowl poke " +
        "around shore. Here and there, you spot boats drifting " +
        "across its surface. In the distance, you see something " +
        "twinkle in the horizon.\n");
    add_item( "waterfowl",
        "You see ducks, geese, merganzars, and other waterfowl " +
        "around the shore's edge.\n");
    add_item( "shore",
        "The shore is marshy in parts. Waves lap at the edge " +
        "as the waterfowl rides the surf.\n");
    add_item( "marsh",
        "The marsh is full of water plants and offers refuge " +
        "for the lake's inhabitants.\n");
    add_item(({ "lake's inhabitants", "inhabitants"}),
        "All you can see are an occaisonal bird poking its " +
        "head out of the marsh.\n");
    add_item( "water plants",
        "You see tall grasses, water flowers, reeds, rushes, and " +
        "other tall plants that grow at the edge of lakes. " +
        "They offer refuge for the lake's inhabitants.\n");
    add_item( "boats",
        "You see some fishing boats, ferries, and recreational " +
        "boats on the lake.\n");
    add_item(({ "something", "something"}),
        "You can make out what appears to be an island, rising " +
        "from the surface of the lake.\n");
    add_item( "island",
        "You squint while look out onto the lake. In the distance " +
        "you think you see an island, but you're not sure. Whatever " +
        "it is, it is tiny from here.\n");
    add_item( "trees",
        "Most of the trees here are primarily deciduous trees " +
        "like maples, birches, and willows. The prominent trees " +
        "growing here are poplars. They grow along the lake's edge, " +
        "creating a wall of foliage and cover the foothills but " +
        "stop at the base of the mountains. Growing on the mountains " +
        "are evergreen trees like pine, hemlocks, firs, and other " +
        "coniferous trees. Under the trees is a carpet of dead twigs, " +
        "leafs and other forest debris. Some scraggly grasses grow " +
        "under the trees.\n");
    add_item(({ "grass", "grasses"}),
        "The grass waves in the breeze as it covers the field here. " +
        "Oddly enough, it is cut short by the numerous animals that " +
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
        "The leaves rustle in the breeze that comes from off the " +
        "lake. Some dead leaves lie under the trees.\n");
    add_item( "twigs",
        "A few dead twigs lie under the trees.\n");
    add_item( "canopy",
        "As you look up, you notice the canopy is thick " +
        "with leaves and branches. They block most of the " +
        "sunlight, creating a cool area here in the fields.\n");
    add_item( "field",
        "The field spreads out away from the road and lake. It " +
        "is green and healthy.\n");

    create_road();
}
 
create_road()
{
}
 
string
road_desc()
{
    switch(random(5))
    {
        case 0:
        return "   You are walking along the western edge of " +
        "a great lake. Many trees grow along the shore and " +
        "obscure your view of the water. They rise tall into " +
        "the sky creating a shaded canopy across the road here. " +
        "The road is well used by travellers heading north into " +
        "the mountains and south into Emerald. A great field " +
        "spreads out in all directions from the shore.\n\n";
        break;
        case 1:
        return "   You walk along a worn road that cuts through " +
        "a large field. It continues north into some mountains " +
        "and south into Emerald. To your east is a great lake. " +
        "Tall trees grow along its edge. Their foliage shades " +
        "the road here. A gentle breeze blows through the trees " +
        "as it comes off the lake. It cools you and fills the " +
        "air with sweet fragrance.\n\n";
        break;
        case 2:
        return "   The road wanders here as it goes under the " +
        "tall trees. The trees block your view of " +
        "the western edge of a great lake. Sunlight shines through " +
        "the trees and creates a mosaic of dancing shapes on the " +
        "ground. You can see animals in the field as you travel on " +
        "the road.\n\n"; 
        break;
        case 3:
        return "   The road is quiet here. You feel relaxed as you " +
        "look around at the beauty of the land. The trees along " +
        "the shore offer shade but are open to allow a view of the " +
        "lake. The lake is large, you can't even see the other " +
        "side of it. Boats can be seen on its surface. Birds swim " +
        "around on the edge. Occasionally, you see a fish jump " +
        "from the water.\n\n";
        break;
        case 4:
        return "   The road meanders here as it follows the " +
        "shoreline. It is well worn from constant use. Trees grow " +
        "along the eastern edge of the road. Between the trees " +
        "you see the lake, stretching out in the distance. Heavy " +
        "bushes grow along the other side of the road, making it " +
        "impossible to leave the road. Mountains rise in the north.\n\n";
        break;
        default:
        return "   You walk along the edge of a great lake. " +
        "The road is smooth and well worn. Beautiful trees grow " +
        "along the shoreline. They shade the road and bend in " +
        "the gentle wind. You can see through them and out onto " +
        "the lake. A field grows from the edge of the road and " +
        "out into the distance. Bushes grow along the edge of the " +
        "road preventing travellers from leaving the road.\n\n";
        break;
     }
}
