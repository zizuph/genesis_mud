inherit "std/armour.c";
inherit "/lib/keep";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

public string color = "carmine";
public string    query_color();

nomask void
create_armour()
{
    set_name("robe");
    set_ac(30);
    set_at(A_ROBE);
    set_af(TO);

    add_adj(color);
    set_short(color + " robe");
    set_long("This @@query_color@@ robe is covered with runes " +
       "and ancient royal symbols of the Empire of Ergoth.\n");

    add_prop(OBJ_I_VOLUME, 4750);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(30, A_ROBE));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30));

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO, "This robe is worn by the Ergothian " +
        "battlemage found on a ship in the Turbidus Ocean, " +
        "/d/Krynn/turbidus_ocean/living/ergothian_wizard.c\n" +
        "This robe provides armour protection to A_ROBE " +
        "of between 5 and 45, dependent on the wearer's " +
        "SS_FORM_ABJURATION skill (50% of skill = ac value, max 45).\n");

    add_prop(MAGIC_AM_ID_INFO, ({
         "This is the traditional robe worn by those battlemages " +
         "of the Ergothian Empire held in highest of esteem by " +
         "the royal family. It is enchanted to provide great " +
         "protection, dependent on the wearer's skill in " +
         "abjuration magic.\n", 60}));

    add_prop(MAGIC_AM_MAGIC, ({ 75, "enchantment" }) );
}

public void
set_color(object wearer, int skill)
{
    skill = max(5, min(45, skill / 2));

    switch(skill)
    {
       case 0..10:
        color = "dull";
        break;
       case 11..20:
        color = "carmine";
        break;
       case 21..30:
        color = "scarlet";
        break;
       case 31..40:
        color = "crimson";
        break;
       case 41..50:
        color = "vermillion";
        break;
       default:
        color = "dull";
        break;
    }

    remove_adj(color);
    set_short(0);
    set_adj(color);
    set_short(color + " robe"); 
 
    set_ac(skill); 
    wearer->update_armour(TO);                     
}

string
query_color()
{
    return color;
}

public mixed
wear(object what)
{
    int abjuration_skill = TP->query_skill(SS_FORM_ABJURATION);

    write("As you wear the " +query_color()+ " robe it subtly " +
        "begins to change colour.\n");
    say("As " +QTNAME(TP)+ " begins to wear the " +query_color()+ 
        " robe it begins to subtly change colour.\n");

    set_color(TP, abjuration_skill);

    return 0;
}

public mixed
remove(object what)
{
    // set_this_player(query_worn());

    return 0;
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
}
