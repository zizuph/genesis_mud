

inherit "/std/monster";
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <money.h>
#include <language.h>


query_mm_in(){ return "scrambles in."; }
create_monster() {

    if (!IS_CLONE)
	return;

    seteuid(getuid(this_object()));

    set_race_name("goblin"); 
    set_name("goblin");
    set_adj(face());

    set_long("A goblin of the black-horned tribe, they are\n"+
	     "cruel and sadistic creatures.\n");

    set_base_stat(SS_STR, random(14)+10);
    set_base_stat(SS_DEX, 14);
    set_base_stat(SS_CON, random(22)+10);
    set_base_stat(SS_INT, 3);
    set_base_stat(SS_WIS, 3);
    set_base_stat(SS_DIS, 10);
    set_hp(2000); /* reduced to correct level according to con. */
/*    set_random_move(50); */
    set_aggressive(1);
    set_attack_chance(70);
    set_alignment(-300 - random(200));

    set_skill(SS_PARRY, 10);
    set_skill(SS_DEFENCE, 15);
    set_skill(SS_WEP_POLEARM, 10);
    set_skill(SS_WEP_SWORD, 20);
    set_skill(SS_WEP_KNIFE, 25);
    set_skill(SS_WEP_CLUB, 15);

    set_all_hitloc_unarmed(15);
    
    call_out("get_wepon", random (4)+4);
    call_out("get_money", 1);
}

face() {
    string *faces;
    faces = ({"bastard", "grim", "experienced", "sturdy", "massive",
	      "big", "nasty", "angry", "mean", "dirty", "ugly", "foul",
	      "brutal", "battered", "savage", "ugly", "ugly"});
    return faces[random(sizeof(faces))];
}

get_wepon() {
    object ob2;
   ob2 = clone_object("/d/Terel/mountains/obj/knife");
    if (!ob2) return;
    ob2 -> move(this_object());
    command("grin");
    command("wield knife");
}

get_money() {
    make_money(random(5)+5,"copper");
    make_money(random(2), "silver");
}


make_money(i,type) {
    MONEY_MOVE(i, type, 0, this_object());
}


query_gender() { return 0; }

query_ac() { return 5; }		/* Return the armour class.         */

query_at() { return 2; }		/* Return the armour type.          */

query_am() { return ({ 0, 0, 0 }); }	/* Return the armour modifier.      */

query_hit() {  }    	/* Sets the weapon 'to hit'.        */
					/* W_HAND_DAM is set to 5           */

query_pen() { return W_HAND_PEN; }	/* Sets the weapon penetration.     */
					/* W_HAND_PEN is set to 5           */

query_wt() { return W_CLUB; }		/* Set the weapon type. 	    */

query_dt() { return W_BLUDGEON; }	/* Set the damage type. 	    */

query_hands() { return W_ANYH; }	/* Set the hand(s) used in combat   */

try_hit() { return 1; }			/* If it returns false we WILL fail */
					/* to hit. Otherwise we might...    */



/*
 * Function name:
 * Description:
 * Arguments:
 *
 */

