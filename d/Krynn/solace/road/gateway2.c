/* created by Aridor, 03/95 */

#include "local.h"
#include RND_MEET

inherit SOLACE_ROOM

#include <language.h>

int dracos = 1;
int to_find = 2;

void
reset_solace_room()
{

    dracos = random(3) + 1;
    to_find = random(2) + 1;

}

void
create_solace_room()
{
    set_short("Gateway");
    set_long("You are standing in what used to be the center of the village of " +
	     "Gateway. Now there is nothing left but " +
	     "ashes. The foundations of the buildings are all that is still " +
	     "recognizable here. Smoke is still rising in some places from the " +
	     "remains, but you cannot see anything alive in here.@@no_wait@@ " +
	     "The main road can be reached again in the northeast, leading towards " +
	     "Solace and towards Newports.\n");
    add_item(({"gateway","village"}),
	     "All that is left now is ashes.\n");
    add_item("ashes","It's all black and sooty!\n");
    add_item(({"remains","foundations"}),
	     "You can't see much except the outlines of the buildings. " +
	     "Everything is covered with black sooty ashes.\n");
    add_item("buildings","No buildings are left. You can barely see the remains of the " +
	     "foundations.\n");
    add_item("smoke","Thin smoke curls up into the sky in some places, the fires have " +
	     "not all died out yet apparently.\n");
    add_item(({"fires","fire"}),
	     "From the last fires around here, you conclude that whatever destroyed the " +
	     "place still may be very close! Or at least it's not long gone yet.\n");
    add_item(({"road","main road"}),
	     "It can be seen northeast from here.\n");
    add_item(({"clouds","sky"}),
	     "It is fairly blue sky, with extremely menacing dark clouds building " +
	     "up far away in the north.\n");
    add_search(({"ashes","foundations","remains","buildings"}),5,"search_it",1);
    add_search(({"fire","fires"}),2,"ouch_hot",1);

    add_exit(HROAD + "gateway","northeast",0,1);

    reset_room();
}


void
init()
{
    object drac;

    ::init();

    if (interactive(TP))
    if (dracos > 0 && !present("draconian", this_object()))
	{
    while (dracos--)
        {
	    drac = RANDOM_MEET(DRAC_TABLE);
	    drac->set_color("red");
	    drac->set_aggressive(1);
	    drac->move(TO);
    }
	}
}


string
no_wait()
{
    mixed dracs = (all_inventory(TO)->id("draconian"));
    int num;
    dracs -= ({ 0 });
    num = sizeof(dracs);
    if (!num)
      return "";
    return " No, wait! There is actually someone moving about in the ruins." +
      (num > 1 ? " Looking closer you can see " + num + " draconians storming " +
       "towards you!" : "");
}

string
search_it(object searcher, string what)
{
    object found;
    string str;
    if (to_find <= 0)
      return 0; /* Nothing found */
    to_find--;
    if (random(5))
      found = RANDOM_MEET(OBJECT_TABLE);
    else
      {
	  (found = clone_object("/std/coins"))->set_amount(random(40));
	  if (!random(10) && found->query_amount() < 8)
	    found->set_coin_type("silver");
      }
    str = "You search through the " + what + " and you find " +
      LANG_ASHORT(found) + ".";
    if (found->move(searcher))
      return str + "\n";
    return str + " You quickly pick it up.\n";
}

string
ouch_hot(object searcher, string what)
{
    searcher->heal_hp(-10);
    return "Ouch! The fire is hot!\n";
}
