/* 	
    blue sword for the good knight in the crystalline palace

    coder(s):   Glykron

    history:    31.7.2000   added required magic properties  Maniac
                25. 2.92    recovery added                   Glykron
                25. 2.92    header added                     Glykron

*/

#pragma save_binary

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("sword");
    set_adj("blue");
    set_short("blue sword"); 
    set_pshort("blue swords"); 
    set_long("This sword glows with a blue aura.\n" );
    set_hit(30);
    set_pen(30);
    set_hands(W_RIGHT);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(MAGIC_AM_MAGIC, ({ 15, "enchanted" }) );
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1); 
    add_prop(MAGIC_AM_ID_INFO, ({ "This sword is enchanted to " +
             "give off a blue light permanently.", 15, 
             "Blue was the forger's favourite colour.", 30 })); 
    add_prop(OBJ_S_WIZINFO, "This magic weapon gives off one " + 
             "level of light permanently. It's wielded by " + 
             "/d/Calia/glykron/palace/monsters/good_calian " + 
             "which is cloned in the room /d/Calia/glykron" +
             "/palace/rooms/light/good.\n"); 
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}
