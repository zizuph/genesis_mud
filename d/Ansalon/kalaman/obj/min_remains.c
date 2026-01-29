inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

int bag_taken = 0;
object pouch;

void
create_object()
{
    set_name(({"remains","skeletal remains"}));
    set_short("skeletal remains of a minotaur");
    set_long("This is the skeletal remains of a large "+
      "minotaur. It looks like he suffered many nasty " +
      "blows from a heavy slashing object, most likely "+
      "an axe. " + "@@bag_message@@" +"\n");
    add_prop(OBJ_I_VOLUME, 30000);
    add_prop(OBJ_I_WEIGHT,50000);

    add_cmd_item(({"pouch from skeletal remains",
	"pouch from remains","pouch from skeletal remains of a minotaur"}),
      ({"get","take"}),"@@get_bag");
    setuid; seteuid(getuid());
}

void
remove_remains()
{
    tell_room(E(TO),"The skeletal remains of a minotaur suddenly "+
      "crumble to dust, and is blown away by the wind.\n");
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
	return "You notice a pouch lodged in its rib cage.";
}

string
get_bag()
{
    if(bag_taken == 1)
    {
	write("There is no pouch to get from the remains.\n");
	return "";
    }
    else
	write("You pull a dusty pouch from the rib cage "+
	  "of the remains of the minotaur.\n");
    say(QCTNAME(TP)+ " pulls a dusty pouch from the rib cage of "+
      "the remains of the minotaur.\n");
    pouch = clone_object(KOBJ + "pouch");
    pouch->move(TP);
    clone_object(KOBJ+"merc_medallion")->move(pouch,1);
    clone_object(KOBJ+"scry_crystal")->move(pouch,1);
    clone_object(KOBJ+"broken_crystal")->move(pouch,1);
    clone_object(KOBJ+"broken_crystal")->move(pouch,1);
    clone_object(KOBJ+"broken_crystal")->move(pouch,1);
    clone_object(KOBJ+"broken_crystal")->move(pouch,1);
    bag_taken = 1;
    set_alarm(30.0,0.0,&remove_remains());
    return "";
}
