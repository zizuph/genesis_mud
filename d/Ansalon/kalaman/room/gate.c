#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <options.h>
#include <ss_types.h>
#include <wa_types.h>

#include <formulas.h>
#include <filter_funs.h>

inherit KALAMAN_OUT;
object gatemaster, guard1, guard2, guard3;

void
reset_kalaman_room()
{
    if(!objectp(guard1))
    {
	guard1 = clone_object(KNPC + "guard");
	guard1->arm_me();
	guard1->move(TO);
    }
    if(!objectp(guard2))
    {
	guard2 = clone_object(KNPC + "guard");
	guard2->arm_me();
	guard2->move(TO);
    }
    if(!objectp(guard3))
    {
	guard3 = clone_object(KNPC + "guard");
	guard3->arm_me();
	guard3->move(TO);
    }
    if(!objectp(gatemaster))
    {
	gatemaster = clone_object(KNPC + "gatemaster");
	gatemaster->arm_me();
	gatemaster->move(TO);
    }
}

create_kalaman_room()
{
    set_short("Before the gates of Kalaman");
    set_long("@@long_descr");

    add_item(({"great harbour gates","harbour gates","gates"}),
      BSN("To your southwest are the great harbour gates of Kalaman. At present " +
	"they stand open."));
    add_item(({"city","kalaman"}),
      BSN("To your southwest is the entrance to the city of Kalaman."));
    add_item(({"battlements","walls","wall"}),
      BSN("Lining the city walls are formidable battlements, manned by loyal soldiers " +
	"of Kalaman."));
    add_item(({"barracks","gate's barracks","guards"}),
      BSN("To your northwest and southeast are the barracks that guard the " +
	"harbour gate."));
    add_item(({"paved road","road"}),
      BSN("A paved road leads northeast towards the harbour and southwest " +
	"into the city."));
    add_item("harbour",
      BSN("To the northeast is the harbour of Kalaman."));
    add_item("sign",
      BSN("The sign seems to be a list of some kind. You could probably read it."));

    add_cmd_item("sign","read","@@read_sign");
    add_prop(ROOM_I_ALLOW_STEED, 1);

    add_exit(KROOM + "road5","northeast",0);
    add_exit(KROOM + "guard1","northwest",0);
    add_exit(KROOM + "guard2","southeast",0);
    add_exit(CITY + "r1","southwest","@@not_open");

    reset_kalaman_room();
}

string
long_descr()
{
    string str;

    str = "You stand before the great harbour gates that lead into the city of " +
    "Kalaman. Above you are the gate's battlements, where the city guards would " +
    "prepare themselves if the harbour was ever attacked. To your northwest " +
    "and southeast are the gate's barracks where guards would be stationed, " +
    "ready for any trouble. A paved road leads northeastwards towards the harbour, " +
    "and southwestwards into the city. " +
    "A sign has been placed to the side of the gates, which " +
    "stand open at the moment.";

    return BSN(str);
}


int
not_open()
{

    string who;
    if(objectp(gatemaster) && E(gatemaster) == TO)
    {
	who = L(TP->query_name());
	if(TP->query_guild_member("Solamnian Knights"))
	{
	    write("The stern gatemaster raises his hand in welcome.\n");
	    say("The stern gatemaster raises his hand in welcome to " +QTNAME(TP)+ ".\n");
	    say("The stern gatemaster says to " +QTNAME(TP)+ ": Greetings " +
	      "Knight of Solamnia! May your stay in Kalaman be pleasant.\n");
	    write("The stern gatemaster says to you: Greetings Knight of " +
	      "Solamnia! May your stay in Kalaman be pleasant.\n");
	    return 0;
	}
	if(TP->query_race_name() == "goblin" ||
           TP->query_race_name() == "hobgoblin" ||
           TP->query_race_name() == "minotaur")
	{
	    write("The stern gatemaster spits in disgust at you.\n");
	    say("The stern gatemaster spits in disgust at " +QTNAME(TP)+ ".\n");
	    write("The stern gatemaster says: Read the sign filth! No " +
	      "minotaurs or goblinkin allowed!\n");
	    say("The stern gatemaster says to " +QTNAME(TP)+ ": Read the sign filth! " +
	      "No minotaurs or goblinkin allowed!\n");
	    return 1;
	}
	if(TP->query_race_name() == "kender")
	{
	    write("The stern gatemaster looks at you suspiciously, while " +
	      "keeping a hand on his money pouch.\n");
	    say("The stern gatemaster looks at " +QTNAME(TP)+ " suspiciously, while " +
	      "keeping a hand on his money pouch.\n");
	    write("The stern gatemaster says: Read the sign! No kenders allowed in " +
	      "Kalaman!\n");
	    say("The stern gatemaster says to " +QTNAME(TP)+ ": Read the sign! No " +
	      "kenders allowed in Kalaman!\n");
	    return 1;
	}
	if(TP->query_attack())
	{
	    write("The stern gatemaster stops you from entering, saying: " +
	      "Troublemakers are not welcome! Stay out if you are " +
	      "going to fight!\n");
	    say("The stern gatemaster stops " +QTNAME(TP)+ " from " +
	      "entering, saying: Troublemakers are not welcome! " +
	      "Stay out if you are going to fight!\n");
	    return 1;
	}
    }

    if((objectp(guard1) && E(guard1) == TO) ||
      (objectp(guard2) && E(guard2) == TO) ||
      (objectp(guard3) && E(guard3) == TO))
    {
	if(TP->query_race_name() == "goblin" ||
           TP->query_race_name() == "hobgoblin" ||
           TP->query_race_name() == "minotaur" ||
           TP->query_race_name() == "kender" ||
	  TP->query_attack())
	{
	    write("A well-armoured guard stops you from passing through " +
	      "the gate.\n");
	    say("A well-armoured guard stops " +QTNAME(TP)+ " from passing " +
	      "through the gate.\n");
	    return 1;
	}
	return 0;
    }
    return 0;
}

string
read_sign()
{
    say(QCTNAME(TP) + " reads the sign.\n");
    write("You read the sign:\n" +
      "          Visitors to Kalaman! For the safety of our citizens, the\n" +
      "          following races have been decreed not welcome beyond our gates:\n\n" +
      "          Giantkin,\n" +
      "          Goblinoids,\n" +
      "          Draconians,\n" +
      "          Minotaurs,\n" +
      "          and Kender.\n" +
      "\n          -The council of Kalaman.\n\n");
    return "";
}
