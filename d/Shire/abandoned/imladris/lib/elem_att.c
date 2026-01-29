/*
 * A generic elemental attack spell.
 *
 */

#include "defs.h"

inherit SpellFile;
inherit SpellParse;
inherit TellemFile;
inherit MessageFile;

create_spell()
{
    add_prop(SPELL_I_GENERAL,	    SS_SPELLCRAFT);
    add_prop(SPELL_AI_FORM,	    ({ SS_FORM_CONJURATION, 10 }) );
    add_prop(SPELL_AI_ELEMENT,	    ({ SS_ELEMENT_FIRE, 10 }) );
    add_prop(SPELL_AM_MATERIALS,    0);
    add_prop(SPELL_I_CASTING_TIME,  "@@query_casting_time@@");
    add_prop(SPELL_I_DIFFICULTY,    "@@query_difficulty@@");
    add_prop(SPELL_I_MANA,	    "@@query_mana@@");
    add_prop(SPELL_O_EFFECT,	    0);

    add_prop(SPELL_S_SYNTAX, "[on] <living>");

    this_object()->create_elemental_attack();
}

object *
area_of_effect(string str)
{
    object *targets;

    if(!str)
	if(caster->query_attack())
	    return ({ caster->query_attack() });
	else
	    return ({});

    targets =  parse_livings(str, "[on] %l");
    targets -= ({ caster });

    notify_fail(C(query_prop(SPELL_S_VERB)+" who?\n"+query_syntax());
    return targets;
}

/*
 * Function:	      cast_elemental_bolt
 * Description:       Casts an elemental bolt upon a target.
 */
mixed
cast_elemental_bolt(object *targets, int success)
{
    object ob = targets[0];
    int resistance;
    mixed did_hurt;
    string how, good;
    object helmet, plate;
    mixed shields;
    int i;

    if(!CAN_SEE(caster, ob))
	success = success * caster->query_skill(SS_BLIND_COMBAT) / 100;

    success *= spell_class_wanted;

    if(success>spell_class_wanted*200)
	success = spell_class_wanted*200;  /* 1:200, 10:2000 */

    success +=	random(level(caster)*10 + Dex(caster));
    success -=	random(Dex(ob)+Acrobatics(ob));

    helmet  = ob->query_armour(A_HEAD);
    shields = ob->query_armour(A_SHIELD);
    plate   = ob->query_armour(A_TORSO);

    if(helmet)
	success -= helmet->query_ac()*5/100;
    if(plate)
	success -= plate->query_ac()*20/100;
    if(shields)
    {
	if(objectp(shields))
	    shields = ({ shields });
	for(i=0;i<sizeof(shields);i++)
	    if(shields[i]->query_at()==A_SHIELD)
		success -= shields[i]->query_ac()*10/100;
    }

    if(!present(ob, environment(caster)))
	success = 0;

    resistance = ob->query_magic_res(MAGIC_RES[query_prop(SPELL_I_DAM_TYPE)]);

    success = success * (100-resistance) / 100;

    if(success<10)
    {
	Tell(caster, ob,
	    "[You] cast[*s] a shock bolt, but it hits the ground!\n");
	return;
    }

    did_hurt = ob->hit_me(success, MAGIC_DT, caster, -1);

/*  did_hurt =	({ proc_hurt, hitloc description, phit, dam }) */

    if(did_hurt[0]==-1)
    {
	Tell(caster, ob,
	    "[You] cast[*s] "+LANG_ADDART(query_prop(SPELL_S_NAME))+
	    " upon [oth], but [he] skillfully jumps away!\n");
	return;
    }

    switch(did_hurt[2])
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

    Tell(caster, ob,
	 "[You] cast[*s] "+LANG_ADDART(good)+" "+query_prop(SPELL_S_NAME)+
	 " upon [oth]!\n");

    message(caster, ob, query_prop(SPELL_I_DAM_TYPE), did_hurt[1], did_hurt[0]);

    if(Hp(ob)<=0)
	ob->do_die(caster);

    return;
}

void
do_instant_effect(object *targets, int res)
{
    string retval;

    retval = cast_elemental_bolt(targets, res);
    if(stringp(retval))
	write(retval);
}
