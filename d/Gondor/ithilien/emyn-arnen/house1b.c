inherit "/d/Gondor/common/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define MIN_AWARENESS		25
#define ITEM_ARRAY		({ (WEP_DIR + "knife"), \
                        	   (WEP_DIR + "hatchet"), \
                        	   (WEP_DIR + "qstaff"), \
				   (ARM_DIR + "fjacket"), \
				   (EDORAS_DIR + "obj/leather"), \
				   (EDORAS_DIR + "obj/robe"), \
				   (EDORAS_DIR + "obj/leathcoat"), \
				   (EDORAS_DIR + "obj/diamond"), \
                                   (OBJ_DIR + "pan"), \
                                   (OBJ_DIR + "oilflask"), \
                                   (OBJ_DIR + "oilflask"), \
                                   (OBJ_DIR + "torch"), \
                                   (OBJ_DIR + "torch"), \
				})
void    reset_room();

int     c;
object  wdog;

void
create_room()
{
    set_short("a back room in a house in Emyn Arnen");
    set_long(BSN("This back room looks worse than the rest of the ground " +
        "floor. In the back, the ceiling has collapsed and the walls and " +
        "the roof of the upper floor buried that part of the room. There " +
        "are no windows here, and the only door leads back south."));

    add_item(({"ceiling", "roof"}), BSN(
        "The ceiling of this room has collapsed in the back, and the upper " +
        "floor fell down into this room, filling it with rubble."));
    add_item(({"ground", "floor"}), BSN(
        "The ground is covered by rubble and dirt. Where the old floor " +
        "is still visible, rotten wooden planks can be seen."));
    add_item(({"rubble", "dirt", "earth"}), BSN(
        "Just rubble and dirt. It stinks, and there is most likely " +
        "nothing valuable among it."));
    add_item(({"window", "windows", "door"}), BSN(
        "If the room once had windows, they must have been in the northern " +
        "wall that is hidden behind the rubble filling the room. The only " +
        "door is leading south."));

    add_exit(ITH_DIR + "emyn-arnen/house1", "south", 0, 1);

    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    reset_room();
}

void
reset_room()
{
    c = random(3) + 2;

    if (!objectp(wdog))
    {
        wdog = clone_object(NPC_DIR + "wdog");
        wdog->set_random_move(1);
        wdog->move(TO);
        tell_room(TO, QCNAME(wdog)+" stealthily trots into view.\n");
    }
}

string
do_search(object pl, string str)
{
    int     as;
    object  ob;

    if (!strlen(str))
        return 0;

    if (member_array(str, ({"rubble", "heap", "garbage", "dirt", "earth"}))
        == -1)
        return 0;

    if ((((as = pl->query_skill(SS_AWARENESS)) < MIN_AWARENESS) && 
        random((100 - as + MIN_AWARENESS)/MIN_AWARENESS*2)) || (c == 0))
        return "You search through the rubble in the back part of the room, " +
               "but you don't find anything interesting.\n";

    ob = clone_object(ONE_OF_LIST(ITEM_ARRAY));
    if (ob->move(TO))
        ob->move(TO, 1);
    c--;
    return "You search through the rubble and find "+LANG_ASHORT(ob)+".\n";
}
