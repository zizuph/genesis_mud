
/* 09 Sept 2003 Shut down temporarily after players got stuck here
 *
 * There seems to be a problem with more than one player trying
 * to climb at once. Possibly in teams.
 *
 * Note: When a player starts climbing he doesn't yell to the
 * correct player if more than one in the room.
 *
 *   Updated 2008-04-24 by Toby
 *
 *     - updated code checking if allowed to climb
 *       Not leading a team = allowed
 *
 *   2008-05-05: The climbing part opened again! /Toby
 *
 */

/* highpass */

#include <filter_funs.h>
#include "local.h"
#include "climb.h"

inherit SHIRE_ROOM;


/*
 * Prototypes
 */
void who_climb(mixed foo);
void climb_next(int how_high,object climber);

static int gStage = 0;
int quest_closed = 0; // 0 = open, 1 = closed

void
create_shire_room()
{
    seteuid(getuid());

    ROOM_CLIMB->load_me();
    ROOM_U->load_me();
    set_short("behind rock");
    set_long("You are crawling the slope of the Misty Mountains trying to " +
      "pass a huge rock. It seems that you haven't chosen the right " +
      "way. The other one must be much easier than this one. You " +
      "also notice a cave here.\n@@who_climbs@@");


    add_item("rock", "It is big and dark. No way to pass it except " +
      "walk around. You may try to climb it too but " +
      "beware!!! It is quite high and if you fall down " +
      "you can be severely hurt.\n@@exa_rock@@");
    add_item("cave", "It is dim and looks dangerous. "+
      "Better stay out of it.\n");

    /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"p3", "west",     0,    10);
    add_exit(MISTY_DIR+"p4", "north",    0,    10);
    add_exit(MISTY_DIR+"c1", "in",       0,    4);
//    add_exit(MISTY_DIR + "climb", "rock", 1,0,1);

    reset_shire_room();
}

void
reset_shire_room()
{

    object monster;

    seteuid(getuid());

    monster = present("mimo");

    if (!monster)
    {
        monster = CLONE_NPC(MISTY_NPC_DIR+"climber");
    }

}

string
exa_rock()
{
    say(QCTNAME(TP)+" studies the rock carefully.\n");
    return "";
}

init()
{
    ::init();
    add_action("climb_rock", "climb");
}

