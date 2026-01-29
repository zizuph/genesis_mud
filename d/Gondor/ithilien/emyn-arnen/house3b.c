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
object  cb;

void
create_room()
{
    set_short("a kitchen in a small house in Emyn Arnen");
    set_long(BSN("This was the kitchen of the small house. In the west wall "
      + "is a fireplace. Like almost everywhere else there is no furniture "
      + "left here either."));

    add_item(({"ceiling", "roof"}), BSN(
        "The ceiling looks like it will fall down any moment."));
    add_item(({"ground", "floor"}), BSN(
        "The ground is covered by rubble and dirt. In the northeast corner "
      + "is a large heap of rotten wood, stones, ashes, bones, and other "
      + "refuse."));
    add_item(({"heap", "pile", "rubble", "dirt", "earth", "wood", 
        "stones", "ashes", "bones"}), BSN(
        "Just rubble and dirt, rotten wood, a few small rocks, ashes from old "
      + "fires, bones and other refuse. It stinks, and there is most likely "
      + "nothing valuable among it."));
    add_item(({"window", "windows", "door"}), BSN(
        "The windows are just gaping holes in the wall. There is only "
      + "one door, leading south into the rest of the house."));
    add_item(({"fireplace", "west wall", "western wall", "mantle",
        "bricks", }), BSN(
        "Inside the west wall of the kitchen is a fireplace, large enough "
      + "to roast a piglet or a small deer whole. The mantle of the "
      + "fireplace is made from bricks. In the corner next to the small "
      + "fireplace, there is a cupboard."));
    add_item(({"walls", "wall", "rocks", "mortar", }), BSN(
        "The walls are made from small rocks, roughly hewn to fit together. "
      + "The gaps are filled with mortar."));

    
    cb = clone_object(ITH_DIR + "emyn-arnen/obj/h3_cupboard");
    cb->move(TO);

    add_exit(ITH_DIR + "emyn-arnen/house3", "south", 0, 1);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    reset_room();
}

void
reset_room()
{
    c = random(3) + 2;
    cb->reset_container();
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
        return "You search through the rubble in the corner of the room, " +
               "but you don't find anything interesting.\n";

    ob = clone_object(ONE_OF_LIST(ITEM_ARRAY));
    if (ob->move(TO))
        ob->move(TO, 1);
    c--;
    return "You search through the rubble and find "+LANG_ASHORT(ob)+".\n";
}
