#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Shire/sys/defs.h"

#define WEP_TYPE    W_POLEARM
#define HIT            25+random(7)
#define PEN            28+random(5)
#define HANDS          W_BOTH
#define DAMAGE         W_SLASH | W_IMPALE

void
create_weapon()
{
    set_name("polearm");
    add_name(({"halberd"}));
    add_adj(({"sinister"}));
    set_short("sinister halberd");
    set_long("This sinister halberd is full of evil. Signs of orc misuse " +
        "is evident from all the evil signs all over it. The halberd looks " +
        "like it would do some damage, though.\n");
    set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(PEN,WEP_TYPE));
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
    add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);
    set_keep();

}
   
string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}
