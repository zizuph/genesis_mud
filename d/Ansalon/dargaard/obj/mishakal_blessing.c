/* This is a magic shield, protecting the wearer from blows.
   It was directly copied from mag_shield.c example in the doc files
 */


/* Navarre 25th June 2006,
   Changed the magical AC from 30 to 5, it is totally ridiculous
   that players should get 30 AC extra on all body parts for 3 hours
   We have a huge AC inflation as it is.
   Time also downgraded from 3 hours to 30 minutes.

   Navarre August 6th 2006, added set_no_show(),
   Since the long description showed it was in prime condition.
*/

inherit "/std/armour";
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"


#define BLESS_ID     "ansalon_bless_object"

void
create_armour()
{
    set_name("blessing");
    set_short("magical blessing");
    add_name(BLESS_ID);
    add_name("aura");
    set_adj(({"magic","magical"}));
    set_af(this_object());
    set_long("A protective aura surrounds you, the blessings of the goddess " +
      "Mishakal.\n");
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO, "A magical blessing from the goddess Mishakal. Will " +
      "improve the armour value of the wearer by about 30 points. Lasts between " +
      "one and three hours.\n");
    add_prop(MAGIC_AM_MAGIC, ({ 20, "abjured" }) );
    add_prop(MAGIC_AM_ID_INFO, ({
	"The blessing offers protection to the wearer.\n", 0}) );
    set_no_show();
    TP->add_subloc("_mishakal_bless_obj", TO);

    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    
    set_default_armour(5, A_MAGIC);
}

mixed
remove(object ob)
{
    return "";
}

mixed
wear(object ob)
{
    return 1;
}

varargs void
remove_broken(int silent = 0)
{
    return;
}



string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "You are surrounded by a blue aura, the blessings of " +
        "the goddess Mishakal.\n";

    if (for_obj == me)
	return "You are surrounded by a blue protective aura.\n";
    else
	return C(PRONOUN(me)) + " is surrounded by a blue protective " +
        "aura.\n";
}


int
remove_myself()
{
    if (!worn || !wearer)
	return 0;
    worn = 0;

    wearer->remove_arm(this_object());
    tell_object(wearer, "The blessing of Mishakal dissipates, and you feel " +
      "less protected.\n");
    tell_room(environment(wearer), "Suddenly, the blue aura " +
      "surrounding "+QTNAME(wearer)+ " disappears!\n",wearer);
    remove_object();
    return 1;
}

void
enter_env(object dest, object old)
{
    if(dest->query_alignment() < 1000)
	remove_object();
    else
    {
	wearer = dest;
	worn = 1;
	tell_object(dest, "You are surrounded by a blue aura, the blessings " +
          "of Mishakal, and you feel the protection of the goddess around you.\n");
	tell_room(environment(dest), "Suddenly " + QTNAME(dest)  + " is " +
	  "surrounded by a holy blue aura!\n", dest);
	wearer->wear_arm(this_object());

        TO->remove_mish_obj();
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


void
remove_mish_obj()
{
/*
    time = 3600 + random(7200);
    time = 120;
*/
    set_alarm(1800.0, 0.0, "remove_object");
}


int
dispel_magic(int magic)
{
    if (magic > 40)
    {
	set_alarm(1.0,0.0, "remove_object");
	return 1;
    }
    return 0;
}


