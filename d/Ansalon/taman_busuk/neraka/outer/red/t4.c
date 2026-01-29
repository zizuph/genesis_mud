#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_IN;
object troll1, troll2, troll3;

void
reset_neraka_room()
{
  if(!present(troll1, this_object()))
  {
    troll1 = clone_object(NNPC+"troll");
    troll1->move(this_object(), 1);
    troll1->arm_me();
  }

  if(!present(troll2, this_object()))
  {
    troll2 = clone_object(NNPC+"troll");
    troll2->move(this_object(), 1);
    troll2->arm_me();
  }

  if(!present(troll3, this_object()))
  {
    troll3 = clone_object(NNPC+"troll");
    troll3->move(this_object(), 1);
    troll3->arm_me();
  }
}
void
create_neraka_room()
{
    set_short("Inside a canvas tent");
    set_long("You have entered a large tent made of black canvas. The " +
        "canvas withstands the harsh weather of the winter in the " +
        "mountains. In the middle of the tent is a fire pit, and a " +
        "few bedrolls and chests are placed around the tent.\n");
    set_quarter(RED);
    add_item_tent();
    add_exit(NOUTER+"red/r31","out","@@msg@@",0,0);
    reset_room();
}

int
msg()
{
    write("You pull aside the flap, and exit the tent.\n");
    return 0;
}
