//
// Leus Spell - cause the guild staff to glow with lamp light
//
#include "defs.h"
inherit GEN_MAGIC+"spell";
inherit SR_SPELLS+"srspell";

object  staff;

public varargs int
config_spell(object caster, object *targets, string arg)
{
   set_spell_name("leus");  
   set_spell_desc("Illumination");
   set_spell_time(5);
   set_spell_task(TASK_SIMPLE);				//default TASK_ROUTINE
   set_spell_element(SS_ELEMENT_FIRE,  20); //element, required level
   set_spell_form(SS_FORM_ENCHANTMENT, 20), //form,    required level
   set_spell_mana(100);						//amt of mana used
   set_spell_mana_fail(33);					//%mana deducted 4 fails (def=33)

   //set_spell_ingredients(mixed ingrs);
   //set_spell_optional_ingredients(mixed ingrs);
   //set_spell_offensive(int)

   //set_spell_fail(mixed);					//actions if spell fails, def=0
   //set_spell_resist(function f)			//resist rtn, def=spell_resist()

   //set_spell_resist_task(TASK_FORMIDABLE);//default 
   //set_spell_stationary(int);				//default true
   //set_spell_vocal(int);					//caster must speak; def true
   //set_spell_visual(int);					//caster must see; def true; 
   //set_spell_peaceful(int);				//must be peaceful? def false
   //set_spell_no_reveal(int);				//reveal hidden caster; def no
   //set_spell_target(function);			//targeting function, use def
   //set_spell_target_verify(function)		//ver. targ still valid@cast,def0
   //set_spell_exp_factor(int)
        //Set a percentage of normal general exp this spell is to
        //give the caster. def 100
   return 0;
}


//--------------------------------------------------------------------------
// query_casting_success - check guild requirements for casting
//--------------------------------------------------------------------------
static int
query_casting_success(object caster)
{
	string sshort;
	string msg     = "OK";
	int    harmony =  (caster->query_skill(SS_SR_HARMONY));
	int    aura;
	int    anointed;

	//check saggart properly vested, wielding flamming staff, & enough harmony
	staff   = present(SR_STAFF_ID,caster);
	if (objectp(staff))
		{
		aura     = staff->query_aura();
		sshort   = staff->query_short();
		anointed = staff->query_prop(SR_OIL_ANOINTED);
		}

	if (!vested(caster))		 
		msg = "You are not properly vested to invoke the powers of Ardaugh!";
	else if (!objectp(staff)) 
		msg = "You do not have a staff of the Order!";
	else if (aura)
		msg = "Your "+sshort+" is already empowered!";
	else if (!anointed)
		msg = "Your "+sshort+" must be anointed.";
	else if (anointed != BL_BEATHA_OIL)
		msg = "Your "+sshort+" is not anointed with the correct oil!";
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
// resolve_spell - what ELSE happens when spell is successfully cast
//--------------------------------------------------------------------------
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
	int   harmony = (caster->query_skill(SS_SR_HARMONY));
	float fire    = itof(caster->query_skill(SS_ELEMENT_FIRE));
	float ench	  = itof(caster->query_skill(SS_FORM_ENCHANTMENT));
	float spcraft = itof(caster->query_skill(SS_SPELLCRAFT));
	float ints	  = itof(caster->query_stat(SS_INT));
	float wis     = itof(caster->query_stat(SS_WIS));
	int   seconds;
 
	//::resolve_spell(caster, targets, resist, result);

	//calculate minutes staff will remain lit, and light it, max 10mins=600sec
	seconds = ftoi(((600.0 * (ints+wis+fire+ench+spcraft))/500.0));
	staff->illuminate(1,seconds);

	//reduce harmony
	harmony -= SR_SPELL_HARMONY_LEUS;
	caster->set_skill(SS_SR_HARMONY,harmony);

	//remove anointing
	staff->remove_prop(SR_OIL_ANOINTED);
}
