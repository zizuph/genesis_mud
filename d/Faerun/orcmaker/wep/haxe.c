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

#define ADJ1        "hand"
#define WEAPON      "axe"
#define WEP_TYPE    W_AXE
#define DAMAGE      W_SLASH
#define HIT         24
#define PEN         27
#define HANDS       W_ANYH

void create_faerun_weapon()
{
    set_name(WEP_TYPE);
    add_name("axe");
    add_name(WEAPON);
    set_adj(ADJ1);
    set_short(ADJ1 + " " + WEAPON);
    set_long("This is a " + short() + ". It has a wooden handle and a " +
        "rectangular blade attached to the top.\n");

    set_hit(HIT);
    set_pen(PEN);
    set_wt(WEP_TYPE);
    set_dt(DAMAGE);

   set_default_weapon(HIT,PEN ,WEP_TYPE,DAMAGE, HANDS, 0);
   add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(PEN,WEP_TYPE));
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
   add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);
}
