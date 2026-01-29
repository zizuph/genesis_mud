/*
 * Filename: /d/Avenir/common/ships/bazaar/puller.c
 * Original creator: Kazz on Apr 1995
 * Purpose: Sea monster to pull the outpost Great Sea boat  ** UNFINISHED **
 * Last update(s):
 *    Boriska on Sep 1995
 *    Manat on Jul 2000   - changed coding style and stuff
 *                          moved #include below inherit
 * Note: This will be used as a captain of boats.
 * Known bug(s):
 * Ideas: * Will it be able to be used as a regular monster also?
 *        * it only lives/fights in water, a fight only starts by
 *          stabbing (unless someone ever ends up swimming under water)
 * To-do:
 */
#pragma save_binary
#pragma strict_types
/* added strict_types check because you always want it! Manat on Aug 2000 */

inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/act/domove";
inherit "/std/combat/unarmed";

#include </sys/ss_types.h>
#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/ships/bazaar/ship.h"

private int food_state = 0;
private int food_amount = 0; // how much food is in our belly

public void set_hungry();
public void add_food(int amount);
public int  query_food_state();
public void decrease_food();

private void update_state();

/*
 * Function name: create_creature
 * Description  : the creator for this creature
 */
public void
create_creature()
{
    if (!IS_CLONE)
        return;
    
    set_name("monster");
    add_name("sea monster");
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
}

/*
 * Function name: set_hungry
 * Description  : food_amount is the actual gram count of food in the
 *                creature's belly
 */
public void
set_hungry()
{
    food_amount = 0;
    update_state();
}

/*
 * Function name: add_food
 * Description  : add an amount of food to the creature's belly
 * Arguments    : int amount - the food amount
 */
public void
add_food(int amount)
{
    food_amount += amount;
    update_state();
}

/*
 * Function name: decrease_food
 * Description  : removes some of the amount of food in the creature's belly
 */
public void
decrease_food()
{
    if (food_state == HUNGRY)
        return;

    food_amount -= FOOD_CONSUMPTION;
    update_state();
} 

/*
 * Function name: update_state
 * Description  : update the food_state depending on the food_amount
 */
private void
update_state()
{
    if (food_amount < 0 )
        food_amount = 0;
    if (food_amount < FOOD_CONSUMPTION)
        food_state = HUNGRY;
    else
        food_state = FED;
}

/*
 * Function name: query_food_state
 * Description  : return the current food state
 * Returns      : HUNGRY/FED - the food state
 */
public int
query_food_state()
{
    return food_state;
}

/*
 * Function name: equip_me
 * Description  : This is called to let the creature equip it's stuff
 */
public void
equip_me ()
{
    /* Nothing to equip since this creature doesn't use anything */
}
