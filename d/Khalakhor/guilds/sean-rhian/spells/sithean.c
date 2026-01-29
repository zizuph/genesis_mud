//-------------------------------------------------------------------------
//							Sithean - Peace Spell
//-------------------------------------------------------------------------
// Description: invokes a spirit of peace which stops fighting and prevents
//              the start of fighting for a period of time.
// Preparation: cleric must have created a cloud of incense in the room
// Related Files: see comments of sithean_effect.c in this directory

#pragma strict_types
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

inherit GEN_MAGIC+"spell";
inherit SR_SPELLS+"srspell";

private object room;		//room where peace is made

//-------------------------------------------------------------------------
// config_spell
//-------------------------------------------------------------------------
public varargs int
config_spell(object caster, object *targets, string argument)
{
    ::config_spell(caster, targets, argument);
    set_spell_name("sithean");  
    set_spell_desc("Spirit of peace");
    set_spell_time(5);
    set_spell_mana(50);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_LIFE,  40);
    set_spell_form(SS_FORM_ENCHANTMENT, 40);
    set_spell_ingredients(({ }));
    set_spell_object(SR_SPELLS+"sithean_effect");
    return 0;
}

//--------------------------------------------------------------------------
// query_casting_success - check guild requirements for casting
//--------------------------------------------------------------------------
static int
query_casting_success(object caster)
{
	string msg       = "OK";
	int    harmony   =  (caster->query_skill(SS_SR_HARMONY));
	object cloud;
	object sith_eff;

	room  = ENV(caster);
	cloud = present(SR_INC_CLOUD,room);

	if (!vested(caster))		 
		msg = "You are not properly vested to invoke the powers of Ardaugh!";
	else if (!objectp(cloud))
		msg = "The spirits will not hear you without the fragrance of peace.";
	else if (objectp(cloud->query_spell_effect_object()))
		msg = "Spirits are already active amongst the wisps of incense here.";
	else if (harmony < SR_SPELL_HARMONY_LEUS)
		msg = "Your harmony with Ardaugh is displeasing.";

	//ok, if anything wrong
	if (msg != "OK")
	{
		caster->catch_msg(msg+"\n");
		return 0; // stops casting of spell
	}

	//now check standard stuff
	return (::query_casting_success(caster));
}

//--------------------------------------------------------------------------
// resolve_spell
//--------------------------------------------------------------------------
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object target  = targets[0];
	int    harmony = caster->query_skill(SS_SR_HARMONY);
	

    //inform caster & audience of success
	target->catch_msg("You raise your arms aloft and chant: "+
		              "Maigh Beannaithe deanta as Sithean!\n"); 
	tell_room(room,QCTNAME(target)+" raises "+(target->query_possessive())+
		           " arms and chants: Maigh Beannaithe deanta as Sithean!\n",
				   target);

	//the object stops all fighting in room & makes peace, informs cloud
    make_spell_effect_object(query_spell_object(),caster,room,resist,result);

	//reduce the caster's harmony
	caster->add_sr_harmony(-SR_SPELL_HARMONY_SITHEAN);
}
