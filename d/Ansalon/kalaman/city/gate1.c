#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KALAMAN_IN;
object g1,g2,g3,g4;

void
reset_kalaman_room()
{
    if(!objectp(g1))
    {
	g1 = clone_object(KNPC + "militiaman");
	g1->arm_me();
	g1->move(TO);
    }
    if(!objectp(g2))
    {
	g2 = clone_object(KNPC + "militiaman");
	g2->arm_me();
	g2->move(TO);
    }

    if(!objectp(g3))
    {
	g3 = clone_object(KNPC + "militiaman");
	g3->arm_me();
	g3->move(TO);
    }

    if(!objectp(g4))
    {
	g4 = clone_object(KNPC + "elite_guard");
	g4->arm_me();
	g4->move(TO);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Before the western gates of Kalaman");

    add_item("gatehouse","@@long_descr");
    add_item(({"western gates","gates","twin iron gates","iron gates","gate"}),
      "To your northwest are twin iron gates, currently open.\n");
    add_item("road","A road runs " +
      "southeast towards the inner city of Kalaman, and to your northwest out " +
      "the city gate.\n");
    add_item(({"city","kalaman"}),
      "The city of Kalaman, considered by most to be one of the finest " +
      "port cities in all of Solamnia, rivalling even the glorious Palanthas.\n");
    add_item(({"guardhouse","guardhouses"}),
      "To your northeast and southwest are the gates guardhouses.\n");
    add_prop(ROOM_I_ALLOW_STEED, 1);

    add_exit(CITY + "r27","southeast",0);
    add_exit(CITY + "guard3","northeast",0);
    add_exit(CITY + "guard4","southwest",0);
    add_exit(SOLPLAINS,"northwest","@@no_go");

    reset_kalaman_room();
}

int
no_go()
{
    return 0; // pass opened

    if (TP->query_wiz_level())
    {
	write("You pass through the city gates and leave the city of Kalaman.\n");
	return 0;
    }
    write("You walk straight into the closed gate. Ouch.\n");
    say(QCTNAME(TP) + " walks straight into the closed gate " +
      "to your northwest.\n");
    g1->command("laugh merrily " +TP->query_real_name());
    g2->command("chuckle");
    g3->command("smirk");
    g4->command("say to " +TP->query_real_name() + " Ha ha! I'll bet that hurt!");
    return 1;
}


string
long_descr()
{
    return "You stand in a gatehouse before the western gates of Kalaman. " +
    "Here, twin iron gates stand open to your northwest, while to your " +
    "southeast a road continues towards the center of the city of Kalaman. " +
    "To your northeast and southwest are two guardrooms.\n";
}
