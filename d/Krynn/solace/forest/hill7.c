/* Forest coded by Lord Rastlin */
/* Modified by Teth, Feb.13,96  */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>

inherit FORINROOM;

#define FRAME    OBJ + "pframe"

int frame_found;

void
reset_solace_room()
{
    { frame_found = 0;
    }

{   object ob;

    if (present("goblin"))
      return;
    ob = clone_object(MONSTER + "goblin2");
    ob->move_living("xx", TO);
    ob->seq_new("do_thing");
    ob->seq_addfirst("do_thing",
		     ({"@@arm_me", 
		       "say Me likes you. Me pulp youze last!",
		       "scratch behind"}));
    ob = clone_object(MONSTER + "goblin2");
    ob->move_living("xx", TO);
    ob->seq_new("do_thing");
    ob->seq_addfirst("do_thing",
		     ({"@@arm_me", "say Me not likes you! Me pulps you now!"}));
}
}

void
create_solace_room() 
{
    set_short("A small damp dark cave");
    set_long("This small cave is the home of goblins. It reeks " +
             "of death and decay. Bones are scattered about the floor, " +
             "surrounding a murky puddle. The walls of the cave are " +
             "made of a greyish rock, and are both damp and very solid.\n");
    add_item("cave", "You're standing in it.\n");
    add_item("bones", "Perhaps the bones of nearby wildlife...you hope.\n");
    add_item(({"puddle", "murky puddle"}), "A breeding ground for " +
             "mosquitoes, this puddle is probably the drinking and " +
             "the waste water of the cave's inhabitants!\n");
    add_item(({"rock", "walls", "wall", "greyish rock", "grey rock"}),"The " +
             "walls of the cave are made out of some worn igneous rock. " +
             "It is most likely granite or andesite.\n");
    add_exit(TDIR + "hill2", "west");
    add_search("bones",5,"find_frame",1);

    DARK;
    
    set_alarm(1.0,0.0,"reset_room");
}

string
find_frame(object who, string what)
{
    if (frame_found)
    {
        return 0;
    }

    say(QCTNAME(who) + " discovers something in the bones!\n");
    clone_object(FRAME)->move(TO, 1);
    frame_found = 1;

    return "You find an old picture frame among the bones!\n";
}





