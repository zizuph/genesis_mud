inherit "/std/monster";
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <money.h>

create_monster() {

    if (!IS_CLONE)
	return;

    set_race_name("orc"); 
    set_name("orc");
    set_adj(face());

    set_long("This is probably one of the most worthless\n"+
	     "creatures ever put upon this world.\n");

    /* default_config_npc(); */
    set_base_stat(SS_STR, random(5)+4);
    set_base_stat(SS_DEX, 7);
    set_base_stat(SS_CON, 6);
    set_base_stat(SS_INT, 5);
    set_base_stat(SS_WIS, 5);
    set_base_stat(SS_DIS, 6);
    set_hp(1000); /* reduced to correct level according to con. */
    set_aggressive(1);
/*    set_attack_chance(50);  */

    set_skill(SS_WEP_KNIFE, 4);

    call_out("get_wepon", random (8));
    get_money();
}

face() {
    string *faces;
    faces = ({"scarred", "grim", "grumpy", "young", "sturdy", "massive",
	      "big", "nasty", "angry", "mean", "dirty", "ugly", "foul",
	      "brutal", "dirty", "dirty", "ugly", "ugly"});
    return faces[random(sizeof(faces))];
}

get_wepon() {
    object ob;

    if (random(5)) return;
    ob = clone_object("/d/Genesis/start/human/obj/knife");
    if (!ob) return;
    ob -> move(this_object());
    command("wield knife");
}
get_money() {
    if (random(10)<3) {
	make_money(random(8)+2,"copper");
	if (!random(100)) make_money(1,"silver");
    }
}


make_money(i,type) {
    object money;

#ifndef UNDEF
    MONEY_MOVE(i, type, 0, this_object());
#else
    money = clone_object("/std/coins");
    money->set_heap_size(i);
    money->set_coin_type(type);
    money->move(this_object(),1);
#endif
}



/* query_nonmet_name() { return "rat"; } */
query_gender() { return 0; }

/*	Since this is suposed to be an animal and not a 'weapon wielding'
	monster, we have to define how the animal fights with teeth, claws,
	hoofs or whatever possible.  The query functions below are taken
	from /std/living/ucombat.c. Those functions wich are unique for
	this creature should be defined here. The rest is inherited and 
	need not be masked. However, it is strongly recomended that you
	go through ucombat.c a few times to see what you need to redefine.
 */

query_ac() { return 5; }		/* Return the armour class.         */
					/* Ac set to 2 due to small size.   */

query_at() { return 0; }		/* Return the armour type.          */
					/* In this case, no armor.          */

query_am() { return ({ 0, 0, 0 }); }	/* Return the armour modifier.      */
					/* Often A_NAKED_MOD can be used.   */
					/* which is, ({ 0, 0, 0 }).      */

query_hit() { return W_HAND_HIT; }	/* Sets the weapon 'to hit'.        */
					/* W_HAND_HIT is set to 5           */

query_pen() { return W_HAND_PEN; }	/* Sets the weapon penetration.     */
					/* W_HAND_PEN is set to 5           */

query_wt() { return W_CLUB; }		/* Set the weapon type. 	    */
					/* A knife is the closest to a rats */
					/* teeth that I could think of...   */

query_dt() { return W_BLUDGEON; }	/* Set the damage type. 	    */
					/* A rat has impaling teeth rigt??  */

query_hands() { return W_ANYH; }	/* Set the hand(s) used in combat   */
					/* This animal uses no hands (limbs)*/

try_hit() { return 1; }			/* If it returns false we WILL fail */
					/* to hit. Otherwise we might...    */



/*
 * Function name:
 * Description:
 * Arguments:
 *
 */

