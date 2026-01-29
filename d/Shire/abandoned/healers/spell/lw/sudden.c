/*
 * Sudden light.
 *
 * Causes a 10'R burst of intense light, all within are stunned
 * for 1 rnd/10 failure. [Force spell, Duration instant, Range: 100']
 *
 * I will make this a kind of a attack spell, and use the fumble
 * routines in rogon/skills/fumble.
 */

#include "defs.h"
#include <composite.h>
#include <filter_funs.h>

inherit SPELL_FILE;

#define FUMBLE_FILE "/d/Shire/moria/skills/fumble"

create_spellobj()
{
    set_form(FORM_CONJURATION, 10);
    set_elem(ELEMENT_FIRE, 10);      /* Light really */
    set_spell_name("sudden light");
    set_classes(([1:5, 3:11]));
    set_desc(
	"Causes a burst of intense light to explode in front of "+
	"victim, usually resulting in temporary blindness and "+
	"foe stunned for a while."
    );
    set_syntax("on <living>");
}

object *
area_of_effect(string str)
{
    object *targets = ({});
    int i;

    notify_fail("Who do you want to cast Sudden Light on?\n"+query_syntax());

    if (!strlen(str) && living(caster->query_attack()))
	targets = ({ caster->query_attack() });
    else if (sizeof(targets = parse_environment_items(str, "'on'")))
	targets = ({ targets[0] });

    if((i=member_array(caster, targets))>=0)
    {
	targets = exclude_array(targets, i, i);
	notify_fail("You shouldn't cast a Sudden Light spell on yourself!\n");
    }
    return targets;
}

mixed
cast_sudden_light(object *targets, int res)
{
    object ob, blind;
    int i;

    targets = FILTER_PRESENT_LIVE(targets);

    if(!sizeof(targets))
	return "No targets present!\n";
    if(sizeof(targets)==1)
    {
	ob = targets[0];
	if(!ob || !living(ob))
	    return "But, that is not a living creature!\n";

	res = res * (100 - ob->query_magic_res(MAGIC_I_RES_LIGHT))/100;
	if(!CAN_SEE(caster, ob))
	    res = res * caster->query_prop(SS_BLIND_COMBAT)/200;

	caster->catch_msg(
	    "You point your arms towards "+QTNAME(ob)+" and release your spell!!\n");
	ob->catch_msg(
	    QCTNAME(caster)+" points "+HIS_HER(caster)+" arms towards you "+
	    "and releases his spell!!\n");
	tell_room(ENV(caster),
	    QCTNAME(caster)+" points "+HIS_HER(caster)+" arms towards "+
	    QTNAME(ob) + " and releases "+HIS_HER(caster) + " spell.\n",
	    ({ caster, ob }));

	FIXEUID;
	switch(res)
	{
	    case 0..10:
		  caster->catch_msg("A flash of light sizzles on the floor in front "+
		    "of "+QTNAME(ob)+".\n");
		  ob->catch_msg("A flash of light sizzles on the floor in front "+
		    "of you.\n");
		  tell_room(ENV(caster),"A flash of light sizzles on the floor in "+
		    "front of "+QTNAME(ob)+".\n", ({ caster, ob }));
		/*tellem(caster, ob,
		    "A flash of light sizzles on the floor in front of (him).\n",1);*/
		  return;
	    case 11..100:
		  caster->catch_msg(QCTNAME(ob)+" is struck by a bright light!\n");
		  ob->catch_msg("You are struck by a bright light!\n");
		  tell_room(ENV(caster),QCTNAME(ob)+" is struck by a bright light!\n",
		    ({ caster, ob }));
		/*tellem(caster, ob,
		    "#N is struck by a bright light!\n");*/
		  FUMBLE_FILE->hit_yourself(ob, caster);
		  return;
	    case 101..200:
		  caster->catch_msg("You conjure a flashing light in front of "+
		    "of "+QTNAME(ob)+"!\n");
		  tell_room(ENV(caster),QCTNAME(caster)+" conjures a flashing light "+
		    "in front of "+QTNAME(ob)+"!\n", ({ caster, ob }));
		/*tellem(caster, ob,
		    "$N $conjure a flashing light in front of #o!\n",1);*/
		  ob->catch_msg("You are struck by the flash of light!!\n");
	      FUMBLE_FILE->add_fumble(ob, "You can not see! You are blinded!!\n", 8);
		  return;
	    case 201..500:
		  caster->catch_msg("You cast a flashing light in front of "+
		    QTNAME(ob)+"!\n");
		  ob->catch_msg(QCTNAME(caster)+" casts a flashing light in front "+
			"of you!\n");
		  tell_room(ENV(caster),QCTNAME(caster)+" casts a flashing light "+
			"in front of "+QTNAME(ob)+"!\n", ({ caster, ob }));
		/*tellem(caster, ob,
		  "$N $cast a flashing bright light in front of #o!!\n");*/
		  ob->command("scream");
		  FUMBLE_FILE->loose_grip(ob, caster);
		  return;
	    default:
		  caster->catch_msg("You cast an exploding light in front of "+
			QTNAME(ob)+"!\n");
		  ob->catch_msg("A flash of light explodes in front of you!\n");
		  tell_room(ENV(caster),"You stand amazed as an incredible "+
			"flash of light explodes in front of "+QTNAME(ob)+"!\n", ({ caster, ob }));
		/*tellem(caster, ob,
		  "You stand amazed as an increadible flash of light explodes in "+
		  "front #o!!\n",1);*/
		  ob->command("scream");
		/*tellem(caster, ob,
		  "#N tried to save #p eyes, but could not!\n",1);*/
		  tell_room(ENV(caster),QCTNAME(ob)+" tried to save his eyes, but could not!\n");
		  blind = clone_object(LW_DIR+"blindeff");
		  blind->init_shadow(ob, res);
		return;
	}
    }
    return 1;
}

void
do_instant_effect(object *targets, int res)
{
    string retval;

    retval = cast_sudden_light(targets, res);
    if(stringp(retval))
	write(retval);
}
