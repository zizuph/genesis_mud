/*
 * /w/mirandus/ideas/dewargully/wep/dewarthanewep.c
 *
 * Axe used by Dewar Dwarves in Newbie Zone
 * Coded by Leia, Modified from Mirandus' dewarthanewep.c file
 */

inherit "/std/weapon";
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../local.h"


#define ADJ1 ({"old","cracked", "beaten"})
#define ADJ2 ({"iron", "steel"})

/*
 * Function name: create_weapon()
 * Description  : Constructor, redefine this to configure your weapon
 */
void
create_weapon() 
{
	
	string adj1 = one_of_list(ADJ1);
	string adj2 = one_of_list(ADJ2);
	
	set_name("hammer");
	set_adj(adj1);
    add_adj(adj2);
    set_short(adj1 + " " + adj2 + " hammer");
	set_long("This is "+LANG_ASHORT(this_object())+". It appears to be "
	+"discarded by a dewar smith, and repurposed as"
	+" a fighting weapon by the aghar. Being the nicest weapon "
	+"within the clan, it has been afforded to the highbulp.\n");
	set_default_weapon(10,10,W_CLUB,W_BLUDGEON,W_NONE,0);
	add_prop(OBJ_I_WEIGHT, 300);
	add_prop(OBJ_I_VOLUME, 600);
	add_prop(OBJ_I_VALUE,200);
	
}

