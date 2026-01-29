/* eastroad coded by Ashbless */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit  OUTWILDROOM

create_wild_room()
{
    set_short("East road");
    set_long(
        "You are on the east road. Southwest of here the road bends " +
         "to the west, heading through farmlands and disappearing " +
         "into a distant forest. " +
        "East of the road is a grassy meadow, nestled between " +
        "a dark wood to the northeast and a thick forest to the south. " +
        "The road leads straight into the dark wood, " +
        "which lies at the foot of some low mountains. " +
        "To the west is farmland and you can " +
        "occasionally catch a glimpse of farmers wading through the " +
        "tall golden wheat." +
        " Ominous on the northern horizon, unnatural looking " +
        "storm clouds claw the sky with dark fingers.\n");

    add_exit(TDIR + "east5", "southwest");
    add_exit(TDIR + "field4", "west");
    add_exit(TDIR + "east7", "northeast");

    add_item("distant forest", BS(
        "The road disappears into a forest far to " +
        "the west. You can't make out much detail from here.",70));
    add_item(({"wheat","tall wheat","tall golden wheat",
        "farmlands","golden wheat","farmland","field","wheat field"}),BS(
        "Swaying rhythmically " +
        "in the wind, the golden wheat is ready to be " +
        "harvested. West of here, the field stretches to the north " +
        "and further west.",70));
    add_item(({"road","east road"}),BS(
        "This is the east road of Solace. " +
        "Southwest of here it bends west towards " +
        "a distant forest. It continues northeast and " +
       "disappears into a dark wood at the foot of " +
        "some low mountains.",70));
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
        "A thick forest of aspen and pine lines the south side " +
        "of the road. The cool shade looks inviting but " +
        "there is no visible path through the dense undergrowth.",70));
    add_item(({"meadow","grassy meadow"}),BS(
        "To the east, nestled between the dark wood and " +
        "the forest south of here, a grassy meadow " +
        "runs east towards the mountains. " +
        "One of the favorite picnic spots of the " +
        "residents of Solace, it offers a well " +
        "needed escape from the rigors of ordinary " +
        "life.",70));
}
