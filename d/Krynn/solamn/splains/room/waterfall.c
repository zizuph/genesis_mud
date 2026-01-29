/* created by Aridor 12/20/93 
 *
 * chest and scroll added by Arman 27/06/2018
 */

#include "../local.h"
#include <stdproperties.h>
#include <money.h>

inherit INSIDE_BASE;

object chest, scroll, money;

void
reset_splains_room()
{
    seteuid(getuid(TO));

    if (!present("chalk",TO))
    {
        clone_object("/d/Krynn/solamn/thief/obj/chalk")->move(TO);
    }

    if(!objectp(chest))
    {
        chest = clone_object("/d/Krynn/solamn/splains/obj/chest");
        chest->move(TO);
    }

    if (!present(scroll, chest))
    {
        scroll = clone_object("/d/Krynn/common/scrolls/flaming_fist_scroll");
        scroll->move(chest, 1);
        chest->add_prop(CONT_I_CLOSED, 1);
        chest->add_prop(CONT_I_LOCK, 1);
    }

    if (!P(money, chest))
    {
        money = MONEY_MAKE_SC(random(40) + 40);
        money->move(chest, 1);
        chest->add_prop(CONT_I_CLOSED, 1);
        chest->add_prop(CONT_I_LOCK, 1);
    }

}

void
create_splains_room()
{
    set_short("Behind the waterfall");
    set_long(BS("You are in a small cave behind the waterfall. There is nothing here except " +
		"a small hole in the northwestern wall. The ground is wet from the water " +
		"rushing by next to you.",SL));

    add_item(({"ground","walls","wall"}),
	     "The ground and walls are solid rock. This cave looks natural and is very " +
	     "well hidden behind the waterfall. There are some scratches on the northwestern " +
	     "wall, though, next to the hole leading into darkness.\n");
    add_item(({"scratches"}),"Hmm, it almost looks like you can read them!\n");
    add_cmd_item(({"scratches"}),"read","You decipher the words 'Danger ahead.'!\n");
    add_item(({"hole","small hole"}),
	     "It's just a hole, there seems to be another room behind it. It is large enough " +
	     "that you can enter it by going northwest.\n");
    add_item(({"water","waterfall","curtain"}),
	     "The water rushes by to your east. You cannot see anything beyond the curtain " +
	     "of water.\n");
    add_item(({"river"}),
	     "It's not a very wide river, and the waterlevel is much lower than the " +
	     "plains. The river is comes from a narrow valley to your northwest and flows " +
	     "north of you and to the east onto the plains.\n");
    add_cmd_item(({"river","water","waterfall","in water"}),({"swim","enter"}),
		 "@@go_back_to_plains");

    add_exit(THIEF,"northwest","@@not_yet");

    reset_room();
}


string
go_back_to_plains()
{
  write("Headfirst, you plunge into the water of the river.\n");
  TP->move_living("paddling along the river",ROOM + "in_water",0,1);
  find_player("aridor")->catch_msg(TP->query_name() + " leaves THIEFAREA to waterfall.\n");
  return "";
}

int
not_yet()
{
  write("You climb into the hole.\n");
  find_player("aridor")->catch_msg(TP->query_name() + " enters THIEFAREA from waterfall.\n");
  return 0;
}
