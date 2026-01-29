/* 
 * /d/Kalad/common/wild/pass/underdark/u19.c
 * Purpose    : A space in rock to walk through
 * Located    : Under Hespyre Mts.
 * Created By : Antharanos
 * Modified By: Nikklaus, Aug'97: adapated to dark_dom
 */

# pragma strict_types
# include "dark_dom.h"
# include <macros.h>
# define TO this_object()
# define TP this_player()

inherit DARK_DOM;

object ob1;
object ob2;
/* by Antharanos */

void
create_dark_dom()
{
    set_long(long()+
      "The air is stale, reeking of half-rotten flesh and unburied fecal "+
      "waste. Whispered grumblings seem to come from the western and eastern "+
      "sides of the room. A flattened stalagmite serves as a crude throne "+
      "chair on the far side of the cavern. In the center of the cavern is "+
      "a crude pit. A dark passage leads to the south.\n");
    add_item(({"large oval cavern","large cavern","oval cavern","cavern"}),
      "An expansive hollow here within the underdark, side passages seem "+
      "to lead to other rooms.\n");
    add_item(({"strange dark stone","strange stone","dark stone","stone"}),
      "The entire cavern is made out of the substance.\n");
    add_item(({"flattened stalagmite","stalagmite","crude throne chair","crude chair","throne chair","throne","chair"}),
      "The natural stone formation has been carved, albeit roughly, into a "+
      "reasonable facsimale of a throne chair. It doesn't look very comfortable.\n");
    add_item(({"crude pit","pit"}),"Looking down you see nothing but "+
      "darkness, was that a sound you just heard coming from it? Perhaps "+
      "you should climb down and investigate...\n");
    add_exit(DARK(u19a), "west", "@@query_move");
    add_exit(DARK(u20), "south");
    add_exit(DARK(u19b), "east", "@@query_move");
    add_cmd_item(({"pit", "down"}), "climb", "@@climb");
    add_cmd_item("down", "climb", "@@climb");
    set_alarm(1.0, 0.0, "reset_room");
}

void
reset_room()
{
    if (!ob1)
	(ob1 = clone_object(TROG_CHIEF))->move_living("xxx", this_object());
    if (!ob2)
	(ob2 = clone_object(TROG_GUARD))->move_living("xxx", this_object());

    ob1->team_join(ob2);
}

int
query_move()
{
    if (present(ob2))
    {
	write("You are stopped by the troglodyte guard!\n");
	say("The troglodyte guard stops " + QCTNAME(TP) + " from going to the sidechamber.\n");
	return 1;
    }
    return 0;
}

string
climb()
{
    write("You start to climb down the pit but slip all the way down!\n");
    set_dircmd("down");
    TP->move_living("down into the pit", "/d/Kalad/common/wild/pass/underdark/u19c");
    return "You've landed at the bottom of the pit!\n";
}
