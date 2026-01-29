inherit "/std/monster";
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <money.h>


create_monster() {

    if (!IS_CLONE)
	return;

    set_race_name("urukhai"); 
    set_name("urukhai");
    set_adj(face());

    set_long("This warrior has no love to spare for those of your kind.\n"+
	     "He would probably sell his mother for a copper.\n");

    set_base_stat(SS_STR, random(8)+10);
    set_base_stat(SS_DEX, 9);
    set_base_stat(SS_CON, 10);
    set_base_stat(SS_INT, 6);
    set_base_stat(SS_WIS, 8);
    set_base_stat(SS_DIS, 9);
    set_hp(1000); /* reduced to correct level according to con. */
    set_attack_chance(90);

    set_skill(SS_WEP_SWORD, 12);

    call_out("get_wepon", random (4)+4);
    get_money();
}

face() {
    string *faces;
    faces = ({"veteran", "grim", "grumpy", "experienced", "sturdy", "massive",
	      "big", "nasty", "angry", "mean", "dirty", "ugly", "foul",
	      "brutal", "battered", "savage", "ugly", "ugly"});
    return faces[random(sizeof(faces))];
}

get_wepon() {
    object ob;
    
    if (random(20))
	ob = clone_object("/d/Genesis/start/human/obj/ssword");
    else
	ob = clone_object("/d/Genesis/start/human/obj/lsword");

    if (!ob) return;
    ob -> move(this_object());
    command("grin");
    command("wield sword");
    command("say Ok you bastard. Make me happy!");
    set_aggressive(1);

}

get_money() {
    make_money(random(40)+25,"copper");
    if (random(10)) return;
    make_money(random(10)+5, "silver");
}


make_money(i,type) {
    MONEY_MOVE(i, type, 0, this_object());
}



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

query_at() { return 2; }		/* Return the armour type.          */
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

