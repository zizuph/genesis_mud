
/* This is a dummy object used in case of magic interaction.
 * It's cloned by the revive spell.
 * for the new spell system by Aridor, 10/95
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
    set_name("reviveobj");
    set_adj("magic");
    set_no_show();
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
}

void
init_spell(object caster, object target, object prev)
{
    int mana, mxhp, hp, healed, factor = 5;

    mana = caster->query_mana();
    mxhp = target->query_max_hp();
    hp = target->query_hp();

    healed = MIN((mxhp - hp) / 3, mana / 2);
    healed = (query_power() > 60 ? 60 : query_power()) * healed / 60;

    target->heal_hp(healed);
    
    switch(query_power())
      {
      case 121..149:
	factor = 6;
      case 150..1000:
	factor = 7;
      }

    caster->add_mana(-healed/factor);  /* 5/6/7 HP per 1 MANA! */
  
    find_living("aridor")->catch_msg("REVIVE (R) P:" + query_power() + " HP:" +
				     healed + " COST: " + healed/factor + ".\n");
}
