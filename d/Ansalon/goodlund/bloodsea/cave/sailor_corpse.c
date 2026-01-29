inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"


int bag_taken = 0;
object scroll;

void
create_object()
{
    set_name(({"skeleton","sailor skeleton", "skeleton of a sailor"}));
    set_short("the skeleton of a sailor");
    set_long("This bleached and gnawed skeleton is all that remains of an unfortunate " +
      "sailor marooned in this cave. By the looks of the scraps of his remaining " +
      "apparel he was likely a rich merchant who fell victim to the rough waters " +
      "of the Vingaard River, possibly while enjoying a drunken evening on a " +
      "pleasure cruise, ending up marooned in this cave. " + "@@bag_message@@" +"\n");
    add_prop(OBJ_I_VOLUME, 100000);
    add_prop(OBJ_I_WEIGHT,100000);
    add_prop(OBJ_M_NO_GET, 1);

    add_cmd_item(({"scroll from skeleton", "furled scroll from skeleton", "scroll from corpse",
	"furled scroll from corpse", "furled scroll from skeleton of a sailor",
        "scroll from skeleton of a sailor"}),
      ({"get","take"}),"@@get_bag");
    setuid; seteuid(getuid());
}

void
remove_remains()
{
    tell_room(E(TO),"The skeleton decays into dust.\n");
    TO->remove_object();
}

string
bag_message()
{
    if(bag_taken == 1)
    {
	return "";
    }
    else
	return "You notice its skeletal hand still holds tightly to a furled scroll.";
}

string
get_bag()
{

    if(bag_taken == 1)
    {
	write("There is no scroll to get from the skeleton.\n");
	return "";
    }
    else
	write("You pry the scroll from the dead sailor's hand...\n");
    say(QCTNAME(TP)+ " pries a scroll from the dead sailor's hand.\n");
    scroll = clone_object("/d/Krynn/common/scrolls/breath_water_scroll");
    scroll->move(TP);


    bag_taken = 1;
    set_alarm(30.0,0.0,&remove_remains());
    return "";
}
