/*
 * Weapon for the Neverwinter guard
 * by Kehr, July 2005
 */

#pragma save_binary
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

inherit FAERUN_WEP_BASE;

#define ADJ1        "steel"
#define ADJ2        "bastard"
#define WEAPON      "sword"
#define WEP_TYPE    W_SWORD
#define DAMAGE      W_SLASH|W_IMPALE



#define HIT 35
#define PEN 35

void
create_faerun_weapon()
{

    set_name("bastardsword");
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON); 
    
    set_long("This is a " + short() + ", one of the most versatile tools of warfare. " +
    	"For a sword of this size it is very fast and light. Its 50\" long blade is wide " +
    	"and pointed at the end, making the sword suitable for both slashing and thrusting " +
    	"attacks. The blade is balanced with long grip, capped with a diamond-shaped pommel.\n");  

    set_hit(HIT);
    set_pen(PEN);
    set_wt(WEP_TYPE); 
    set_dt(DAMAGE); 

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, WEP_TYPE));
    //add_prop(OBJ_I_VOLUME,2500+random(500));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));

    set_hands(W_ANYH); 
}
