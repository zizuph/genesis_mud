#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;
object g1,g2,g3;

void
reset_kalaman_room()
{
    if(!objectp(g1))
    {
	g1 = clone_object(KNPC + "elite_guard");
	g1->arm_me();
	g1->move(TO);
    }

    if(!objectp(g2))
    {
	g2 = clone_object(KNPC + "elite_guard");
	g2->arm_me();
	g2->move(TO);
    }

    if (!objectp(g3))
    {
        g3 = clone_object(KNPC + "captain");
        g3->arm_me();
        g3->move(TO);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Crossroad before the palace gates of Kalaman");

    add_item(({"grey stone walls","stone walls","walls","palace walls"}),
      "The grey stone walls surrounding the palace end here at an elaborate " +
      "pair of silver-steel gates.\n");
    add_item("palace","To your south rises the graceful palace of Kalaman, " +
      "home of the Lord of the city.\n");
    add_item(({"elaborate silver-steel gates","silver-steel gates","gates","gate"}), 
      "Two elaborate silver-steel gates stand open to your south, welcoming " +
      "all citizens and guests into the palace of Lord Calof.\n");
    add_item("paved road","A paved road leads down to the south towards " +
      "the palace.\n");
    add_item(({"marketplace","market place"}),
      "To the north the road opens into a busy market place.\n");

    add_exit(CITY + "p1","south","@@go_south");
    add_exit(CITY + "r23","north",0);
    add_exit(CITY + "r20","west",0);
    add_exit(CITY + "r22","east",0);

    add_item_city();

    reset_kalaman_room();
}

int
go_south()
{
    if(TP->query_race_name() == "goblin" ||
       TP->query_race_name() == "hobgoblin")
    {
//	if(objectp(g1) || objectp(g2))
//	changed that because when not in the room Baxter still blocked entrance
//	to the castle - Torqual 17.11.2001
	if(present(g1) || present(g2))
	{
	    write("The elite guard stops you.\n");
	    say(QCTNAME(TP) + " is stopped by the elite guard.\n");

	    g1->command("say Goblin at the gate! Attack!");
	    g2->command("say Die goblin scum!");
	    g1->command("kill " +TP->query_real_name());
	    g2->command("kill " +TP->query_real_name());
	    return 1;
	}
	write("You pass through the palace gates.\n");
	return 0;
    }
    write("You pass through the palace gates.\n");
    return 0;
}

string
long_descr()
{
    return "The grey stone walls that surround the palace end here at two elaborate " +
    "silver-steel gates that stand open to your south. Through the gates, a paved " +
    "road leads towards the palace. " +tod_descr1()+ season_road() +
    "To your north the cobbled street heads towards the local market place, " +
    "while the street also follows the palace walls to the east and west.\n";
}
