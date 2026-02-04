inherit "/std/monster";
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <money.h>
#include <language.h>
#include <stdproperties.h>


create_monster() {
   
   if (!IS_CLONE)
      return;
   
   seteuid(getuid(this_object()));
   
   set_race_name("skeleton"); 
   set_name("skeleton");
   set_adj(face());
   
   set_gender(2);
   add_prop(LIVE_I_NO_CORPSE, 1);
   add_prop(NPC_I_NO_LOOKS, 1);
   set_long("It is a skeleton of a man, somehow raised to life\n"+
      "by the powers of darkness.\n");
   
   set_base_stat(SS_STR, random(14)+10);
   set_base_stat(SS_DEX, 14);
   set_base_stat(SS_CON, random(30)+20);
   set_base_stat(SS_INT, 3);
   set_base_stat(SS_WIS, 3);
   set_base_stat(SS_DIS, 20);
   set_hp(9999); /* reduced to correct level according to con. */
   set_random_move(70);
   set_aggressive(1);
   set_attack_chance(70);
   set_alignment(-200 - random(200));
   
   set_skill(SS_PARRY, 50);
   set_skill(SS_DEFENCE, 40);
   set_skill(SS_WEP_POLEARM, 30);
   set_skill(SS_WEP_SWORD, 20);
   set_skill(SS_WEP_KNIFE, 25);
   set_skill(SS_WEP_CLUB, 15);
   
   add_prop(LIVE_I_UNDEAD, 25);
   set_all_hitloc_unarmed(33);
   
   call_out("get_wepon", random (4)+4);
}

face() {
   string *faces;
   faces = ({"rotted", "decayed", "half-decayed", "massive",
         "monstrous", "wicked", "headless", "foul"});
   return faces[random(sizeof(faces))];
}

get_wepon() {
   object ob2;
   ob2 = clone_object("/d/Terel/mecien/valley/hforest/spear");
   if (!ob2) return;
   ob2 -> move(this_object());
   command("grin");
   command("wield spear");
}



query_ac() { return 5; }/* Return the armour class.         */

query_at() { return 2; }/* Return the armour type.          */

query_am() { return ({ 0, 0, 0 }); }/* Return the armour modifier.      */
   
query_hit() {  }    /* Sets the weapon 'to hit'.        */
/* W_HAND_DAM is set to 5           */

query_pen() { return W_HAND_PEN; }/* Sets the weapon penetration.     */
/* W_HAND_PEN is set to 5           */

query_wt() { return W_CLUB; }/* Set the weapon type.     */

query_dt() { return W_BLUDGEON; }/* Set the damage type.     */

query_hands() { return W_ANYH; }/* Set the hand(s) used in combat   */

try_hit() { return 1; }/* If it returns false we WILL fail */
/* to hit. Otherwise we might...    */



/*
* Function name:
* Description:
* Arguments:
*
*/

