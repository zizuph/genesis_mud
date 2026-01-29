#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

inherit FOREST_OUT;
#define KEY1 "/d/Ansalon/balifor/flotsam/obj/window_key"
object bull;

int needle_found = 0,
reset_count = 1;


void
reset_flotsam_room()
{
    if (reset_count)
    {
	needle_found = 0;
	reset_count  = 0;
    }
    else
    {
	reset_count++;
    }

    if(!objectp(bull))
    {
	bull = clone_object(FNPC + "bull");
	bull->move(TO);
    }
}

create_flotsam_room()
{
    set_short("A small paddock");
    set_long("@@long_descr");

    add_item(({"paddock","small paddock","grazing cattle","cattle"}),
      "You stand in a small paddock used for grazing cattle. It " +
      "smells here of cow manure. A haystack stands at the eastern " +
      "side of the paddock.\n");
    add_item(({"fields","fields of wheat","wheat","field"}),
      "The paddock is surrounded by fields of wheat except to the west.\n");
    add_item("fence","A low wooden fence encloses the paddock. You " +
      "could probably jump over the fence to the west.\n");
    add_item(({"gate","closed gate"}),"On the western side of " +
      "the fence is a closed gate. It is nailed shut so you " +
      "doubt you could open it.\n");
    add_item(({"hay", "haystack"}), "On the eastern side of the "
      + "paddock stands a golden pile of hay, used for feeding "
      + "the cattle.\n");

    add_search(({"hay", "haystack"}), 2, "find_key", 1);
    add_cmd_item(({"fence","gate","over fence","over gate"}),
      ({"climb","jump"}),"@@jump_fence");
    add_cmd_item("gate","open","@@open_gate");

    reset_flotsam_room();
}

string
long_descr()
{
    return tod_descr1() + "You stand in a small paddock used for " +
    "grazing cattle. A fence separates the paddock from the fields " +
    "of wheat on all sides bar the western side, where a trail runs " +
    "up to a closed gate. A haystack stands at the eastern side of " +
    "the paddock.\n";
}

string
jump_fence()
{
    write("You jump over the fence and back to the trail.\n");
    TP->move_living("over the fence",FROOM + "pathd",1,0);
    return "";
}

string
open_gate()
{
    write("You try and open the gate but it is nailed shut.\n");
    return "";
}

string
find_key(object who, string what)
{
    if (needle_found)
    {
	return 0;
    }

    say("It looks like " + QCTNAME(who) + " has found a needle "
      + "in the haystack!\n");
    clone_object(KEY1)->move(who, 1);
    needle_found = 1;

    return "What's this?! It looks like you have found a "
    + "needle in the haystack! On second glance it seems "
    + "to be only a bent piece of wire.\n";

}
