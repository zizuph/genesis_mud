inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"

create_weapon()
{
    set_name("partisan");
    set_adj("bronzed");
    add_adj("impressive");
    add_adj("metal");  /* added by Gorboth, July 2007 */
    set_short("impressive bronzed partisan");
    set_long("This weapon looks very similar to a long-handled spear-like "+
      "halberd, although its large axe-like head has been bronzed " +
      "and engraved with mysterious runes.\n");
    add_item(({"runes","mysterious runes"}),
      "The runes twist and turn on the head of this weapon like "+
      "snakes, and you are unable to make out what "+
      "they say.\n");
    set_default_weapon(35,47, W_POLEARM, W_SLASH | W_IMPALE, W_BOTH);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This polearm is one of two weapons traditionally used by the gatekeepers of Kalaman. " +
	"Enchantments placed upon this weapon in Ages past give it an increased ability to damage " +
	"opponents, as well as gifts the wielder with great skill in defending oneself with this " +
	"weapon.\n",35}));
    add_prop(MAGIC_AM_MAGIC,({40,"enchantment"}));
    set_wf(TO);
    seteuid(getuid(TO));
}

void
wield_message1()
{
    if(E(TO) != wielder)
	return;
    wielder->catch_msg("You spin the impressive bronzed partisan, feeling more " +
      "confident in your abilities to defend yourself.\n");
    tell_room(E(wielder), QCTNAME(wielder) + " spins the impressive bronze partisan " +
      "confidently.\n", wielder);
}

mixed
wield(object what)
{
    TP->set_skill_extra(23, 7);
    wielder = TP;
    set_alarm(1.0, 0.0, "wield_message1");
    return 0;
}
mixed
unwield(object what)
{
    TP->set_skill_extra(23, 0);
    return 0;
}
