
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("On a precipice");
  set_long("You stand atop a small precipice that looks out "+
     "west into a gaping chasm. The sheer eastern wall rises "+
     "out of sight, running in a north-south direction. A fierce "+
     "wind tears through here. You wince at the sound of its high "+
     "pitched wailing. The only exit appears to be north, back "+
     "into the windy tunnel.\n");

  add_item(({ "chasm", "darkness" }),
     "It fills the western half of this cavern.\n");
  add_item(({ "face", "wall", "eastern wall" }),
     "Its grey surface looks relatively smooth and even.\n");
  add_item(({ "depths", "darkness" }),
     "Looking down into the chasm gives you a momentary sense "+
     "of vertigo.\n");
  add_item(({ "precipice", "ledge" }),
     "You stand atop the overhang of the cliff beneath you. "+
     "There's not much room to move around here.\n");
/* add_exit("/d/Shire/khazad/west/tunnel3b","north",0,1);*/
}

public void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if (!living(ob))
    return;
  if (file_name(from) == "/d/Shire/khazad/west/tunnel3b")
  {
    write("A strong wind buffets your body as you attempt to go south.\n");
    write("You step out of the tunnel onto a small precipice.\n");
  }
}

void
init()
{
  ::init();
  add_action("do_exit","enter");
}

int
do_exit(string str)
{
  if (str != "tunnel")
  {
    notify_fail("Enter what?\n");
    return 0;
  }

  else
  {
    say(QCTNAME(TP) + " enters the tunnel.\n");
    TP->move_living("M","/d/Shire/khazad/west/tunnel3b",0);
    say(QCTNAME(TP) + " arrives.\n");
    say(QCTNAME(TP) + " leaves north.\n");
    TP->move_living("M","/d/Shire/khazad/west/tunnel3a",0);
    say(QCTNAME(TP) + " arrives.\n");
    say(QCTNAME(TP) + " leaves north.\n");
    TP->move_living("M","/d/Shire/khazad/west/wp15",0);
    say(QCTNAME(TP) + " arrives.\n");
    return 1;
  }
}
