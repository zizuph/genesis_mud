inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <formulas.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

create_weapon()
{
    set_name("sword");
    set_pname(({"swords","weapons"}));
    set_short("gleaming sword");
    set_pshort("gleaming swords");
    set_adj("gleaming");
    set_long("A sharp gleaming sword made for the hands of a hobbit.\n");

    set_default_weapon( 
       18,                     
       15,                     
       W_SWORD,                
       W_SLASH,     
       W_NONE,                 
       0);           
   add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(15,W_SWORD) + random(275)); 
   add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON + random(201)); 
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(18,15) - random(101));
}


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}
