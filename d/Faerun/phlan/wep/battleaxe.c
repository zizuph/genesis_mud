/*
 *  Generic weapons for Phlan shops
 *  Tharizdun, 2021
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

#define ADJ1        "two-handed"
#define ADJ2        "steel"
#define WEAPON_NAME "battleaxe"
#define WEAPON      "axe"
#define WEP_TYPE    W_AXE
#define DAMAGE      W_SLASH



int hit = 30 + random(5),
    pen = 33 + random(5);

void create_faerun_weapon()
{
    set_name(WEAPON_NAME);
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON_NAME); 
    set_long("This is a " + short() + ". It a three and a half foot"
        +" long wooden pole of deeply grained ash for the handle and"
        +" a large steel head with two sharpened concave blades. The"
        +" head has a tang going into the handle fastened with steel pins"
        +" and a wrapping of leather near the lower end of the handle"
        +" for improved grip.\n");
        
    set_hit(hit);
    set_pen(pen);
    set_wt(WEP_TYPE); 
    set_dt(DAMAGE); 

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(pen,W_AXE)+random(50)-25);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit, pen)+random(20)-10);

    set_hands(W_BOTH); 
}
