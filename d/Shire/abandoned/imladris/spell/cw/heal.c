#include "defs.h"

inherit SPELL_FILE;

create_spellobj()
{
    set_form(FORM_CONJURATION, 10);
    set_elem(ELEMENT_LIFE, 10);
    set_spell_name("healing");
    add_prop(SPELL_S_DESC,
	"Heals a being. Can be yourself or another living.");
    add_prop(SPELL_S_SYNTAX, "[on] <living>");
}

object *
area_of_effect(string str)
{
    object *targets;

    if(!str)
	return 0;

    targets = parse_livings(str, "[on]", 1);

    notify_fail("Healing on who?\n"+query_syntax());
    return targets;
}

void
heal_one(object tp, object ob, int amount)
{
    string how;
    int hp;

    hp = HP(ob);
    ob->heal_hp(amount);
    hp = HP(ob) - hp;
    switch (hp*100/MAX_HP(ob))
    {
	case 0..5:   how = "a little bit";	break;
	case 6..10:  how = "a little";		break;
	case 11..20: how = "somewhat";		break;
	case 21..30: how = "quite";		break;
	case 31..50: how = "much";		break;
	case 51..70: how = "very much";		break;
	case 71..90: how = "increadibly";	break;
        default:     how = "divinely";	        break;
    }
    tellem(tp, ob,
	"#He #{feel that you are;looks} "+how+" #{healthier;better} now.\n");

    if (MAX_HP(ob)-HP(ob)< 10)
	if (tp != ob)
	    tp->catch_msg(QCTNAME(ob)+" is completely healed.\n");
	else
	    tp->catch_msg("You are completely healed.\n");
}

mixed
cast_healing(object *targets, int power)
{
    int i, no, amount;
    int *powers;
    int heal_power;  /* A power of spell of 1 equals 20 hitpoints.
			I.e.: A power of 100 will heal 2000 hps.   */

    targets = FILTER_CAN_SEE(targets, caster);

    heal_power = power * 20;

    if (caster->query_wiz_level()) {
	write("Wizinfo: power   = " + power + "\n");
	write("         heal_hp = " + heal_power + "\n");
    }

    no = sizeof(targets);

    if (no==0)
    {
	caster->catch_msg("You cast a healing spell, but the target is not here.\n");
	return 0;
    }

    spell_msg(1);

    if (no==1)
	heal_one(caster, targets[0], heal_power);
    else {
	powers = rnd_dist(no, heal_power);
	i = no;
	while(--i)
	    heal_one(caster, targets[i], powers[i]);
    }
}

void
do_instant_effect(object *targets, int power)
{
    string retval;

    retval = cast_healing(targets, power);
    if(stringp(retval))
	write(retval);
}
