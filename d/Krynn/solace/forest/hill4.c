/* Forest coded by Lord Rastlin */
/* Modified by Teth, Feb.13,96  */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>

inherit FORINROOM;

#define BONE    OBJ + "bone"

int bone_found;

void
reset_solace_room()
{
    {  bone_found = 0;
    }

{   object ob;

    if (present("goblin"))
      return;
    ob = clone_object(MONSTER + "goblin2");
    ob->move_living("xx", TO);
    ob->seq_new("do_thing");
    ob->seq_addfirst("do_thing",
		     ({"@@arm_me", 
		       "say C'mon ya bum! I jest traned, I'm readie!",
		       "laugh evil"}));
    ob = clone_object(MONSTER + "goblin2");
    ob->move_living("xx", TO);
    ob->seq_new("do_thing");
    ob->seq_addfirst("do_thing",
		     ({"@@arm_me", "say I needs sum practiss!."}));
}
}

void
create_solace_room() 
{
    set_short("A small lit cave");
    set_long("This small cave is the abode of a couple goblins. It reeks " +
             "of death and decay. Bones are scattered about the floor, " +
             "as are tattered pieces of cloth. The walls of the cave are " +
             "made of a greyish rock, and are both damp and very solid.\n");
    add_item("cave", "You're standing in it.\n");
    add_item("bones", "Perhaps the bones of nearby wildlife...you hope.\n");
    add_item(({"cloth", "pieces of cloth"}), "The pieces of cloth are " +
             "dull brown in colour, stained and torn beyond repair.\n");
    add_item(({"rock", "walls", "wall", "greyish rock", "grey rock"}),"The " +
             "walls of the cave are made out of some worn igneous rock. " +
             "It is most likely granite or andesite.\n");
    add_exit(TDIR + "hill1", "south");
    add_search("bones",1,"find_bone",1);
    
    set_alarm(1.0,0.0,"reset_room");
}

string
find_bone(object who, string what)
{
    if (bone_found)
    {
        return 0;
    }

    say(QCTNAME(who) + " finds something among the bones.\n");
    clone_object(BONE)->move(TO, 1);
    bone_found = 1;

    return "You discover a whitened bone among the bones!\n";
}





