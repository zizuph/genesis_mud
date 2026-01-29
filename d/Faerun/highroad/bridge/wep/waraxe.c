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

#define ADJ1        "black"
//#define ADJ2        "crescent"
#define WEAPON      "waraxe"
#define WEP_TYPE    W_AXE
#define DAMAGE      W_SLASH



#define HIT 35
#define PEN 35

void
create_faerun_weapon()
{

    set_name("axe");
    add_name(WEAPON);
    set_adj(ADJ1);
    //set_short("waraxe");
    set_short(ADJ1 + " " + WEAPON); 
    //set_long("This is a " + short() + ". FIXME: fill it up here\n");
    set_long("This is a " + short() + ". It is a heavy weapon, with " +
	"two sharp blades. The handle is wrapped with black leather, " +
	"creating an excellent grip. The weapon itself is well balanced " +
	"and could be a dangerous tool in a hands of a skilled warrior.\n");

    set_hit(HIT);
    set_pen(PEN);
    set_wt(WEP_TYPE); 
    set_dt(DAMAGE); 

    add_prop(OBJ_I_WEIGHT,5000+random(1000));
    add_prop(OBJ_I_VOLUME,2500+random(500));
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));

    set_hands(W_ANYH); 
}
