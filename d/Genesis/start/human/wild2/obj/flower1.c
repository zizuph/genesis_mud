/*
 * /w/mirandus/ideas/dewargully/wep/dewarwep.c
 *
 * Axe used by Dewar Dwarves in Newbie Zone
 * Coded by Mirandus with help from Mercade
 */

inherit "/std/object";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <money.h>
#include <stdproperties.h>


#define COLOUR ({"black", "blue", "green", "red", "violet", "orange"})
#define FLOWER ({"snapdragon", "rose", "lily", "carnation", "buttercup"})


/*
 * Function name: create_object()
 * Description  : Constructor, redefine this to configure your weapon
 */
void
create_object() 
{
    
    string colour = one_of_list(COLOUR);
    string flower = one_of_list(FLOWER);
    
    set_name(({"flower",flower}));
    set_adj(colour);
    set_short(colour + " " + flower);
    set_long("This is "+LANG_ASHORT(this_object())+". It is beautiful and "+
	"is a "+flower+" that many people might want.\n");
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_VALUE,100);
    
}

