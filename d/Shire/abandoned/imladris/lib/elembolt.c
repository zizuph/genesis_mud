/*
 * A generic elemental attack spell.
 *
 */

#include "defs.h"
#include <wa_types.h>

inherit "/d/Shire/imladris/lib/spellobj";
inherit MESSAGE_FILE;

create_spellobj()
{
    set_form(FORM_CONJURATION, 10);
    set_elem(ELEMENT_FIRE, 10);
    set_syntax("[on] <living>");
    this_object()->create_elemental_bolt();
}

object *
area_of_effect(string str)
{
    notify_fail(capitalize(query_prop(SPELL_S_NAME))+" who?\n"+query_syntax());
    return parse_attack(str, "[on]");
}

int
query_armour_spell_db(int ac, int wgt)
{
    switch(ac)
    {
	case 1..4:    return MAX(wgt,  5000)*5/5000;
	case 5..8:    return MAX(wgt, 10000)*10/10000;
	case 9..15:   return MAX(wgt, 15000)*15/15000;
	case 16..20:  return MAX(wgt, 20000)*20/20000;
	case 21..30:  return MAX(wgt, 25000)*20/25000;
	default:      return MAX(wgt, 30000)*20/30000;
    }
}

int
query_armour_reverse_spell_db(int ac, int wgt)
{
    switch(ac)
    {
	case 1..4:    return (5000-MIN(wgt,5000))*40/5000;
	case 5..8:    return (10000-MIN(wgt,10000))*30/10000;
	case 9..15:   return (15000-MIN(wgt,15000))*20/10000;
	case 16..20:  return (20000-MIN(wgt,20000))*15/10000;
	case 21..30:  return (25000-MIN(wgt,25000))*10/10000;
	default:      return (30000-MIN(wgt,30000))*5/10000;
    }
}

/*
 * Function:	query_armour_db(living, reverse)
 * Description:
 *	This function returns a defensive bonus number according to which
 *	armour type a living wears. If reverse is true, then the attack
 *	will be more effective with armour on, than if not.
 */
