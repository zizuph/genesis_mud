/* 
 * /d/Kalad/common/wild/pass/underdark/u19a.c
 * Purpose    : Provide space for bloodshed.
 * Located    : Under Hespyre, near shaft to Dark Dominion
 * Created By : Antharanos
 * Modifed By : Nikklaus, Oct'97: adapted to dark_dom inherit
 */

# pragma strict_types;
# include "dark_dom.h"

inherit DARK_DOM;

object ob1;
object ob2;
object ob3;
object ob4;

void
create_dark_dom()
{
    set_short("Chamber");
    set_long("You seem to have reached what can only be described as a "+
      "birthing chamber. Many crude and smelly furs blanket the stone floor "+
      "of this room. A raised area to the side of the chamber is covered in "+
      "some strange reddish moss. There seems to be a lot more waste here "+
      "than in other areas of the cavern.\n");
    add_item(({"crude furs","crude fur","smelly furs","smelly fur"}),
      "The stench coming from the crude hides is so bad that you can't bring "+
      "yourself to come close enough to examine them.\n");
    add_item(({"stone floor","floor"}),"The floor, like the rest of this "+
      "chamber is made of that same strangely dark stone of the underdark.\n");
    add_item(({"raised area","area"}),"A section of this room where the "+
      "rock is higher and apparently cleaner.\n");
    add_item(({"strange reddish moss","strange moss","reddish moss","moss"}),
      "It covers the entire raised area protectively.\n");
    add_exit(DARK(u19), "east");
    set_alarm(1.0, 0.0, "reset_room");
}

void
reset_room()
{
    if (!ob1)
	(ob1 = clone_object(TROG_FEM))->move_living("xxx", this_object());
    if (!ob2)
	(ob2 = clone_object(TROG_HATCH))->move_living("xxx", this_object());
    if (!ob3)
	(ob3 = clone_object(TROG_HATCH))->move_living("xxx", this_object());
    if (!ob4)
	(ob4 = clone_object(TROG_HATCH))->move_living("xxx", this_object());

    ob1 -> team_join(ob2);
    ob1 -> team_join(ob3);
    ob1 -> team_join(ob4);
}
