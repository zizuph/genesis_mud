inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

int adjusted = 0; /*The bandana is not adjusted */

create_armour()
{
    set_name("bandana");
    set_adj("black");
    set_short("black bandana");
    set_long("This bandana consists of a cloth of black " +
      "silk, lined with silver thread. A small silver rune marks the front of the cloth.\n");
    add_item(({"small silver rune","rune","silver rune"}),
      "This silver rune looks like the symbol for infinity.\n");
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This silk cloth has been enchanted by elven spellweavers " +
	"of Silvanesti, allowing the person who wears this " +
	"cloth the ability to see in the dark when the cloths silver infinity rune has been " +
	"adjusted so that it sits above the eyes. This ability is rather mentally taxing, to " +
	"the wearer.\n", 40}));
    add_prop(MAGIC_AM_MAGIC, ({15,"enchantment"}));
    set_ac(2);
    set_am(({0,0,0}));
    set_at(A_HEAD);
    set_af(TO);
    add_prop(OBJ_I_VALUE, 1700);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 200);
    add_cmd_item(({"bandana","black bandana"}),"adjust","@@adjust_bandana");
}

int
adjust_bandana()
{
    //wearer = E(TO);
    if (!objectp(wearer))
	return 0;
    if (!wearer->query_prop(LIVE_I_IS))
	return 0;
    if(TO->query_worn())
    {
	if(adjusted)
	{
	    wearer->catch_msg("The rune is already positioned over your eyes.\n");
	    return 1;
	}
	wearer->catch_msg("You adjust the black bandana so that the silver infinity " +
	  "rune sits above your eyes.\nYou blink to refocus your eyes.\n");
	wearer->add_prop(LIVE_I_SEE_DARK, wearer->query_prop(LIVE_I_SEE_DARK) + 1);
	adjusted = 1;
	set_alarm(1.0, 0.0, "mana_drain");
	return 1;
    }
}

mixed
wear(object what)
{
    return 0;
}

mixed
remove(object what)
{

    //wearer = E(TO);
    if (!objectp(wearer))
	return 0;
    if (!wearer->query_prop(LIVE_I_IS))
	return 0;
    if(adjusted)
    {
	wearer->add_prop(LIVE_I_SEE_DARK, wearer->query_prop(LIVE_I_SEE_DARK) - 1);
	adjusted = 0;
    }
    return 0;
}

void
mana_drain()
{
    if(!adjusted)
	return;
    if(wearer->query_mana() < 10)
    {
	write("The bandana begins to unravel!\n");
	remove_object();
	write("The bandana mysteriously vanishes!\n");
	return;
    }
    if((wearer->query_max_mana() /50) < 20)
	wearer->add_mana(-10);
    else
	wearer->add_mana(-(wearer->query_max_mana() /50));
    set_alarm(60.0, 0.0, "mana_drain");
    return;
}
