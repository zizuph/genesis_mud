inherit "/std/weapon";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/d/Shire/common/defs.h"

create_weapon()
{
   set_name("club");
   set_short("massive spiked club");
   set_long("This is a large club made of wood and steel, with "
           +"huge spikes covering its massive head. It looks "
	   +"like it could do an incredible amount of damage if "
	   +"it connected with your head.\n");
   set_default_weapon(25, 25, W_AXE, W_SLASH, W_LEFT, 0);
    add_prop(OBJ_I_WEIGHT, 5800);
   set_default_weapon(29, 40, W_CLUB, W_BLUDGEON, W_ANYH, 0);
   add_adj("massive","spiked");
}

query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

init_recover(arg)
{
    init_wep_recover(arg);
}
