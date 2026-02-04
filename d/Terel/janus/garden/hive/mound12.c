/* mound 12 */
/* janus 921111 */
/*
    Modified: 1 Aug 2003, by Bleys
	- Changed the gem reward here to use standard gems
 *
 * Lucius - Jan 2021
 *    Cleaned up and modernized.
 */
inherit "/std/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Terel/common/terel_defs.h"
#include "/d/Genesis/gems/gem.h"

#define TP             this_player()
#define TO             this_object()

private string *GEMS = ({
    GEM_OBJ_DIR + "jade.c",
    GEM_OBJ_DIR + "opal.c",
    GEM_OBJ_DIR + "pearl.c",
    GEM_OBJ_DIR + "spinel_red.c"
});

public int ITEMS = 3;

public void
reset_room()    { ITEMS = 3; }

public void
create_room()
{
    setuid();
    seteuid(getuid());

    set_short("dump");
    set_long("This small room must be used as a dump for the refuse "+
	"that the bugs produce. The smell in here is almost overwhelming. "+
	"There are large piles of debris, consisting of skeletons, trash and "+
	"more recent refuse.\n");

    add_item(({"ground","floor","walls","room","trash","refuse","debris"}),
        "The walls, floor and ceiling are warm to the touch.\n");
    add_item(({"room","debris"}),
        "There is a lot of debris lying around in this room. "+
        "The piles of debris might contain something useful.\n");

    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(ROOM_I_LIGHT,  0);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(JANUSDIR + "garden/hive/mound10","up",0,6);

    add_npc(JANUSDIR + "monsters/wbug");
    add_npc(JANUSDIR + "monsters/wwbug");
}

public string
do_search()
{
    int i1 = TP->query_skill(SS_AWARENESS),
        i2 = i1 - random(15);

    if (!CAN_SEE_IN_ROOM(TP))
    {
        return "You are blind as a bat in the darkness, so you'd better "+
	  "get some light if you want to search here.\n";
    }

    if (i2 > 0)
    {
        object ob;
	if (!TP->test_bit("Terel", QUEST_JJ2_GROUP, QUEST_JJ2_BIT))
        {
	    ob = clone_object(JANUSDIR + "garden/hive/bracelet");
	    ob->add_prop("_bracelet_finder", TP->query_name());
	    ob->move(TO);
            return "On the arm of a skeleton you find an onyx bracelet.\n";
	}

        switch(ITEMS--)
        {
        case 3:
	{
	    //ob=RANDOM_GEM(GEM_SLIGHTLY_COMMON);
	    ob = clone_object(one_of_list(GEMS));
	    ob->move(TO);
	    return "You find a valuable gem. The previous owner won't "+
	      "complain since, the corpse you found the gem on has been "+
	      "here for quite some time.\n";
	}
        case 2:
        {
	    ob = clone_object(JANUSDIR + "garden/hillebard");
	    ob->move(environment(TP));
	    return "You find a polearm of some kind.\n";
	}
        case 1:
        {
	    ob = clone_object(JANUSDIR + "garden/potion");
	    ob->move(environment(TP));
	    return "You find a small bottle containing a strange fluid.\n";
	}
        } // switch()
    }
    return "";
}
