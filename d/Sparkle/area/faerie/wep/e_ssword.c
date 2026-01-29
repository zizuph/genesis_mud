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

int hit = 14,
    pen = 16;
string adj1 = "exceptional",
       adj2 = "shiny",
       wep  = "shortsword"; 
void
create_weapon()
{

    set_name("sword");
    add_name("short sword");
    add_name("shortsword");
    set_adj(adj1);
    set_adj(adj2);
    set_short(adj1 + " " + adj2 + " " + wep); 
    set_long("This is a " + short() + ". It has been polished and appears " +
        "sharp.  Forged of steel by elves, it is shorter than a regular " +
        "sword but still looks dangerous.\n");

    set_hit(hit);
    set_pen(pen);

    set_wt(W_SWORD); 
    set_dt(W_SLASH | W_IMPALE); 
    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,1500);

    set_hands(W_ANYH); 
}

