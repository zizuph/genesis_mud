/*
 * standard axe in Dol Guldur 
 * /d/Gondor/rhovanion/dolguldur/wep/axe.c
 *
 * Varian - November 2020
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

#define WEP ({"hand-axe", "axe", "war-axe"})
#define ADJ ({"rusty", "long", "dirty", "short", "chipped"})
#define ADJ2 ({"blood-stained", "cruel", "dull", "corroded", "iron"})

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
    add_name("axe");
    set_short(adj + " " + adj2 + " " + wep);
    set_adj(adj);
    add_adj(adj2);

    set_long("This is a " + adj + " " + adj2 + " " + wep + 
        ", similar to the sort most inhabitants from Dol Guldur use.\n");
    	    
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
    set_hit(25);
    set_pen(25);
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
