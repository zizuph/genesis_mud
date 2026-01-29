#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

inherit FLOTSAM_IN;
object wand;

#define KEY1 "/d/Ansalon/balifor/flotsam_forest/obj/wand2"
#define PLAYER_I_FOUND_FISH "_player_i_found_flotsam_fish"

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

}

create_flotsam_room()
{
    set_short("An abandoned fish shop");
    set_long("@@long_descr");

    add_item("walls","The walls of this abandoned fish " +
      "shop are lined with wooden boxes that once used " +
      "to display seafood.\n");
    add_item("dust","Dust seems to cover everything " +
      "in this place, although it seems to have been " +
      "disturbed in some places by small feet.\n");
    add_item(({"dim light","light","barred windows","windows",
	"window","west"}),
      "Dim light filters through the cracks of the barred " +
      "windows. You think you can squeeze through back out " +
      "onto the street if you wanted to.\n");
    add_item(({"wooden boxes","boxes"}),
      "All around the room stand wooden boxes, " +
      "once used to display a variety of fish to those " +
      "interested in such delicacies of the ocean, but now " +
      "displaying only dust and decay.\n");

    add_prop(ROOM_I_NO_ALLOW_STEED,1);

    add_cmd_item(({"out window","barred window",
	"through window","through barred window"}),
      ({"squeeze","climb"}),
      "@@enter_window");
    add_search(({"boxes","wooden boxes"}),2,"find_wand",1);
    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand within an abandoned fish shop " +
    "that sits at the edge of a cliff in the port town " +
    "of Flotsam. Stacks of wooden boxes line the walls, " +
    "boxes that once held a great variety of fish " +
    "from all over the Bloodsea of Istar. Apart from that " +
    "the room is empty except for dust, that seems to " +
    "cover everything. A dim light filters through the " +
    "barred windows to your west.\n";
}

string
enter_window()
{
    write("You squeeze through the barred window and " +
      "find yourself back out on the street.\n");
    TP->move_living("through the window",FROOM + "street17",1,0);
    return "";
}

string
find_wand(object who, string what)
{
    if (needle_found)
    {
	return 0;
    }

    say("It looks like " +QCTNAME(who)+ " has found " +
      "something in the wooden boxes!\n");
    wand = clone_object(FOBJ + "r_fish");
    /*
	if(TP->test_bit("ansalon",0,12))
	    wand->set_charge(1);
    */
    wand->move(who,1);
    TP->add_prop(PLAYER_I_FOUND_FISH, 1);
    needle_found = 1;

    return "Rumaging through the wooden boxes, you come " +
    "across a rotting fish! Eew... it sticks to " +
    "your hand!\n";

}
