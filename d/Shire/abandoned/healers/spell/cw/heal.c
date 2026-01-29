#include "defs.h"
#include <filter_funs.h>

inherit SPELL_FILE;

create_spellobj()
{
    set_form(FORM_CONJURATION, 10);
    set_elem(ELEMENT_LIFE, 10);
    set_spell_name("healing");
	set_classes( ([1:5, , 2:10, 5:17, 10:25]) );
    set_desc("Heals a being. Can be yourself or another living.");
    set_syntax("[on] <living>");
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
	ob->catch_msg("You feel healthier now.\n");
	tell_room(ENV(ob),QCTNAME(ob)+" looks better now.\n", tp, ob);
	
/*    tellem(tp, ob,
	"#He #{feel that you are;looks} "+how+" #{healthier;better} now.\n");
*/
    if (MAX_HP(ob)-HP(ob)< 10)
	if (tp != ob)
	    tp->catch_msg(QCTNAME(ob)+" is completely healed.\n");
	else
	    tp->catch_msg("You are completely healed.\n");
}

mixed
cast_healing(object *targets, int power)
{
    int i, no, amount, sz, j, k;
    int *powers;
    int heal_power;  /* A power of spell of 1 equals 10 hitpoints.
			I.e.: A power of 100 will heal 1000 hps.   */

    targets = FILTER_CAN_SEE(targets, caster);
/* The spellcaster heals a maximum of element skill (100)
	+ spellcraft skill (100) * class of the spell (max 10)
	/ 100, which at present is 90 + 90 * 10 / 100;
	that would make it 1800 / 100, 18 as a maximum factor do calculate how much
    healed.
*/
	sz = caster->query_skill(SS_ELEMENT_LIFE) + 
	     caster->query_skill(SS_SPELLCRAFT);
	j  = sz * query_spell_class() / 100;

	heal_power = j;
	
    //heal_power = power * 10;

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
    else 
	{
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
