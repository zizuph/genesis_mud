/*
 * /d/Gondor/anorien/cairandros/wep/dagger.c
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
#include "../../defs.h"

inherit "/std/weapon";
inherit "/lib/keep";

#define WEP ({"knife", "dagger", "blade"})
#define ADJ ({"slender", "slim", "elegant", "beautiful"})
#define ADJ2 ({"engraved", "jeweled", "ivory-handled"})

string adj, adj2, wep;

void
set_weapon_data()
{
    seteuid(getuid());

    if(!strlen(adj))
    {
        adj = one_of_list(ADJ);
        adj2 = one_of_list(ADJ2);
        wep = one_of_list(WEP);
    }

    set_name(wep);
    add_name("knife");
    set_short(adj + " " + adj2 + " " + wep);
    set_adj(adj);
    add_adj(adj2);

    set_long("This "+adj+" "+wep+" is "+adj2+" and is clearly a very " +
        "valuable weapon, crafted by one of the finest smiths in Gondor. " +
        "In addition to being very attractive, it is also clearly " +
        "strongly crafted and perfectly balanced.\n");
            
    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
    set_hit(20);
    set_pen(20);
    
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
    add_prop(GONDOR_M_RANGERS_NO_SELL,1);
}

void
create_weapon()
{
    set_weapon_data();
    set_wf(this_object());
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    
    if (sizeof(a) >= 4)
    {
        adj = a[1];
        adj2 = a[2];
        wep = a[3];
    }

    init_wep_recover(arg);
    set_weapon_data();
}

string
query_recover()
{
    return ::query_recover() + "&&" + adj + "&&" + adj2 + "&&" + wep;
}