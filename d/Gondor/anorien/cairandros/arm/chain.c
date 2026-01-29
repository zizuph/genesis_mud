/*
 * /d/Gondor/anorien/cairandros/arm/chain.c
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

inherit "/std/armour";
inherit "/lib/keep";

#define ARM ({"breastplate", "chainmail"})
#define ADJ ({"heavy", "sturdy", "shiny", "worn", "strong"})
#define ADJ2 ({"steel", "iron"})

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

    set_long("This is a "+adj+" "+adj2+" "+arm+" which has been issued out " +
        "to soldiers of Gondor. It appears to be in reasonably good " +
        "condition, and it should protect your quite well.\n");
    
    set_at(A_BODY);
    set_ac(35);
    
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
    add_prop(GONDOR_M_RANGERS_NO_SELL,1);   
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