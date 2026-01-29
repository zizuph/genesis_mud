#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;
object g1;

void
reset_kalaman_room()
{
    if(!objectp(g1))
    {
	g1 = clone_object(KNPC + "elite_guard");
	g1->arm_me();
	g1->move(TO);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Paved courtyard before the entrance to " +
      "a great palace");

    add_item(({"paved courtyard","courtyard"}),
      "A beautifully paved courtyard before the entrance " +
      "to the palace of Kalaman.\n");
    add_item(({"palace","great palace","palace of kalaman",
	"spires","graceful spires"}),
      "To your south rises the elegant palace of Kalaman. Graceful " +
      "spires rise into the air to your east and west, " +
      "overlooking the surrounding city.\n");
    add_item(({"marble pillars","pillars"}),
      "A number of beautiful marble pillars stand " +
      "on either side of the entrance to the palace.\n");
    add_item(({"entrance","steps"}),
      "Steps lead up to the open entrance to the palace.\n");
    add_item(({"elaborate silver-steel gates","gates",
	"gate","silver-steel gates"}),
      "Two elaborate silver-steel gates stand open to your north, " +
      "leading out to the street surrounding " +
      "the palace.\n");
    add_item("street","To your north is the street that " 
      + "surrounds the palace.\n");

    add_exit(CITY + "r21","north",0);
    add_exit(CITY + "p2","south","@@enter_palace");


    reset_kalaman_room();
}

int
enter_palace()
{
    if(TP->query_race_name() == "goblin" ||
       TP->query_race_name() == "hobgoblin")
    {
	if(objectp(g1) && environment(g1) == TO)
	{
	    write("The elite guard stops you from entering.\n");
	    say(QCTNAME(TP) + " is stopped by the elite guard from entering the palace.\n");
	    g1->command("say Now is your time to die goblin!");
	    g1->command("kill "+TP->query_real_name());
	    return 1;
	}
	write("You climb the steps and enter the palace.\n");
	return 0;
    }
    write("You climb the steps and enter the palace.\n");
    return 0;
}

string
long_descr()
{
    return "You stand in a paved courtyard before the palace " +
    "of Kalaman. " +tod_descr1() + "Marble pillars " +
    "rise beside the entrance to the palace to your south, " +
    "while a pair of elaborate silver-steel gates stand " +
    "open to the street to your north.\n";
}
