#include "defs.h"
#include <stdproperties.h>
inherit "/d/Shire/healers/lib/spell/effect";
inherit "/d/Shire/moria/skills/fumble";

int see_val;
#define SUBLOC "_blind_effect_subloc_"
#define FUMBLE_MSG "Your eyes hurts!!\nYou are temporarily blinded!\n"
#define MET_SHORT " (blinded)"
#define NONMET_SHORT " blinded "

//qme = shadow_who();

void
notify_dispel()
{
    qme()->catch_msg("AH!! Finally! You can see again!\n");
    qme()->command("laugh happ");
    qme()->command("shout I CAN SEE AGAIN!!!!");
    qme()->command("flip");
    qme()->remove_subloc(SUBLOC);
    remove_cont_fumble(qme(), FUMBLE_MSG);
    ADD_PROP(qme(), LIVE_I_SEE_DARK, -see_val);
}

string
show_subloc(mixed subloc, object on, object who)
{
    if (subloc!=SUBLOC)
	return qme()->show_subloc(subloc, on, who);
    if (who->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";
    if (who == on)
	return "";
    else
	return CAP(HIS_HER(qme())) + " eyes seems scorched!!!\n";
}

int
init_effect(object spell, object caster, int res)
{
    if(!living(qme()) || !living(caster) || !spell)
	return 0;

    set_element(ELEMENT_DEATH);
    set_secondary_element(ELEMENT_FIRE);
    //set_duration(MAX(res, 1000)/100 * 60);
    set_duration(30 + random(70));
    set_power(1+res/10);
    set_reducible(1);
    add_cont_fumble(qme(), FUMBLE_MSG);
    qme()->add_subloc(SUBLOC, TO);
    see_val = -100; /* Completely blind! */
    ADD_PROP(qme(), LIVE_I_SEE_DARK, see_val);
    qme()->catch_msg("You feel an intense ache in your eyes!!\n");
    qme()->catch_msg("You have been blinded by that light!\n");
    qme()->command("scream");    return 1;
}
string
query_met_name()
{
    return qme()->query_met_name()+" (blinded)";
}
string
query_nonmet_name()
{
    return "blinded "+qme()->query_nonmet_name();
}

varargs public mixed
short(object who)
{
	string desc, blind;
	if(qme()->nonmet_me(who))
	{
		desc = qme()->query_nonmet_name();
		blind = "blinded "+ desc;
	}
	else 
	{
		desc = qme()->query_met_name();
		blind = desc + " (blinded)";
	}
	if (qme()->query_prop(LIVE_S_EXTRA_SHORT))
	blind += " and "+qme()->query_prop(LIVE_S_EXTRA_SHORT);
	return blind;
}
/*
string
query_title()
{
    string title = qme()->query_title();
    if(strlen(title))
	return "the Blind, "+title;
    else
	return "the Blind";
}
*/
/*
string
short(object who)
{
	string desc = qme()->query_short();
	if(strlen(desc))
	return short() +" (blinded)";
	else
	return "blinded "+short();
}
*/
