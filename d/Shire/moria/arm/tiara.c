inherit "/std/armour";
#include "defs.h";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_armour()
{
    set_name("tiara");
    add_name("_moria_tiara_");
    set_adj( ({ "beautiful", "emerald" }) );
    set_short("beautiful emerald tiara");
    set_long(
	"You are looking at an astonishingly beautiful tiara! It is " +
	"inset with green emeralds which sparkle in the light. Obviously " +
	"an item befit a princess of high rank. It must be worth " +
	"a lot!\n");
    set_ac(12);
    set_am(0);
    set_at(A_HEAD);
    set_af(TO);

    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 140);
    add_prop(OBJ_I_VALUE, 3777);
}

wear(object to)
{
    ENV(to)->add_subloc("_moria_tiara_look", this_object());
}

remove(object to)
{
    ENV(to)->remove_subloc("_moria_tiara_look");
}

string
show_subloc(mixed subloc, object on, object who)
{
    if (subloc!="_moria_tiara_look")
	return "";
    if (who->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";
    if (!query_worn())
	return "";
    if (who==ETO)
	if (who->query_gender() == 1)
	    return "You look terribly beautiful with your emerald tiara!\n";
        else
	    return "You look quite silly wearing that tiara...\n";
    else
	if (ETO->query_gender() == 1)
	    return CAP(HE_SHE(ETO))+" looks beutiful wearing the emerald tiara!\n";
	else
	    return CAP(HE_SHE(ETO))+" looks quite silly wearing that tiara...\n";
}



