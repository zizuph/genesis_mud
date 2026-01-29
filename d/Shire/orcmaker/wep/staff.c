#pragma save_binary
 
inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
 
#define WEP_TYPE    W_POLEARM
#define HIT            25
#define PEN            6
#define HANDS          W_BOTH
#define DAMAGE         W_BLUDGEON
 
void
create_weapon()
{
    set_name("polearm");
    add_name(({"staff"}));
    add_adj(({"long"}));
    set_short("long staff");
    set_pshort("long staves")  ;
    set_long("This is a long staff. It is thin and stout and " +
        "looks like it was crafted from a single piece of wood. " +
        "The staff looks like it would do some damage in the " +
        "right hands.\n");
    set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(PEN,WEP_TYPE));
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
    add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);
 
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
