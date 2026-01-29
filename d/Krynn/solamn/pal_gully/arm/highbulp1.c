/*
 * /w/mirandus/ideas/dewargully/arm/highbulp1.c
 *
 * Leg armour used by Dewar Dwarves in Newbie Zone
 * Coded by Leia, Modified from Mirandus' dewarthane1.c file
 */
#pragma strict_types
inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../local.h"

#define ADJ1 ({"old","rusty", "beaten"})
#define ADJ2 ({"iron", "copper", "bronze"})

/*
 * Function name: create_armour()
 * Description  : Constructor, redefine this to configure your armour
 */
void
create_armour()
{
    string adj1 = one_of_list(ADJ1);
    string adj2 = one_of_list(ADJ2);
    
    set_name("leggings");
    set_adj(adj1);
    add_adj(adj2);
    set_short(adj1 + " " + adj2 + " leggings");
    set_long("A pair of "+adj1+" "+adj2+ " leggings. Much nicer than "
    +"those of the other aghar, these are the "
    +"prized findings of the clan of aghar. They have been "
    +"given to the highbulp as a matter of pride and honour.\n");
    set_default_armour(10, A_LEGS, 0, this_object());
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE,200);
    
    
}

