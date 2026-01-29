/*
 * Elven shield - /d/Gondor/rhovanion/dolguldur/arm/elf_shield.c
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

#define ARM ({"buckler", "shield"})
#define ADJ ({"sturdy", "light"})
#define ADJ2 ({"elven", "wooden"})

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
    add_name(({"armour", "shield"}));
    set_short(adj + " " + adj2 + " " + arm);
    set_adj(adj);
    add_adj(adj2);

    set_long("This is a "+adj+" "+adj2+" "+arm+" which has been " +
        "covered in Silvan scrollwork from the Elves of Mirkwood " +
        "forest.\n");
    
    set_at(A_SHIELD);
    set_ac(39);  
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