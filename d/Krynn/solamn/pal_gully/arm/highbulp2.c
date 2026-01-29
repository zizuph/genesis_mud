/*
 * /w/mirandus/ideas/dewargully/arm/dewararmour2.c
 *
 * Leg armour used by Dewar Dwarves in Newbie Zone
 * Coded by Leia, Modified from Mirandus' dewararmour2.c file
 */
#pragma strict_types
inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../local.h"

#define ADJ1 ({"old","dirty", "beaten"})
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
    
    set_name("chainmail");
    set_adj(adj1);
    add_adj(adj2);
    set_short(adj1 + " " + adj2 + " chainmail");
    set_long("A "+adj1+" "+adj2+ " chainmail. Much nicer than the "
    +"armour of the other aghar, this is a "
    +"prized finding of the clan of aghar. It has been "
    +"given to the highbulp as a matter of pride and honour.\n");
    set_default_armour(10, A_BODY|A_ARMS, 0, this_object());
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE,200);
    
    
}

