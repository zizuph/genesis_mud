/*
 * Shortsword for elf npcs
 * by Finwe, August 2004
 */
#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

int hit = 32,
    pen = 30;
string adj1 = "long",
       adj2 = "smooth",
       wep  = "spear"; 
void
create_weapon()
{

    set_name("spear");
    add_name("polearm");
    set_adj(adj1);
    set_adj(adj2);
    add_adj("metal"); /* It is, isn't it? - Gorboth */
    set_short(adj1 + " " + adj2 + " " + wep); 
    set_long("This is a " + short() + ". It is made by elves from a " +
        "long, smooth piece of wood with a knife-like tip. In the " +
        "right hands, the spear looks cumbersome but dangerous to use.\n");

    set_hit(hit);
    set_pen(pen);

    set_wt(W_POLEARM); 
    set_dt(W_SLASH | W_IMPALE); 
    add_prop(OBJ_I_WEIGHT,3500);
    add_prop(OBJ_I_VOLUME,2058);

    set_hands(W_BOTH); 
}

