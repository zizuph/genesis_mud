/*
  Caravan master object,
  by Udana, 03/06
*/
#pragma strict_types

inherit "/std/object.c";

#include <stdproperties.h>
#include <macros.h>

#include <filter_funs.h>
#include "/d/Terel/include/Terel.h"

#include "../include/defs.h"

#define COLOURS ({"green", "red", "blue", "yellow"})
#define PLAYER_I_DEFENDED_CARAVAN "_player_i_defended_caravan"
#define PLAYER_I_DESTROYED_CARAVAN "_player_i_destroyed_caravan"

/*index in ROUTE array, telling in which room caravan currently is*/

int position;
int move_alarm = 0;
int created = 0;

/* if it's one, caravan is moving north, it goes backwards if it's -1 */
int step = 1;

/*For quest purpose */
object attacker = 0, defender = 0; 

/* creates new caravan, the direction is used as a step in move_caravan
  method. So if it's one it goes up the ROUTE array, if it's -1 it goes
  opposite direction
  */
public void create_caravan(int direction);


/*moves caravan to the next location, or disbands it if it made it to the end*/

void move_caravan();

/*sets player defending the caravan - means someone is doing a quest*/
public void set_defender(object ppl);

/*sets player attacking the caravan - means same */
public void set_attacker(object ppl);

/*returns 1, every caravan object has such a rutine*/
public int is_caravan();

/*after caravan reached its destination, it disbands. If any quest will be involved, the reward
  can be given at this point.*/

void disband_caravan();



public void create_object()
{
    set_name("caravan");
    set_short("caravan");
    set_long("caravan");

    set_no_show(); // <<--------
}


public void create_caravan(int direction)
{
	FIX_EUID;
	
	/* something baaad happened before */
	if(created)
		return;
	created = 1;
	
	
  step = (direction == 1) ? direction : -1;
  object *wagons = allocate(4); 
  position = (step == 1 ? 0 : sizeof(ROUTE) - 1);
	/* assuming no one is doing the quest, it will be set if otherwise. */
	defender = 0;
	attacker = 0;
	
  int tmp;

  move(ROUTE[position]);
	/* wagons */
  for(int i = 0; i < sizeof(COLOURS); ++i)
  {
	wagons[i] = E(TO)->clone_here(OBJ + "wagon.c");
	tmp = i + 1;
	
	wagons[i]->create_wagon(COLOURS[i], CARAVAN + "wagon" + tmp +  ".c");
	int blh = (wagons[i]->query_inside())->create_inside(wagons[i], step);
	if(blh)
	{
		wagons[i]->move(E(TO), 1);
	}
	else
		wagons[i]->remove_object();
	
  }

  /* Guards going on foot */
  for(int i = 0; i < sizeof(COLOURS); ++i)
  {
    int j = random(2) + 1;
    while(j--)
    {
      object free_guard = E(TO)->clone_here(NPC + "guard.c");
      free_guard->set_colour(COLOURS[i]);
      free_guard->move(E(TO));
    }
  }


  tell_room(E(TO), "In great noise and chaos, merchant, guards and citizens gathers around, "+
    "forming a new caravan that will soon set off to " + (step == 1 ? "the Town of Last" : "Calathin")
    + "\n");
  move_alarm = set_alarm(120.0, 0.0, &move_caravan());
}



public int is_caravan()

{

  return 1;

}



void move_caravan()
{
  object *caravan_members = filter(all_inventory(E(TO)), &->is_caravan());
  string move_command;
	string *exits = ROUTE[position]->query_exit();
  /*there is no caravan, if player did it give him some credit*/
  if(sizeof(caravan_members) == 1)
  {
	if(objectp(attacker))
	{
		attacker->catch_msg("The caravan is no more, you can get your reward from "+
			"bandits now.\n");
		attacker->add_prop(PLAYER_I_DESTROYED_CARAVAN, 1);
	}
    remove_object();
    return;
  }
  /*the caravan made it to the end - reward any players helping it now*/
  if(position + step == sizeof(ROUTE) || position + step < 0)
  {
	if(defender)
	{
		defender->catch_msg("The caravan is safe now, you can go to the office in "+
			"Calathin and ask for your reward.\n");
		defender->add_prop(PLAYER_I_DEFENDED_CARAVAN, 1); 
	}
	return disband_caravan();
  }
  
	if(ROUTE[position]->caravan_block(attacker))
	{
		if(!pointerp(get_alarm(move_alarm)))
			move_alarm = set_alarm(30.0, 0.0, &move_caravan());
		return;
	}
  
	
	for(int i = 0; i < sizeof(exits); ++i)
		if(exits[i] + ".c" == ROUTE[position + step])
			move_command = exits[i + 1];

	if(strlen(move_command))
	{
		for(int i = 0; i < sizeof(caravan_members); ++i)
			caravan_members[i]->command(move_command);
		if(objectp(defender) && E(defender) == E(TO))
		{
			defender->catch_msg("You move along with the caravan.\n");
			defender->command(move_command);
		}
	}
  
  /* Some have moved normally */
  caravan_members = filter(all_inventory(E(TO)), &->is_caravan());
  /*the caravan keeps moving*/
  tell_room(ROUTE[position], "The caravan continues along its route.\n", defender);
  position+= step;
  tell_room(ROUTE[position], "Wagon after wagon, the caravan emerges from behind the trees.\n");
  for(int i = 0; i < sizeof(caravan_members); ++i)
    caravan_members[i]->move(ROUTE[position], 1);
  if(!pointerp(get_alarm(move_alarm)))
	move_alarm = set_alarm(30.0, 0.0, &move_caravan());
  /* If there is a defending player bandits can show up*/
  if(objectp(defender))
	ROUTE[position]->ambush_caravan(defender);
}

public int set_defender(object ppl)
{
	if(!objectp(defender) && position == 0 && step == 1)
	{		
		defender = ppl;
		return 1;
	}
	return 0;
}


public int set_attacker(object ppl)
{
	
	if(!objectp(attacker) && position == 0 && step == 1)
	{		
		attacker = ppl;
		return 1;
	}
	return 0;
}

void disband_caravan()
{
  object *caravan_members = filter(all_inventory(E(TO)), &is_caravan());

  /*there is no caravan*/
  if(!sizeof(caravan_members))
  {
    remove_object();
    return;
  }

  for(int i = 0; i < sizeof(caravan_members); ++i)
    caravan_members[i]->remove_caravan_object();
  remove_object();
}


