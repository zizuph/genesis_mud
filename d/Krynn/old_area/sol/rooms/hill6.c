/* Forest coded by Lord Rastlin */
/* Modified by Teth, Feb.13,96  */

#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit FORINROOM;

void
reset_solace_room()
{
    object ob;

    if (present("goblin"))
      return;
    ob = clone_object(MONSTER + "goblin2");
    ob->move_living("xx", TO);
    ob->seq_new("do_thing");
    ob->seq_addfirst("do_thing",
		     ({"@@arm_me", 
		       "say Yooz wants to fight me??",
		       "cackle evil"}));
    ob = clone_object(MONSTER + "goblin2");
    ob->move_living("xx", TO);
    ob->seq_new("do_thing");
    ob->seq_addfirst("do_thing",
		     ({"@@arm_me", "say Yer head as a trophy will mek " + 
                                   "mez a seeker gard fer sure!"}));
}

void
create_solace_room() 
{
    set_short("A small dark cave");
    set_long("This small cave is the abode of goblins. It reeks " +
             "of death and decay. Bones are scattered about the floor, " +
             "as are jagged pieces of rock. The walls of the cave are " +
             "made of a greyish rock, and are both damp and very solid.\n");
    add_item("cave", "Dark and foreboding, it is narrow and damp.\n");
    add_item("bones", "Perhaps the bones of nearby wildlife...you hope.\n");
    add_item("pieces of rock", "The pieces of rock are sharp and jagged, " +
             "and some look blood-stained.\n");
    add_item(({"rock", "walls", "wall", "greyish rock", "grey rock"}),"The " +
             "walls of the cave are made out of some worn igneous rock. " +
             "It is most likely granite or andesite.\n");
    add_exit(TDIR + "hill2", "south");
    
    DARK;
    
    set_alarm(1.0,0.0,"reset_room");
}

