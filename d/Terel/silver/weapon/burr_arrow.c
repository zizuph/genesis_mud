/* File         : /d/Terel/silver_new/weapon/burr_arrow.c
 * Creator      : Udana				
 * Date         : March 2006         
 * Purpose      : Burr Arrow
 * Related Files: 
 * Comments     : 
 * Modifications: Modified by Pasqua
 */

#include <stdproperties.h>
#include <macros.h>
#include "../include/defs.h"

/*Be sure to change that if you move bad_arrow.c*/
#define BAD_ARROW WEAPON + "bad_arrow.c"


inherit "/std/arrow";
inherit "/lib/keep";



public void create_arrow()
{
    set_adj("burr-headed");
    add_adj("black");
    
    set_projectile_id("burr_arrow");
    set_heap_size(3);
    set_hit(45);
    set_pen(45);
    set_keep(1);
	add_prop(OBJ_S_WIZINFO, "When those arrows hit target with "+
		"anything better then glance they stuck in target. Target get "+
		"dexterity penality, and loose hp over time from bleeding. Arrows "+
		"be pulled out - for price of big amount of hp, or broken. Breaking "+
		"remove dex penality, and reduces bleeding, but arrows gets "+
		"harder to pull out (bigger health loss).\n");

    setuid();
    seteuid(getuid());
}





public varargs void 
projectile_hit_target(object archer, int aid, string hdesc, int phurt, 
		      object enemy, int dt, int phit, int dam, int hid)
{
    string responsible_living;
    
    if(!query_broken() && phurt >= 4)
    {
      object b_arrow = clone_object(BAD_ARROW);
      b_arrow->move(enemy, 1);
      responsible_living = interactive(archer) ? archer->query_real_name() : MASTER_OB(archer);  
      b_arrow->land(responsible_living, hid);
      remove_object();
    }
    return;
}




string
get_projectile_long(string str, object for_obj, int num)
{
     return "The " + ((num == 1) ? "head" : "heads" ) + " of " 
     + ((num == 1) ? "this arrow is" : "these arrows are") +
     " made of black steel. Not only " + ((num == 1) ? "it's" : "they are") +
       " very sharp, but nasty looking burrs have been added on sides - it " +
       "must be very hard to pull " + ((num == 1) ? "this arrow" : "these arrows") +
       " out when "  + ((num == 1) ? "it pierces" : "they pierce" ) 
       + " the enemy.\n";

}

