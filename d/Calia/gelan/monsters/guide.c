/* 
    This guide makes sightseeings in Gelan. 

    coder(s):   Deinonychus 

    history:    DD.MM.YY    what done                       who did 
                7/3/01      npc remember update            Maniac
                3/8/99      fixed problem with "wait" 
                            ambiguity from new emote       Maniac 
               16/6/96     call_outs taken out             Maniac 
		   17.01.95    changed init_living             Deinonychus
               14.09.94    some small updates              Deinonychus
               07.02.93    created                         Deinonychus
 
    purpose:    none 
 
    weapons:    none 
    armours:    none 
 
    objects:    none 
 
    quests:     touristing quest 
    special:    none 
 
    to do:      none 
    bug:        none known 
*/ 

#include "monster.h" 
inherit STD_GUARD;
#include HAUNT_CODE
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>
#include "guide.h"	/* The commands for the guide to move and talk */

#define COST 12 	/* Costs for the tour (in cc) */
#define BIT_NUMBER 4	/* bit to set */
#define BIT_GROUP 1	/* group of quest-bits */
#define REWARD 100	/* amount of exp you get for quest */
#define WAIT_TO_GO 60	/* time between first participate an start */
#define WAIT 6		/* How long he should wait */
#define MAXWAIT 10	/* He should wait not more than MAXWAIT * WAIT */
#define PREP_CALLS 3 	/* How many times the guide tells the time */
			/* that is left to start */
#define TELL_TIME 4	/* Time it takes to say a sentence */
#define SHOUT_OUT_TIME 120

/*
 *  prototypes
 */

string long();
/*
   void work();
*/
int tell(string what);
void shout_out();
int participate();
void start();
int go(string where);
int wait();
int finished();
int sleep(string time);
void walk_through();
void give_reward(object player);
void prepare_to_start();

/*
 *  global variables
 */

object * participients; /* array of players making the tour */
string * parts;		/* parts of a long string */
int busy;		/* Flag if guide's on a tour */
int index;		/* Index for the command array */
int waited;		/* Counter how many periods guide has waited */
int idle;		/* Flag if guide's idle or not */
int shout_out_alarm; 
int start_alarm; 


private void
setup_actions()
{
    enable_commands();
    add_action(tell, "tell");
    add_action(go, "go");
    add_action(wait, "wait");
    add_action(finished, "finished");
    add_action(sleep, "sleep");
    shout_out_alarm = set_alarm(1.0, 0.0, shout_out);
}



/*
 * Function name: create_monster
 * Description:   creates the monster (what else?)
 * Arguments:	  none
 * Returns:	  nothing
 */

void
create_monster()
{
    participients = ({});

    set_race_name("guide");
    set_adj(({"clumsy", "blue-haired",}));
    set_long(BS("@@long@@"));
    default_config_npc(50);
    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,100);
    set_alignment(1000);
    set_alarm(0.0, 0.0, setup_actions); 

/*
    add_prop(OBJ_I_NO_ATTACK, 1);
*/
}



/*****************************************************************************/


/*
 * Function name: init_living
 * Description:   add some commands to the player
 * Arguments:	  none
 * Returns:	  nothing
 */

void
init_living()
{
    add_action("participate", "participate");
    ::init_living();
}


/*****************************************************************************/


/*
 * Function name: long
 * Description:   change long depending if guide's busy or not
 * Arguments:	  flag if he's busy
 * Returns:	  long description
 */

string
long()
{
    if(busy)
	return ("This is a guide making sightseeing tours in Gelan. He " +
		"seems to be leading a tour around the city at the moment.\n");
    else
	return ("This is a guide making sightseeing tours in Gelan. " +
		"Why don't you 'participate' in one of his tours? You " +
		"surely won't regret it.\n");
}


/*****************************************************************************/


/*
 * Function name: tell
 * Description:   like say
 * Arguments:	  string to say
 * Returns:	  0/1
 */


int
tell(string what) 
{
    command("say " + what);
    command(commands[++index]);	
    return 1;
}


/*****************************************************************************/


