//--------------------------------------------------------------------------
// Stua -  Arc of Light 
//         Attack spell for the saggarts
//		   Must be wielding red-glowing staff
// History:
// 01/07/00  Zima		Created
//--------------------------------------------------------------------------
#include "defs.h"
inherit GEN_SPELLS+"bolt";
inherit SR_SPELLS+"srspell";
 
#include <ss_types.h>
#include <composite.h>
#include <macros.h>


//--------------------------------------------------------------------------
// config_spell
//--------------------------------------------------------------------------
public varargs int
config_spell(object caster, object *targets, string argument)
{
    ::config_spell(caster, targets, argument);

    set_spell_element(SS_ELEMENT_FIRE, 50);
    set_bolt_pen(800);
	set_spell_name("stua");
    set_spell_desc("Arc of Light");
    return 0;
}

//--------------------------------------------------------------------------
// query_casting_success - check guild requirements for casting
//--------------------------------------------------------------------------
static int
query_casting_success(object caster)
{
	object staff   = present(SR_STAFF_ID,caster);
	string sshort;
	string msg     = "OK";
	int    harmony =  (caster->query_skill(SS_SR_HARMONY));
	int    aura;
	int	   anointed;

	//check saggart properly vested, wielding flamming staff, & enough harmony
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
	else if (!(staff->query_wielded()))
		msg = "You must be wielding the "+sshort+"!";
	else if (!aura)
		msg = "Your "+sshort+" is not empowered!";
	else if (aura != 2)
		msg = "Your "+sshort+" is not properly empowered!";
	else if (!anointed)
		msg = "Your "+sshort+" must be anointed!";
	else if (anointed != BL_BEATHA_OIL)
		msg = "Your "+sshort+" is not anointed with the correct oil!";
	else if (harmony < SR_SPELL_HARMONY_STUA)
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
// desc_bolt_damage - describe the damage to the caster, target and audience
//-------------------------------------------------------------------------- 
public void
desc_bolt_damage(object caster, object target, mixed *result)
{
    string how;

    switch (result[3])
    {
        case 0..20:    how = "slightly singed";  break;
        case 21..50:   how = "singed";			 break;
        case 51..80:   how = "slightly burned";  break;
        case 81..110:  how = "burned";           break;
        case 111..140: how = "scorched";		 break;
        case 141..170: how = "charred";          break;
        default:       how = "incenerated";      break;
    }

    target->catch_tell("You are " + how + " by the arc of light!\n");
    caster->catch_tell(target->query_The_name(caster) + " appears " +
			how + " by the arc of light!\n");
	tell_room(ENV(caster),QCTNAME(target) + " appears " + how +
		      " by the arc of light!\n", ({caster, target}));
	/*
    caster->tell_watchers(QCTNAME(target) + " appears " + how + 
		    " by the arc of light!\n", target);
	*/
}


//--------------------------------------------------------------------------
// desc_bolt_miss - describe a miss to the caster, target and audience
//--------------------------------------------------------------------------
public void
desc_bolt_miss(object caster, object target)
{
    string bolt = "The arc of light misses ";

    target->catch_tell(bolt + "you.\n");
    caster->catch_tell(bolt + target->query_the_name(caster) + ".\n");
    caster->tell_watcher_miss(bolt + QCTNAME(target) + ".\n", target);
}

//--------------------------------------------------------------------------
// desc_bolt_cast - describe a successful casting to caster,targ,audienc
//--------------------------------------------------------------------------
public void
desc_bolt_cast(object caster, object *targets)
{
    string msg, pos, bolt, sdesc;
	object staff=present(SR_STAFF_ID,caster);

    pos = caster->query_possessive();
	if (objectp(staff))
		sdesc=(staff->query_short());
	else //something's wrong!
		sdesc="glowing staff";

    msg = " swings " + pos + " " + sdesc;
 
    caster->catch_tell("You swing your " + sdesc + " through the air!\n" +
		               "An arc of light hurls toward "+
                       FO_COMPOSITE_ALL_LIVE(targets, caster) + 
					   "!\n");

    msg = " swings "+pos+" "+sdesc+" through the air!\n"+  
		  "An arc of light hurls toward ";

    targets->catch_msg(({
        caster->query_Met_name()                + msg + "you!\n",
        capitalize(caster->query_nonmet_name()) + msg + "you!\n",
        "" }));
                           
    caster->tell_watcher(QCTNAME(caster) + msg + QCOMPLIVE +"!\n", targets);
}

//--------------------------------------------------------------------------
// resolve_spell - what ELSE happens when spell is successfully cast
//--------------------------------------------------------------------------
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
	int    harmony = (caster->query_skill(SS_SR_HARMONY));
	object staff=present(SR_STAFF_ID,caster);
 
	//do standard bolt damage
	::resolve_spell(caster, targets, resist, result); 

	//reduce harmony
	harmony -= SR_SPELL_HARMONY_STUA;
	caster->set_skill(SS_SR_HARMONY,harmony);

	//remove anointing on staff
	staff->remove_prop(SR_OIL_ANOINTED);
}

