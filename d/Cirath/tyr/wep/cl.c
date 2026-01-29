// -*-C++-*-
// file name: /d/Avenir/arm/knuckles.c
// creator(s):  Boriska, Jun 1995
// last update: 
// purpose:   A piece of armour improving unarmed attacks for humanoids  
// note:
// bug(s):
// to-do:     

/*
* Created by: Luther
* Date: Jan 2002
*
* File: /d/Cirath/tyr/wep/reaper_claw.c
* Comments: The claw for /d/Cirath/tyr/jail/zarth_reaper.c
*           
*/

#pragma strict_types

inherit "/std/armour";

#include "/d/Avenir/defs.h"
#include "/std/combat/combat.h"

// unarmed wchit and wpen bonus
// Don't forget to update case statement picking a message for player
// if bonus range changes
#define F_BONUS(skill) (3+(skill)/25)

// saves unarmed attack bonus 
private int bonus;

void configure_me(int hand);

void
create_armour()
{
  set_name ("claw");
  set_pname("claws");
set_short("kank's claw");
set_pshort("kank's claws");

  set_ac(5); // it does protect the hand somehow.
  set_af(this_object());

  add_prop(OBJ_I_WEIGHT, 1000);
  add_prop(OBJ_I_VOLUME, 800);
  add_prop(OBJ_I_VALUE, 1000); // yes, we're expensive
}

// called from cloning environment
void
configure_me(int hand) {

    	hand = A_R_HAND;
  	set_at(hand);
  	set_long("Its obvious where this strange weapon got its "
		+"name from.  "
		+"Three massive claws stretch out from the hard "
		+"chitinous shell that snaps seamlessly around "
		+"your wrist.  Your thumb fits into one of the "
		+"three claws, while two fingers fit into each "
		+"of the other two claws.  The claws themselves "
		+"initially look line they are made of obsidian, "
		+"but upon further inspection, they are skillfully "
		+"crafted black steel.  Ancient runes cover the "
		+"claws and gauntlet itself, occasionally "
		+"flashing with some fell power. It can be worn on " +
           	 "right hand.\n");  	
        add_item(({"runes","ancient runes"}),
		"Strange indecipherable characters in some "
		+"ancient tongue blanket the bizarre gauntlet.  "
		+"From time to time, they seem to ripple with "
		+"hidden power.\n");
}

// convinience routines for debugging

void
right() { configure_me(A_R_HAND); }

private string
message(int bonus) {
  switch (bonus) {
  case 1:
    return "Your feel a little weird wearing the claw.\n";
  case 2:
    return "Your feel like a big bully.\n";
  case 32:
    return "Your feel like an assassin ready to surprise someone.\n";
  case 4:
    return "You feel you are able to cut open anyone who messes with you.\n";
  case 5:
    return "No foe can stand against you, carrying your claw of kank " +
      "in a deadly grip.\n";
  default:
    return "You wear the claw of kank.\n";
  }
}

// If it is called, the appopriate slot is free. Modify unarmed attack.
int
wear(object to) {
  object tp, co;
  int id;
  mixed *att = 0;

  if (!living(tp = environment()))
    return 0;
  if (!objectp(co = tp->query_combat_object()))
    return 0;

  id = (query_at() == A_R_HAND ? W_RIGHT : W_LEFT);
  att = co->query_attack(id);
  if (!att)
    return 0; // they have hands as hitlocs but not as attacks
  
  bonus = F_BONUS(tp->query_skill(SS_UNARM_COMBAT));
  if (!interactive(tp))
    bonus*=2; //NPCs fight better with these.. not fair I know.. :)

  att[ATT_WCHIT] += bonus;
  if (pointerp(att[ATT_WCPEN]))
    att[ATT_WCPEN][1] += bonus;  // modify bludgeon wcpen
  else
    att[ATT_WCPEN] += bonus;
  
  co->add_attack(att);
  // direct call to combat object here...
  // Should call set_attack_unarmed() in the living instead, if it gets fixed.
  // At the moment it sets wskill of unarmed attack equal to wcpen
  
  tp->catch_msg(message(bonus));
  tell_room(environment(tp),
            QCTNAME(tp) + " pulls a claw of razors on " +
            tp->query_possessive() +
            (query_at() == A_R_HAND ? " right" : " left") + " hand.\n", tp);
  return 1;
}

int
remove(object to) {
  object co;
  int id;
  mixed *att = 0;

  if (!living(environment()))
    return 0;
  if (!objectp(co = environment()->query_combat_object()))
    return 0;
  
  id = (query_at() == A_R_HAND ? W_RIGHT : W_LEFT);
  att = co->query_attack(id);
  if (!att)  // should never happen  
    return 0;

  // extract the same amount as was added..
  // direct calculation won't work because they might train unarmed while
  // wearing the knuckles.
  att[ATT_WCHIT] -= bonus;
  if (pointerp(att[ATT_WCPEN]))
    att[ATT_WCPEN][1] -= bonus;  // modify bludgeon wcpen
  else
    att[ATT_WCPEN] -= bonus;

  bonus=0;  //ensures correct resutls even if remove() gets called
            //in armour that is not worn for some weird reason
  co->add_attack(att); 
  return 0;
} 


