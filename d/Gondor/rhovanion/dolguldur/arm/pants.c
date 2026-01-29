/*
 * Pants from Dol Guldur 
 * /d/Gondor/rhovanion/dolguldur/arm/shirt.c
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

inherit "/std/armour";
inherit "/lib/keep";

#define ARM ({"pants", "trousers", "leggings"})
#define ADJ ({"studded", "spiked", "black", "brown", "grey", "ripped"})
#define ADJ2 ({"leather", "elf-skin"})

string adj, adj2, arm;

void
set_armour_data()
{
    seteuid(getuid());

    if(!strlen(adj))
    {
        adj = one_of_list(ADJ);
        adj2 = one_of_list(ADJ2);
        arm = one_of_list(ARM);
    }

    set_name(arm);
    add_name("armour");
    set_short(adj + " " + adj2 + " " + arm);
    set_adj(adj);
    add_adj(adj2);

    set_long("These " + adj + " " + adj2 + " " + arm + " looks like they " +
        "have seen better days, but they are still wearable.\n");
    
    set_at(A_LEGS);
    set_ac(25);
}

void
create_armour()
{
    set_armour_data();
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
        arm = a[3];
    }

    init_arm_recover(arg);
    set_armour_data();
}

string
query_recover()
{
    return ::query_recover() + "&&" + adj + "&&" + adj2 + "&&" + arm;
}