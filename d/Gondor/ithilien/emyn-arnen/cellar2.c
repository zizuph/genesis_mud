inherit "/std/room";

#include <language.h>
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

void
create_room()
{
    set_short("damp cellar");
    set_long(BSN("This is the cellar of the house. In a corner "
      + "stands a rickety ladder leading up. Along the walls, the "
      + "floor is littered by broken shelves."));

    add_item(({"ladder", "rickety ladder"}), BSN(
        "The ladder is leading up back to the ground floor of the "
      + "house. It does not look very strong but since it carried you "
      + "when you climbed down on it, it will probably be strong "
      + "enough to let you leave again."));
    add_item(({"roof", "ceiling", }), BSN(
        "The roof is made from stones forming a roman arch through "
      + "the whole length of the cellar. The construction looks rather "
      + "sturdy."));
    add_item(({"ground", "floor", }), BSN(
        "The floor is just earth that was stamped to make it level. "
      + "Along the walls, it is covered with the remains of shelves "
      + "that probably once were used to store food and valuables "
      + "here in the cellar."));
    add_item(({"wall", "walls"}), BSN(
        "The walls are made of rough stone which was hewn into large "
      + "uneven blocks. Along the walls lie the remains of broken "
      + "shelves."));
    add_item(({"stone", "stones", "blocks", }), BSN(
        "Large roughly hewn stone blocks hewn from grey rock."));
    add_item(({"remains", "shelves", "broken shelves"}), BSN(
        "The floor is littered with broken shelves. Once they probably "
      + "were used to store food and valuables. From the way all the "
      + "shelves were systematically destroyed you deduce that the "
      + "cellar was probably sacked long ago, and all valuable items "
      + "stolen, while the rest was smashed into little pieces."));

    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    clone_object(ITH_DIR + "emyn-arnen/obj/h2down_door")->move(TO);

    add_exit(ITH_DIR + "emyn-arnen/house2", "up", 0, 4);
    reset_room();
}

void
reset_room()
{
    c = random(3) + 1;
}

string
do_search(object pl, string str)
{
    int     as;
    object  ob;

    if (!strlen(str))
        return 0;

    if (member_array(str, ({"remains", "shelves", "ground", "floor", })) == -1)
        return 0;

    if ((((as = pl->query_skill(SS_AWARENESS)) < MIN_AWARENESS) && 
        random((100 - as + MIN_AWARENESS)/MIN_AWARENESS*2)) || (c == 0))
        return "You search through the remains of the shelves, " +
               "but you don't find anything interesting.\n";

    ob = clone_object(ONE_OF_LIST(ITEM_ARRAY));
    if (ob->move(TO))
        ob->move(TO, 1);
    c--;
    return "You search through the remains of the shelves and find "+LANG_ASHORT(ob)+".\n";
}
