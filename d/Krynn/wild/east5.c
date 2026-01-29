/* eastroad coded by Ashbless */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit  OUTWILDROOM

create_wild_room()
{
    set_short("Bend in east road");
    set_long(
        "You are on the east road. Here the road bends " +
         "to the northeast, heading towards a dark wood at the foot " +
         "of some low mountains. The road leads west through farmland " +
         "towards a distant forest " +
        "and the village of Solace. " +
        "Twenty feet from the road, a thick forest blocks travel " +
        "to the south and east. " +
        "To the north is farmland and you can " +
        "occasionally catch a glimpse of farmers wading through the " +
        "tall golden wheat." +
        " Ominous on the northern horizon, unnatural looking " +
        "storm clouds claw the sky with dark fingers.\n");

    add_exit(TDIR + "east4", "west");
    add_exit(TDIR + "east6", "northeast");
    add_exit(TDIR + "field4", "north");

    add_item("distant forest", BS(
        "The road disappears into a forest far to " +
        "the west. You can't make out much detail from here.",70));
    add_item(({"wheat","tall wheat","tall golden wheat",
        "farmlands","golden wheat","farmland","field","wheat field"}),BS(
        "Swaying rhythmically " +
        "in the wind, the golden wheat is ready to be " +
        "harvested. The field stretches to the north and west.",70));
    add_item(({"road","east road"}),BS(
        "This is the east road of Solace. " +
        "Here it bends northeast towards " +
        "a dark wood at the foot of some low mountains, " +
        "and west through farmlands to a distant forest.",70));
    add_item(({"mountains","low mountains","mountain range"}),BS(
        "A low range of mountains is visible on the eastern " +
        "horizon.",70));
    add_item(({"cloud","clouds","storm cloud","storm clouds",
        }),BS("These clouds do not look natural and give you " +
        "a feeling of forboding evil.",70));
    add_item(({"dark wood","wood"}),BS(
        "It lies at the foot of a low mountain range and " +
        "the road leads into it. " +
        "Gnarled oak trees cast dark shadows on the surrounding area." +
        "",70));
    add_item("thick forest",BS(
        "A thick forest of aspen and pine lines the south and east sides " +
        "of the road. The cool shade looks inviting but " +
        "there is no visible path through the dense undergrowth.",70));
}
