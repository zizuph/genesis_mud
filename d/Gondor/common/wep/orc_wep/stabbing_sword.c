/* Weapon coded by Arren, April 94 */ 

inherit "/std/weapon";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/formulas.h"
#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name("sword");
    add_name("shortsword");
    add_name("stabbing-sword");
    set_pname("swords");
    add_pname("shortswords");
    add_pname("stabbing-swords");
    set_adj("broad-bladed");
    add_adj(({ "short", "broad bladed", "broad", "stabbing", "orc" }));
    set_short("broad-bladed stabbing-sword"); 
    set_long(BSN("A short double-edged sword, made for thrusting, with a "+
    "broad blade."));

    set_default_weapon(20, 17, W_SWORD, W_IMPALE, W_ANYH, 0);
    
    add_prop(OBJ_I_VOLUME, 500);  
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20,17)+random(100)-50);
}
