/*
 * /d/Gondor/rohan/farm/farm/camp/arm/d_bracers.c
 * Original code by
 * Varian - 2016
 *
 * - Modified with help from Arman to save random factors
 *   Varian - April 2020
 *
 * - Shamelessly stolen for Dunlendings
 *   Raymundo, spring 2020
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <filter_funs.h>
#include <files.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

#define ARM ({"bracers", "arm-bands", "sleeves"})
#define ADJ ({"black", "spiked", "shiny"})
#define ADJ2 ({"hardened-steel"})

string adj, adj2, arm;

void
set_armour_data()
{
   if(!strlen(adj))
    {
        adj = one_of_list(ADJ);
        adj2 = one_of_list(ADJ2);
        arm = one_of_list(ARM);
    }

    set_name(arm);
    add_name("armour");
    add_name("bracers");
    set_short(adj + " " + adj2 + " " + arm);
    set_adj(adj);
    add_adj(adj2);
    set_long("These are "+adj+" "+adj2+" "+arm+". As evidence by their"
        + " unscratched condition, these " + arm + " are nearly new. The "
        + adj2 + " feels thick and strong.\n");
    
    set_at(A_ARMS);
    set_ac(38+random(3));
    
    add_prop(OBJ_I_VALUE,100);
    
}

void
create_armour()
{
    set_armour_data();
    set_wf(TO);
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