int
climb_rock(string rock)
{
    int how_high;

    if(rock=="rock")
    {

        switch(quest_closed)
        {
            case 1: // quest closed
            {
                write("The avalanche has settled, and fewer boulders have " +
                    "rolled away, but it looks like the way is still blocked.\n");
                return 1;
                break;
            }
        }

	    if (gStage)
	    {
	        TP->catch_msg("You decide to wait until the other climber "+
	          "finishes. It is really much safer...\n");
	        return 1;
	    }
        // Check if a leader of a team wants to climb...
        else if(sizeof(TP->query_team()))
        {
            write("It looks very precarious to lead a whole team up that rock!\n");
            write("Perhaps if you ventured up that big dark rock alone...\n");
            say(QCTNAME(TP)+" looks up at the rock.\n");
        
            return 1;
        }
	    else
	    {
    	    how_high = random(TP->query_skill(SS_CLIMB));

	        if(sizeof(TP->query_weapon(-1)))
	            how_high = MIN(how_high , 29);

            (ROOM_U)->set_climber_state(1);
	        say(QCTNAME(TP)+" starts to climb the rock.\n");
	        TP->catch_msg("You start to climb the rock...\n");
	        gStage = 1;
	        set_alarm(itof(DELAY), 0.0, &climb_next(how_high,TP));
	        TP->move_living("M", ROOM_CLIMB);
	        present("mimo")->notify_player_starts_climb(TP);
	        return 1;
	    }
    }
    else
    {
	    NF("What do you want to climb?\n");
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

    if (how_high < gStage * 4)
    {
	    climber->catch_msg("Oooops..!!! You lost your grip and slipped down.\n"+
	      "You shout: AAAAAAAaaaaaaaaa.....\nOuch, it hurts!\n"+
	      "Now you have to try it again...\n");
	    tell_room(ROOM_D,QCTNAME(climber)+" lost the grip on the rock "+
	      "and fell down.\n");
	    tell_room(ROOM_D,QCTNAME(climber)+" shouts: AAAAAAAaaaaaaaaa..... \n"+
	      "Now "+HE_SHE(climber)+" has to try again...\n");
	    tell_room(ROOM_U,"A "+climber->query_gender_string()+" "+
	      climber->query_race_name()+" voice shouts: "+
	      "AAAAAAAaaaaaaaaa.....\n");
	    present("mimo")->notify_player_falls(climber);
	    climber->move_living("M",ROOM_D);
	    climber->reduce_hit_point(DAMAGE * how_high);

    	if (climber->query_hp() == 0)
    	    climber->do_die(TO);

    	gStage = 0;
	    return;
    }

    if (gStage == 6)
    {
	    climber->catch_msg("You crawl up and over the edge of the rock...\n"+
	      "You made it!!!.\n");
	    tell_room(ROOM_D,QCTNAME(climber)+" made it!!!\n");
	    tell_room(ROOM_U,QCTNAME(climber)+" comes crawling through the "+
	      "edge of the rock.\n");
	    climber->move_living("M",ROOM_U);
	    present("mimo")->notify_player_made_it(climber);
        (ROOM_U)->set_climber_state(0);
	    gStage = 0;
	    return;
    }

    switch (gStage)
    {
      case 1:
	    climber->catch_msg("You are a few feet above the ground.\n");
	    tell_room(ROOM_D, QCTNAME(climber)+" is a few feet above the "+
	      "ground.\n");
	    break;
      case 2:
	    climber->catch_msg("You are steadily moving further.\n");
	    tell_room(ROOM_D,QCTNAME(climber)+" is steadily moving further.\n");
	    break;
      case 3:
	    climber->catch_msg("You have reached the middle of the rock.\n");
	    climber->catch_msg("You breathe hard from the strain in your muscles!\n");
	    tell_room(ROOM_D,QCTNAME(climber)+" has reached the middle of "+
	      "the rock.\n");
	    break;
      case 4:
	    climber->catch_msg("You have found a crack and rest a bit before "+
	      "the next part.\n");
	    tell_room(ROOM_D,QCTNAME(climber)+" has found a crack and "+
	      HE_SHE(climber)+" is resting a bit before the next part.\n");
	    break;
      case 5:
	    climber->catch_msg("You are only little below the top.\n");
	    climber->catch_msg("You breathe very hard from the strain in your muscles!\n");
	    tell_room(ROOM_D,QCTNAME(climber)+" is only little below the top.\n");
	    tell_room(ROOM_U,"Someone can be heard breathing rather hard from below "+
                  "the edge of the rock.\n");
	    break;
      default:
	    climber->catch_msg("Hmmm... How strange... for some reason "+
	      "you did not climb all the way so you fall to the bottom.\n");
	    climber->move_living("M",ROOM_D);
        (ROOM_U)->set_climber_state(0);
	    gStage = 0;
	    return;
    }

    gStage += 1;
    set_alarm(itof(DELAY), 0.0, &climb_next(how_high,climber));

    return;
}


string
who_climbs()
{
    object *in_room_climb;

    in_room_climb=FILTER_LIVE(all_inventory(find_object(ROOM_CLIMB)));

    if(sizeof(in_room_climb) > 0)
    {
        set_alarm(0.0,0.0, &who_climb(({TP, in_room_climb[0]})));
    }
    return "";
}

void
who_climb(mixed foo)
{
    foo[0]->catch_msg(QCTNAME(foo[1])+" is climbing the rock.\n");
}

int
set_climber_state(int newStage)
{ gStage = newStage; }

int
query_climber_state()
{ return gStage; }


