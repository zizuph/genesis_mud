/* ***************************************************************************
   NAME:       Encourage (for Sword Knights)
   COST:       40 Mana, (20 fail)
   TAX:        0.3% (uses recharge technique instead of material component)
   DESC:       Success encourages (raises DIS) of target by 2-10 points.

	       ~Aridor, 07/95
*************************************************************************** */

#include <composite.h>

#define ENCOURAGE_MANA      40
#define ENCOURAGE_MANA_FAIL 20
#define ENCOURAGE_TASK    (TASK_DIFFICULT)
#define ENCOURAGE_LIST    ({SS_ELEMENT_LIFE, \
			  SS_FORM_DIVINATION, \
			  SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
			  SKILL_WEIGHT, 50, TS_WIS})

/*prototypes*/
public object *encourage_target(string str);
public void encourage_message(object caster, object *targets);
public mixed encourage_success(object caster, object *targets);


void
create_spell_encourage(string arg)
{
    set_element(SS_ELEMENT_LIFE, 25);
    set_form(SS_FORM_DIVINATION, 22);
    set_spell_time(5);
    set_mana_spell(ENCOURAGE_MANA);
    //set_mana_spell_fail(ENCOURAGE_MANA_FAIL);

    set_spell_time(4);

    set_find_target(encourage_target);
    //set_spell_area_function("my_area_of_effect");
    
    set_spell_task(ENCOURAGE_TASK);
    set_spell_message(encourage_message);
    set_spell_success(encourage_success);
    set_spell_object(SOBJ + "encourageobj");
}

string
encourage_mutter(mixed target)
{
    if (target)
      return "the strength of Paladine flow through " + target + ", that you " +
	"may be more encouraged";
    return "the strength of Paladine flow through me, that I may be more " +
      "encouraged";
}

public object *
e_no_target_message()
{
    write("Encourage who?\n");
    return 0;
}

public object *
encourage_target(string str)
{
    int i;
    mixed *targ;

    if (!str)
      return ({ query_caster() });

    if (str == "team")
      return ({ query_caster() }) + query_caster()->query_team_others();

    if (!parse_command(str,E(query_caster()),"[the] %l",targ))
      return e_no_target_message();
    
    i = targ[0];
    if (i==0)
      return targ[1..];
    if (i<0)
      return targ[-i..-i];
    return targ[1..i];
}

public void
encourage_message(object caster, object *targets)
{
    string pl = (targets && sizeof(targets) > 1) ? "" : "s";

    tell_room(E(caster),"The medal briefly flares to light. ");
    write("Your call for Paladine's support has been answered. ");
    if (member_array(caster,targets) == -1)
      write(C(COMPOSITE_LIVE(targets)) +
	    " suddenly appear" + pl + " more confident and determined.\n");
    targets->catch_msg("Suddenly you feel the spirit of Paladine supporting " +
		       "you.\n");
    tell_room(E(caster),C(QCOMPLIVE) + " suddenly appear" + pl + " more confident and " +
	      "determined.\n", targets + ({caster}));
    
}

int
has_enc_object(object who)
{
    if (present("encourageobj",who))
      return 0;
    return 1;
}

public mixed
encourage_success(object caster, object *targets)
{
    int result;

    fail_message = "";
    if (spell_failed)
      return 0;

    if (caster->query_prop(KNIGHT_I_DEVOTION) < caster->query_age() + 200)
      caster->add_prop(KNIGHT_I_DEVOTION, caster->query_age() + 200);
    
    fail_message = "You begin to pray but don't feel confident enough for this prayer.\n";
    if (random(caster->query_stat(SS_DIS)) < random(20))
      return 0;

    fail_message = "This prayer is already in operation.\n";
    
    /* check which targets have the object already and remove them as target*/
    targets = filter(targets,has_enc_object);
    targets -= ({ 0 });
    fail_message = "This prayer is already in operation.\n";
    if (!targets || !sizeof(targets))
      return 0;
    
    fail_message = "Despite your best efforts, your prayer is unheard.\n";
    if ((result = caster->resolve_task(ENCOURAGE_TASK, ENCOURAGE_LIST)) <= 0)
      return 0;

    reduce_spell_availability("encourage");
    set_duration(145 + 2 * result + random(caster->query_stat(SS_INT) + 50));
    return result;
}

mixed
do_encourage(string str)
{
    return cast_spell();
}

