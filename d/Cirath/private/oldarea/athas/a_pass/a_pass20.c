/* a_pass20.c: Pass into moutains. */

inherit "/std/room";
#include "defs.h"

public void get_up_now(object player,object para);

void create_room()
{
    set_short("Top of mountain");
    set_long ("You are standing on the top of a mountain. "+
              "Looking up there is nothing but sky, and the sun "+
              "beating down on you. Beneath your feet there is a "+
              "huge platform which does not seem to be natural. "+
              "Another thing that catches your eye is a bench "+
              "situated in the shade under a jutting ledge. "+
              "A little sign is nailed to the rock makes you "+
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
    add_exit(PASS_DIR+"a_pass19.c","north",0,2);
    add_exit("/d/Cirath/ships/roke/tyr_port.c","down",0,1,0);
}

void init()
{
	::init();
	add_action("my_rest","rest");
        add_action("my_read","read");
}

int my_rest(string str)
{
	
object para;
       para=clone_object(PASS_DIR+"rest.c");
       if(str!="on bench")
	{
	     NF("Rest would be most comfortable on the bench.\n");
	     return 0;
        }
	else
	{
		write ("You sit down and rest on the bench for a while, with a relieved sigh.\n");
		say (QTNAME(TP) + " sits down and rests on the bench for a while.\n");
	        TP->add_prop(LIVE_S_EXTRA_SHORT, " is resting on the bench");
                para->move(TP);
                TP->set_fatigue(TP->query_fatigue()+30);
                set_alarm(10.0,0.0,&get_up_now(this_player(),para));       
        return 1;
	}
}



public void get_up_now(object player,object para)
{
	player->catch_msg("You rise from the bench, feeling less fatigued.\n");
	para->remove_object();
        TP->remove_prop(LIVE_S_EXTRA_SHORT);
        return;
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
	    write("You don't know what this sign says, becuase you can't read.\n");
	    say (QTNAME(TP) + " bends his head to one side and looks confused as he tries in vain to read the sign.\n");
            return 1;
	}
	if(TP->query_skill(109)>10)
	{
      write("Transportation to Roke now available.\n");
	   say(QTNAME(TP) + " reads the sign.\n");  	
	   return 1;
	}
}

 
public int
mona_block()
{
    TP->catch_msg("The roc's perch has been moved into the city "
                 +"across from the Guild of Gladiators for the "
                 +"next few weeks.\n");
    return 1;
}
