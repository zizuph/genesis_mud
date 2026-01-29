#include "../default.h"
inherit CVAN_ROOM;

#include <macros.h>
#include <filter_funs.h>
#include <ss_types.h>

#define KALAD_FOUND_LOT_EXIT "_kalad_found_lot_exit"

#define STEP	("@@step:/d/Kalad/common/caravan/step")

void
create_cvan_room()
{
    add_prop(OBJ_S_SEARCH_FUN, "search_ground");

    set_short("Caravan lot");
    set_long("You've reached a dead end on this large, muddy pathway. "+
      "The rest of the pathway continues back to the northeast. All "+
      "around you are crowded wagons of all kinds of descriptions. The "+
      "wagons are so tightly packed that the only visible exit is to "+
      "backtrack to the northeast. Bits of animal refuse are scattered here "+
      "and there along the muddy path.\n");

    add_item(({ "pathway" }), "It ends here and is completely covered in mud.\n");

    add_item(({ "crowded wagons", "wagons", "wagon" }),
      "Many wagons can be seen, each with its individual merchant-symbol "+
      "colorfully displayed on its side. One wagon in particular, in the "+
      "south, catches your attention. On its side is a symbol you have "+
      "never seen before, a sun that emits darkness, instead of light.\n");

    add_item(({ "animal refuse", "refuse" }),
      "There are a few scattered piles of animal droppings here, not nearly "+
      "as much as in other parts of the lot.\n");

    add_item(({ "pile", "piles" }),
      "The large piles of filth lie scattered about, covering much of the ground.\n");

    add_item(({ "ground", "filth" }),
      "It is muddy and covered with several piles of filth. There appears "+
      "to be one spot in particular where there is less filth.\n");

    add_item(({ "spot" }),
      "A small place, on the ground, that appears to have much less filth "+
      "on it, as though many people walked upon that particular part of the "+
      "ground.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/s9", "northeast",STEP);
    add_exit(CVAN + "lot/s15", "south");
    add_exit(CVAN + "lot/ur", "down", "@@exit_down", 1, 1);
}

int
exit_down()
{
    object *witnesses;
    if (TP->query_prop(KALAD_FOUND_LOT_EXIT))
    {
        witnesses = filter(FILTER_CAN_SEE_IN_ROOM(AINV(E(TP)) - ({TP})),
                TP->check_seen);
        foreach (object witness: witnesses)
        {
            if (!witness->query_prop(KALAD_FOUND_LOT_EXIT))
            {
                witness->add_prop(KALAD_FOUND_LOT_EXIT, 1);
                witness->catch_msg(QCTNAME(TP) + 
                    " uses a tunnel hidden amonst the filth!\n");
            }
        }
        return 0;
    }
    write("There is no obvious exit down.\n");
    return 1;
}

string
search_ground(object me, string arg)
{
    if (member_array(arg, ({"ground", "filth", "spot"})) < 0)
	    return "";

    if (TP->query_skill(SS_AWARENESS) < 30)
	    return "";

    TP->add_prop(KALAD_FOUND_LOT_EXIT, 1);
    return "You search carefully and discover a tunnel leading down!\n";
}
