/* This is a magic shield, protecting the wearer from blows.
   It was directly copied from mag_shield.c example in the doc files
 */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

void
create_armour()
{
    set_name("forcefield");
    add_name("mag_shield_prot");
    set_adj("magic");
    set_long("A magical forcefield covering your whole body.\n");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO, "A magical shield to protect the wearer. Will " +
      "only be usable by the npc Ariakas. Raises the " +
      "armour value of the wearer by about 50 points.\n");
    add_prop(MAGIC_AM_MAGIC, ({ 20, "abjured" }) );
    add_prop(MAGIC_AM_ID_INFO, ({
	"The forcefield will protect your entire body.\n", 0}) );
    set_no_show();

    set_default_armour(50, A_MAGIC);
}

int
remove_myself()
{
    if (!worn || !wearer)
	return 0;
    worn = 0;

    wearer->remove_arm(this_object());
    tell_object(wearer, "The magic forcefield is gone, you feel " +
      "unprotected.\n");
    tell_room(environment(wearer), "Suddenly, the forcefield " +
      "surrounding "+QTNAME(wearer)+ " disappears!\n",wearer);
    remove_object();
    return 1;
}

void
enter_env(object dest, object old)
{
    if(dest->query_real_name() != "ariakas")
	remove_object();
    else
    {
	wearer = dest;
	worn = 1;
	tell_object(dest, "You become surrounded by a forcefield, you feel " +
	  "protected.\n");
	tell_room(environment(dest), "Suddenly " + QTNAME(dest)  + " is " +
	  "surrounded by a forcefield.\n", dest);
	wearer->wear_arm(this_object());
    }
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
    if (magic > 20)
    {
	set_alarm(1.0,0.0, "remove_object");
	return 1;
    }
    return 0;
}


