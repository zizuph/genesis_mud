//--------------------------------------------------------------------------
// srspell - general spellcasting functions 
//
// 1/7/00   Zima     Created
//--------------------------------------------------------------------------
#include "defs.h"

//--------------------------------------------------------------------------
// vested - is the saggart properly vested to cast spells?
//--------------------------------------------------------------------------
int vested(object p)
{
	int level;
    if (!p->is_saggart()) return 0;
	//finish it!


	return 1;
}

//--------------------------------------------------------------------------
// break_spell - general message for breaking a spell
//--------------------------------------------------------------------------
public void
break_spell(object caster, object breaker)
{
	caster->catch_msg("Your harmonization is broken!\n");
}

//--------------------------------------------------------------------------
// abort_spell - general message for aborting a spell
//--------------------------------------------------------------------------
public void
abort_spell(object caster)
{
	caster->catch_msg("Your harmonization is broken!\n");
}

//--------------------------------------------------------------------------
// concentrate_msg
//--------------------------------------------------------------------------
public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell(	"You close your eyes and begin to harmonize "+
					    "with the powers of Ardaugh.\n");
	tell_room(ENV(caster),QCTNAME(caster)+" closes "+
		      (caster->query_possessive())+" eyes and begins to pray.\n",
			  caster);
}
 
