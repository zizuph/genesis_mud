// Navarre March 19th 2010, refactored to add correct wield/unwield handling.

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

void
create_weapon()
{
    set_name("mace");
    set_adj("black");
    add_adj("flaming");
    set_short("@@short_descr");
    set_long("@@long_descr");
    set_default_weapon(42,42, W_CLUB, W_BLUDGEON, W_ANYH);
    set_magic_spellpower(42);
    set_spellpower_elements(({
        SS_ELEMENT_DEATH, SS_ELEMENT_AIR, SS_ELEMENT_WATER, SS_ELEMENT_FIRE
    }));

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({ 50, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"Once a fine weapon crafted by the weaponsmiths "+
	"of Istar, it survived the Cataclym in the hands of a fallen knight of Solamnia " +
	"who was caught in the curse of the death knight Lord Soth. The curse has "+
	"transferred fell powers to the weapon, making it hit harder and more "+
	"regularly than a normal mace, as well as enhance the spell power of " +
        "the wielder.\n",15}));

    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VOLUME, 7000);

    set_wf(TO);
    seteuid(getuid(TO));
}

string
short_descr()
{
    if(query_wielded())
    {
	return "flaming black mace";
    }
    return "black mace";
}

string
long_descr()
{
    if(wielded)
    {
	return "A weapon of black steel, its head carved with skulls "+
               "where demonic fires rage out from their screaming mouths, "+
               "surrounding the head of the mace.\n";
    }
    return "A mace of black steel, its head carved with skulls.\n";
}

mixed
wield(object what)
{
    write("Hellish flames engulf the black mace with a roar!\n");
    say("Flames suddenly engulf the black mace wielded by " +
        QTNAME(TP) + " with a hellish roar!\n");
    return 0;
}

mixed
unwield(object what)
{
    if (wielder)
    {
        wielder->catch_tell("The hellish flames suddenly die down and " +
            "disappear as you release your grip of the black mace.\n");

        tell_room(environment(wielder), "The hellish flames surrounding " +
            QTNAME(wielder) + "'s black mace suddenly " +
            "die down and disappear.\n", wielder);
    }
    return 0;
}

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}