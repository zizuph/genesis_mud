/*
 * quest_master's glasses for the 4th small adventure 
 * created by Aridor, 01/95 
 *
 * Bugfixed by Cotillion 2003-12-19
 */
inherit "/std/object";

#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#define PLAYER_I_PICKED_UP_GLASSES "_player_i_picked_up_glasses"

static int found_first;
static object worn;
static int lang_inc;
static int found_alarm;

public nomask void
create_object()
{
    set_name("spectacles");
    set_adj("crooked");
    add_adj("tiny");
    add_name("qmaster_spectacles");
    add_name("glasses");
    add_name("pair");
    set_short("pair of crooked tiny spectacles");
    set_long("These are indeed strange spectacles. You wonder who they " +
        "could belong to? The glasses are shaped like octagons and " +
        "the frame is made of gold. They're probably worth a lot of " +
        "money, too.\n");
    add_prop(OBJ_I_VALUE, 900);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_S_WIZINFO, 
        "These glasses increase the language skill of the wearer random(5)+3 points. " +
        "They are glasses of 'true seeing' and belong to the questmaster in Solace.\n");
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(MAGIC_AM_MAGIC, ({20, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,
        ({"These glasses are magical.\n", 3,
              "You are able to read better with them.\n", 8,
              "Even languages you couldn't before!\n", 22,
              "Your understanding of spoken languages will improve as " + 
              "well.\n", 28 }));

    lang_inc = random(5) + 3;
    
}


public mixed
command_wear()
{

    if (worn || (TP->subloc_id("glasses")))
    {
        return "You are already wearing something on your nose.\n";
    }

    write("You wear the spectacles on your nose.\n");
    SAYBB(" wears a pair of spectacles on " + POSSESSIVE(TP) + " nose.\n");
	
    TP->add_subloc("glasses", TO);
    set_no_show_composite(1);
    
    TP->set_skill_extra(SS_LANGUAGE, TP->query_skill_extra(SS_LANGUAGE) + 
        lang_inc);
    worn = TP;
    return 1;
}

public mixed
command_remove()
{
    if (!worn)
    {
        return "You are not wearing the " + short() + ".\n";
    }

    write("You remove the spectacles from your nose.\n");
    SAYBB(" removes a pair of spectacles from " + POSSESSIVE(TP) + " nose.\n");
    TP->set_skill_extra(SS_LANGUAGE, TP->query_skill_extra(SS_LANGUAGE) - 
        lang_inc);
    TP->remove_subloc("glasses");
    set_no_show_composite(0);
    worn = 0;
    return 1;
}

public nomask string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "You are wearing a pair of crooked tiny spectacles on your " + 
            "nose.\n";
    
    if (for_obj == me)
        return "You are wearing a pair of crooked tiny spectacles on your " + 
            "nose.\n";
    else
        return C(PRONOUN(me)) + " is wearing a pair of crooked tiny " + 
            "spectacles on " + POSSESSIVE(me) + " nose.\n";

}

public nomask void
enter_env(object dest, object old)
{
    if (interactive(dest) && !found_first)
    {
        found_first = 1;
        dest->add_prop(PLAYER_I_PICKED_UP_GLASSES, 1);
    }
    ::enter_env(dest, old);
}

/* When the glasses have been found but dropped again, the found_first
 * is reset after 6 minutes. This is of course only done in the dwarf
 * (/d/Krynn/solamn/thief/) area, where it can must be found to solve
 * the quest.
 */
void
reset_found_first()
{
    if (objectp(E(TO)) &&
	file_name(E(TO))[0..21] == "/d/Krynn/solamn/thief/")
        found_first = 0;
}


public nomask void
leave_env(object from, object to)
{
    object otp;

    if (worn) {
        otp = this_player();
        set_this_player(worn);
        command_remove();
        set_this_player(otp);
    }

    remove_alarm(found_alarm);
    found_alarm = set_alarm(360.0, 0.0, &reset_found_first());
    ::leave_env(from, to);
}



