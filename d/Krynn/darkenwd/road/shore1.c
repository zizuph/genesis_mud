/* Shore1 coded by Teth
 * April 2, 1996
 * Last update Oct 26, 1996
 */

#include "local.h"

inherit ROADOUT;
inherit HERBSEARCHNEW

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

string *herbs = HERB_MASTER->query_herbs( ({ "shore", }) );

void
reset_darkenwd_room()
{
    set_searched(random(2));
}

void
create_darkenwd_room()
{
    set_place(SHORE);

    set_long_desc("This part of the beach is covered with large rocks and "+
                  "cobblestones. A cliff stands tall far to the northwest. "+
                  "Two upright marker rocks make this part of the shore "+
                  "distinguishable from the rest. You can walk along the "+
                  "shore to the northwest. Small brush can be found along "+
                  "the line of the beach.");
    AI(({"beach","shore"}), "The beach is covered with rocks and "+
        "cobblestones. It is difficult to move around in this terrain.\n");
    AI(({"large rocks","cobblestones","rocks","stones","rock","stone"}),
        "These rocks and stones have smooth rounded surfaces, undoubtedly "+
        "the effect of waves. They are volcanic in origin, most likely "+
        "granite or diorite.\n");
    AI(({"upright rocks","marker rocks","upright marker rocks"}),"These two "+
        "stones stand tall, perhaps 3 meters high. They are useful in giving "+
        "one some idea of location.\n");
    AI("waves","The waves are slow and gentle, never creating the effect "+
        "called whitecapping. They create a soothing sound.\n");
    AI("north","A haze seems to cover the sky to the north.\n");
    AI("cliff","This cliff stands tall against the northwestern "+
        "sky. Like most other rock around here, it is dark grey.\n");
    AI(({"brush","small brush"}),"This small brush can be found scattered "+
        "along the rocky shore of Crystalmir Lake.\n");

    add_prop(LIVE_I_CAN_FISH, "freshwater"); 

    set_tell_time(120);
    add_tell("Waves crash along the shore of Crystalmir Lake.\n");
    add_tell("A cold breeze blows off the lake, chilling you.\n");


    add_exit(TDIR + "shore2", "northwest",0,2);
   
    seteuid(getuid(TO));
    set_up_herbs( ({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs)}), ({ "brush", "herbs", "small brush", }), 3);
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


