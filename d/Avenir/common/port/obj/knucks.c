// -*-C++-*-
// file name: ~Avenir/common/port/obj/knuckles.c
// creator(s):  Boriska, Jun 1995
// last update: 
//  Lilith 2000.12.18 patched drop bug
//  Cirion 1999.03.19 made keepable
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

inherit "/lib/keep";
inherit "/std/armour";

mixed check_worn();

// saves unarmed attack bonus 
private int bonus;

void configure_me(int hand);

void
create_armour()
{
    set_name ("knuckles");
    add_name(({"knucks", "nucks"}));
    set_pname("knuckles");
    add_pname(({"knucks","nucks"}));
    set_short("pair of brass knuckles");
    set_pshort("pairs of brass knuckles");
    add_adj("brass");

    set_ac(5); // it does protect the hand somehow.
    set_af(this_object());

    add_prop(OBJ_M_NO_DROP,  "@@check_worn");
    add_prop(OBJ_M_NO_GIVE,  "@@check_worn");
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_VALUE, 1000); // yes, we're expensive

    set_keep();
}

// called from cloning environment
void
configure_me(int hand)
{
    // sanity check
    if (hand != A_R_HAND && hand != A_L_HAND)
        hand = A_R_HAND;
    set_at(hand);
    set_long("A piece of heavy metal with holes for fingers and protruding " +
        "spikes. Looks frightening, especially when used by person " +
        "skilled in martial arts. It can be worn on " +
        (hand == A_R_HAND ? "right" : "left") + " hand.\n");
}

// convinience routines for debugging
void
left()
{
    configure_me(A_L_HAND);
}

void
right()
{ 
    configure_me(A_R_HAND);
}

private string
message(int bonus)
{
    switch (bonus)
    {
        case 1:
            return "Your fist feels stronger as you wear the knuckles.\n";
        case 2:
            return "Your fist becomes more powerful as you tighten your grip on the " +
                "knuckles.\n";
        case 3:
            return "As you wear the knuckles your arms gain a new mightiness.\n";
        case 4:
            return "You feel like you can break walls with your fist as you wear " +
                  "the brass knuckles.\n";
        case 5:
            return "You feel you are able to smash everything with your mighty " +
              "hands as you wear the brass knuckles.\n";
            case 6:
            return "No foe can stand against your mighty and skilled hand, carrying " +
              "the brass knuckles in deadly grip.\n";
        default:
            return "You wear the brass knuckles.\n";
  }
}

// This was added because for some reason remove isn't being 
// called when drop and give commands are used, and the benefit
// from wearing these remains.  Note: calling remove() in the 
// leave_env() isn't working either.
mixed
check_worn()
{
    if (!query_worn() || query_worn()->query_hp() <= 0)
        return 0;
    else
        return "You can't do that while the knuckles are worn!\n";
}
    

// If it is called, the appopriate slot is free. Modify unarmed attack.
int
wear(object to)
{
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
        att[ATT_WCPEN][2] += bonus;  // modify bludgeon wcpen
    else
        att[ATT_WCPEN] += bonus;
    
    co->add_attack(att);
    // direct call to combat object here...
    // Should call set_attack_unarmed() in the living instead, if it gets fixed.
    // At the moment it sets wskill of unarmed attack equal to wcpen
    
    tp->catch_msg(message(bonus));
    tell_room(environment(tp),
        QCTNAME(tp) + " pulls nasty looking brass knuckles on " +
        tp->query_possessive() +
        (query_at() == A_R_HAND ? " right" : " left") + " fist.\n", tp);
    return 1;
}

int
remove(object to)
{
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
        att[ATT_WCPEN][2] -= bonus;  // modify bludgeon wcpen
    else
        att[ATT_WCPEN] -= bonus;
  
    bonus=0;  //ensures correct resutls even if remove() gets called
              //in armour that is not worn for some weird reason

    co->add_attack(att); 
    return 0;
} 


void
leave_env(object from, object to)
{
    // This should work, but it doesn't :(
    remove(from);
    ::leave_env(from, to);
}

void
init_recover(string arg)
{
    string foo;
    int hand;
    
    sscanf(arg, "%shjhj#%d%s", foo, hand, foo);
    init_arm_recover(arg);
    configure_me(hand);
    init_keep_recover(arg);
}

string
query_recover() {
   return MASTER + ":" + query_arm_recover() 
       + sprintf("hjhj#%d", query_at())
       + ":" + query_keep_recover();
}

