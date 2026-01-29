/*
 * /w/mirandus/ideas/dewargully/wep/dewarwep.c
 *
 * Axe used by Dewar Dwarves in Newbie Zone
 * Coded by Mirandus with help from Mercade
 */

inherit "/std/weapon";
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../local.h"

#define ADJ1 ({"sharp","cracked","blemished","blackened","crimson",\
                      "heavy","double-bladed"})
#define ADJ2 ({"broad","hand","battle","wooden","iron",\
                      "well-made","dark"})


/*
 * Function name: create_weapon()
 * Description  : Constructor, redefine this to configure your weapon
 */
void
create_weapon() 
{
    
    string adj1 = one_of_list(ADJ1);
    string adj2 = one_of_list(ADJ2);
    
    set_name(({"axe","battleaxe"}));
    set_adj(adj1);
    add_adj(adj2);
    set_short(adj1 + " " + adj2 + " battleaxe");
    set_long("This is "+LANG_ASHORT(this_object())+". It bears the mark "
    +"of the Dewar Dwarves located near Palanthas. It has "
    +"seen better days. The Dewar are not known for their "
    +"forging skills and this axe shows signs of wear.\n");
    set_default_weapon(5,5,W_AXE,W_SLASH | W_IMPALE,W_NONE,0);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_VALUE,100);
    
}

