/* Forest2 coded by Teth
 * Last updated October 25, 1996
 */

#include "local.h"
#include <macros.h>

inherit ROADOUT;

inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "mixedforest", }) );

#define FEATHER   KROBJECT + "jay_feather"

int feather_found;
object snake;

void
reset_darkenwd_room()
{
    set_searched(random(2));

    feather_found = 0;

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
                  "to the Solace-Haven road in the southwest direction. "+
                  "A hazelnut shrub looks rather interesting.");
    AI("forest", "The forest is omnipresent, except to the southwest where "+
        "it leads to the Solace-Haven road.\n");
    AI(({"undergrowth","hazelnut","tangleshoot","solid undergrowth"}),"These "+
        "plants cover the ground, making it difficult to see the ground.\n");
    AI("air","The air is moist, and poor for people with arthritis.\n");
    AI(({"Lake","Crystalmir Lake","crystalmir lake","lake"}),"You cannot "+
        "see the lake from inside the forest.\n");
    AI(({"organic","organic matter","decaying matter","matter",
        "decaying organic matter"}),"Leaf litter and decaying wood blankets "+
        "the ground.\n");
    AI(({"shrub","hazelnut shrub","hazelnut"}),"It stands about as tall as "+
        "you. Little scratch marks can be seen on some branches.\n");
    AI(({"little marks","marks","scratches","scratch marks","branches"}),
        "The little scratches may have been made by a bird.\n");
    AI(({"ground","leaf litter","litter","wood","decaying wood"}),"It may "+
        "be of interest to someone who studies these things, but you're an "+
        "adventurer.\n");
    add_search(({"shrub","hazelnut shrub","hazelnut"}),1,"find_feather",1);

    reset_darkenwd_room();

    add_exit(TDIR + "forest3", "northwest",0,4,1);
    add_exit(TDIR + "forest1", "southeast",0,4,1);
    add_exit(TDIR + "road3", "southwest",0,4,1);

    set_tell_time(120);
    add_tell("A rustling sound from somewhere in the distance can be "+
             "heard.\n");
    add_tell("A small bird flits by your face, then disappears in the "+
            "forest.\n");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({ "forest", "undergrowth", "herbs", }), 4);
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
find_feather(object who, string what)
{
    if (feather_found)
    {
    return 0;
    }
 
    say(QCTNAME(who) + " finds something on a shrub!\n");
    clone_object(FEATHER)->move(TO, 1);
    feather_found = 1;
    return "You find a feather on the hazelnut shrub.\n";
}
