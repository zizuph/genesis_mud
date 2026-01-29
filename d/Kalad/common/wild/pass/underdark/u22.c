/*
 * /d/Kalad/common/wild/pass/underdark/u22.c
 * Purpose    : For the hell of it
 * Located    : Under Hespyre Mts.
 * Created By : Antharanos
 * Modified By: Nikklaus, Oct'97: adapted to dark_dom inherits
 */

# pragma strict_types
# include "dark_dom.h"

inherit DARK_DOM;

object ob1;
object ob2;
object ob3;
object ob4;

void
create_dark_dom()
{
    set_short("Small Pool");
    set_long(long()+
      "This fair-sized cavern contains a small, dark pool at its center. "+
      "The ground is remarkably clear of any large debris, the largest "+
      "being a few small stalagmites. The walls about you seem to cover "+
      "you protectively, unlike the rest of the underdark, where the walls "+
      "seem to close in upon you. A small passage leads west.\n");
    add_item(({"small dark pool","small pool","dark pool","pool"}),
      "Its dark surface is broken only by the occasional ripple, otherwise "+
      "it is as still as death itself.\n");
    add_item(({"ground","small stalagmites","small stalagmite","stalagmites","stalagmite"}),
      "The rocky surface of the cavern floor is cluttered with a few "+
      "insignificant stalagmites and other tiny debris.\n");
    add_item(({"tiny debris","debris"}),"A few small rocks lie scattered "+
      "on the ground.\n");
    add_item(({"walls","wall"}),"Made of the dark stone of the underdark, it "+
      "seems to radiate darkness.\n");
    add_item(({"ceiling"}),"It lies many feet above you, definitely out of your "+
      "reach.\n");
    add_exit(DARK(u21), "west");
    set_alarm(1.0, 0.0, "reset_room");
}

void
reset_room()
{
    if(!ob1)
	(ob1 = clone_object(DEEP_ROTHE))->move_living("xxx", this_object());
    if(!ob2)
	(ob2 = clone_object(DEEP_ROTHE))->move_living("xxx", this_object());
    if(!ob3)
	(ob3 = clone_object(DEEP_ROTHE))->move_living("xxx", this_object());
    if(!ob4)
	(ob4 = clone_object(DEEP_ROTHE))->move_living("xxx", this_object());

    ob1 -> team_join(ob2);
    ob1 -> team_join(ob3);
    ob1 -> team_join(ob4);
}
