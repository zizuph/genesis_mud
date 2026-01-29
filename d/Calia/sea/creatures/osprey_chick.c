/*  file:  /d/Calia/sea/creatures/osprey_chick.c
 *  coder:  Tigerlily
 *  date:  2002-09-03
 *  description:  Creature who plays a role in the lucky lure
 *                  quest--see /d/Calia/private/QUESTS/lucky_lure_quest
 *                  for more info.
 */ 

#pragma strict_types

inherit "/std/creature"; 
inherit "/std/act/domove"; 
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <const.h>
#include "defs.h"
#include SEA_QUESTS


#define A_BEAK  0
#define H_BODY  1
#define A_TALON 3
#define A_WING 2

// function prototypes

int react_attack(object attacker);
void react_give(object gift, object giver); 
int make_doodoo(object player);
int reset_quest();


void
create_creature()
{
    set_name("chick");
    set_race_name("chick");
    add_name("bird");
    add_name("osprey");
    set_adj(({"fluffy", "osprey"}));
    add_adj("baby");

    set_long("This is a fluffy white osprey chick."+
      " It is covered in downy feathers. Its beak is"+
      " constantly open, begging for food.\n");

    set_gender(G_MALE);  
    set_stats(({20, 20, 20, 20, 20, 30}));
    set_hp(query_max_hp()); 
    set_skill(SS_UNARM_COMBAT, 100); 
    set_skill(SS_DEFENCE,100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);

    // always hungry
    set_stuffed(0);
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    set_attack_unarmed(A_BEAK,30,30, W_IMPALE, 100, "beak");
    set_attack_unarmed(A_TALON,30,30, W_IMPALE, 100, "talons");
    set_attack_unarmed(A_WING,30, 30, W_BLUDGEON, 100, "wings");

    set_hitloc_unarmed(H_BODY, ({5,30,30,30}), 100, "body");

    add_prop(LIVE_I_NEVERKNOWN, 1); 
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_HEIGHT, 5000);
    add_prop(OBJ_I_WEIGHT, 4500);
    add_act("emote squawks hungrily.");
    add_act("emote hops around."); 
    add_act("emote eyes you as possible competition."); 
    add_prop(NPC_I_NO_LOOKS, 1);
    set_cact_time(20);
    add_cact("emote squawks loudly for his mother.");

    set_act_time(10);  
    set_m_in("hops in"); 
    set_m_out("hops out"); 
}


void
attacked_by(object attacker)
{
    set_alarm(1.0, 0.0, &react_attack(attacker));
}

int
react_attack(object attacker)
{
    command("emote squawks loudly for its mother.");
    return 1;
}

/*******************************************************************
 * Function name: enter_inv
 * Description  : responses to gifts from player (especially
 *                looking for fish (FISH_I_THALASSIAN_SEA)
 * Arguments    : object given to chick, from = player
 * Returns      : nothing
 */
void 
enter_inv(object obj, object from) 
{ 
    // Call the inherited function code 
    ::enter_inv(obj, from); 

    // If it's a gift, set up a reaction one second after.. 
    if (living(from)) 
	set_alarm(1.0, 0.0, &react_give(obj, from)); 
} 
/* 
 *  Function:     react_give 
 *  Description:  React to receiving an object from a living. This 
 *                is called by alarm from "enter_inv" below. Most 
 *                monsters deal with attempts to give items to them 
 *                in the default way, i.e. just they don't accept. 
 *                This guy accepts and responds though. 
 *                If the gift is a fish, chick will eat and
 *                like most babies create a mess as result
 *                The poop object can contain the lucky lure
 *                if the player is questing for it
 * 
 *  Arguments:    object gift   -    the given object 
 *                object giver  -    the living who gave it 
 */ 
void 
react_give(object gift, object giver) 
{ 
    int i = 0;
    int amnt = 0;
    /* 
     * If the gift giver has gone or can't be seen, what should 
     * be done? This monster will get suspicious and drop the 
     * item. 
     */ 
    if (!objectp(giver) || 
      !objectp(present(giver, environment(this_object()))) || 
      !CAN_SEE(this_object(), giver) ||
      !CAN_SEE_IN_ROOM(this_object())) 
    { 
	command("peer suspiciously"); 
	command("drop " + OB_NAME(gift));
	return; 
    } 
    // .. else if the giver is an enemy, don't accept it.. 
    else if (member_array(giver, query_enemy(-1)) > -1) 
    { 
	if (query_attack() == giver) 
	{ 
	    command("emote pecks at you."); 
	} 
	command("drop " + OB_NAME(gift)); 
	return; 
    } 
    /* 
     * .. else if the item is fish, trigger quest event  
     */ 
    if (gift->query_prop(FISH_I_FROM_THALASSIAN_SEA))
    {
	i = command("eat all");

	// bird is always hungry
	amnt = this_object()->query_stuffed() - 10;
	this_object()->eat_food(-amnt);

	// only one poop per customer
	if (present("_chick_poop_", environment(this_object())))
	{
	    return;
	}

	// bird already pooped, reset necessary before it
	// will happen again
	if (this_object()->query_prop(BIRD_POOPED))
	{
	    return;
	}

	// check to see if eating fish was successful
	if (i)
	{

	    // ok this is kind of gross 
	    // chick responds to 'call of nature'

	    set_alarm(3.0, 0.0, &command("emote appears to strain mightily."));
	    set_alarm(5.0, 0.0, &command("emote squawks and"+
		" fluffs its feathers."));
	    set_alarm(7.0, 0.0, &make_doodoo(giver));
	    return;
	}
    }
    command("drop " + OB_NAME(gift)); 
    return;  
} 
/*******************************************************************
 * Function name: make_doodoo
 * Description  : happens when player feeds chick a fish and is 
 *                on the quest
 * Arguments    : player
 * Returns      : 1
 */
int
make_doodoo(object player)
{
    object poop;

    setuid(); 
    seteuid(getuid(this_object())); 
    command("emote produces a large steaming heap of poop.");
    // leaves excrement object in environment of this
    // creature
    this_object()->add_prop(BIRD_POOPED, 1);
    poop = clone_object(SEA_OBJECTS + "excrement");
    poop->move(environment(this_object()), 1);

    set_alarm(2.0, 0.0, &command("emote chirps happily, "+
	"obviously relieved."));

    return 1;
}
/*******************************************************************
 * Function name: reset_quest
 * Description  : This function called from room to reset chick
 * Arguments    : none
 * Returns      : 1
 */

int
reset_quest()
{
    this_object()->remove_prop(BIRD_POOPED);
    return 1;
}
