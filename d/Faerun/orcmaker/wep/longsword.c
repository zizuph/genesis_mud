/*
 * Weapon for orcmaker
 * by Finwe, November 2007
 */

#pragma save_binary
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_WEP_BASE;

#define ADJ1        "battered"
#define WEAPON      "longsword"
#define WEP_TYPE    W_SWORD
#define DAMAGE      W_SLASH | W_IMPALE
#define HIT         35
#define PEN         35
#define HANDS       W_ANYH

void create_faerun_weapon()
{
    set_name(WEP_TYPE);
    add_name("shortsword");
    add_name("sword");
    add_name(WEAPON);
    set_adj(ADJ1);
    set_short(ADJ1 + " " + WEAPON);
    set_long("This is a " + short() + ". The sword was forged of steel " +
        "and has patches of rust on it. However, it still looks dangerous. " +
        "The workmanship is decent, considering it was forged by orcs.\n");

    set_hit(HIT);
    set_pen(PEN);
    set_wt(WEP_TYPE);
    set_dt(DAMAGE);

   set_default_weapon(HIT,PEN ,WEP_TYPE,DAMAGE, HANDS, 0);
   add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(PEN,WEP_TYPE));
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
   add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);
}
