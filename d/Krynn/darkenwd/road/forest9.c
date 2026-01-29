/* Forest9 coded by Teth
 * April 3, 1996
 * Last updated Oct 26, 1996
 */

#include "local.h"

inherit ROADOUT;

inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "mixedforest", }) );

object drac1,drac2,drac3;

int
dracs_present()
{
    if (present("baaz",TO) || present("kapak",TO))
        return 1;

    return 0;
}

void
reset_darkenwd_room()
{
    set_searched(random(2));
    if (!dracs_present()) 
    {
        drac1 = clone_object(NPC + "kapak");
        drac2 = clone_object(NPC + "baaz");
        drac3 = clone_object(NPC + "baaz");

        drac2->set_leader(drac1);
        drac3->set_leader(drac1);

        drac1->team_join(drac2);
        drac1->team_join(drac3);

        drac1->move(TO);
        drac2->move(TO);
        drac3->move(TO);
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
                  "to the Solace-Haven road in the northeast direction. A "+
                  "small trail leads south from here, as well.");
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
    AI(({"trail","small trail"}),"This trail would lead in the direction "+
        "of Prayer's Eye Peak.\n");

    add_exit(TDIR + "forest10", "northwest",0,4,1);
    add_exit(TDIR + "forest8", "southeast",0,4,1);
    add_exit(TDIR + "road5", "northeast",0,4,1);
    add_exit(TDIR + "trail1", "south",0,2,1);

    set_tell_time(400);
    add_tell("A dark cloud rolls in the sky overhead.\n");
    add_tell("A rustling sound is made somewhere nearby.\n");

    seteuid(getuid(TO));
    set_up_herbs( ({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({"forest","undergrowth","herbs",}), 5);
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



