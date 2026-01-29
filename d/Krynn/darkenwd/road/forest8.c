/* Forest8 coded by Teth
 * April 3, 1996
 * Last updated Oct 26 1996
 */

#include "local.h"
#include <macros.h>

inherit ROADOUT;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "mixedforest", }) );

#define TOOTH   KROBJECT + "wolf_tooth"

int tooth_found;
object snake;

void
reset_darkenwd_room()
{
    set_searched(random(2));
    tooth_found = 0;

    if(!objectp(snake))
    {
      snake = clone_object("/d/Krynn/tant/npc/snake");
      snake->move(TO);
    }
}

void
create_darkenwd_room()
{
    set_place(FOREST);

    set_long_desc("This forest is quite dense, with a solid undergrowth " +
                  "of tangleshoot and hazelnut. The air is rather moist, "+
                  "likely because of the proximity of Crystalmir Lake. "+
                  "Decaying organic matter litters the ground. The forest "+
                  "continues to the northwest and southeast, or leads back "+
                  "to the Solace-Haven road in the northeast direction. "+
                  "You can see the decayed skeleton of some animal here.");
    AI("forest", "The forest is omnipresent, except to the northeast where "+
        "it leads to the Solace-Haven road.\n");
    AI(({"undergrowth","hazelnut","tangleshoot","solid undergrowth"}),"These "+
        "plants cover the ground, making it difficult to see the ground.\n");
    AI("air","The air is moist, and poor for people with arthritis.\n");
    AI(({"Lake","Crystalmir Lake","crystalmir lake","lake"}),"You cannot "+
        "see the lake from inside the forest.\n");
    AI(({"organic","organic matter","decaying matter","matter",
        "decaying organic matter"}),"Leaf litter and decaying wood blankets "+
        "the ground.\n");
    AI(({"ground","leaf litter","litter","wood","decaying wood"}),"It may "+
        "be of interest to someone who studies these things, but you're an "+
        "adventurer.\n");
    AI(({"skeleton","decayed skeleton"}),"This skeleton appears to be from "+
        "some canine creature, perhaps a wolf.\n");
    AI("butterfly","The butterfly flies from place to place, often "+
        "disappearing behind a tree.\n");
    add_search(({"skeleton","decayed skeleton"}),4,"find_tooth",1);

    reset_darkenwd_room();

    add_exit(TDIR + "forest9", "northwest",0,4,1);
    add_exit(TDIR + "forest7", "southeast",0,4,1);
    add_exit(TDIR + "road4", "northeast",0,4,1);

    set_tell_time(400);
    add_tell("The smell from the skeleton wafts up...luckily, it is not "+
             "terribly fresh.\n");
    add_tell("A butterfly floats by.\n");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({"forest","undergrowth","herbs",}), 4);

       OUTSIDE;  /* An outside room */
   
}

void
enter_inv (object ob, object from)
{
  ::enter_inv(ob, from);
 
  if (interactive(ob))
    start_room_tells();
}

string
find_tooth(object who, string what)
{
    if (tooth_found)
    {
    return 0;
    }
 
    say(QCTNAME(who) + " finds something on the skeleton of the animal!\n");
    clone_object(TOOTH)->move(TO, 1);
    tooth_found = 1;
    return "You find a tooth on the skeleton!\n";
}

