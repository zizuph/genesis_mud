/* created by Aridor, 03/95 */

#include "local.h"
#include RND_MEET

inherit SOLACE_ROOM

#include <language.h>

int to_find = 1;

void
reset_solace_room()
{
    to_find = random(2);
}

void
create_solace_room()
{
    set_short("Gateway");
    set_long("You have reached the village of Gateway, or rather, what once " +
	     "was the village of Gateway. Now there is nothing left but " +
	     "ashes. The foundations of the buildings are all that is still " +
	     "recognizable here. Smoke is still rising in some places from the " +
	     "remains, but you cannot see anything alive in here. " +
	     "The major part of the village is actually further southwest, but " +
	     "you can only see soot and blackened remains that way. You have the " +
	     "feeling that whoever did this isn't completely gone yet though!\n");
    add_item(({"gateway","village"}),
	     "All that is left now is ashes.\n");
    add_item(({"soot","ashes"}),"It's all black and sooty!\n");
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
	     "It's covered with soot, too.\n");
    add_item(({"clouds","sky"}),
	     "It is fairly blue sky, with extremely menacing dark clouds building " +
	     "up far away in the north.\n");
    add_search(({"ashes","foundations","remains","buildings"}),5,"search_it",1);
    add_search(({"fire","fires"}),2,"ouch_hot",1);
    

    add_exit(HROAD + "wroad3","northwest",0,2);
    add_exit(TO_NEWPORTS,"east",0,2);
    add_exit(HROAD + "gateway2","southwest",0,1);

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
