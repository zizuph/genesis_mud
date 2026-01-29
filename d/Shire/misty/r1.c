/* highpass */
/*
 *  Here player is rewarded for success in climbing down.
 *  Reward is XP + possibility to train SS_CLIMB up to 50
 *
 *   Milan
 *
 *   Updated by Igneous
 *
 *   Updated 2008-04-24 by Toby,
 *   updated 2008-05-05 by Toby:
 *
 *     - updated code for falling and if allowed to climb or jump down
 *     - removed the old traces of climbers guild...
 *  Update 5/29/2020 by Raymundo:
 *      - fixed typo
 *  
 */


#include <filter_funs.h>
#include <money.h>
#include "local.h"
#include "climb.h"
#include "/d/Shire/private/shire_admin.h"

inherit SHIRE_ROOM;

#define PLAYER_HAS_FOUND    "_Shire_found_hole_in_roots"

// Protoytypes
void climb_next(int how_high, object climber);

static int gStage = 0;
object oClimber;

void
create_shire_room()
{
    add_prop(OBJ_S_SEARCH_FUN, "search_roots");
    add_prop(OBJ_I_SEARCH_TIME, 15);
    set_short("top of the rock");
    set_long(
      "You are standing on small plateau on the top of the high dark " +
        "rock. The view is incredible from up here, and it's amazing to " +
        "have made it up to the top of the rock. But eventually you " +
        "will have to go down again. Large, ancient trees grow up here, " +
        "surrounding the large rock. " + VBFC("you_see_hole"));


    add_item("rock", "Don't look around too long! You must climb down "+
      "now. Or if you are crazy enough, you may simply jump down.\n");
    add_item("plateau", "Very strange that there is a tree "+
      "on this plateau. You wonder how this tree could "+
      "grow on such compact rock.\n");
    add_item(({"tree", "oak tree", "dry oak tree", "dry tree"}), 
        "It is a nearly dry oak. You can see many twisted "+
        "roots that are desperately trying to find some "+
        "hole or crack in the rock and so give some support "+
        "and life to this tree.\n");
    add_item(({"trees", "ancient trees", "large trees"}),
        "They are large and ancient looking trees. They grow around the " +
        "large rock and and plateau.\n");

    add_item("roots", "You see a huge maze of roots here.\n");
    add_item("maze", "You see a huge maze of roots here.\n");
    add_item("hole", "@@hole_desc@@");
}

string
you_see_hole()
{
    if (TP->query_prop(PLAYER_HAS_FOUND)){
	return "A hole is hidden is between the tree roots.\n";
    }
    return "\n";
}

string
hole_desc()
{
    if (TP->query_prop(PLAYER_HAS_FOUND))
    {
	return "This hole was well hidden among the tree roots. It is small but "+
	"maybe you can squeeze through it.\n";
    }
    return "You find no hole.\n";
}

void
init()
{
    ::init();
    add_action("climb_down", "climb");
    add_action("look_down", "look");
    add_action("jump_down", "jump");
    add_action("enter_hole", "enter");
}

int 
climb_down(string down) 
{
    int how_high;

    if(down == "down")
    {
	    if (gStage)
    	{
    	    TP->catch_msg("You decided to wait until the other climber "+
    	      "finishes. It is really safer...\n");
    	    return 1;
    	}
        // Check if a leader of a team wants to climb...
        else if(sizeof(TP->query_team()))
        {
            write("Hey! It is too dangerous to lead your team down the rock!\n");
            write("Perhaps if you ventured down the big dark rock alone...\n");
            say(QCTNAME(TP)+" looks down the rock as if considering climbing down... " +
            "The way everyone must go eventually.\n");
        
            return 1;
        }
    	else
    	{
    	    how_high = random(TP->query_skill(SS_CLIMB));
	
            if(sizeof(TP->query_weapon(-1)))
                how_high = MIN(how_high , 10+random(20));

            (ROOM_D)->set_climber_state(1);
            TP->remove_prop(PLAYER_HAS_FOUND);
    	    TP->move_living("M",ROOM_CLIMB);
    	    tell_room(ROOM_D,QCTNAME(TP)+" starts to climb down from the rock.\n");
    	    tell_room(ROOM_U, QCTNAME(TP)+" crawls to the edge and with a sad wave starts "+
    	      "to climb down. Remember! You will have to go there too.\n");
    	    TP->catch_msg("You crawl to the edge and with a sad wave start "+ 
    	      "to climb down.\n");
    	    set_alarm(itof(DELAY), 0.0, &climb_next(how_high, TP));
    	    gStage = 1;
    	    return 1;
    	}
    }
    else
    {
        NF("Where do you want to climb?\n");
        return 0;
    }
}

