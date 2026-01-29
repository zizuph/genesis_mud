// -*-C++-*-
// file name: ~Avenir/common/port/obj/spur.c
// creator(s):  Boriska, Aug 1995
// last update: 
// purpose:   A piece of armour improving unarmed attacks for humanoids  
// note:
// bug(s):
// to-do:     

#pragma strict_types

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/std/combat/combat.h"

// unarmed wchit and wpen bonus
// Don't forget to update case statement picking a message for player
// if bonus range changes
#define F_BONUS(skill) (1+(skill)/20)

inherit "/std/armour";

// saves unarmed attack bonus 
private int bonus;

void configure_me(int foot);

void
create_armour() {
  set_name ("spur");
  set_short("wicked spur");
  add_adj("wicked");

  set_ac(5); // it does protect the hand somehow.
  set_af(this_object());
  
  add_prop(OBJ_I_WEIGHT, 1000);
  add_prop(OBJ_I_VOLUME, 800);
  add_prop(OBJ_I_VALUE, 800); // yes, we're expensive
}

// called from cloning environment
void
configure_me(int foot) {
  // sanity check
  if (foot != A_R_FOOT && foot != A_L_FOOT)
    foot = A_R_FOOT;
  set_at(foot);
  set_long("A simple gadget used by horse riders. It consists of small " +
	   "spiked wheel made of steel and two leather striped to fix it " +
	   "on the boots. It can be worn on " +
	   (foot == A_R_FOOT ? "right" : "left") + " foot.\n");
}

// convinience routines for debugging
void
left() { configure_me(A_L_FOOT); }

void
right() { configure_me(A_R_FOOT); }

private string
message(int bonus) {
  return "You attach the wicked spur to your foot.\n";
  // add switch statement with nice messages here
}

// If it is called, the appopriate slot is free. Modify unarmed attack.
int
wear(object to) {
  object tp, co;
  int id;
  mixed *att = 0;

  if (!living(tp = environment()) || tp != this_player())
    return 0;
  if (!objectp(co = tp->query_combat_object()))
    return 0;

  id = (query_at() == A_R_FOOT ? W_FOOTR : W_FOOTL);
  att = co->query_attack(id);
  if (!att)
    return 0; // they have feet as hitlocs but not as attacks

  bonus = F_BONUS(tp->query_skill(SS_UNARM_COMBAT));
  if (!interactive(tp))
    bonus*=3; //NPCs fight better with these.. not fair I know.. :)

  att[ATT_WCHIT] += bonus;
  if (pointerp(att[ATT_WCPEN]))
    att[ATT_WCPEN][2] += bonus;  // modify bludgeon wcpen
  else
    att[ATT_WCPEN] += bonus;
  
  co->add_attack(att);
  // direct call to combat object here...
  // Should call set_attack_unarmed() in the living instead, if it gets fixed.
  // At the moment it sets wskill of unarmed attack equal to wcpen
  tp->catch_msg(message(bonus));
  tell_room(environment(tp),
	    QCTNAME(tp) + " attaches a wicked spur to " +
	    tp->query_possessive() +
	    (query_at() == A_R_FOOT ? " right" : " left") + " foot.\n", tp);
  return 1;
}

int
remove(object to) {
  object co;
  int id;
  mixed *att = 0;

  if (!living(environment()) || environment() != this_player())
    return 0;
  if (!objectp(co = environment()->query_combat_object()))
    return 0;
   
  id = (query_at() == A_R_FOOT ? W_FOOTR : W_FOOTL);
  att = co->query_attack(id);
  if (!att)  // should never happen  
    return 0;

  // extract the same amount as was added..
  // direct calculation won't work because they might train unarmed while
  // wearing the spur.
  att[ATT_WCHIT] -= bonus;
  if (pointerp(att[ATT_WCPEN]))
    att[ATT_WCPEN][2] -= bonus;  // modify bludgeon wcpen
  else
    att[ATT_WCPEN] -= bonus;

  bonus=0;  //ensures correct resutls even if remove() gets called
            //in armour that is not worn for some weird reason
  co->add_attack(att); 
  return 0;
} 

void
init_recover(string arg) {
  string foo;
  int foot;
  
  sscanf(arg, "%shjhj#%d%s", foo, foot, foo);
  init_arm_recover(arg);
  configure_me(foot);
}
     

string
query_recover() {
  return MASTER + ":" + query_arm_recover() + sprintf("hjhj#%d", query_at());
}


