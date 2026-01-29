inherit "/d/Gondor/common/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

int    potion_taken;

void
create_room()
{
    set_short("in a small damp cellar");
    set_long(BSN("The cellar isn't any larger than the hut above, and "
      + "the damp air and earth walls makes it a less pleasant place to "
      + "stay. There is not much of interest here. A few blankets are "
      + "rolled up in a corner, and a few shelves are mounted on the "
      + "walls. A wooden ladder leads up through a trapdoor in the "
      + "wooden ceiling."));
    add_prop(ROOM_I_INSIDE,1);
    add_item(({"shelves","shelf"}),"@@exa_shelves");
    add_item("blankets","Probably for use when the winter nights are really cold.\n");
    add_item(({"floor","ground"}), BSN(
        "The floor is dirty soil, really, as are the walls."));
    add_item(({"trapdoor","trap door"}), BSN(
         "This trapdoor seems to be the only way out of here. A ladder "+
         "leads up through it."));
    add_item("ladder","The wooden ladder leads up through a trapdoor.\n");

    add_exit(LEB_DIR + "road/hut1","up",0,2);
}

void
init()
{
   add_action("check_time","time");
   add_action("take_func","take");
   add_action("take_func","get");
   ::init();
}

string
exa_shelves()
{
    if (!potion_taken)
        return "All you see on the shelves is a potion of some sort.\n";
    return "The shelves are rather empty.\n";
}

int
take_func(string str)
{
    object ob;
    if (!strlen(str))
        return 0;
    if (str != "potion" && str != "potion from shelf")
        return 0;
    if (potion_taken)
        return 0;
    ob = clone_object(RANGERS_DIR+"potions/este");
    ob->set_up_effect(50, 0, 80);
    potion_taken = 1;
    write("You take the potion from the shelf.\n");
    say(QCTNAME(TP)+" takes a potion from the shelf.\n",TP);
    if (ob->move(TP))
    {
        ob->move(TO);
        write("You cannot carry more, so you hurriedly put it down.\n");
        say(CAP(OBJECTIVE(TP))+" cannot carry more, and sets the potion "
          + "down on the floor.\n",TP);
    }
    return 1;
}

