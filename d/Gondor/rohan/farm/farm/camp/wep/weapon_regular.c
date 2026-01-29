/*
 * /d/Gondor/anorien/cairandros/wep/axe.c
 *
 * Varian - 2016
 *
 * - Modified with help from Arman to save random factors
 *   Varian - April 2020
 */

#pragma strict_types

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <filter_funs.h>
#include <files.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

inherit "/std/weapon";
inherit "/lib/keep";


#define ADJ ({"nasty", "vicious", "cruel", "blood-spattered", "deadly"})
#define SHARP_ADJ2 ({"double-bladed", "sharp", "steel", "iron"})
#define BLUNT_ADJ2 ({"spiked", "flanged", "round-headed"})
#define TYPE ({"W_AXE", "W_CLUB", "W_POLEARM", "W_SWORD", "W_KNIFE"})
string adj, adj2, wep, type;
string head();
void
set_weapon_data()
{
    seteuid(getuid());

    if(!strlen(adj))
    {
        type = one_of_list(TYPE);
        adj = one_of_list(ADJ);
        if(type == "W_CLUB")
        {
            adj2 = one_of_list(BLUNT_ADJ2);
        }
        else
        {
        adj2 = one_of_list(SHARP_ADJ2);
        }
        
    }
     
    switch(type)
    {
    case "W_SWORD":
    {
        set_dt(W_SLASH);
        wep = "longsword";
        add_name("sword");
        set_hands(W_BOTH);
        if(adj2 == "double-bladed")
        {
            adj2 = "double-edged";
        }
        set_wt(W_SWORD);
        break;
    }
    case "W_AXE":
    {
        set_dt(W_SLASH);
        wep = "battleaxe";
        add_name("axe");
        set_hands(W_BOTH);
        set_wt(W_AXE);
        break;
    }
    case "W_KNIFE":
    {
        set_dt(W_SLASH);
        set_hands(W_ANYH);
        wep = "dagger";
        add_name("knife");
        set_wt(W_KNIFE);
        break;        
    }
    case "W_POLEARM":
    {
        set_dt(W_IMPALE);
        wep = "spear";
        set_hands(W_BOTH);
        set_wt(W_POLEARM);
        break;
    }
    case "W_CLUB":
    {
        set_dt(W_BLUDGEON);
        wep = "mace";
        add_name("club");
        set_hands(W_BOTH);
        set_wt(W_CLUB);
        break;
    }
    }
    
    set_name(wep);
    add_name("weapon");
    set_short(adj + " " + adj2 + " " + wep);
    set_adj(adj);
    add_adj(adj2);

    set_long("This is a " + adj + " " + adj2 + " " + wep + 
        ". It looks as if it has seen its share of battles. The "
        + wep + " has a "
        + "leather-wrapped handle and a " + adj + " metal " + head() 
        + ". It's the type of weapon "
        + "a soldier would carry into battle, but not one a soldier "
        + "would brag about carrying into battle.\n");
    	    
   
   
    
    set_hit(32);
    set_pen(32);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME,1000);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(32,32)/2);

}



void
create_weapon()
{
    set_weapon_data();
    set_wf(this_object());
}
 
string
head()
{
    if(type == "W_CLUB")
    {
        return("head");
    }
    else
    {
        return("blade");
    }
}
 
void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    
    if (sizeof(a) >= 4)
    {
        adj = a[1];
        adj2 = a[2];
        type = a[3];
        
    }

    init_wep_recover(arg);
    set_weapon_data();
}

string
query_recover()
{
    return ::query_recover() + "&&" + adj + "&&" + adj2 + "&&" + type;
}

