inherit "/std/shadow";

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <state_desc.h>
#include <stdproperties.h>
#include <wa_types.h>

string gName;
string gNonmet_name;
string gMet_name;
string gPresentation;
int gGender;
string gRace;

void
setup_shadow()
{
    set_alarm(0.0, 0.0, "shapechange");
}

private void
shapechange()
{
    object *tmp = users();
    object *all;
    int i;

    all = tmp + ({ });

/*
    tell_room(E(shadow_who), "A flash of light causes you to cover your "+
      "eyes momentarily.\n", ({ shadow_who }));
    if (shadow_who->query_name() == "Morrigan")
	shadow_who->catch_msg("You wiggle your nose mischievously.\n");
*/

    for (i = 0; i < sizeof(tmp); i++)
    {
	if (tmp[i]->query_wiz_level())
	    all -= ({ tmp[i] });
    }

    i = random(sizeof(all));

    gName = all[i]->query_name();
    gNonmet_name = all[i]->query_nonmet_name();
    gMet_name = all[i]->query_met_name();
    gPresentation = all[i]->query_presentation();
    gGender = all[i]->query_gender();
    gRace = all[i]->query_race_name();

    set_alarm(60.0, 0.0, "shapechange");
}

string
query_race_name()
{
    if (gRace)
	return gRace;

    return shadow_who->query_race_name();
}

int
query_gender()
{
    if (gGender)
	return gGender;

    return shadow_who->query_gender();
}

string
query_presentation()
{
    if (gPresentation)
	return gPresentation;

    return shadow_who->query_presentation();
}

string
query_met_name()
{
    if (gMet_name)
	return gMet_name;

    return shadow_who->query_met_name();
}

string
query_name()
{
    if (gName)
	return gName;

    return shadow_who->query_name();
}

string
query_nonmet_name()
{
    if (gNonmet_name)
	return gNonmet_name;

    return shadow_who->query_nonmet_name();
}

public varargs string
query_the_name(object pobj)
{
    string pre = "", aft = "";

    if (!objectp(pobj))
	pobj = previous_object(-1);

    if (shadow_who->query_prop(OBJ_I_HIDE))
    {
	pre = "[";
	aft = "]";
    }
    if (shadow_who->query_prop(OBJ_I_INVIS))
    {
	pre = "(";
	aft = ")";
    }

#ifdef MET_ACTIVE
    if (shadow_who->notmet_me(pobj))
	return pre + " " + query_nonmet_name() + aft;
    else
#endif
	return pre + query_met_name() + aft;
}

public varargs string
query_The_name(object pobj)
{
    return capitalize(query_the_name(pobj));
}

