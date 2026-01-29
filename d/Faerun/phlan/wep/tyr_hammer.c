/*
 *  Hammer for Bishop Tulloch - high quality
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

#define ADJ1        "tempered"
#define ADJ2        "steel"
#define WEAPON_NAME "warhammer"
#define WEAPON      "club"
#define WEP_TYPE    W_CLUB
#define DAMAGE      W_BLUDGEON


int hit = 45 + random(5),
    pen = 35 + random(5);
void
create_faerun_weapon()
{

    set_name(WEAPON_NAME);
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON_NAME); 
    set_long("This is a " + short() + ". The bronzewood handle of this"
        +" hammer is decorated with holy symbols of the priesthood of Tyr."
        +" A leather wrapped handle and wrist loop make it easy to control"
        +" in combat. The head is of tempered steel engraved with the"
        +" scales of justice.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(WEP_TYPE); 
    set_dt(DAMAGE); 

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(pen,W_CLUB)+random(50)-25);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit, pen)+random(20)-10);

    set_hands(W_ANYH); 
}
