/*
 * Charity box weapon
 * by Finwe, Feb 2006
 */

inherit "/std/weapon";
#include "/d/Shire/sys/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define WEP_TYPE    W_CLUB
#define HIT         10+random(5)
#define PEN         10+random(5)
#define HANDS       W_ANYH
#define DAMAGE      W_BLUDGEON

void
create_weapon()
{
    set_name("club");
    add_name(({"club"}));
    add_name("_ch_hickclub_");
   
    add_adj(({"smooth"}));
    set_short("smooth club");
    set_pshort("smooth clubs");
    set_long("This is a smooth club, carefully carved from a tree branch, "+
        "probably hickory as it is very solid.\n");
    set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(PEN,WEP_TYPE));
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
    add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);
    add_prop(OBJ_M_NO_SELL, "This is a charity item, it cannot be sold.\n");


}
