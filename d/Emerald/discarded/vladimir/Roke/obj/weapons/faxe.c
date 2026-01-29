inherit "/std/weapon"; 
#include "/sys/macros.h"      
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"      
#include "/d/Roke/common/defs.h"

create_weapon()
{    
    set_name("battleaxe");
    add_name(({"battleaxe","axe"}));
   set_short("double bladed battleaxe");
   set_long("This is a rather large battleaxe with two "+
            "huge blades on either side. The handle is "+
        "wrapped in leather that has been dyed blue.\n");

   add_adj("double bladed");

   set_default_weapon(34, 30, W_AXE, W_SLASH, W_LEFT, 0);
    add_prop(OBJ_I_WEIGHT, 8800);
    add_prop(OBJ_I_VOLUME, 1500);
   add_prop(OBJ_I_VALUE, 600);
}

query_recover()  
{ 
    return MASTER + ":" + query_wep_recover(); 
}

init_recover(arg) 
{ 
    init_wep_recover(arg); 
}

