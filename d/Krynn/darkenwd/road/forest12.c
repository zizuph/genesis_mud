/* Forest 12 coded by Teth
 * October 25, 1996
 * Home of the herbalist
 */

#include "local.h"
#include <macros.h>

inherit ROADOUT;

inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "mixedforest", }) );

object herbalist;

int
herbalist_present()
{
    if (present("herbalist",TO))
        return 1;

    return 0;
}

void
reset_darkenwd_room()
{
    set_searched(random(2));
    if (!herbalist_present()) 
    {
        herbalist = clone_object(NPC + "herbalist");

        herbalist->move(TO);
    }
}

void
create_darkenwd_room()
{
    set_place(FOREST);

    set_long_desc("This forest is quite dense, with a solid undergrowth " +
                  "of tangleshoot and hazelnut. The air is rather moist, "+
                  "likely because of the proximity of Crystalmir Lake. "+
                  "Decaying organic matter litters the ground. The only "+
                  "way out of this section of forest is to the west, as "+
                  "the undergrowth appears to be too thick in other "+
                  "directions.");
    AI("forest", "The forest is omnipresent, except to the west where "+
        "one can go back to the small game trail.\n");
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

    add_exit(TDIR + "path3", "west",0,4,1);

    set_tell_time(150);
    add_tell("Distant sounds of waves can be heard crashing along the shore " +
             "of Crystalmir Lake.\n");
    add_tell("The sounds of the forest echo around you.\n");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({ "forest", "undergrowth", "herbs",}), 3);
       OUTSIDE;  /* An outside room */

    reset_darkenwd_room();   

}

void
enter_inv (object ob, object from)
{
  ::enter_inv(ob, from);
 
  if (interactive(ob))
    start_room_tells();
}




