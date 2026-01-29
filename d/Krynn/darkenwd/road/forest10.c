/* Forest10 coded by Teth
 * Last updated October 25, 1996
 */

#include "local.h"
#include <macros.h>

inherit ROADOUT;

inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "mixedforest", }) );

#define JAR    KROBJECT + "herb_jar"

int jar_found;

void
reset_darkenwd_room()
{
    jar_found = 0;
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
                  "continues to the southeast, and leads back "+
                  "to the Solace-Haven road in the northeast direction. "+
                  "A pile of broken glass is very out of place in this "+
                  "beautiful forest.");
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
    AI(({"pile","glass","broken glass","pile of glass",
        "pile of broken glass"}),"It is difficult to tell where this pile "+
        "of broken glass came from. There are a few broken shards, but most "+
        "of it is shattered fragments. Hmmm...there might even be something "+
        "usable.\n");
    AI(({"broken shards","shards","fragments","shattered fragments"}),"Most "+
        "of this pile is useless dirty glass, nothing of use.\n");
    add_search(({"pile","glass","broken glass","pile of glass"}),4,
        "find_jar",1);

    add_exit(TDIR + "forest9", "southeast",0,4,1);
    add_exit(TDIR + "road6", "northeast",0,4,1);

    set_tell_time(150);
    add_tell("Rustling sounds are very nearby...\n");
    add_tell("A breeze flows briefly in the area, but soon dissipates.\n");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({"forest","undergrowth","herbs"}), 3);
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

string
find_jar(object who, string what)
{
    if (jar_found)
    {
    return 0;
    }

    say(QCTNAME(who) + " finds something in the pile of glass!\n");
    clone_object(JAR)->move(TO, 1);
    jar_found = 1;
    return "You find a usable jar in the pile of glass!\n";
}




