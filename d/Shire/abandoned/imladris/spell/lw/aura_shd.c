#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit EFFECT_SHADOW_FILE;

#define SUBLOC "_aura_subloc_"

//qme = shadow_who();

int class;

mixed
init_effect(object spell_object, object caster, int result)
{
	//set_name("_aura_object_");
    set_element(ELEMENT_FIRE, 10);
    set_secondary_element(ELEMENT_LIFE);
    //set_form(FORM_CONJURATION, 10);
	set_duration(60);
    //set_duration(MAX(caster->query_spell_level(), 25) * 10);
    set_power(MAX(result/10+1, 100));
    set_strength(0, 100);
    set_reducible(1);
    set_remove_on_dispel(0);
    class = spell_object->query_spell_class();

    qme()->add_subloc(SUBLOC, TO);
    qme()->catch_msg("You suddenly appear very powerful!\n");

    tell_room(environment(qme()),QCTNAME(qme())+
    " suddenly appears very powerful!\n",qme());

    return 1;
}

void
notify_dispel()
{
    qme()->catch_msg("You seem to have lost your awesome appearance.\n");
    tell_room(environment(qme()),QCTNAME(qme())+" seems to have lost "+HIS_HER(qme())+
	" awesome appearance.\n", qme());
    qme()->remove_subloc(SUBLOC);
}

int
proc()
{
    if(class>3)
    return 20;
    else
    return class*5;
}
/*   Reducing: Class I	    0-5 %
	       Class II	    0-10 %
	       Class III    0-15 %
	      Classes above 0-20 %
*/
int
has_protection()
{
    return 1;
}
public void
heal_hp(int amount)
{
    int reduce = query_power();
    if (amount >= 0)
    {
	qme()->heal_hp(amount);
	return;
    }
    reduce = MAX(reduce, 100);
    qme()->heal_hp(amount - amount * reduce * proc() / 10000);
}
string
show_subloc(mixed subloc, object on, object who)
{
    if (subloc!=SUBLOC)
	return qme()->show_subloc(subloc, on, who);
	if (who->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";
    if(who == on)
	return "You have a powerful appearance!\n";
    else
	return CAP(HE_SHE(qme()))+" shows an awesome appearance!\n";
}
/*
string
query_title(object who)
{
    string normal_title = qme()->query_title();
    if(living(qme()))
	if(strlen(normal_title))
	    return "the Powerful, "+normal_title;
	else
	    return "the Powerful";
    return qme()->query_title();
}
*/