/*
 * Function name: shout_out
 * Description:   causes the guide to shout that he's looking for participients
 * Arguments:	  none
 * Returns:	  nothing
 */

void
shout_out()
{
  if ((MASTER_OB(environment(TO))) == GELAN_ROOMS + "guards_info")
  {
    command("shout Sightseeing! Participate in a sightseeing you'll " +
      "never forget! Only 1 silver coin per person!");
    remove_alarm(shout_out_alarm); 
    shout_out_alarm = set_alarm(itof(SHOUT_OUT_TIME), 0.0, shout_out);
  }
  else
  {
    TO->move_living("towards his office", GELAN_ROOMS + "guards_info", 1, 0);
    remove_alarm(shout_out_alarm); 
    shout_out_alarm = set_alarm(itof(SHOUT_OUT_TIME), 0.0, shout_out);
  }
}

/*****************************************************************************/


/*
 * Function name: participate
 * Description:   Let a player participate on a tour
 * Arguments:	  none
 * Returns:	  0/1
 */


int 
participate()
{
  object ticket;

  if(member_array(TP, participients) != -1)
  {
    NF("You already participate in this tour.\n");
    return 0;
  }

  if(busy)
  {
    NF("The guide is busy with a tour, so you can't participate at " +
       "the moment. Wait for the guide at the info-office.\n");
    return 0;
  }

  if (MASTER_OB(environment(TO)) != GELAN_ROOMS + "guards_info")
  {
    NF("What?\n");
    TO->move_living("towards his office", GELAN_ROOMS + "guards_info", 1, 0);
    return 0;
  }

  else
  {
    if(!(MONEY_FN->take_money(TP, COST)))
    {
      NF("I'm afraid you can't afford this tour.\n");
      return 0;
    }
    else
    {    
      tell_object(TP, "You get yourself a ticket for the sightseeing " +
	"tour in Gelan.\n");
      TO->command("say Thanks for participating in this tour. I'll just " +
        "wait a little moment to see if there are other people who " +
        "want to participate in this tour. Please stay here.");
      tell_room(environment(TO), QCNAME(TP) + " gets a ticket " +
	"for the sightseeing tour in Gelan.\n", TP);
      setuid();
      seteuid(getuid(TO));
      ticket = clone_object(GELAN_OBJECTS + "tour_ticket");
      ticket->move(TP);
      participients += ({TP});
      if(sizeof(participients) == 1)
      {
	remove_alarm(shout_out_alarm);
        shout_out_alarm = 0; 
	waited = 0;
	start_alarm = set_alarm(itof(WAIT_TO_GO), 0.0, start);
	prepare_to_start();
      }
      return 1;
    }
  }
}


/*****************************************************************************/


/*
 * Function name: prepare_to_start
 * Description:   Tell how long it takes until the tour starts.
 * Arguments:	  none
 * Returns:	  nothing
 */

void
prepare_to_start()
{
    int seconds_left;
    string seconds;
    mixed ga; 

    ga = get_alarm(start_alarm); 
    if (sizeof(ga)) 
        seconds_left = ftoi(ga[2]); 
    else
        return;

    if((waited++ < PREP_CALLS) && (seconds_left > 0))
    {
	seconds = LANG_WNUM(seconds_left);
    	command("say Hurry up if you want to participate in this " +
    	    "tour. I will start in " + seconds + " seconds.");
        set_alarm(itof(WAIT_TO_GO / PREP_CALLS), 0.0, prepare_to_start);  
    }
}


/*****************************************************************************/


/*
 * Function name: start
 * Description:   start the tour
 * Arguments:	  none
 * Returns:	  nothing
 */

void
start()
{
    busy = 1;
    index = 0;
    waited = 0;
    idle = 0;

    command("introduce me");
    command(commands[index]);
}


/*****************************************************************************/


/*
 * Function name: go
 * Description:   move in a direction
 * Arguments:	  where to move
 * Returns:	  0/1
 */

int
go(string where)
{
    command(where);
    command(commands[++index]);
    return 1;
}


/*****************************************************************************/


/*
 * Function name: wait
 * Description:   wait for players to follow
 * Arguments:	  none
 * Returns:	  0/1
 */

