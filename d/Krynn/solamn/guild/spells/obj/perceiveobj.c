
/* This is a dummy object used in case of magic interaction.
 * It's cloned by the perceive spell.
 * for the new spell system
 * Aridor, 10/95
 */
#include "../../guild.h"
#include "../local.h"

inherit "/std/object";
inherit MAGIC_OBJECT;

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

void
create_object()
{
    set_name("perceiveobj");
    set_adj("magic");
    set_no_show();
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
}

void
init_spell(object caster, object target, object prev)
{
    string info = "";
    mixed magic_str = target->query_prop(MAGIC_AM_ID_INFO);
    int i, result = query_power();

    set_this_player(caster);

    for (i = 0; i < sizeof(magic_str); i += 2)
      if (magic_str[i + 1] <= result)
	info += magic_str[i];
    
    if (strlen(info))
      write(info);
    else
      {
	  write("A trickle of energy flows into the medal and withdraws.\n " +
		"You feel certain that the " + check_call(target->short()) + " is "+
		"what it appears to be, and nothing more.\n");
      }


    find_living("aridor")->catch_msg("PERCEIVE P:" + query_power() + " OBJ:" +
				     target->short() + ".\n");
}
