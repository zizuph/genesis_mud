/* File         : /d/Terel/silver_new/weapon/black_arrow.c
 * Creator      : Udana	
 * Date         : March 2006         
 * Purpose      : Black Arrow for the Bow of Rommenus
 * Related Files: 
 * Comments     : 
 * Modifications: Modified by Pasqua
 */

#include </stdproperties.h>
#include "../include/defs.h"
 

inherit "/std/arrow";
inherit "/lib/keep";


public void 
create_arrow()
{
    set_adj("black");
    
    set_projectile_id("black_arrow");
    set_heap_size(10);
    set_hit(40);
    set_pen(38);
    set_keep(1);

}

string
get_projectile_long(string str, object for_obj, int num)
{
     return "The " + ((num == 1) ? "head" : "heads" ) + " of " + 
     ((num == 1) ? "this arrow is" : "these arrows are") +
     " made of black steel. " + ((num == 1) ? "It looks" : "They look") +
       " very sharp and dangerous.\n";

}

