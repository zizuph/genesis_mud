inherit "/std/armour";
inherit "/lib/keep";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

#define ARMOUR_CLASS 1

void
create_armour()
{
    set_name("ring");
    set_pname("rings");

    set_adj("black-gem");
    add_adj("black");
    add_adj("gem");
    set_short("black-gem ring");

    set_long("This is a silver banded ring with a small black gem " +
      "adorning it. Carved along the band is the spidery language " +
      "of the Magi.\n");
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This ring was enchanted long ago by wizards now long forgotten. " +
	"It has the ability to suck the light from the wearers surroundings.\n",5}));
    add_prop(MAGIC_AM_MAGIC,({25,"enchantment"}));

    set_ac(ARMOUR_CLASS);
    set_at(A_ANY_FINGER);
    set_af(TO);

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 80);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS) + 1000);
}

/*
 * I've put the effects in separate, alarm-called functions,
 * because otherwise the changing of the light prop seems to
 * bug the player if the ring is dropped without removing it first.
 */

void
effect_on(object player)
{
    if (objectp(player))
    {
    tell_object(player, "The black-gem ring pulses once, and then " +
      "sucks the light around you into it!\n");
    if (environment(player))
    {
	tell_room(environment(player), "Darkness suddenly engulfs you!\n",
	  player);
    }
    }
    add_prop(OBJ_I_LIGHT, -1);
}

mixed
wear(object what)
{
    set_alarm(0.5,0.0,&effect_on(this_player()));
    return 0;
}

void
effect_off(object player)
{
    if (objectp(player))
    {
    tell_object(player, "The darkness disappears as the black-gem " +
      "ring is removed.\n");
    if (environment(player))
    {
	tell_room(environment(player),"The darkness surrounding you disperses, " +
	  "melting into the ground around you.\n",
	  player);
    }
    }
    add_prop(OBJ_I_LIGHT, 0);
}

mixed
remove(object what)
{
    set_alarm(0.5,0.0,&effect_off(this_player()));
    return 0;
}
