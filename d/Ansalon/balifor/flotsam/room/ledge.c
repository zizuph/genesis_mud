#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <ss_types.h>
#include <macros.h>

inherit FLOTSAM_OUT;
object door;

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("On a window ledge high above an alley");
    set_long("@@long_descr");

    add_item("ledge","This window ledge is high " +
      "above the alley.\n");
    add_item("latch","On the other side of the window, "+
      "this simple wooden latch is used to lock the window.\n");
    add_item("alley","Beneath the ledge is a filthy dark alley. " +
      "Although it is a fair drop from here, it seems to be the " +
      "only way off this ledge, apart from going through the window " +
      "itself.\n");

    add_cmd_item(({"down","off ledge","into alley"}),"jump",
      "@@jump_down");
    add_cmd_item("window",({"smash","break"}),
      "@@break_window");

    door = clone_object(FOBJ + "window1a");
    door->move(TO);
    reset_flotsam_room();
}

string
break_window()
{
    write("You think about taking a mighty "+
      "swing at the window, but then realise that you'll "+
      "probably loose your balance and fall off the ledge "+
      "if you even try breaking the window.\n");
    return "";
}

string
long_descr()
{
    return tod_descr1() + "You balance precariously on a window " +
    "ledge above an alley in the town of Flotsam. \n";
}

string
jump_down()
{
    write("You jump off the ledge and into the alley below...\n\n");
    say(QCTNAME(this_player()) + " jumps off the ledge.\n");
    tell_room(FROOM + "street30",QCNAME(TP) + " drops with " +
      "catlike grace into the alley behind you. \n");
    TP->move_living("M",
      FROOM + "street30",1,0);
    return "";
}

