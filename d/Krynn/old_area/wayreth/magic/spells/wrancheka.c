/*
 * Wrancheka
 *
 * Description: A slow spell. Will work on anyone, and will initiate combat

 * Class:       3
 * Ingredients: honey
 * Mana:        175 (1/3)
 * Tax:		0.7
 * Skills:      SS_ELEMENT_AIR   10
 *              SS_FORM_ENCHANTMENT 20
 * Task:        TASK_EASY
 * Restriction: Must be member and may be in combat,
 *              the caster must not be gagged.
 */
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>
#include <language.h>

#define WRANCHEKA_OBJ "/d/Krynn/wayreth/magic/obj/wrancheka"

public void wrancheka_message(object caster, object *targets);

public int
create_spell_wrancheka()
{

    int level_mod = (query_caster()->query_wohs_level() / 8) + random(3);
    if (check_gagged())
        return 1;

    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_ENCHANTMENT, 20);

    set_spell_fail(spell_wohs_fail);

    set_spell_time(4);
    set_spell_task(TASK_EASY);

    set_spell_offensive(); /* We initiate combat, but no direct damage */
    set_spell_mana(100 + level_mod*20);
    set_find_target(find_team_living_targets);
    set_spell_message(wrancheka_message);
    set_spell_object(WRANCHEKA_OBJ);
    set_spell_ingredients( ({"vamene", "cap", "angeltear"}) );
}

public int
do_wrancheka(string str)
{
    return cast_spell();
}

public void
wrancheka_message(object caster, object *targets)
{
    object *effects = ({ });
    int t = query_spell_result()[0], i, size;
    t = 50 + (t * caster->query_wohs_level() / 7);

    for(i = 0; i < sizeof(targets); i++)
      {
	effects += targets[i]->query_magic_effects();
      }

    size = sizeof(effects);

    while(size--)
    {
        if (MASTER_OB(effects[size]) == WRANCHEKA_OBJ)
            effects[size]->dispel_magic();
    }

    t = (t > 400 ? 400 : t); 

    tell_room(E(caster), QCTNAME(caster) + " leans " +
	POSSESSIVE(caster) + " head back and shouts with a voice that "+
	"seems to be coming from all directions.\n", targets +
	({ caster, })); 

    caster->catch_msg("You lean your head back and give forth a great "+
		"shout that echos from all directions.\n");
    for(i = 0; i < sizeof(targets); i++)
    	targets[i]->catch_msg(QCTNAME(caster) + " leans " +
		POSSESSIVE(caster) + " head back and shouts with a voice "+
		"that seems to come from all directions. Your mind "+
		"clouds over, and you are unsure of what is real and "+
		"what is imagined.\n");
    
    set_spell_duration(t);
}
