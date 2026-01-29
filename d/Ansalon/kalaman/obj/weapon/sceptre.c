inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit "/lib/keep";

object wielder;
int grip;

create_weapon()
{
    set_name("sceptre");
    set_adj("golden");
    set_short("golden sceptre");
    set_long("This golden sceptre is the rod borne by the noble ruler of the " +
      "city of Kalaman. A large circular head studded with gems adorns the top of " +
      "the mace-like weapon. Surprisingly, it is extremely well balanced, " +
      "so much so that it feels like an extension of ones own hand.\n");
    set_default_weapon(40, 35, W_CLUB, W_BLUDGEON, W_ANYH);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This sceptre has been enchanted so as not to be a burden to the wielder " +
	"of this weapon, allowing it to be easily wielded. This has the effect " +
	"of also allowing it to hit opponents far more easily than a normal " +
	"sceptre. It also bonds to its wielder, " +
	"making it difficult to unwield unless the wielder " +
	"forcefully attempts to ungrip it.\n", 40}));
    add_prop(MAGIC_AM_MAGIC,({40,"enchantment"}));
    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_WEIGHT, 6000);

    set_wf(TO);
    seteuid(getuid(TO));
}

void
init()
{
    ::init();
    add_action("ungrip_weapon","ungrip");
}

int
attempt_to_drop()
{
    if(E(TO)->query_hp() > 0)
    {
	tell_room(E(wielder), "The sceptre stays firmly in the hand of " +
	  QTNAME(wielder) + ".\n", wielder);
	write("The sceptre stays firmly in your hand.\n");
	return 1;
    }
    return 0;

}



int
ungrip_weapon(string str)
{
    if(str != "sceptre")
    {
	notify_fail("Ungrip what?\n");
	return 0;
    }
    write("You ungrip the sceptre.\n");
    say(QCTNAME(TP)+ " ungrips the golden sceptre.\n");
    grip = 0;
    remove_prop(OBJ_I_NO_DROP);
    return 1;
}

mixed
wield(object what)
{
    wielder = TP;
    grip = 1;
    write("You feel an almost magnetic bond as your " +
      "hand reaches to grip the sceptre.\n");
    add_prop(OBJ_I_NO_DROP, 1);
    return 0;
}

mixed
unwield(object what)
{
    if(E(TO)->query_hp() > 0 && (grip == 1))
    {
	return "You try and unwield the sceptre, but " +
	"are magically bonded to it! An effort " +
	"to ungrip it may be necessary to unwield " +
	"the sceptre.\n";
    }

    grip = 0;
    wielder = 0;
    return 0;
}
