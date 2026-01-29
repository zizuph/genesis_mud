#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit GRAVE_STD;

object ob;

create_solace_room() 
{
    set_short("Old Graveyard");
    set_long(BS("This is more of the old graveyard. " +
		"An old, peeling, wrought ir" +
		"on fence runs from west to east along the northern side of " +
		"these graves. A huge Vallenwood Tree can be seen to the so" +
		"utheast. There are lots of bushes and brambles here, but t" +
		"hey thin to the east, west and south. It is almost peacefu" +
		"l here. Some birds fly in and out amoung the bushes.", 70));

    add_item(({"bushes", "bush"}),  BS(
               "These are just normal harmless bushes, with birds building n" +
               "ests in them, singing in them, and flying among them.", 70));
    add_item("brambles", BS(
             "These are actually blackberry bushes. The birds are eating th" +
             "e blackberries.", 70));
    add_item(({"fence", "old fence", "wrought iron fence"}),
        "This is the fence that divides the new grave from the old one.\n"+
        "It is in bad need of repair and painting. It is fairly free of \n"+
        "vines and brambles here.\n");
    add_item(({"flowers", "flower", "pretty flowers"}),("\n" +
             "There are a bunch of daisies.\n"));
    add_item("daisies", "They look freshly cut.\n");

    add_cmd_item(({"the", "fence"}), "jump", "@@over_fence");
    add_cmd_item("fence", "climb", "@@over_fence");
    add_cmd_item("daisies", "smell" , "They smell nice!!\n");

    ADD_GRAVES
    ADD_GRAVEYARD
    READ_GRAVE

    add_exit(TDIR + "fence2", "south", "@@south_msg");
    add_exit(TDIR + "o_grave3", "east", "@@east_msg");
    add_exit(TDIR + "o_grave1", "west", "@@west_msg");

    set_alarm(10.0,0.0,"windsay");

    reset_room();
}

reset_solace_room() 
{
    if (!ob)
	(ob = clone_object(MONSTER + "skeletal_dog"))->move_living("xx", TO);
}

init()
{
    ::init();
    ADA("pick");
}

pick(string str)
{
  NF("Pick what?\n");
  if ((str == "blackberries") || (str == "berries") || (str == "blackberry") 
	   || (str == "berry"))
	{
      write(BS("You move in amoung the blackberry bushes and start to pick b" +
	       "lackberries. The first one you pick looks so good you eat i" +
	       "t. YUMMY! It is so good you pick more and eat them all. Th" +
	       "ey are the best berries you had in a long time.", 70));
      say(QCTNAME(TP) + "is picking and eating lots of blackberries.\n");
      return 1;
    }
  return 0;
}

void
windsay()
{
     tell_room(TO, "The wind ruffles your hair.\n");
}

over_fence()
{
    return "The fence is too much of a challange.\n";
}
