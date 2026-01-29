//--------------------------------------------------------------------------
//								sithean_effect
//--------------------------------------------------------------------------
// Description:	spell effect object for the sithean spell
//				causes peace in the room - stops fighting, and sets 
//				ROOM_*_NO_ATTACK properties in the affected room
//
// NOTE:		start() invokes a function in an incense cloud, giving it
//				the max life of the cloud. The cloud object is responsible
//				for dispelling the effect of this spell, thus there is no
//				set_alarm for dispelling in this object
// 
// Related		- /d/Khalakhor/guilds/sean-rhian/spells/sith.c
// Files:		- /d/Khalakhor/guilds/sean-rian/tool/censor.c
//				- /d/Khalakhor/guilds/sean-rhian/objects/inc_cloud.c
//				- /d/Khalakhor/guilds/sean-rhian/objects/cake_incense.c
// History:
// 1/12/00	Zima	Created
//			
//--------------------------------------------------------------------------
#include <stdproperties.h>
#include <filter_funs.h>
#include "defs.h"
 
inherit  GEN_MAGIC+"spell_effect_object";

static int   in_effect=0;
static int   o_iattack;
static int   o_iMattack;
static mixed o_mattack;
static mixed o_mMattack;

varargs public int dispel_spell_effect(object dispeller); 

//--------------------------------------------------------------------------
// start - start the spell effect
//--------------------------------------------------------------------------
public int
start()
{
	object caster, rm, *liv, cloud;
	int    wis, inte, spcraft, life, ench, factor, i;
	float  sec;

	set_spell_effect_desc("peace");
 
	//get local objects
	rm      = query_spell_effect_target();
	caster  = query_spell_effect_caster();
	cloud	= present(SR_INC_CLOUD,rm);

	if ((!::start()) || (!objectp(cloud)))
	{
		remove_spell_effect_object();
		return 0;
	}

	//calculate #seconds peace will remain
	wis     = caster->query_skill(SS_WIS);
	inte    = caster->query_skill(SS_INT);
	spcraft = caster->query_skill(SS_SPELLCRAFT);
	life    = caster->query_skill(SS_ELEMENT_LIFE);
	ench    = caster->query_skill(SS_FORM_ENCHANTMENT);
	factor  = ((ench*50) + (life*25) + (spcraft*13) + (wis*8) + (inte*4))/100;
	sec     = itof(factor) * 6.0; //10 minutes max (6 = 600 sec / 100 for %)
    
	//save room's original _ATTACK props
	o_iattack  = rm->query_prop(ROOM_I_NO_ATTACK);
	o_mattack  = rm->query_prop(ROOM_M_NO_ATTACK);
	o_iMattack = rm->query_prop(ROOM_I_NO_MAGIC_ATTACK);
	o_mMattack = rm->query_prop(ROOM_M_NO_MAGIC_ATTACK);

	//change room's _ATTACK props
	in_effect=1;
	rm->add_prop(ROOM_I_NO_ATTACK,1);
	rm->add_prop(ROOM_M_NO_ATTACK,
		         "A powerful spirit of peace prevents your attack!\n");
	rm->add_prop(ROOM_I_NO_MAGIC_ATTACK,1);
	rm->add_prop(ROOM_M_NO_MAGIC_ATTACK, 
		         "A powerful spirit of peace prevents your attack!\n");

	//stop any ongoing fights
	liv = all_inventory(rm);
	liv = FILTER_LIVE(liv);
	for (i=0; i<sizeof(liv); i++) 
		liv[i]->stop_fight(liv);

	//inform room of arrival of "spirit"
	tell_room(rm,"A powerful spirit of peace descends upon this place!\n");

	//if caster is a wizard, give a little hint
	if (caster->query_wiz_level())
		caster->catch_msg("WIZINFO: #seconds of peace = "+ftoa(sec)+"\n");

	//schedule normal dispel - cloud will dispel when it dissipates
	cloud->set_spell_effect_object(TO,sec);
 
	return 1;
}

//--------------------------------------------------------------------------
// dispel_peace
//--------------------------------------------------------------------------
public void
dispel_peace()
{
   object rm = query_spell_effect_target();
   if (!in_effect) return;

   //remove the spell's effect
   in_effect=0;
   rm->add_prop(ROOM_I_NO_ATTACK,o_iattack);
   rm->add_prop(ROOM_M_NO_ATTACK,o_mattack);
   rm->add_prop(ROOM_I_NO_MAGIC_ATTACK,o_iMattack);
   rm->add_prop(ROOM_M_NO_MAGIC_ATTACK,o_mMattack);

   tell_room(rm,"There is a mysterious chilling breeze as if a mighty "+
                "presence has departed.\n");
}

//--------------------------------------------------------------------------
// dispel_spell_effect 
//--------------------------------------------------------------------------
varargs public int
dispel_spell_effect(object dispeller)
{
	dispel_peace();
	remove_spell_effect_object();
	return 1;
} 

