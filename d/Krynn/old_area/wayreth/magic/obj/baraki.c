/* 
 * Bakari object, simple shield, protecting the wearer from blows.
 */
inherit "/std/armour";
inherit "/d/Krynn/rastlin/open/spells2/magic.object";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "../../guild/local.h"

#define BARAKI_SUBLOC "wohs_baraki_subloc"

void
create_armour()
{
    add_name("mag_shield_prot");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO, "A magical shield to protect the wearer. Will " +
      "out before to long\n");
    add_prop(MAGIC_AM_MAGIC, ({ 20, "abjured" }) );
    add_prop(MAGIC_AM_ID_INFO, ({
        "The magic aura will protect your entire body.\n", 0}) );

    set_no_show();
    set_default_armour(35, A_MAGIC);
}

public int
remove_myself()
{
    if (!worn || !wearer)
        return 0;
    worn = 0;

    wearer->remove_arm(this_object());

    wearer->remove_subloc(BARAKI_SUBLOC);
    tell_object(wearer, "The aura surrounding you fades away, you feel " +
      "unprotected.\n");
    return 1;
}

public void
enter_env(object dest, object old)
{
    wearer = dest;

    wearer->add_subloc(BARAKI_SUBLOC, TO);
    worn = 1;
    wearer->wear_arm(this_object());
}

public int *
query_shield_slots()
{
    return ({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS});
}

public void
notify_dispel_magic(object ob)
{
    remove_myself();
}

public string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == me)
        return "You are surrounded by a glowing aura.\n";

    return capitalize(PRONOUN(me)) + " is surrounded by a glowing " +
        "aura.\n";
}

