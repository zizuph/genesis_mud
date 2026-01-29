/* Mortis 9.2014
 */

#include <cmdparse.h>
#include <macros.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>
#include "../../local.h"
#include CLOCKH

inherit TOA_ROOMBASE;

#define VIEWE                (TOA + "toa01")
#define VIEWW                (MERCH + "m05")

object tguard1, tguard2, tguard3;

string
query_to_jail()
{
    return "northeast";
}

void
reset_palan_room()
{
    if (!present(tguard1, TO))
    {
        tguard1 = clone_object(TOA + "living/toa_guard");
        tguard1->move(TO);
    }
    if (!present(tguard2, TO))
    {
        tguard2 = clone_object(TOA + "living/toa_guard");
        tguard2->move(TO);
    }
    if (!present(tguard3, TO))
    {
        tguard3 = clone_object(TOA + "living/toa_guard");
        tguard3->move(TO);
    }
}

void
create_palan_room()
{
    SHORT("A windowed corridor on the ground floor of the Tower of Arms");
    LONG("A slit window looks out to the west and down at the entrance of "
    + "the tower from this guardroom. The chink of armour and clump of "
    + "bootsteps echo about.\n");

    ITEM(({"corridor", "corridors"}), "A marble corridor extends from "
    + "here.\n");
    ITEM(({"slit", "window", "slit window"}), "The slit window is not large "
    + "enough to climb through, but it does provide a <view> of the stair "
    + "landing west of the Tower of Arms as well as a <view> of the entrance "
    + "below into the tower.\n");

    CMD(({"down", "below", "entrance"}), "view", "@@view_entrance");
    CMD(({"out", "west", "landing"}), "view", "@@view_landing");

    EXIT(TOA + "toa04", "northeast", 0, 0);

    reset_palan_room();
}

view_entrance()
{
    /* This function returns an equivalent of 'look' from m01
     * most importantly without any supporting code from the
     * target room.
     */

    object *inv, *obs, *ppl, target;
    string desc;

    write(VIEWE->long());
    target = find_object(VIEWE);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    {
        write(one_of_list(({"From above you can make out ",
                            "You believe you spot ",
                            "Your eyes come across "}))
                            + desc + " on the ground.\n");
    }

    if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    {
        write(one_of_list(({"Down below you see ",
                            "You notice below ",
                            "Down below you spy "}))
                            + desc + " inside the tower.\n");
    }
 
    return 1;
}

view_landing()
{
    /* This function returns an equivalent of 'look' from m01
     * most importantly without any supporting code from the
     * target room.
     */

    object *inv, *obs, *ppl, target;
    string desc;

    write(VIEWW->long());
    target = find_object(VIEWW);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    {
        write(one_of_list(({"From above you can make out ",
                            "You believe you spot ",
                            "Your eyes come across "}))
                            + desc + " on the ground.\n");
    }

    if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    {
        write(one_of_list(({"Down below you see ",
                            "You notice below ",
                            "Down below you spy "}))
                            + desc + " outside the tower.\n");
    }
 
    return 1;
}

