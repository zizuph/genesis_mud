/* Forest coded by Lord Rastlin */
/* modified by Teth, Feb.13,96  */

#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit FOROUTROOM;

void
reset_solace_room()
{
    if (present("goblin"))
      return;
    set_alarm(1.0,0.0,"load_first_goblin");
    set_alarm(4.0,0.0,"load_second_goblin");
}

void
create_solace_room()
{
    set_place(HILL);

    set_long_desc("You are in the goblin camp. This is probably " +
      "the encampment for the goblins that patrol Solace. Nestled in the " +
      "foothills of Sentinel Peaks, this rocky terrain is perfect goblin " +
      "habitat. Signs of goblins are everywhere, whether it be litter " +
      "strewn about or half-eaten meat. There appear to be dark caves " +
      "to the north and east. The northeast trail leads further into the " +
      "camp, while you can leave this gruesome and smelly place by going " +
      "southwest.");
    add_item("litter", "Messy, messy! But it is typical of goblins to live " +
      "in filth and squalor. The litter mostly consists of rusting and " +
      "discarded metal objects. Nothing too much of interest to you.\n");
    add_item(({"meat", "half-eaten meat"}), "Maggot-infested and stomach-" +
      "wretching, no goblin would even consider eating it now!\n");
    add_item(({"cave", "caves"}), "They appear to be dark. Most " +
      "likely, they are the home of more goblins.\n");  

    add_exit(TDIR + "hill1", "southwest");
    add_exit(TDIR + "hill3", "northeast");
    add_exit(TDIR + "hill6", "north");
    add_exit(TDIR + "hill7", "east");
   
    OUTSIDE;
    set_alarm(1.0,0.0,"reset_room");
}

void
load_first_goblin() 
{
    object mon;
    mon = clone_object(MONSTER + "goblin");
    mon->move_living("xx", TO);
    mon->seq_new("do_thing");
    mon->seq_addfirst("do_thing",({"@@arm_me",
        "say Gobbos, gobbos...are so smurt!"}));
}

void
load_second_goblin() 
{
    object mon;
    mon = clone_object(MONSTER + "goblin2");
    mon->move_living("xx", TO);
    mon->seq_new("do_thing");
    mon->seq_addfirst("do_thing",({"@@arm_me", "say I'm smurter than yew!"}));
}