void 
climb_next(int how_high, object climber)
{
    if (!present(climber, find_object(ROOM_CLIMB)))
    {
        gStage = 0;
        return;
    }
    
    if (how_high < gStage * 5)
    {
        climber->catch_msg("Oooops..!!! You lost your grip and slipped "+
    	  "down.\nYou shout: AAAAAAAaaaaaaaaa.....\n"+
          "     AAAaaaaaAAAAaaaa......\n\nOouch, it hurts!\n"+
    	  "Fortunately you wanted to go down anyway...\n\n");
    	tell_room(ROOM_U,"Some climber must have lost the grip on the rock "+
    	  "and is now falling down!\nScreams can be heard: "+
    	  "AAAAAAAaaaaaaaaa.....\n     AAAaaaaaAAAAaaaa......\n"+
          "Well, that climber, like every other climber, wanted "+
          "to go down anyway...\n");
    	tell_room(ROOM_D,QCTNAME(climber)+" lost the grip on the rock "+
    	  "and fell down.\n" +QCTNAME(climber)+ " shouts: "+
          "AAAAAAAaaaaaaaaa.....\n     AAAaaaaaAAAAaaaa......\n"+
    	  "AAAAAAAaaaaaaaaa.....\nWell, "+HE_SHE(climber)+
          " wanted to go down anyway...\n");

    	climber->move_living("M",ROOM_D);
    	climber->reduce_hit_point(DAMAGE*(30 - how_high));

    	if (climber->query_hp() == 0) 
    	    climber->do_die(TO);

    	gStage = 0;
    	return;
    }

    if (gStage == 6)
    {
    	climber->catch_msg("You jump down the last few inches.\n"+
    	  "What a relief that you are down again!\n");
    	tell_room(ROOM_D,QCTNAME(climber)+" jumps down the last few inches.\n"+
    	  QCTNAME(climber)+" made it!!!\n");
    	climber->move_living("M",ROOM_D);

    	/****************************************/
    	/*   HERE I REWARD FOR GOOD CLIMBING    */
    	/****************************************/

    	if (REWARD_QUEST(climber, "climbing"))
    	{
    	    climber->catch_msg("You feel more experienced.\n"+
    	      "Only now you are THE CLIMBER!\n");
    	}

        (ROOM_D)->set_climber_state(0);
       	gStage = 0;
    	return;
    }

    switch (gStage)
    {
        case 5:
        	climber->catch_msg("You are a few feet above the ground.\n");
        	tell_room(ROOM_D, QCTNAME(climber)+" is a few feet above the "+
        	  "ground.\n");
        	break;
        case 4:
        	climber->catch_msg("You are steadily moving further.\n");
        	tell_room(ROOM_D,QCTNAME(climber)+" is steadily moving further.\n");
        	break;
        case 3:
        	climber->catch_msg("You have reached the middle of the rock.\n");
        	tell_room(ROOM_D,QCTNAME(climber)+" has reached the middle of "+
        	  "the rock.\n");
        	break;
        case 2:
        	climber->catch_msg("You have found a crack and rest a bit before "+
        	  "the next part.\n");
        	tell_room(ROOM_U,"The sound of " +QTNAME(climber)+" climbing down "+
              "grows more silent and soon nothing more can be heard of " +
              HIM_HER(climber)+ "...\n");
        	tell_room(ROOM_D,QCTNAME(climber)+" has found a crack and "+
        	  HE_SHE(climber)+" is resting a bit before the next part.\n");
        	break;
        case 1:
        	climber->catch_msg("You are only little below the top.\n");
        	tell_room(ROOM_U,QCTNAME(climber)+" can be heard climbing down the rock.\n");
        	tell_room(ROOM_D,QCTNAME(climber)+" is only little below the top.\n");
        	break;
        default:
        	climber->catch_msg("Hmmm... How strange... for some reason "+
        	  "you did not climb all the way so you fall to the bottom.\n");
        	climber->move_living("M",ROOM_D);
            (ROOM_D)->set_climber_state(0);
        	gStage = 0;
        	return;
    }

    gStage += 1;
    set_alarm(itof(DELAY), 0.0, &climb_next(how_high,climber));

    return;
}


