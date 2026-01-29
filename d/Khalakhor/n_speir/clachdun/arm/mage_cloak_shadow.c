#include <language.h>

inherit "/std/shadow";

static object gCloak;

public mixed
wear_arm(object arm)
{
    if (arm == gCloak)
	return shadow_who->wear_arm(arm);
    if (!gCloak->filter_armours(arm))
	return shadow_who->wear_arm(arm);

    return "The snowflakes of the "+gCloak->short()+" unexpectantly "+
    "shift and block your attempt to wear "+LANG_THESHORT(arm)+".\n";
}

void
set_cloak_object(object cloak)
{
    gCloak = cloak;
}

void
remove_clachdun_cloak_shadow()
{
    remove_shadow();
}
