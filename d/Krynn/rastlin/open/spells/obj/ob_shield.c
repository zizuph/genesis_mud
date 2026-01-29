/* 
 * This is a magic shield, protecting the wearer from blows
 * and blows only.
 */

inherit "/std/armour";
inherit "/d/Krynn/rastlin/open/spells/std.object";
inherit "/d/Krynn/rastlin/open/spells/std.magic.object";

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
        "out before to long\n");
    add_prop(MAGIC_AM_MAGIC, ({22, "abjuration"}));
    add_prop(MAGIC_AM_ID_INFO, ({
	"The forcefield will protect your entire body.\n", 0}) );

    add_prop(MAGIC_I_RES_FIRE, ({20, 0}));
    set_no_show();

    set_default_armour(6, A_MAGIC);
}

int
remove_it()
{
    object ob;

    if (!worn || !wearer)
        return 0;
    worn = 0;

    wearer->remove_arm(this_object());
    wearer->remove_subloc("magic_forcefield");
    wearer->remove_magic_effect(this_object());
    tell_object(wearer, "The magic forcefield is gone, you feel " +
        "unprotected.\n");
    remove_call_out("remove_object");
    remove_object();
    return 1;
}

void
enter_env(object dest, object old)
{
    object ob;

    wearer = dest;
    worn = 1;
    tell_object(dest, "You become surrounded by a forcefield, you feel " +
        "protected.\n");
    tell_room(environment(dest), "Suddenly " + QTNAME(dest)  + " is " +
        "surrounded by a forcefield.\n", dest);
    wearer->wear_arm(this_object());
    wearer->add_subloc("magic_forcefield", this_object());
    wearer->add_magic_effect(this_object());
}

string
show_subloc(string subloc, object me, object for_obj)
{   
    if (for_obj == me)
      return "You are surrounded by a magic forcefield.\n";
    else
      return capitalize(me->query_pronoun()) + " is surrounded " +
        " by a magic forcefield.\n";

}

void
leave_env(object old, object dest)
{
    remove_it();
}

int *
query_shield_slots()
{
    return ({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS});
}

notify_reduced_power(object ob, int i)
{
    write(sprintf("Anti-Magic: %O %O\n", ob, i));
} 
