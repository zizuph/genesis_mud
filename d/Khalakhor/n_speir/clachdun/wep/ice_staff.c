#include "/d/Khalakhor/sys/defs.h"
#include "local.h"
#include "../spells/spells.h"
#include <formulas.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include <stdproperties.h>

inherit "/d/Khalakhor/std/weapon";
inherit "/d/Genesis/magic/spellcasting";
inherit SPELL_INHERIT;

// Prototypes
void create_frost_spell();

// Global vars
static int gSpell_active, gStun_id;

void
create_khalakhor_weapon()
{
    set_name("staff");
    add_name(({"polearm", "weapon"}));
    add_name("reodhadh");
    add_adj(({"ice", "sparkling"}));
    set_short("sparkling staff of ice");
    set_long("This is a staff made completely from ice, which sparkles "+
      "with a strange, dull light.  The "+short()+" is completely "+
      "flawless, it is a solid piece of crystal with absolutely no "+
      "imperfections.  Along the staff are carved a few whispy words "+
      "from which the dull glow of the staff seems to radiate from.\n");

    set_wt(W_POLEARM);
    set_hit(48);
    set_pen(43);
    set_hands(W_BOTH);
    set_dt(W_BLUDGEON);
    set_wf(this_object());
    set_likely_break(1);
    set_likely_dull(2);
    set_likely_corr(0);

    // This weapon is very resistant to other magics
    add_prop(OBJ_I_RES_COLD, 100);
    add_prop(OBJ_I_RES_LIFE, 100);
    add_prop(OBJ_I_RES_DEATH, 100);
    add_prop(OBJ_I_RES_WATER, 100);
    add_prop(OBJ_I_RES_ACID, 80);
    add_prop(OBJ_I_RES_AIR, 40);
    add_prop(OBJ_I_RES_ELECTRICITY, 40);
    add_prop(OBJ_I_RES_EARTH, 20);

    // Add the props required for magical items
    add_prop(OBJ_I_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(query_pen(), W_POLEARM));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, (3 * F_VALUE_WEAPON(query_hit(), query_pen())));

    // Reodhadh means frost in Scottish Gaelic (from MacFarlane's)
    add_spell("reodhadh", "Enchant this "+short()+" with a magical frost",
      create_frost_spell, spell_target_this_object);
}

void
deactivate_staff()
{
    gSpell_active = 0;
    tell_room(ENV(TO), "Deactivating staff!!\n");
}

void
activate_staff(object caster, object *targets, int *resist, int result)
{
    tell_room(ENV(TO), "Activating staff!!\n");
    gSpell_active = 1;
    set_alarm(300.0, 0.0, deactivate_staff);
}

int
create_frost_spell()
{
    if (gSpell_active)
    {
	write("The "+short()+" has already been enchanted!\n");
	return 1;
    }
    set_spell_element(SS_ELEMENT_WATER, 30);
    set_spell_form(SS_FORM_ENCHANTMENT, 40);
    set_spell_time(9);
    set_spell_peaceful(1);
    set_spell_task(TASK_SIMPLE);
    set_spell_mana(150);
    set_spell_effect(activate_staff);
}

mixed 
wield(object wep)
{
    add_spell_object(this_player());
    return 0;
}

mixed
unwield(object wep)
{
    remove_spell_object(query_wielded());
    return 0;
}

void
remove_stunning(object player)
{
    player->catch_tell("You finally manage to break free of the bitter cold "+
      "which was stunning you.\n");
    player->remove_stun();
    gStun_id = 0;
}

int
try_hit(object enemy)
{
    if (gSpell_active && !gStun_id &&
      random(500) <= query_spell_strength())
    {
	query_wielded()->catch_tell("A burst of frosty energy evelops "+
	  enemy->query_the_name(query_wielded())+", stunning "+
	  HIM_HER(enemy)+".\n");
	enemy->catch_tell("You are surrounded by a frosty cold "+
	  "which leaves you feeling stunned.\n");
	query_wielded()->tell_watchers("A burst of frosty energy from "+
	  LANG_POSS(QTNAME(query_wielded()))+" "+short()+" leaving "+
	  QTNAME(enemy)+" looking stunned.\n", enemy);
	enemy->add_stun();
	gStun_id = set_alarm(itof(random(21)+20),0.0, &remove_stunning(enemy));
	return 0;
    }
    return 1;
}
