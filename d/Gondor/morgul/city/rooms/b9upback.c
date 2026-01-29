#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MIN_AWARENESS		25
#define ITEM_ARRAY		({ (WEP_DIR + "dagger"), \
				   (ARM_DIR + "fsshield"), \
                                   (OBJ_DIR + "pan"), \
                                   (OBJ_DIR + "oilflask"), \
                                   (OBJ_DIR + "torch"), \
				})


public void    reset_room();
static object  yrchor;
static int     c;

public void
create_morgul_room()
{
    set_extraline("This back room is the living quarters and office " +
    "of an uruk Captain in the army of Morgul. It is dirty and in " +
    "the corner there lies a heap of garbage. The furniture consists " +
    "of a bed and a table.");
  add_item(({"bed","cot","blanket", "wooden frame", "frame"}), BSN(
    "There is a single bed standing against the west wall. It is made " +
    "from a rough wooden frame filled with rags and straw, covered " +
    "by a heavy blanket."));
  add_item(({"table"}), BSN(
    "The table is of the same rough fabrication as the wooden frame " +
    "of the bed. Strangely, it is covered with papers and scrolls. " +
    "You wonder what use an orc might have for paper, and you shudder " +
    "at the thought."));
  add_item(({"papers", "scrolls"}), BSN(
    "Just a wild heap of papers and scrolls covering the table. " +
    "You cannot imagine that there might be anything of interest " +
    "among them, so you decide to ignore them."));
  add_item(({"furniture"}), "A table and a bed.\n");
  add_item(({"corner", "heap", "garbage", "pile", "rubbish"}), BSN(
    "A large pile of stinking garbage. You can make out gnawed bones, " +
    "broken parts of weapons and furniture, old, half-decayed books, " +
    "a few stones and rocks are mouldering on top of the heap, and " +
    "who knows what else might be found deeper inside the pile."));
  add_item(({"bones", "parts", "books"}), BSN(
    "It stinks, and it is rotten beyong any use whatsoever. So forget " +
    "about it."));
  set_road(5);
  set_side("east");
  add_prop(ROOM_I_LIGHT,1);
  add_prop(OBJ_S_SEARCH_FUN, "do_search");

  add_exit(MORGUL_DIR + "city/rooms/b9up", "east", "@@block_npc",1);
  reset_room();
}

void
clone_orc()
{
    if (objectp(yrchor))
        return;

    yrchor = clone_object(MORGUL_DIR + "npc/yrchor");
    yrchor->arm_me();
    yrchor->move_living("down", TO);
}

void
reset_room()
{
    c = random(4)+1;
    clone_orc();
}

string
do_search(object pl, string str)
{
    int     as;
    object  ob;

    if (!strlen(str))
        return 0;

    if (member_array(str, ({"corner", "heap", "garbage", "pile", "rubbish"}))
        == -1)
        return 0;

    pl->command("puke");

    if ((((as = pl->query_skill(SS_AWARENESS)) < MIN_AWARENESS) && 
        random((100 - as + MIN_AWARENESS)/MIN_AWARENESS*2)) || (c == 0))
        return "You search through the pile of garbage, but you don't find " +
               "anything interesting.\n";

    ob = clone_object(ONE_OF_LIST(ITEM_ARRAY));
    if (ob->move(TO))
        ob->move(TO, 1);
    c--;
    return "You search through the pile of garbage and find "+LANG_ASHORT(ob)+".\n";
}

