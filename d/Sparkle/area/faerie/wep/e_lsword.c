/*
 * Longsword for elf npcs
 * by Finwe, August 2004
 */
#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

int hit = 27,
    pen = 27;
string adj1 = "polished",
       adj2 = "gleaming",
       wep  = "longsword"; 
void
create_weapon()
{

    set_name("sword");
    add_name("longsword");
    set_adj(adj1);
    set_adj(adj2);
    set_short(adj1 + " " + adj2 + " " + wep); 
    set_long("This is a " + short() + ". Forged by elves from steel, the " +
        "blade is sharpened on both ends, with the blade tapering to a " +
        "point. It is the weapon of choice favored by elven guards.\n");

    set_hit(hit);
    set_pen(pen);

    set_wt(W_SWORD); 
    set_dt(W_SLASH | W_IMPALE); 
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,900);

    set_hands(W_ANYH); 
}

