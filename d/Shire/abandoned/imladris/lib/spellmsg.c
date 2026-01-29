#include <macros.h>
#include <language.h>
#include <composite.h>
#include <filter_funs.h>
#include "defs.h"

object *gOther;

string
other_desc()
{
    object to_who = previous_object(-2);
    object *oth;
    int pos = member_array(to_who, gOther);

    if(pos>=0)
    {
	oth = exclude_array(gOther, pos, pos);
	switch(sizeof(oth))
	{
	    case 0:
		return "you";
	    case 1:
		return "you, and "+QTNAME(oth[0]);
	    default:
		return "you, "+COMPOSITE_LIVE(oth);
	}
    }
    else
	return COMPOSITE_LIVE(gOther)+sprintf("%O", to_who);
}

string
other_desc_me()
{
    object to_who = previous_object(-2);
    object *oth;
    int pos = member_array(to_who, gOther);

    if(pos>=0)
    {
	oth = exclude_array(gOther, pos, pos);
	switch(sizeof(oth))
	{
	    case 0:
		return "and you";
	    case 1:
		return ", you, and "+QTNAME(oth[0]);
	    default:
		return ", you, "+COMPOSITE_LIVE(oth);
	}
    }
    else
	return COMPOSITE_LIVE(gOther)+sprintf("%O", to_who);
}


int
sees_fight(object ob)
{
    return ob->query_see_blood();
}

spell_message(object caster, mixed targ, string spell, int tell_all = 0)
{
    object *objs;
    object *livs;
    object *targets;
    object *watchers;
    object *can_see;
    string cast_on;
    string qname;

    if (objectp(targ))
	targets = ({ targ });
    else if (pointerp(targ))
	targets = targ;
    else
	targets = ({});

    qname = PO->query_prop(SPELL_S_NAME);
    if (stringp(qname) && qname != spell)
	spell = qname;

    objs = FILTER_DEAD(targets);
    livs = FILTER_LIVE(targets);
    watchers = FILTER_LIVE(all_inventory(ENV(caster))) - ({ caster });

    if(!tell_all)
	watchers = filter(watchers, "sees_fight", this_object());

    if(sizeof(objs)==0)
    {
	if(member_array(caster, livs)>=0)
	{
	    livs -= ({ caster });
	    watchers = FILTER_CAN_SEE(watchers, caster);
	    watchers -= livs;

	    if(sizeof(livs)==0)
	    {
		caster->catch_msg("You cast "+LANG_ADDART(spell)+" on yourself.\n");
		watchers->catch_msg(
		    QCTNAME(caster)+" casts a spell on "+
		    HIM_HER(caster)+"self.\n");
		return;
	    }
	    if(sizeof(livs)==1)
	    {
		caster->catch_msg(
		    "You cast "+LANG_ADDART(spell)+" on yourself and "+QTNAME(livs[0])+".\n");
		livs[0]->catch_msg(
		    QCTNAME(TP)+" casts a spell on you and "+HIM_HER(caster)+"self.\n");
		COMPOSITE_LIVE(livs);
		watchers->catch_msg(
		    QCTNAME(TP)+" casts a spell on "+HIM_HER(caster)+"self and "+QCOMPLIVE+".\n");
		return;
	    }

	    caster->catch_msg(
		"You cast "+LANG_ADDART(spell)+" on yourself, "+
		COMPOSITE_LIVE(livs)+".\n");
	    watchers->catch_msg(
		QCTNAME(caster)+" casts a spell on "+HIM_HER(caster)+"self, "+
		QCOMPLIVE+".\n");

	    gOther = livs;
	    livs->catch_msg(
		QCTNAME(caster)+" casts a spell on "+HIM_HER(caster)+"self"+
		VBFC_ME("other_desc_me")+".\n");
	    return;
	}
	else /* Caster not a target. */
	{
	    watchers = FILTER_CAN_SEE(watchers, caster)-livs;

	    caster->catch_msg(
		"You cast "+LANG_ADDART(spell)+" on "+COMPOSITE_LIVE(livs)+".\n");
	    watchers->catch_msg(
		QCTNAME(caster)+" casts a spell on "+QCOMPLIVE+".\n");
	    gOther = livs;
	    livs->catch_msg(
		QCTNAME(caster)+" casts a spell on "+VBFC_ME("other_desc")+".\n");
	    return;
	}
    }
    else /* Targets are objects. */
    {
	watchers = FILTER_CAN_SEE(watchers, caster);
	if (!sizeof(objs))
	{
	    caster->catch_msg("You cast " + LANG_ADDART(spell) + " spell!\n");
	    can_see->catch_msg(QCTNAME(caster)+" casts a spell!\n");
	    return;
	}
	else if(sizeof(objs)==1)
	{
	    caster->catch_msg(
		"You cast "+LANG_ADDART(spell)+" on "+LANG_THESHORT(objs[0])+".\n");

	    can_see = FILTER_CAN_SEE(watchers, objs[0]);

	    can_see->catch_msg(
		QCTNAME(caster)+" casts a spell on "+LANG_THESHORT(objs[0])+".\n");
	    (watchers-can_see)->catch_msg(
		QCTNAME(caster)+" casts a spell on something.\n");
	    return;
	}
	else
	{
	    caster->catch_msg(
		"You cast "+LANG_ADDART(spell)+" on "+COMPOSITE_DEAD(objs)+".\n");
	    watchers->catch_msg(
		QCTNAME(caster)+" casts a spell on "+QCOMPDEAD+".\n");
	    return;
	}
    }
}
