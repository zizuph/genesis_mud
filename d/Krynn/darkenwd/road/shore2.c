/* Shore2 coded by Teth
 * April 1, 1996
 * Last update Oct 26, 1996
 */

#include "local.h"

inherit ROADOUT;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "beach", }) );

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

void
reset_darkenwd_room()
{
    set_searched(random(2));
}

void
create_darkenwd_room()
{
    set_place(SHORE);

    set_long_desc("This area of the beach is covered with large rocks and "+
      "cobblestones. A stalwart cliff stands tall to the north, "+
      "the only flaw in its granitic surface being a large crack. "+
      "Thick brush stands near the base of the cliff. "+
      "The shore continues to the southeast, while a path to the "+
      "south enters the woods north of the Solace-Haven road.");
    AI(({"beach","shore"}), "The beach is covered with rocks and "+
      "cobblestones. It is difficult to move around in this terrain.\n");
    AI(({"large rocks","cobblestones","rocks","stones","rock","stone"}),
      "These rocks and stones have smooth rounded surfaces, undoubtedly "+
      "the effect of waves. They are volcanic in origin, most likely "+
      "granite or diorite.\n");
    AI("waves","The waves are slow and gentle, never creating the effect "+
      "called whitecapping. They create a soothing sound.\n");
    AI("north","A haze seems to cover the sky to the north.\n");
    AI("path", "It looks to be a treacherous path to walk on. Vines and "+
      "undergrowth cover the trail, but you are too far away to see any "+
      "more detail.\n");
    AI(({"cliff","stalwart cliff"}),"This cliff stands tall against the "+
      "sky. Like most other rock around here, it is granitic.\n");
    AI(({"crack","large crack","flaw"}),
      "It appears to be the entrance to a cave.\n");
    AI(({"brush","thick brush"}),"This thick brush stands in the recesses "+
      "of the cliff. It is quite bushy.\n");
    AI("woods", "The forest appears to be quite dense.\n");
    AI(({"surface","granitic surface"}),"The face of the cliff is solid "+
      "and imposing, with the exception of the large crack.\n");

    add_prop(LIVE_I_CAN_FISH, "freshwater");  

    add_exit(TDIR + "shore1", "southeast",0,2);
    add_exit(TDIR + "cave1", "crack");
    add_exit(TDIR + "path1", "south",0,4,1);

    set_tell_time(120);
    add_tell("Waves crash along the shore of Crystalmir Lake.\n");
    add_tell("A slight breeze blows off the lake.\n");

    seteuid(getuid(TO));
    set_up_herbs( ({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs)}), ({ "brush","thick brush","herbs", }), 4);

    OUTSIDE;

    reset_darkenwd_room();

}

void
enter_inv (object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
        start_room_tells();
}         
