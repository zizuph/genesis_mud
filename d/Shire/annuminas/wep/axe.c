inherit "/std/weapon";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/d/Shire/common/defs.h"

create_weapon()
{
    set_name("battleaxe");
    add_name(({"battleaxe","axe"}));
   set_short("wicked battleaxe");
   set_long("This is an obviously goblin made axe, even though it "
           +"is of poor quality, it looks rather wicked.\n");

   add_adj("wicked");

   set_default_weapon(25, 25, W_AXE, W_SLASH, W_LEFT, 0);
    add_prop(OBJ_I_WEIGHT, 5800);
    add_prop(OBJ_I_VOLUME, 1500);
   add_prop(OBJ_I_VALUE, 400);
}

query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

init_recover(arg)
{
    init_wep_recover(arg);
}
