/* -*- C++ -*- */
/* This is a dummy object used in case of magic interaction.
 * It's cloned by the encourage spell.
 * for the new spell system
 * by Aridor, 10/95
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
    set_name("encourageobj");
    set_adj("magic");
    set_no_show();
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
}

void
init_spell(object caster, object target, object prev)
{
    int pow = query_power();
    int pnc, tmp;

    /* first, reduce some panic if necessary. */
    
    pnc = target->query_panic();
    if (pnc > 0)
      {
	tmp = MIN(pnc, pow);
	target->add_panic(-tmp*5);
	pow -= tmp;
	//target->catch_msg("You feel calmer again.\n"); Not necessary (done inside add_panic)
      }

    /* if there are still 'power' points left, (also) increase the DIS */

    target->add_tmp_stat(SS_DIS, pow / 5 + 1,
			 query_duration() / F_INTERVAL_BETWEEN_HP_HEALING);
    
    caster->add_mana(-20);
    find_living("aridor")->catch_msg("ENCOURAGE C: " + tmp + " P:" + (pow/5+1) +
				     " D:" + query_duration() + ".\n");
}

void 
remove_object() 
{
    write("Paladine's supporting presence withdraws from you.\n");
    ::remove_object();
}
