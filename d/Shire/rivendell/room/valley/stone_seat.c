/*
 * The terrace path along the river in Imladris
 * By Finwe, December 1997
 */

#include "local.h"
#include "/d/Shire/guild/noldor/noldor.h"
#include "/d/Shire/sys/defs.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"

#define BENCH_NAME  "stone bench"

inherit VALLEY_BASE;
inherit "/d/Gondor/common/lib/drink_water.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";

public string	look_at(string arg);
void
create_valley_room()
{
    set_extraline("You stand in a large garden east of the " +
        "house. Many flowers have been planted in various beds " +
        "here. In the center of the garden is a large tree. Its " +
        "bark is perfectly smooth with branches that spread out " +
        "shading the area. A stone bench encircles the tree " +
        "providing a place for visitors to sit and rest. A " +
        "balcony extends out over the river allowing visitors " +
        "to enjoy the view and sounds of the river. A large " +
        "white stone building stands north of here.");

    add_item(({"stone building", "building", "white stone building",
            "large white stone building"}),
        "The building stands in the distance. It is made " +
        "of white stone blocks and looks beautiful. A silver " +
        "fence surrounds the building with a gate in its center.\n");
    add_item(({"silver gate", "gate"}),
        "The gate is set in front of the building. It is simple " +
        "in design but effectively blocks out trespassers. The " +
        "gate is opened.\n");
    add_item(({"fence", "metal fence"}),
        "The metal fence is waist high and surrounds the stone " +
        "building. It is simple in design with a gate in the " +
        "center.\n");
    add_item(({"white blocks", "white stones"}),
        "Details are hard to make out of them, but they make " +
        "up a building north of here.\n");
    add_item(({"road","ground","path","stony path", "down"}),
        "The path is made out of flat stones that closely fit " +
        "together.\n");
    add_item(({"river", "river bruinen", "bruinen"}),
        "This finger of the river Bruinen rushes over west over " +
        "polished rocks. The water is clear and cold as it " +
        "comes from deep in the mountains. Its gentle music " +
        "fills the air.\n");
    add_item("balcony",
        "The balcony is a large piece of rock that that juts " +
        "out and overlooks the river. A silver banister " +
        "surrounds the outside of the rock, preventing " +
        "unsuspecting visitors from falling into the river " +
        "below.\n");
    add_item(({"banister", "handrail"}),
        "The banister is graceful and wrought of a silver " +
        "substance. It's strong and prevent anyone from falling " +
        "off the balcony and into the water.\n");
    
    add_item("flat stones",
        "The flat stones are smooth from countless feet that " +
        "have come this way. They are white with sublte streaks " +
        "of red and gold in them. They fit neatly together, " +
        "forming a path here.\n");
    add_item("large tree",
        "This tree is very large with branches that stretch out " +
        "and cover the garden. The width of the trunk suggests " +
        "that the tree is truly ancient. Large green leaves, " +
        "larger than a elf's hand, rustle in the breeze and " +
        "block your view of the sky. Nonetheless, gentle light " +
        "filters through the leaves, creating shifting pools of " +
        "light everywhere.\n");
    add_item(({"trunk", "trunks"}),
        "The trunk of the large tree is larger than anything " +
        "you have seen. The trunks of the other trees are " +
        "substantially large, too\n");
    add_item(({"bark", "tree bark"}),
        "The bark of the trees is smooth and dark brown.\n");
    add_item(({"branches", "branch"}),
        "The branches of the larger tree are very large and fan " +
        "out over the entire garden. They are covered with " +
        "leaves. The branches of the other trees are equally " +
        "impressive and covered with leaves.\n");
    add_item(({"leaves", "leaf"}),
        "The leaves are larger than a elf's hand. They are " +
        "green and tear shaped. They rustle in the breeze, " +
        "filling the air with a quiet whisper.\n");
    add_cmd_item(({"gate", "silver gate"}), "open",
        "The gate is closed and locked with a small lock.\n");
    add_item(({"lock", "small lock"}),
        "The lock on the gate is small and delicate looking, " +
        "yet probably quite strong. It requires a small key to " +
        "unlock it.\n");

	add_chair(BENCH_NAME,
	          "[down] [on] [the] [stone] 'bench'", 6);
    add_item(({"stone bench", "bench"}), &look_at(BENCH_NAME));

/*
    add_item(({"stone bench", "bench"}),
        "The bench is circular and surrounds the ancient " +
        "tree. The bench is smooth and ornately carved " +
        "from stone.\n");
*/
    set_drink_from(({"river", "river bruinen", "bruinen"}));

//    add_exit(NOLGLD_DIR + "foyer",  "north", "@@block_way@@");
    add_exit(NOLGLD_DIR + "foyer",  "north", check_sitting, 1);
    add_exit(VALLEY_DIR + "t_path14",  "southwest", check_sitting, 1);
}

void
init()
{
    ::init();
    init_drink();
    init_room_chairs();	

}

string short_desc()
{
    return ("A garden east of the House");
}

public int
do_climb(string str)
{
    if(!str)
    {
        NF("Climb what?\n");
        return 0;
    }
    write("You can't climb the " + str + ".\n");
    return 1;
}

block_way()
{

   if((!TP->query_wiz_level()) && (!IS_MEMBER(TP)))
      {
      write("A golden-haired Noldor blocks your way saying: " +
        "You are not permitted to go there, but soon the doors " +
        "will open.\n");
      return 1;
   }
   return 0;
}

/*
 * Function name:	leave_inv
 * Description	:	mask parent to be sure that departing players
 *			        are removed from chair/sofa occupants
 * Arguments	:	object ob -- the departing object
 *			        object dest -- its destination
 *
 * If they leave via a normal exit, they've already been made to stand
 * by the exit efunc check_sitting().
 * However, if they leave by quitting, going netdead, teleporting, etc
 * and we don't call leave_inv_room_chairs(), then they'll still look
 * as if they're here.
 */
public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */


/*
 * Function name:	look_at
 * Description	:	VBFC to describe chair/sofa + occupants
 * Arguments	:	string arg -- what's being looked at
 *				    null str -> it's the room
 * Returns	    :	string -- the description
 */
public string
look_at(string arg)
{

    switch ( arg )
    {
        case BENCH_NAME:
	    return "The bench is circular and surrounds the ancient " +
        "tree. The bench is smooth and ornately carved " +
        "from stone.\n" +
	    sitting_on_chair(BENCH_NAME, this_player(), 0);
    }
} /* look_at */