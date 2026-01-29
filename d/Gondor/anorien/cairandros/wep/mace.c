/*
 * /d/Gondor/anorien/cairandros/wep/mace.c
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

#define WEP ({"mace", "club"})
#define ADJ ({"heavy", "massive", "large", "huge", "banded"})
#define ADJ2 ({"spiked", "iron", "steel"})

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
    add_name("club");
    set_short(adj + " " + adj2 + " " + wep);
    set_adj(adj);
    add_adj(adj2);

    set_long("The "+adj+" "+adj2+" "+wep+" is extremely heavy, and " +
        "looks as if it would be absolutely deadly in the hand of a " +
        "trained soldier. Markings on the "+wep+" indicate that this " +
        "weapon belongs to the army of Gondor.\n");
            
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    set_hit(33);
    set_pen(33);
    
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