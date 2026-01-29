/* The Wild Runner ring. This is the symbol of the Wildrunners guild,     */
/* and proudly worn by many Elves. It also handles loading the soul.      */
/* Some code taken from the old Wild Runners ring allegedly by Mylos.     */
/* Based on the nose-ring made by Quis.                                   */
/* Totally recoded 28/08/95 by Tulix III to bring up to Grunts standard.  */
/* No longer loads the soul (see shadow), 
 * no longer auto loads (see shadow), 
 * no longer contains the "ground" command (see soul)
 * -- Shiva 12/04/96 
 * 
 * Updated for Cypress
 * Finwe, June 2001
 */

#pragma save_binary

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "wrunner_defs.h"
#include "/d/Shire/cypress/sys/defs.h"

void
create_armour()
{
    if (!IS_CLONE)
      return;
   
    set_name("ring");
    set_adj("golden");
    add_adj("tiny");
    add_name(RING_ID);
    set_long("This tiny ring is fashioned from gold. For "+
         "more information on the Wild Elves guild, type 'help "+
         "wild elves'.\n");
    set_short("golden ring of the Wild Elves");
   
    set_ac(0);            /* Not much use as armour, to be honest */
    set_at(A_FINGERS);    /* This ring is worn around the fingers */
    
    seteuid(getuid());    /* Needed for cmdsoul manipulation      */
    
    add_prop(OBJ_I_WEIGHT, 60);  /* Weight 60g */
    add_prop(OBJ_I_VOLUME, 3);   /* Volume 3ml */
    add_prop(OBJ_I_VALUE, 0);     /* Genuinely priceless */
    add_prop(OBJ_M_NO_DROP, "You won't even consider losing your ring.\n");
}

public string
query_recover()
{
    return 0;
}

void enter_env(object env, object from)
{
  ::enter_env(env, from);

  if (env->query_wiz_level() && !env->query_guild_member(GUILD_NAME))
  {
    remove_object();
    return;
  }

  // we don't want more than one ring at a time
  filter(all_inventory(env) - ({ this_object() }),
      &->id(RING_ID))->remove_object();
  
}
