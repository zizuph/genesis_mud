#include "defs.h"
#include <stdproperties.h>

inherit EFFECT_SHADOW_FILE;
inherit TELLEM_FILE;

int
init_effect(object spell_object, object caster, int result)
{
	set_element(ELEMENT_FIRE);
	set_secondary_element(ELEMENT_LIFE);
	set_duration(MAX(caster->query_spell_level(), 25) * 60);
	set_power(MAX(result/10+1, 100));
	set_strength(0, 100);
	set_reducible(1);
	set_remove_on_dispell(1);

	class = spell_object->query_spell_class();

	qme()->add_subloc(SUBLOC, TO);
	qme()->catch_msg("You are suddenly surrounded by a strange light.\n");

	tell_room(ENV(qme()),
	QCTNAME(qme())+" is al of a sudden surrounded by a divine light!\n", qme());
}	

void
notify_dispel()
{
	qme()->catch_msg("The light shield protecting you fades away.\n");
	qme()->catch_msg("You loose it's protection.\n");
	tell_room(ENV(qme()),
	" looses "+HIS_HER(qme())+" protection from the divine light as it suddenly disappears.\n", qme());
	qme()->remove_subloc(SUBLOC);
}

int
proc()
{
	if(class>5)
	return 30;
	else
	return class*5;
}

int
has_protection()
{
	return 1;
}

public void
heal_hp(int amount)
{
	int reduce = query_power();

	if(amount >= 0)
	{
		qme()->heal_hp(amount);
		find_player("odin")->catch_msg("Amount : "+amount+".\n");
		return;
	}

	reduce = MAX(reduce,100);
	qme()->heal_hp(amount - amount *reduce*proc()/10000);
}

string
show_subloc(mixed subloc, object who, object on)
{
	if(subloc !=SUBLOC)
	return "";
	if(who==qme())
	return "You are protected by a divine light!\n");
	else
	return CAP(HE_SHE(qme()))+" is surrounded by a strange divine light!\n");
}


