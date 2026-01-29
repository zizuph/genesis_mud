/* The spear of the guards of Esgaroth */ 
#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep";
 
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
 
void
create_weapon()
{
    set_short("long spear");
    set_name(({ "spear" }));
    set_adj("long");
    set_long(BS("This spear is almost 6 feet long. It looks quite "
      + "powerful. It's a standard equipment of the guards of the Lake "
      + "Town.\n"));
    set_default_weapon(25, 30, W_POLEARM, W_IMPALE, W_BOTH, 0);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(25,30)+1000-random(500));
}
 
query_recover()  { return MASTER + ":" + query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
