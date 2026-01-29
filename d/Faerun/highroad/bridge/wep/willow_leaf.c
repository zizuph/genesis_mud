/*
 * Weapon for the Neverwinter guard's boss (
 * by Kehr, July 2006
 */

#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

inherit FAERUN_WEP_BASE;

#define NAME        "sword"
#define ADJ1        "willow"
#define ADJ2        "leaf"
#define WEAPON      "longsword"
#define WEP_TYPE    W_SWORD
#define DAMAGE      W_SLASH | W_IMPALE

#define HIT	45
#define PEN	43

void
create_faerun_weapon()
{

    set_name(NAME);
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON); 
    set_long("This is a " + short() + ". The blade of this weapon " +
	"resembles a curved willow leaf, long and narrow, somewhat " +
	"wider on the end. It is quite heavy and perfectly balanced " +
	"for all cutting and slashing strokes.  Its 7\" long " +
    	"handle has been wrapped with cord to provide a firm grip.\n");

    set_hit(HIT);
    set_pen(PEN);
    set_wt(WEP_TYPE); 
    set_dt(DAMAGE); 

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, WEP_TYPE)+random(1000)-500);
    add_prop(OBJ_I_VOLUME, 2500 + random(500));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT,PEN) + random(500)-250);

    // little bonus, hard to dull, hard to break
    set_likely_dull(1);	  // crescent: 5,6   BSA: 5,4  fire: 5,4
    set_likely_break(1);  // DBB: 5,6   crystal: 1,1
    
    set_hands(W_ANYH); 

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 52, "enchantment" }));  
    	// value as good as any other...
    add_prop(MAGIC_AM_ID_INFO, ({
		"The sword was forged in the ancient times.\n", 10,
		"Its blade is extremely sharp and hard.\n", 20, 
	}));
	
	add_prop(OBJ_S_WIZINFO,
    	"----------------------------------------------------------------------------\n" +
        "This sword is wielded by Greyven, lieutanant near Neverwinter gates " +
        "(/d/Faerun/highroad/bridge/npcs/lieutanant.c)\n " +
        "\n" +
        "Parameters: hit = " + HIT + ", PEN = " + PEN + "\n" +
        "Specials: none\n" +
        "Other: \n" + 
        "  - Smiths get slightly different description\n" +
        "  - It is extremely durable and unlikely to break \n" +
        "----------------------------------------------------------------------------\n");
}