int
wait()
{
    int i;
    int should_have;	/* length of actual participation list */
    int have;		/* how many players in the surroundigs are found */
    object * room_inv;	/* holds the objects in the room */
    object * new_list;	/* List of those who followed */

    if(waited++ <= MAXWAIT)
    {
	should_have = sizeof(participients);
	have = 0;
	new_list = ({});
	room_inv = all_inventory(environment(TO));
	for(i = 0; i < sizeof(room_inv); i++)
	    if(member_array(room_inv[i], participients) != -1)
	    {
		new_list += ({room_inv[i]});
		++have;
	    }
    }

    if((waited > MAXWAIT) || (have == should_have))
    {
	waited = 0;
	if(have < should_have)
	    for(i = 0; i < should_have; i++)
		if(member_array(participients[i], new_list) == -1)
		    tell_object(participients[i], "Uups, I think you missed " +
			"a part of the tour. You should have paid more " +
			"attention where the guide walked along. Now you " +
			"have to pay again for a new tour.\n");
	if(have == 0) /* no more players in participients list */
	{
	    ++index;
	    walk_through();
	    return 1;
	}
	participients = new_list;
	command(commands[++index]);
    }
    else
        set_alarm(itof(WAIT), 0.0, wait); 

    return 1;
}


/*****************************************************************************/


/*
 * Function name:   sleep
 * Description:     stops actions for time seconds
 * Arguments:	    time
 * Returns:	    0/1
 */

int
sleep(string time)
{
    int how_long;

    sscanf(time, "%d", how_long);

    if(!idle)
    {
	idle = 1;
        set_alarm(itof(how_long), 0.0, &sleep(time));  
    }
    else
    {
	idle = 0;
	command(commands[++index]);
    }
    return 1;
}


/*****************************************************************************/


/*
 * Function name:   finished
 * Description:     this function's called at the end of the tour
 * Arguments:	    none
 * Returns:	    0/1
 */


int 
finished()
{
    int i;

    for(i = 0; i < sizeof(participients); i++)
	give_reward(participients[i]);

    participients = ({});
    busy = 0;
    shout_out_alarm = set_alarm(itof(SHOUT_OUT_TIME), 0.0, shout_out); 
    return 1;
}


/*****************************************************************************/


/*
 * Function name:   walk_through
 * Description:     this function's called when the participation list
		    somehow's empty
 * Arguments:	    none
 * Returns:	    nothing
 */


void 
walk_through()
{
    string direction;
 
    participients = ({});
    for(; index < (sizeof(commands) - 1); ++index)
	if(sscanf(commands[index], "go %s", direction))
	    command(direction);

    busy = 0;
    shout_out();

    return;
}


/*****************************************************************************/


/*
 * Function name: give_reward
 * Description:   sets the bit of the player and adds exp
 * Arguments:	  player
 * Returns:	  nothing
 */


void
give_reward(object player)
{
    if(player->test_bit(DOMAIN, BIT_GROUP, BIT_NUMBER)){
	tell_object(player, "You really love this tour, eh?\n");
	log_file("gelan_tour", player->query_name() + 
          " made an additional tour.\n");
    }
    else
    {
	player->set_bit(BIT_GROUP,BIT_NUMBER);
	player->add_exp(REWARD);
	tell_object(player, "Now that you've seen so much of Gelan you " +
	    "really feel more experienced.\n");
	log_file("gelan_tour", player->query_name() +
	  " made a tour through Gelan.\n");
      player->remove_prop(LIVE_I_KNOW_CALIA_GELAN_NPCS); 
    }
    return;
}

	

/*****************************************************************************/


/*
 * Function name: help_other
 * Description:   shadows the help_other function in STD_GUARD
 * Arguments:	  none
 * Returns:	  nothing
 */

void
help_other(string room, object attacker)
{
    if (!query_attack())
    command("say Evil's lurking around. Hope you won't be killed by " +
	    "some nasty invader.");
    set_start_room(file_name(environment(TO)));
    return;
}


/* shouldn't go anywhere when an enemy leaves */
void
notify_enemy_gone(object attacked)
{
}

