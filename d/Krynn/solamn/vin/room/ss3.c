/* Street south 3, new VK
 * By Teth, Dec. 3 1996
 */


#include "../local.h"
inherit STREET;

public void
create_street()
{
    add_my_desc("A merchant has set up a store to the north, " +
        "with a prominent storefront. The street continues to " +
        "the west, and also opens into a courtyard to the east.\n");
    AI("store","The store has a prominent storefront.\n");
    AI(({"storefront","prominent storefront"}),"A banner on " +
        "the storefront proclaims:\n\nVingaard Keep Store\n\n");
    AI("banner","The banner proclaims:\n\nVingaard Keep Store\n\n");
    AI("courtyard","The courtyard lies near the entrance to " +
        "Vingaard Keep.\n");

    AE(VROOM + "ss2", "west", 0);
    AE(VROOM + "weap_arm_store", "north", 0);
    AE(VROOM + "courtyard", "east", 0);
}
