inherit "/std/monster";
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <money.h>
#include <language.h>

string random_weapon(){
   switch(random(3)){
      case 0: return "dagger";
      case 1: return "scimitar";
      case 2: return "spear";
   }
}

create_monster() {
   
   if (!IS_CLONE)
      return;
   
   seteuid(getuid(this_object()));
   
   set_race_name("hobgoblin"); 
   set_name("hobgoblin");
   set_adj(face());
   
   set_long("A goblin of the black-horned tribe, they are\n"+
      "cruel and sadistic creatures.\n");
   
   set_base_stat(SS_STR, random(20)+15);
   set_base_stat(SS_DEX, 25);
   set_base_stat(SS_CON, random(30)+15);
   set_base_stat(SS_INT, 3);
   set_base_stat(SS_WIS, 3);
   set_base_stat(SS_DIS, 25);
   set_hp(2000); /* reduced to correct level according to con. */
   /*    set_random_move(50); */
   set_aggressive(1);
   set_attack_chance(70);
   set_alignment(-100 - random(50));
   
   set_skill(SS_PARRY, 30);
   set_skill(SS_DEFENCE, 25);
   set_skill(SS_WEP_POLEARM, 35);
   set_skill(SS_WEP_SWORD, 40);
   set_skill(SS_WEP_KNIFE, 25);
   set_skill(SS_WEP_CLUB, 15);
   
   set_all_hitloc_unarmed(22);
   
   call_out("get_wepon", random (4)+4);
   call_out("get_money", 1);
}

face() {
   string *faces;
   faces = ({"black-masked", "diabolic", "ghoulish", "sturdy", "massive",
         "brutal", "battered", "savage", "ugly", "ugly"});
   return faces[random(sizeof(faces))];
}

get_wepon() {
   object ob2;
   int type;
   seteuid(getuid(this_object()));
   type=random_weapon();
   ob2=clone_object("/d/Terel/mecien/dark/obj/"+type);
   ob2->move(this_object());
   command("wield " +type);
}

get_money() {
   make_money(random(25)+5,"copper");
   make_money(random(8), "silver");
}


make_money(i,type) {
   MONEY_MOVE(i, type, 0, this_object());
}


query_gender() { return 0; }

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

