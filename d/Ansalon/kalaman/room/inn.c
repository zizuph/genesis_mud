#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KALAMAN_IN;
object bartender;

void
reset_kalaman_room()
{
    if(!objectp(bartender))
    {
	bartender = clone_object(KNPC + "bartender");
	bartender->arm_me();
	bartender->move(TO);
    }
}

create_kalaman_room()
{
    set_short("An empty inn");
    set_long("@@long_descr");

    add_item("inn","@@long_descr");
    add_item(({"well-used tables","tables","candles","candle"}),
      BSN("Once well-used tables stand bare of food and drink throughout the inn, " +
	"with only extinguished candles on each keeping them from being completely bare."));
    add_item(({"comfortable looking chairs","chairs"}),
      BSN("Comfortable looking chairs sit empty around the tables throughout the inn."));
    add_item(({"bar","western wall","wall"}),
      BSN("Against the western wall of the inn stands a bar. A sign rests on top of it."));
    add_item("sign",
      BSN("This sign covers over what was once a menu list. Writing is on it that you " +
	"can probably read."));

    add_cmd_item("sign","read","@@read_sign");
    add_exit(KROOM + "road1","east",0);

    reset_kalaman_room();
}

string
long_descr()
{
    string str;

    str = "You stand within 'The Stout Dwarf Inn', an inn that is presently devoid of " + 
    "all customers. Once well-used tables stand bare of food and drink, and comfortable " +
    "looking chairs sit empty. A bar stands against the western wall of the inn.";

    return BSN(str);
}

string
read_sign()
{
    say(QCTNAME(TP) + " reads the sign.\n");
    write("The sign says:\n" +
      "     As Lord Calof has declared a State of War, all taverns and inns must be\n" +
      "     closed until further notice.\n\n");
    return "";
}