int 
look_down(string down)
{
    object *in_room_d, *in_room_climb;
    string l_o_names="";
    int i;
    if(down=="down")
    {
	say(QCTNAME(TP)+" bends over the edge and looks down.\n");
	tell_room(ROOM_D,QCTNAME(TP)+" peeps from the top of the rock.\n");
	tell_room(ROOM_CLIMB,QCTNAME(TP)+" peeps from the top of the rock.\n");
	TP->catch_msg("After you bend over the edge you can see the whole "+
	  "rock that you have climbed up.\n");
	in_room_d=FILTER_LIVE(all_inventory(find_object(ROOM_D)));
	in_room_climb=FILTER_LIVE(all_inventory(find_object(ROOM_CLIMB)));
	if(sizeof(in_room_d) == 1)
	{
	    TP->catch_msg("You see "+QSHORT(in_room_d[0])+" below the rock.\n");
	};
	if(sizeof(in_room_d) > 1)
	{
	    for (i = 0; i < (sizeof(in_room_d)-2); i++) 
		l_o_names += (QSHORT(in_room_d[i])+", ");
	    l_o_names += (QSHORT(in_room_d[sizeof(in_room_d)-2])+" and "+
	      QSHORT(in_room_d[sizeof(in_room_d)-1]));
	    TP->catch_msg("You see "+l_o_names+" below the rock.\n");
	};
	if(sizeof(in_room_climb) > 0)
	{
	    TP->catch_msg(QCTNAME(in_room_climb[0])+" is climbing the rock.\n");
	}
	return 1;
    }
    NF("Where do you want to look?\n");
    return 0;
} 

int 
jump_down(string down)
{
    if(down=="down")
    {

    // Check if a leader of a team wants to climb...
    if(sizeof(TP->query_team()))
    {
        write("Hey! Want to endanger your whole team, will you!?\n");
        write("You better try that foolishness alone...\n");
        say(QCTNAME(TP)+" takes a step back and take aim for the edge of " +
        "the big dark rock as if to jump down!!! \n\nBut descide not to...\n");
    
        return 1;
    }

	TP->remove_prop(PLAYER_HAS_FOUND);
	TP->catch_msg("With a mad laugh you run to the edge of the rock and "+
	  "jump down.\n"+"You are so mad that you don't even "+
	  "feel how it hurts when you fall to the ground.\n");
	say("With a mad laugh "+QSHORT(TP)+" runs to the edge of the rock and "+
	  "jumps down.\n");
	tell_room(ROOM_D,"You hear someone laugh from above.\n");
	tell_room(ROOM_CLIMB,"You hear someone laugh from above.\n");
	tell_room(ROOM_D,"You look up and see "+
	  "how "+QSHORT(TP)+" jumps from the top of the rock.\n");
	tell_room(ROOM_CLIMB,"You look up and see "+
	  "how "+QSHORT(TP)+" jumps from the top of the rock.\n");
	present("mimo", find_object(ROOM_D))->notify_player_jumps(TP);

	TP->move_living("M",ROOM_D);
	TP->reduce_hit_point(DAMAGE*35);
	if(TP->query_hp()==0) TP->do_die(TO);
	return 1;
    }
    NF("Where do you want to jump? Down???/n");
    return 0;
}

string
search_roots(object searcher, string str)
{
    int sum_skills = searcher->query_skill(SS_AWARENESS);

    if(str == "roots")
    {
    TELL_ADMIN(TP->query_cap_name() +" is doing Prisoner quest.");
	if(CAN_SEE_IN_ROOM(searcher))
	{
	    if(searcher->query_prop(PLAYER_HAS_FOUND))
	    {
		return "Your search reveals nothing more.\n";
	    }
	    if(sum_skills > 29)
	    {
		searcher->add_prop(PLAYER_HAS_FOUND, 1);
		return "You have found a hole hidden between roots.\n";
	    }
	    else
		return "Your search reveals nothing special.\n";
	}
	else
	    return "Your search reveals nothing special.\n";
    }
    return "";
}

int 
enter_hole(string hole)
{
    object *in_room=FILTER_LIVE(all_inventory(TO));
    int i;

    if((hole=="hole") && TP->query_prop(PLAYER_HAS_FOUND))
    {
	for (i = 0; i < sizeof(in_room); i++)
	    in_room[i]->add_prop(PLAYER_HAS_FOUND,1);
	TP->catch_msg("You squeeze through a hole under the roots.\n");
	say(QCTNAME(TP)+" squeezes through a hole under the roots.\n");
	tell_room(MISTY_DIR+"r2",QCTNAME(TP)+" enters through hole.\n");
	TP->move_living("M",MISTY_DIR+"r2");
	return 1;
    } 
    NF("Enter what?\n");
    return 0;
}

int
set_climber_state(int newStage)
{ gStage = newStage; }

int
query_climber_state()
{ return gStage; }