varargs int
query_armour_db(object ob, int reverse)
{
    object helmet, plate;
    mixed shields;
    int defense = 0;
    int add_def = 0;
    int i;

    if (!ob||!living(ob)) return 0;

    plate   = ob->query_armour(A_TORSO);
    helmet  = ob->query_armour(A_HEAD);
    shields = ob->query_armour(A_SHIELD);

    if (plate->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
	defense += plate->query_ac();
    else if (reverse)
	defense += query_armour_reverse_spell_db(plate->query_ac(), 
						 plate->query_prop(OBJ_I_WEIGHT));
    else
	defense += query_armour_spell_db(plate->query_ac(), 
					 plate->query_prop(OBJ_I_WEIGHT));

    if (helmet)
	add_def += helmet->query_ac()*5/100;
    if (plate)
	add_def += plate->query_ac()*20/100;
    if (shields)
    {
	if (objectp(shields))
	    shields = ({ shields });
	for(i=0;i<sizeof(shields);i++)
	    if (shields[i]->query_at()==A_SHIELD)
		add_def += shields[i]->query_ac()*10/100;
    }

    if (reverse)
	return MAX(defense-add_def, 0);
    else
	return defense+add_def;
}

/*
 * Function:	bolt_missed
 * Argument:	target
 * Description:
 *	Called when a bolt missed its target.
 */
void
bolt_missed(object target)
{
	caster->catch_msg("You cast "+LANG_ADDART(query_prop(SPELL_S_NAME))+
	", but it hits the ground!\n");
	target->catch_msg(QCTNAME(caster)+" casts "+
	LANG_ADDART(query_prop(SPELL_S_NAME))+", but it hits the ground!\n");
	tell_room(ENV(caster),QCTNAME(caster)+" cast "+
	LANG_ADDART(query_prop(SPELL_S_NAME))+", but it hits the ground!\n",
	({caster, target}));
/*
    tellem(caster, target,
	"$You $cast "+LANG_ADDART(query_prop(SPELL_S_NAME))+
	", but it hits the ground!\n");
*/
}

void
target_jumped(object target)
{
	caster->catch_msg("You cast "+LANG_ADDART(query_prop(SPELL_S_NAME))+
	" upon "+QTNAME(target)+", but "+HE_SHE(target)+" skillfully "+
	"jumped away!\n");

	target->catch_msg(QCTNAME(caster)+" cast "+
	LANG_ADDART(query_prop(SPELL_S_NAME))+
	" upon you, but you skillfully jump away!\n");

	tell_room(ENV(caster),QCTNAME(caster)+" cast "+
	LANG_ADDART(query_prop(SPELL_S_NAME))+" upon "+QTNAME(target)+
	" but "+HE_SHE(target)+" skillfully jumped away!\n",({caster, target}));

/*    tellem(caster, target,
	 "$You $cast "+LANG_ADDART(query_prop(SPELL_S_NAME))+
	 " upon #name, but #he skillfully #jump away!\n");
*/
}

void
tell_how_good(object target, int did_hurt)
{
    string good;

    switch(did_hurt)
    {
	case 0..15:    good = "poor"; break;
	case 16..30:   good = "weak"; break;
	case 31..59:   good = "fairly potent"; break;
	case 60..75:   good = "powerful"; break;
	case 76..91:   good = "nasty"; break;
	case 92..110:  good = "awesome"; break;
	case 111..200: good = "devastating"; break;
	case 201..500: good = "massacrating"; break;
	default:       good = "deadly"; break;
    }

	caster->catch_msg("You cast " + LANG_ADDART(good) + " \"" +
	CAP(query_prop(SPELL_S_NAME)) + "\" upon "+QTNAME(target)+"!\n");

	target->catch_msg(QCTNAME(caster)+" cast "+LANG_ADDART(good)+" \"" +
	CAP(query_prop(SPELL_S_NAME)) + "\" upon you!\n");

	tell_room(ENV(caster),QCTNAME(caster)+" cast "+LANG_ADDART(good)+
	" \""+CAP(query_prop(SPELL_S_NAME))+"\" upon "+QTNAME(target)+"!\n",
	({caster,target}));

/*
    tellem(caster, target,
	 "$You $cast "+LANG_ADDART(good)+" \""+CAP(query_prop(SPELL_S_NAME))+
	 "\" upon #name!\n");
*/
}

/*
 * Function:	      cast_elemental_bolt
 * Description:       Casts an elemental bolt upon a target.
 *
 * Calculations:
 *
 */
mixed
cast_elemental_bolt(object *targets, int succ)
{
    object target = targets[0];
    int resistance;
    mixed did_hurt;
    string how, good;
    object helmet, plate;
    mixed shields;
    int i, mana;
    int offensive_bonus;
    int power;

    power = query_spell_power();

    if (!CAN_SEE_IN_ROOM(caster))
	power = power * caster->query_skill(SS_BLIND_COMBAT) / 100;

    if (!CAN_SEE(caster, target))
	power = power * caster->query_skill(SS_AWARENESS) / 100;

    if (!CAN_SEE(target, caster))
	power += power *
	    ABS(200 - target->query_skill(SS_BLIND_COMBAT) -
		      target->query_skill(SS_AWARENESS)) / 100;

    mana = query_prop(SPELL_I_MANA);

    offensive_bonus = MIN(power, 1000);
    offensive_bonus = MIN(offensive_bonus, mana*10);

    if (query_prop(SPELL_I_DAMAGE))
	offensive_bonus = offensive_bonus * query_prop(SPELL_I_DAMAGE) / 100;

    offensive_bonus += caster->query_stat(SS_DEX)/5;
    /* offensive_bonus += caster->query_skill(SS_DIRECTED_SPELLS); */

    offensive_bonus -= target->query_stat(SS_DEX)/5;
    offensive_bonus -= target->query_prop(LIVE_I_QUICKNESS)/10;

    offensive_bonus -= query_armour_db(target, query_prop(SPELL_I_REVERSE_DEFENCE));

    if (!present(target, environment(caster)))
	offensive_bonus = 0;

    resistance = target->query_magic_res(MAGIC_RES[query_prop(SPELL_I_DAM_TYPE)]);
    resistance = (resistance + random(resistance))/2;

    offensive_bonus = offensive_bonus * (100-resistance) / 100;

    if (offensive_bonus <= 2)
    {
	bolt_missed(target);
	return;
    }

    log_file("ELEMBOLT",
	ctime(time())+":"+caster->query_name()+":"+offensive_bonus+"\n"
    );

    if (caster->query_wiz_level())
    {
	caster -> catch_msg("WIZINFO: Offensive bonus : "+offensive_bonus+"\n");
	caster -> catch_msg("         Mana used       : "+query_prop(SPELL_I_MANA)+"\n");
    }

    did_hurt = target->hit_me(offensive_bonus, MAGIC_DT, caster, -1);

/*  did_hurt =	({ proc_hurt, hitloc description, phit, dam }) */

    if (did_hurt[0]==-1)
    {
	target_jumped(target);
	return;
    }

    tell_how_good(target, did_hurt[2]);
    message(caster, target, query_prop(SPELL_I_DAM_TYPE), did_hurt[1], did_hurt[0]);

    if (target->query_hp()<=0)
	target->do_die(caster);

    return;
}

void
do_instant_effect(object *targets, int res)
{
    string retval;

    retval = cast_elemental_bolt(targets, res);
    if (stringp(retval))
	write(retval);
}

