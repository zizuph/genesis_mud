#include "defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

#define LIVE_I_FLYING	    "_live_i_flying"
#define LIVE_I_LEVITATING   "_live_i_levitating"

CONSTRUCT_ROOM
{
    set_short("On a Plateau");
    set_long(
	  "This is a plateau overlooking a gap with boiling water under.\n"
	+ "As you managed to jump over to this place, let us hope you can "
	+ "jump across backwards as well, because there are no other exits.");

    add_item(({"gap","sounds","water", "steam"}),
	"The gap must be at least 10 meters wide, and you surely would not "+
	"like to fall down into the water below. You would be fried in seconds! "+
	"You can see some sort of narrow passage on the other side."
    );
    add_item(({"passage", "other side", "opposite side"}),
	"It is a distance of approximately 10 meters to the other side. "+
	"You would not even think of what might happen if you tried to "+
	"jump across the gap and fall into the steaming water. "+
	"@@desc_other_side@@"
    );
    reset();
}

RESET_ROOM
{
    if (!present("plate_troll", TO))
	clone_object("/d/Shire/moria/npc/plate_troll")->move(TO);
}

init()
{
    ::init();
    add_action("do_jump", "jump");
}

string
desc_other_side()
{
    object *ob, opp;
    object *liv;
    string str;

    if (LOAD_ERR(THIS_DIR + "shnarrw"))
	return "";

    opp = find_object(THIS_DIR + "shnarrw");

    if (!opp)
	return "";

    if (opp->query_prop(OBJ_I_LIGHT) <= 0)
	return "It is dark on the other side, so you can't percieve any details.";

    ob = FILTER_CAN_SEE(all_inventory(opp), TP);

    if (!sizeof(ob))
	return "You can't see anything special on the other side.";

    return "On the other side you can see "
	 + COMPOSITE_WORDS(map(ob, "desc", TO)) + ".";
}

string
desc(object ob)
{
    if (living(ob))
	return LANG_ADDART(ob->query_race_name());
    else
	return LANG_ADDART(ob->short());
}

int
do_jump(string str)
{
    int succ;
    int diff;

    if (strlen(str) && (str == "into water" || str == "down" || str == "water"))
    {
	if (random(DIS(TP)) < 30)
	{
	    write("You try to convince yourself that it is wise to jump, "
		+ "but fail, and decide not to.\n");
	    return 1;
	}
	write("You jump into the boiling water!!\n");
	TP->move_living("jumping into the water", THIS_DIR + "boilwat");
	return 1;
    }

    if (!strlen(str) || (str!="gap" && str!="across gap" && str != "across the gap"))
    {
	write("If you want to cross the water, you might: jump across the gap.\n"
	    + "But that would be very dangerous considering the hot steam of water.\n");
	return 0;
    }

    if (random(DIS(TP)) < 30)
    {
	write("You try to convince yourself that it is wise to cross it by jumping,\n"
	    + "but fail, and decide not to.\n");
	return 1;
    }

    diff = DIFF_SHEER_FOLLY
	 - 3 * TP->query_prop(LIVE_I_QUICKNESS)
	 - 2 * TP->query_prop(LIVE_I_LEVITATING)
	 - 4 * TP->query_prop(LIVE_I_FLYING)
	 + 2 * TP->query_encumbrance_volume();

    succ = TP->resolve_task(diff, ({ SS_ACROBAT, TS_DEX }));

    if (succ < 0)
    {
	write("You gather speed and try a heroic jump across the 10 meter gap. "
	    + "In the middle of the air you realise that you'll never reach the "
	    + "opposite side!!\n");

	say(QCTNAME(TP) + " gathers speed and heroically tries to jump across "
	  + "the gap, but fails and falls into the boiling water!\n");

	tell_room(THIS_DIR + "boilwat",
	      CAP(LANG_ADDART(TP->query_nonmet_name())) + " "
	    + "heroically jumps across the gap and falls into the boiling "
	    + "water with a splash!\n");

	TP->move_living("M", THIS_DIR + "boilwat", 1);
	return 1;
    }
    else
    {
	write("You gather speed and acrobatically jump across the 10 meter gap. "
	    + "You fly magnificiently through the air and lands safely on the other "
	    + "side!\n");

	say(QCTNAME(TP) + " gathers speed and acrobatically jumps safely "+
	    "over to the other side. You stand stunned there in mere "+
	    "admiration, but shivers when thinking what would happen if "+
	    HE_SHE(TP) + " had failed the maneuver.\n");

	tell_room(THIS_DIR + "shnarrw",
	      CAP(LANG_ADDART(TP->query_nonmet_name())) + " "
	    + "skillfully jumps across the gap and lands safely with a thud!\n");

	TP->move_living("M", THIS_DIR + "shnarrw", 1);
	return 1;
    }
}
