/*
 * /w/mirandus/ideas/dewargully/arm/dewararmour2.c
 *
 * Leg armour used by Dewar Dwarves in Newbie Zone
 * Coded by Mirandus with help from Mercade
 */
#pragma strict_types
inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../local.h"

#define ADJ1 ({"gilded","golden", "ornate"})
#define ADJ2 ({"steel", "iron", "alloy"})

/*
 * Function name: create_armour()
 * Description  : Constructor, redefine this to configure your armour
 */
void
create_armour()
{
    string adj1 = one_of_list(ADJ1);
    string adj2 = one_of_list(ADJ2);
    
    set_name("platemail");
    set_adj(adj1);
    add_adj(adj2);
    set_short(adj1 + " " + adj2 + " platemail");
    set_long("A "+adj1+" "+adj2+ " platemail. Well made and offering a "
    +"decent amount of protection. It bears the mark of the Thane of the Dewar "
    +"dwarves near Palanthas.\n");
    set_default_armour(10, A_BODY|A_ARMS, 0, this_object());
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE,200);
    
    
}

