/*
 * /w/mirandus/ideas/dewargully/wep/agharwep.c
 *
 * Axe used by Dewar Dwarves in Newbie Zone
 * Coded by Leia, Modified from Mirandus' dewarwep.c file
 */

inherit "/std/weapon";
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../local.h"


#define ADJ1 ({"long","short","thick-tailed","blunt-nosed","sharp-toothed",\
                      "earless","legless"})
#define ADJ2 ({"white","brown","black","grey","silver",\
                      "dirty","grimy"})


/*
 * Function name: create_weapon()
 * Description  : Constructor, redefine this to configure your weapon
 */
void
create_weapon() 
{
    
    string adj1 = one_of_list(ADJ1);
    string adj2 = one_of_list(ADJ2);
    
    set_name(({"rat","petrified rat"}));
    set_adj(adj1);
    add_adj(adj2);
    set_short(adj1 + " " + adj2 + " petrified rat");
    set_long("This is "+LANG_ASHORT(this_object())+". It appears "
    +"that the aghar have dipped it into some sort of "
    +"hardened liquid to preserve it and add durability. It "
    +"is the most disturbing club you have ever seen.\n");
    set_default_weapon(5,5,W_CLUB,W_BLUDGEON,W_NONE,0);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_VALUE,100);
    
}

