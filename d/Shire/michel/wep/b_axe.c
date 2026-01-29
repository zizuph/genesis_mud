/* Butchers axe cloned by Michel Delving butcher */
inherit "/std/weapon";
 
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
 
void
create_weapon() {
set_name("axe");
set_short("bloody bronze axe");
set_long("This is a sticky butchers axe - all in blood.\n"
 +"It has a broad-bladed, bronze, skillfully sharpened blade with\n"
 +"a short oak handle. The axe seems well balanced and quite deadly.\n"
 +"There is an inscription on the handle : \n"
       + "Crafted for Bolko by dwarvish smith. \n");
set_adj(({"bloody","butchers","bronze","short"}));
set_hit(15);
set_pen(19);
set_wt(W_AXE);
set_dt(W_SLASH);
set_hands(W_LEFT);
add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(15,19));
add_prop(OBJ_I_VOLUME,290);
add_prop(OBJ_I_WEIGHT,3200);
}
 
string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}
 
 
void init_recover(string arg)
{
    init_wep_recover(arg);
}
