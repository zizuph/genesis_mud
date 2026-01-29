inherit "/std/weapon"; 

#include <wa_types.h> 
#include <stdproperties.h> 

void 
create_weapon() 
{ 
    int type = random(3); 
    
    if (type == 0) 
    { 
        set_name("sword"); 
        set_adj("rusty"); 
        add_adj("two-handed"); 
        set_short("rusty two-handed sword"); 
        set_long("This is an old two-handed sword made from hardened "+ 
                 "steel. The wooden handle is rotten and the entire blade "+ 
                 "is covered with rust.\n"); 
        set_default_weapon(35, 38, W_SWORD, W_SLASH | W_IMPALE, W_BOTH); 
        add_prop(OBJ_I_VOLUME, 7600); 
        add_prop(OBJ_I_WEIGHT, 7500); 
    } 
    if (type == 1) 
    { 
        set_name("halberd"); 
        set_adj("rusty"); 
        add_adj("spiked"); 
        set_short("rusty spiked halberd"); 
        set_long("This is an old halberd sword made from hardened "+ 
                 "steel. A deadly spike has been attached to "+ 
                 "to the blade. The wooden handle is rotten and the entire blade "+ 
                 "is covered with rust.\n"); 
        set_default_weapon(36, 36, W_POLEARM, W_SLASH | W_IMPALE, W_BOTH); 
        add_prop(OBJ_I_VOLUME, 7600); 
        add_prop(OBJ_I_WEIGHT, 7500); 
    } 
    if (type == 2) 
    { 
        set_name("battleaxe"); 

        set_adj("rusty"); 
        add_adj("double-bladed"); 
        set_short("rusty double-bladed battleaxe"); 
        set_long("This is an old battleaxe made from hardened "+ 
                 "steel. The wooden handle is rotten and the blades "+ 
                 "are covered with rust.\n"); 
        set_default_weapon(38, 35, W_AXE, W_SLASH, W_BOTH); 
        add_prop(OBJ_I_VOLUME, 5600); 
        add_prop(OBJ_I_WEIGHT, 5500); 
    } 
}
