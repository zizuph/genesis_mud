/* a_pass20.c: Pass into moutains. */

inherit "/std/room";
#include "defs.h"

void create_room()
{
    set_short("Top of mountain");
    set_long ("You are standing on the top of a mountain. "+
              "Looking up there is nothing but sky and the sun "+
              "beating down on you. Beneath your feet there is a "+
              "huge platform which does not seem to be natural. "+
              "Another thing that catches your eye is a bench "+
              "situated in the shade under a jutting ledge. "+
              "A little sign nailed to the rock here makes you "+
              "think there might be a trifle more to this place "+
              "than just the view.\n");

    ROCK;
    SUN;
    add_item("bench","This bench is made of rock, yet being there "+
            "in the shade it looks very nice indeed. This would be "+
            "a good place to rest.\n");

    add_item(({"sign","little sign"}),"The sign is covered with "+
            "those strange contraptions of lines called letters. "+
            "It might be readable, if you know how to do that.\n");

    add_item("view","The view is magnificent, revealing the barren "+
            "mountains in their horrid splendour.\n");

    add_item("platform","This platform seems to have been carefully "+
            "prepared for something.\n");

    OUTSIDE
    add_exit(WILD_PASS+"pass19.c","north",0,2);
    add_exit("/d/Cirath/ships/roke/tyr_port.c","down",0,1);
}

void init()
{
  ::init();
  add_action("my_read","read");
}

int my_read(string str)
{
	if(str!="sign")
	{
	   NF("Read what ?");
	   return 0;
	}
	if(TP->query_skill(109)<10) /* language*/
	{
	    write("You don't know what this sign says, because you can't read.\n");
	    say (QTNAME(TP) + " bends his head to one side and looks confused as he tries in vain to read the sign.\n");
            return 1;
	}
	if(TP->query_skill(109)>10)
	{
      write("Transportation to Gont now available.\n");
	   say(QTNAME(TP) + " reads the sign.\n");  	
	   return 1;
	}
}

 
