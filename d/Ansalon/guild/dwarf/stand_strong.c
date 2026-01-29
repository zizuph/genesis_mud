/*
This is the code for the clan warriors
defensive special.


Coder : Arman
 */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

#define STAND_STRONG "_stand_strong_clan_special"

int time = 30;

void
create_armour()
{
    set_name("dwarfskin");
    add_name("clan_defensive_obj");
    set_long("Toughened dwarven skin. Technically, " +
      "you should not be able to examine this. Please " +
      "make a bug report.\n");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VALUE, 0);

    set_default_armour(1, A_MAGIC);
    set_no_show();
}


int
remove_myself()
{
    if (!worn || !wearer)
	return 0;
    worn = 0;

    wearer->remove_arm(this_object());
    wearer->remove_prop(STAND_STRONG);
    wearer->remove_stun();
    tell_object(wearer, "You feel yourself relax your " +
      "fierce defensive posture.\n");
    remove_object();
    return 1;
}

void
enter_env(object dest, object old)
{
    wearer = dest;
    worn = 1;
    tell_object(wearer, "You roar a challenge to the "+
      "heavens as you focus your entire attention "+
      "on taking the hits and blows of your opponents.\n");
    tell_room(environment(dest), QCTNAME(dest) + " roars " +
      "a dwarven challenge to the heavens, as "+ HE(dest)+
      " stubbornly focuses on taking the hits and blows of " +
      HIS(dest)+ " opponents.\n", dest);
    wearer->wear_arm(this_object());
    wearer->add_stun();
    wearer->add_prop(STAND_STRONG, 1);
    set_alarm(itof(time), 0.0, "remove_myself");
}

void
leave_env(object old, object dest)
{
    remove_myself();
}

int *
query_shield_slots()
{
    return ({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS});
}

int
dispel_magic(int magic)
{
    return 0;
}


int
remove_broken(int number)
{
    return 0;
}
