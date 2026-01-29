/* Forest5 coded by Teth
 * April 3, 1996
 * Last updated October 26, 1996
 */

#include "local.h"
#include <macros.h>

inherit ROADOUT;

inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "mixedforest", }) );

#define DAGGER    WEAPON + "rdagger"

int dagger_found;

void
reset_darkenwd_room()
{
    set_searched(random(2));

    dagger_found = 0;
}

void
create_darkenwd_room()
{
    set_place(FOREST);

    set_long_desc("This forest is quite dense, with a solid undergrowth " +
                  "of tangleshoot and hazelnut. The air is rather moist, "+
                  "likely because of the proximity of Crystalmir Lake. "+
                  "Decaying organic matter litters the ground. The forest "+
                  "continues to the southeast, or leads back "+
                  "to the Solace-Haven road in the southwest direction. "+
                  "A log stretches itself out on the ground here.");
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
    AI(({"ground","leaf litter","litter","wood","decaying wood"}),"It may "+
        "be of interest to someone who studies these things, but you're an "+
        "adventurer.\n");
    AI("owl","The owl must be hidden somewhere out of your sight.\n");  
    AI("log","The log is decaying slowly, returning its nutrients back to "+
        "soil. However, something seems out of place about it.\n");
    add_search("log",4,"find_dagger",1);

    add_exit(TDIR + "forest4", "southeast",0,4,1);
    add_exit(TDIR + "road6", "southwest",0,4,1);

    set_tell_time(120);
    add_tell("A rustling sound from some distance away can be heard.\n");
    add_tell("A vole skitters by, nearly being squished to death under "+
            "your feet. However, he made it safely.\n");
    add_tell("An owl hoots: WhOOO-who-who-WhOOO!\n");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({"forest","undergrowth","herbs",}), 3);
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
find_dagger(object who, string what)
{
    if (dagger_found)
    {
    return 0;
    }
 
    say(QCTNAME(who) + " finds something under the log!\n");
    clone_object(DAGGER)->move(TO, 1);
    dagger_found = 1;
    return "You find a rusty dagger, peeking out beneath the log.\n";
}


