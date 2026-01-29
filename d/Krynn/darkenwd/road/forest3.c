/* Forest3 coded by Teth
 * April 2, 1996
 * Last updated October 26, 1996
 */

#include "local.h"

inherit ROADOUT;

inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "mixedforest", }) );

void
reset_darkenwd_room()
{
    set_searched(random(2));
}

void
create_darkenwd_room()
{
    set_place(FOREST);

    set_long_desc("This forest is quite dense, with a solid undergrowth " +
                  "of tangleshoot and hazelnut. The air is rather moist, "+
                  "likely because of the proximity of Crystalmir Lake. "+
                  "Decaying organic matter litters the ground. The forest "+
                  "continues to the northwest, or leads back to the Solace-"+
                  "Haven road in the southwest direction. A small path "+
                  "heads north.");
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
    AI(({"small path","path"}),"This path may lead to Crystalmir Lake. It "+
        "heads in that direction, anyway.\n");
    AI(({"ground","leaf litter","litter","wood","decaying wood"}),"It may "+
        "be of interest to someone who studies these things, but you're an "+
        "adventurer.\n");

    add_exit(TDIR + "forest4", "northwest",0,4,1);
    add_exit(TDIR + "forest2", "southeast",0,4,1);
    add_exit(TDIR + "road4", "southwest",0,4,1);
    add_exit(TDIR + "path3", "north",0,4,1);

    set_tell_time(120);
    add_tell("A rustling sound can be heard nearby!\n");
    add_tell("A flock of geese fly by overhead.\n");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({ "forest","undergrowth","herbs",}), 4);
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



