/*
 * /w/mirandus/ideas/dewargully/arm/aghararmour.c
 *
 * Leg armour used by Dewar Dwarves in Newbie Zone
 * Coded by Leia, Modified from Mirandus' dewararmour.c file
 */
#pragma strict_types
inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../local.h"

#define ADJ1 ({"busted","chipped","worn-out",\
                      "useless","beat-up", "dirty"})
#define ADJ2 ({"black","grey","rusty","corroded","stained",\
                      "ruddy","shoddy"})

/*
 * Function name: create_armour()
 * Description  : Constructor, redefine this to configure your armour
 */
void
create_armour()
{
    string adj1 = one_of_list(ADJ1);
    string adj2 = one_of_list(ADJ2);
    
    set_name("scrapmail");
    set_adj(adj1);
    add_adj(adj2);
    set_short(adj1 + " " + adj2 + " scrapmail");
    set_long("A "+adj1+" "+adj2+ " scrapmail. This armour "
    +"appears to literally be made of "
    +"whatever was lying around. The aghar seem to have "
    +"cobbled together this piece of armour "
    +"as some sort of crude protection against invading dewar.\n");
    set_default_armour(5, A_BODY|A_ARMS, 0, this_object());
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE,65);
 
}

