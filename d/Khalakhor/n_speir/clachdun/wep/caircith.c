#include "/d/Khalakhor/sys/defs.h"
#include "local.h"
#include <formulas.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include <stdproperties.h>

inherit "/d/Khalakhor/std/weapon";

#define EXTRA_DAMAGE_PERCENT     20

void
create_khalakhor_weapon()
{
    // cairc (flesh)  ith (eat)
    set_name("caircith");
    add_name(({"sabre", "sword", "weapon"}));
    add_adj(({"blood-red", "jagged", "serrated"}));
    set_short("serrated blood-red sabre");
    set_long("This blade of the "+short()+" is extremely sharp and "+
      "jagged.  The metal of the sword feels warm to the touch and "+
      "seems to absorb all light which would shine on it giving it "+ 
      "an extremely dull luster.  On close inspection the blade "+
      "of the "+short()+" it is made of a mysterious black metal, infused "+
      "with seemingly infinate blood-red coloured viens.\n");

    set_wt(W_SWORD);
    set_hit(37);
    set_pen(52);
    set_pm(({ -3, 3, 0 }));
    set_hands(W_ANYH);
    set_dt(W_SLASH | W_IMPALE);
    set_likely_break(6);
    set_likely_dull(7);
    set_likely_corr(6);

    // This weapon is very resistant to other magics
    add_prop(OBJ_I_RES_COLD, 20);
    add_prop(OBJ_I_RES_FIRE, 20);
    add_prop(OBJ_I_RES_LIFE, 100);
    add_prop(OBJ_I_RES_DEATH, 100);
    add_prop(OBJ_I_RES_WATER, 25);
    add_prop(OBJ_I_RES_ACID, 20);
    add_prop(OBJ_I_RES_AIR, 25);
    add_prop(OBJ_I_RES_ELECTRICITY, 30);
    add_prop(OBJ_I_RES_EARTH, 40);

    // Add the props required for magical items
    add_prop(OBJ_I_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({60, "enchantment"}));
    add_prop(MAGIC_AM_MAGIC, ({"This "+short()+" has been magically enchanted. ",
	10, "The edge of the blade has been altered so that it is extremely "+
	"sharp. ", 25, "The enchantedment on the blade is one which "+
	"shreds exposed flesh. ", 50, "Due to this enchantment this "+short()+ 
	" is known in Khalakhor as Caircith, the Flesheater.", 80}));
    add_prop(OBJ_S_WIZINFO, "This magic weapon will do an extra "+
      EXTRA_DAMAGE_PERCENT+"% on an unarmed hitlocation.\n");

    // The sword is about 2/3 as heavy as a regular one.
    add_prop(OBJ_I_WEIGHT, 2*F_WEIGHT_DEFAULT_WEAPON(query_pen(), W_SWORD)/3);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(), query_pen() + 1000));
}

int
get_hitloc_id(string hdesc, object enemy)
{
    object co = enemy->query_combat_object();
    int *ids = co->query_hitloc_id();
    int sz = sizeof(ids);
    int i = -1;

    while (++i < sz)
    {
	if (co->query_hitloc(ids[i])[2] == hdesc)
	    return ids[i];
    }

    return -1;
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int phit, int dam)
{
    int id;


    if (phurt != -1 && dam)
    {
	id = get_hitloc_id(hdesc, enemy);
	if (id != -1 && !objectp(enemy->query_armour(id)))
	{
	    enemy->catch_tell("You feel your flesh burning as the "+short()+
	      " tears into your "+hdesc+".\n");
	    query_wielded()->catch_tell("Your "+short()+" grows warmer as it "+
	      "tears into "+LANG_POSS(enemy->query_the_name(query_wielded()))+
	      " "+ hdesc +".\n");
	    // I don't think this works but I'll add it anyways.
	    phurt += EXTRA_DAMAGE_PERCENT * phurt / 100;
	    enemy->heal_hp(-(EXTRA_DAMAGE_PERCENT * dam / 100));
	}
    }
    return ::did_hit(aid, hdesc, phurt, enemy, phit, dam);
}
