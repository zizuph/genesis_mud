#pragma save_binary

inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define WEP_TYPE    W_SWORD
#define HIT            28
#define PEN            27
#define HANDS          W_ANYH
#define DAMAGE         W_SLASH

void
create_weapon()
{
   set_name("broadsword");
   add_name(({"sword"}));
   add_adj(({"worn"}));
   set_short("worn broadsword");
   set_long("This is a worn broadsword and you can see "+
        "that it has been well used by all the nicks. Looks like it "+
        "will still do respectable damage, though.\n");
   set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
   add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN,WEP_TYPE));

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
