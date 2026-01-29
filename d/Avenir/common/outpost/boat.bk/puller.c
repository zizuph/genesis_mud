// -*-C++-*-
// $Id: puller.c,v 1.2 1995/09/06 18:08:41 bob Exp $
// Sea monster to pull the outpost Great Sea boat  ** UNFINISHED **
// creator(s):   Kazz   April 1995
// update:       Boriska, Sept 1995
// purpose:      To pull boats in the Great Sea
// note:         This will be used as a captain of boats.
// bug(s):
//
// ideas:	* Will it be able to be used as a regular monster also?
//		* it only lives/fights in water, a fight only starts by
//		  stabbing (unless someone ever ends up swimming under water)

#include </sys/ss_types.h>
#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/boat/ship.h"

#pragma save_binary

inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/act/domove";
inherit "/std/combat/unarmed";

private int food_state = 0;
private int food_amount = 0; // how much food is in our belly

void set_hungry();
void add_food(int amount);
int  query_food_state();
void decrease_food();

private void update_state();

void
create_creature()
{
    if(!IS_CLONE)
      return;
    
    set_name("sea monster");
    add_name("monster");
    set_gender(G_NEUTER);		
    set_long("This monster is covered with large scales.  "+
	     "It's fierce teeth would kill easily. "+
	     "The eyes seem to pierce right through you. "+
	     "It's really just a simple monster to pull boats. "+
	     "\n" );
    set_stats(({ 100, 90+random(10), 90+random(10),
		 10+random(10), 10+random(10), 100 }));
    set_alignment(0);
    
        
    set_skill( SS_DEFENSE, 80 );
    set_skill( SS_BLIND_COMBAT, 80 );
    set_skill( SS_AWARENESS, 50 );

    set_cact_time(3+random(3));
    add_cact("emote snarls with rage." );    
    add_cact("emote blasts water all over the boat." );    
    add_cact("emote sways its head back and forth." );

    set_hungry();
} // create_monster()

// food_amount is the actual gram count of food in the creature's belly

void
set_hungry() {
  food_amount = 0;
  update_state();
}

void
add_food(int amount) 
{
  food_amount += amount;
  update_state();
} 

void
decrease_food()
{
  if (food_state == HUNGRY)
    return;
  
  food_amount -= FOOD_CONSUMPTION;
  update_state();
} 

private void
update_state() {
  if (food_amount < 0 )
    food_amount = 0;
  if (food_amount < FOOD_CONSUMPTION)
    food_state = HUNGRY;
  else
    food_state = FED;
}
  
int
query_food_state() { return food_state; }

void
equip_me () {}
