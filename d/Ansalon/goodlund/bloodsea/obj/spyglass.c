/* 
 * 2016-06-16 - Cotillion
 * - Fixed possible money making exploit
 */

inherit "/std/object";
inherit "/lib/keep";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"


void
create_object()
{
   set_name("spyglass");
   set_short("gnomish spyglass");

   set_long("A remarkable invention, this is a small tube with carefully crafted " +
     "glass lenses at either end that allow you to view distant objects as if you " +
     "were right next to them!  This one looks a bit battered and worn over time, " +
     "and it looks like it once had a number of bells and whistles attached to it " +
     "that have since been ripped off.\nYou are able to 'investigate' distant objects " +
     "with this while sailing on Bloodsea crafts.\n");
   
   add_prop(OBJ_I_VALUE, 30);
   add_prop(OBJ_I_WEIGHT,20);
   add_prop(OBJ_I_VOLUME,20);
   add_prop(OBJ_I_VALUE, 250);

   set_keep(1);
}

int
investigate(string str)
{
   notify_fail("The gnomish gadget doesn't seem to work here!\n");
   return 0;
}

/* 
 * Function:     query_recover 
 * Description:  Used to restore a new copy of the gem between 
 *               logins. 
 */ 
string 
query_recover() 
{ 
    return MASTER; 
} 


void
init()
{
    ::init();
    add_action(investigate, "investigate");

}
