//-*-C++-*-
// helper.c for inheriting in other NPCs
// Coded by Boriska, May 1994
// My first NPC! :)

/*
* Upon being attacked  this monster scans adjacent rooms for its "friends"  
* able to help. Willing to help brothers arrive and attack.
* Defined functions :                                                       
*                                                                           
*  set_helper_friends (string *friends )                                    
*                                                                           
*    Names of NPCs we're willing to help. Setting friends to ({})           
*    makes us help everyone.                                                
*                                                                           
*  set_helper_actions ( string *actions )                                   
*                                                                           
*  Set things  we do  in different stages:                                  
*  actions[0] upon being atacked                                            
*  actions[1] upon receiving call for help                                  
*  actions[2]  before attacking friend's enemy
*
* Note: Only adjacent rooms are scanned, I see no point in loading CPU
* with smart but computationally heavy shortest paths algorithms.
*/


inherit "/std/monster"; 

#include <stdproperties.h>
#include <formulas.h>

#define HELP_ACT 0
#define SUPPORT_ACT 1
#define ARRIVAL_ACT 2

#define CHANCE_TO_FAIL 3
// random (CHANCE_TO_FAIL) probability for help to fail

/* array of NPCs' real names which we're ready to help to */
/* Can be changed by set_helper_friends() */
/* Setting friends to ({}) makes us help everybody */

private string *friends = ({"helper"});


/* texts that are shouted or said in different stages. */
/* Can be changed by set_helper_actions() */

private string *actions = ({"shout Aid me!",
                            "shout Hold fast! I'm on my way!",
			    "say Die, you cold-blooded murderer!"});
void
create_monster()
{
  ::create_monster();
  set_name("helper");
}


/* called when NPC is attacked */
void
attacked_by(object ob)
{
  string *adjacent_rooms;
  object tr; /*this room */
  object nr; /* next room */
  object *neighbors;
  int i;

  
  ::attacked_by(ob);
  
  if ( strlen(actions[HELP_ACT]) )
    command (actions[HELP_ACT]);
  
  /* look for NPCs in this and adjacent rooms */
  
  neighbors = all_inventory(tr = environment());

  adjacent_rooms = tr->query_exit_rooms();

  for ( i = 0; i < sizeof(adjacent_rooms); i++ )
    {
      /* make sure all adjacent rooms are loaded */
      
      if ( !find_object(adjacent_rooms[i]))
	adjacent_rooms[i]->hjhj();
      
      if ( nr = find_object(adjacent_rooms[i]) )
	neighbors += all_inventory(nr);
    }


 /* ask for help only from those who are smart enough to do that */
 //  neighbors = filter (neighbors, "able_to_help",this_object());
 // no need to do it 
  neighbors->summon_help(tr, query_real_name(), ob); 
}



/* Called from another NPC being attacked         */
/* Arguments:                                     */
/*            room - room where attacked NPC is   */
/*            attacked - who's being attacked     */
/*            attacker - attacker :)              */

void
summon_help(object room, string attacked, object attacker)
{
  
  /* we help friends only and don't rush to help when already fighting */
  if ( sizeof(friends) > 0 && member_array (attacked, friends) < 0
      || query_attack() || ! F_DARE_ATTACK (this_object(), attacker)
      || random(CHANCE_TO_FAIL) )
    return;
  
  if ( environment() == room) /* already here, no need to run */
    {
      command ( "kill " + attacker->query_real_name());
      return;
    }
  
  set_alarm (5.0+rnd()*30.0, 0.0, "go_and_attack", room, attacker);

}


void
go_and_attack ( object room, object attacker )
{
  mixed *exits;
  int i;
  
  /* find where to go in order to get to room */
  exits = environment()->query_exit();
  if ( (i = member_array (file_name(room), exits)) < 0 ) /* cannot get there */
    return;

  if ( strlen(actions[SUPPORT_ACT]) )
    command (actions[SUPPORT_ACT]);

  if (  !present(attacker, room) || move_living(exits[i+1], room, 1, 1))
    return; 
  
  if ( strlen (actions[ARRIVAL_ACT]) )
    command (actions[ARRIVAL_ACT]);
  
  command ( "kill " + attacker->query_real_name());
}

void
set_helper_friends (string *fr)
{
  friends = fr;
}

void
set_helper_actions (string *msg)
{
  if (sizeof(msg) == 3)
    actions = msg;
}

/* 
 * The default thief attack function.
 * Will be called if KILL_THIEF is set
 * (from common.h), and will execute one
 * of the creatures random cacts before
 * attacking the player.
 */
public void thief_fun(object thief, object victim, object ob)
{

    string *acts = query_cact();

    if(sizeof(acts))
       set_alarm(1.5, 0.0, 
          &command(acts[random(sizeof(acts))]));

    set_alarm(3.0, 0.0, &command("kill "+
          thief->query_real_name()));
}

