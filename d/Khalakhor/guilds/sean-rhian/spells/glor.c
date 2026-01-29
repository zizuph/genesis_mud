//--------------------------------------------------------------------------
// Glor spell - saggart to any-player tell spell
//              Copied from /d/Genesis/newmagic/spells/tell.c (by Shiva) 
//
// 1/9/00	Zima	Coded
//--------------------------------------------------------------------------
#pragma strict_types
#include <tasks.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <options.h>
#include <language.h>
#include "defs.h"
inherit  GEN_MAGIC+"spell";
inherit  SR_SPELLS+"srspell";

private static string message;
private static string response;

//--------------------------------------------------------------------------
// query_tell_message
//--------------------------------------------------------------------------
public static string
query_tell_message()
{
    return message;
}

//--------------------------------------------------------------------------
// spell_target_one_distant_living
//--------------------------------------------------------------------------
public object *
spell_target_one_distant_living(object caster, string str)
{
    object living;

    if (!strlen(str))
    {
        //caster->catch_tell("Target whom?\n");
		response = "The spirit requires a name of you.";
        return ({});
    }

    living = find_living(str);

    if (!objectp(living) ||
        (living->query_wiz_level() && living->query_invis()))
		{
		//caster->catch_tell("You do not sense " + LANG_POSS(str) +
		//        " presence in the realms.\n");
		response = "The spirit does not find "+str+" within the realms.";
		return ({ });
		}

    return ({ living });     
}

//--------------------------------------------------------------------------
// find_tell_targets
//--------------------------------------------------------------------------
public object *
find_tell_targets(object caster, string str)
{
    return spell_target_one_distant_living(caster, str);
}

//--------------------------------------------------------------------------
// target_tell
//--------------------------------------------------------------------------
public object *
target_tell(object caster, string str)
{
    string who, msg;
    object *targets;

    if (!strlen(str))
    {
        //caster->catch_tell("Tell whom what?\n");
		response = "The spirit requires a name of you.";
        return ({});
    }

    if (!sscanf(str, "%s %s", who, msg))
    {
        //caster->catch_tell("What message do you wish to convey?\n");
		response = "The spirit requires a verse to bear.";
        return ({});
    }

    if (sizeof(targets = find_tell_targets(caster, who)))
    {
        message = implode(explode(msg, " ") - ({ "" }), " ");
    }

    return targets;
}

//--------------------------------------------------------------------------
// query_casting_success - check requirements for casting
//--------------------------------------------------------------------------
static int
query_casting_success(object caster)
{
	string sshort;
	string msg     = "OK";
	int    harmony =  (caster->query_skill(SS_SR_HARMONY));
	int    aura;
	int    anointed;

	if (!vested(caster))		 
		msg = "You are not properly vested to invoke the powers of Ardaugh!";
	else if (harmony < SR_SPELL_HARMONY_GLOR)
		msg = "Your harmony with Ardaugh is displeasing.";
	else if (response != "OK")
		msg = response;

	//if anything wrong
	if (msg != "OK")
		{
		caster->catch_msg(msg+"\n");
		return 0; // stops casting of spell
		}

	//now check standard stuff
	return (::query_casting_success(caster));
}
 
//--------------------------------------------------------------------------
// config_spell
//--------------------------------------------------------------------------
public varargs int
config_spell(object caster, object *targets, string argument)
{
    set_spell_name("glor");  
    set_spell_desc("The spirit voice of air");
    set_spell_time(2);
    set_spell_mana(5);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_AIR, 30);
    set_spell_form(SS_FORM_TRANSMUTATION, 30);
    set_spell_ingredients(({}));
    set_spell_resist(0);
    set_spell_target(target_tell);
	response="OK";
    return 0;
}

//--------------------------------------------------------------------------
// resolve_spell
//--------------------------------------------------------------------------
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
	int    harmony = caster->query_skill(SS_SR_HARMONY);
	string msg="You dispatch the spirit of air to "+
		        targets[0]->query_met_name();

	// inform caster of success
    if (caster->query_option(OPT_ECHO))
        caster->catch_tell(msg + ".\n");
	else
		caster->catch_tell(msg + " saying: " +message+"\n");

	// deliver message to target
    targets[0]->catch_tell("A spirit of air sent from " +
		        caster->query_met_name()                +
				" appears to you saying: "              +
                query_tell_message() + "\n");

	//reduce harmony
	harmony -= SR_SPELL_HARMONY_GLOR;
	caster->set_skill(SS_SR_HARMONY,harmony);
}
