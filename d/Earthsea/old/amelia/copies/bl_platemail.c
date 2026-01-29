inherit "/std/armour.c";



#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 50

static int chunks_of_flesh = 0;


string
flesh_desc();

void
create_armour()
{
    set_name("platemail");
    set_pname("platemails");

    set_adj("blackened");
    set_adj("spiked");

    set_short("blackened spiked platemail");
    set_pshort("blackened spiked platemails");

    set_long("A blackened platemail. Blackened to make it look terrifying, " +
      "this platemail offers quite a lot of protection. Heavily " +
      "reinforced and sturdily constructed, it would take quite a " +
      "lot to penetrate this armour. The protruding spikes covering " +
      "the entire armour are long and sharp protecting the wearer " +
      "like the porcupine and his coat. These spikes must be long " +
      "than an arm. They can " +
"probably really hurt someone. " + "@@flesh_desc@@" +
      "A commander's emblem " +
      "decorates the the front of the armour.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_BODY || A_ARMS || A_LEGS);
    set_am( ({1,0,1}) );

    add_prop(OBJ_I_WEIGHT, 9600 + (random(50) -  25));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(100) +
      1000);

}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}


int
got_hit(int hid, int ph, object att, int aid, int dt, int dam)
{

    int dam_lvl;
    att->heal_hp(-1 * dam);

    dam_lvl = dam / att->query_hp();


    if (ph == 0)
    {
	att->catch_msg("You hurt yourself " +
	  "slightly as you hit the spikes of " +
	  "the blackened spiked platemail.\n");
	query_worn()->catch_msg(QCTNAME(att) + " hurts " +
	  att->query_objective() + "self " +
	  "slightly as " +
	  att->query_pronoun() +
	  " hits the spikes of the blackened " +
	  "spiked platemail.\n");
	att->tell_watcher(QCTNAME(att) + " hurts " +
	  att->query_objective() + "self " +
	  "slightly as " +
	  att->query_pronoun() +
	  " hits the spikes of the blackened " +
	  "spiked platemail.\n", att);
    }
    if (ph > 0)
    { 
	att->catch_msg("You " +
	  "begin to trickle blood as the spikes " +
	  "of the blackened spiked platemail pierce " +
	  "into you.\n");
	query_worn()->catch_msg(QCTNAME(att) +
	  " begins to trickle blood as the spikes " +
	  "of the blackened spiked platemail pierce " +
	  "into " + att->query_objective() + ".\n");
	att->tell_watcher(QCTNAME(att) +
	  "begins to trickle blood as the spikes " +
	  "of the blackened spiked platemail pierce " +
	  "into " + att->query_objective + ".\n", att);
    }
    else if (dam_lvl > 50)
    {
	++chunks_of_flesh;
	att->command("scream");
	att->catch_msg(QCTNAME(query_worn()) + " grins at you as you " +
	  "scream in agony while a chunk of " +
	  "your flesh is ripped away from you.\n");
	query_worn()->catch_msg("You grin at " + QCTNAME(att) +
	  " as " + QCTNAME(att) +
	  " screams in agony while a chunk of " +
	  att->query_possessive() + 
	  " flesh is " +
	  "ripped away from " + 
	  att->query_objective()+ ".\n");
	att->tell_watcher(QCTNAME(query_worn()) + " grins at " + 
	  QCTNAME(att) +
	  " as " + QCTNAME(att) +
	  " screams in agony while a chunk of " +
	  att->query_possessive + " flesh is " +
	  "ripped away from " + 
	  att->query_objective, att);
    }

    hits++;
    if (F_ARMOUR_CONDITION_WORSE(hits, arm_ac, likely_cond))
    {
	hits = 0;
	set_condition(query_condition() + 1);
    }

    return 0;

}

string
flesh_desc()
{
    switch(chunks_of_flesh)
    {
    case 0:
	return " ";
	break;
    case 1:
	return " A chunk of flesh is stuck on the spikes. ";
	break;
    case 2..4:
	return " A couple chunks of flesh decorate the spikes. ";
	break;
    case 5..10:
	return " The spikes are littered with chunks of flesh. ";
	break;
    default:
	return " The entire armour is bloodied with chunks of flesh. ";
    }
}



