inherit "/std/room";

#include "/d/Emerald/defs.h";
#include <tasks.h>

#define FALLEN_ROOM MBLACK_DIR + "pass/mb21"
#define DOWN_ROOM MBLACK_DIR + "pass/mcliff7"

void
create_room()
{
    set_short("Top of Mount Black");
    set_long( ("   You are standing on the very summit of Mount Black. "+
       "The mist is so think here that you can hardly make out your "+
       "hand in front of your face. You think that you can see shapes "+
       "moving in the swirling mist, but you cannot focus on them. "+
       "It is rather cold here and windy here. The area seems to "+
       "be level but you can't tell where to go because the mist "+
       "here is so extremely thick. There is a fairly stout looking "+
       "tree here.\n\n"));

    add_item("tree", ("@@my_tree"));
    add_item(({"mist", "fog"}), "The mist clings to everything. "+
		"It seems to be alive in the way it twists and swirls "+
		"around alternately concealing and revealing the "+
		"landscape.\n");
    add_item(({"cliffs"}), "You look toward the cliffs but you cannot "+
		"see much. All you can tell from here is that they are "+
		"quite steep and drop off a long ways.\n");

    add_cmd_item("north", "look", "The mountain slopes down to "+
		 "some cliffs in that direction.\n");
    
    add_exit(MBLACK_DIR + "cliff_top", "north");
   
}

string
my_tree()
{
     if(present("eagle"))
     return "The tree has an eagle sitting in the branches.\n";
     else
     return "The tree sways slightly in the wind.\n";
}

init()
{
     ::init();
     add_action("do_climb", "climb");
}

int
do_climb(string str)
{
    notify_fail("Climb what?\n");
     if(!str) return 0;
     if(str!="tree") return 0;
     write("You try to grab the lowest branch but it's too high.\n");
    return 1;
}


