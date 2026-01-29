/*
 *  /d/Gondor/clubs/nisse/obj/nisse_admin.c
 *
 *  An invisible object cloned into a room that allows administration
 *  of the Nisse club (joining, leaving, expelling).
 *
 *  Deagol, March 2003 (inspired by Alto's code)
 *
 *  Varian - 11/12/2015 - Adjusted message for dancers attempting to join
 *
 *  Varian - 10/24/2016 - Increased the membership to 50
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";
inherit "/lib/commands";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <std.h>
#include <stdproperties.h>
#include <tasks.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

/*
 *  Global Variables
 */
mapping	gMembers = ([]);

/*
 *  Prototypes
 */
int	join_nisse(string str);
int	leave_nisse(string str);
int	discharge_nisse(string str);

void
create_object()
{
    set_short("_nisse_admin_object");
    set_name("_nisse_admin_object");
    set_long("A strange hawk-shaped object.\n");

    set_no_show_composite(1);

    setuid();
    seteuid(getuid());

    add_prop(OBJ_M_NO_GET, "It looks too dangerous to be picked up.\n");
    add_prop(OBJ_I_VOLUME,      10);
    add_prop(OBJ_I_WEIGHT,      10);
    add_prop(OBJ_I_VALUE,        0);
}

/*
 *  Function name: join_nisse
 *  Description  : The function called when a player wants to join the club.
 *  Arguments    : string str - the argument as entered by the supplicant
 *                              Should be "service".
 *  Returns      : 1 if successful, 0 if not
 */
int
join_nisse(string str)
{
    object token, ni_shadow;
    object who = TP;
    string name = TP->query_real_name();
    int	age = TP->query_age();

    if (NISSE_MEMBER(who))
    {
        who->catch_msg("You throw the small black stone into the tranquil " +
            "pool.\n");
        say(QCTNAME(who) + " throws a small black stone into the tranquil " +
            "pool.\n");
        who->catch_msg("You have already joined the sisterhood!\n");
        return 0;
    }
    else if (who->query_wiz_level())
    {
        who->catch_msg("You throw the small black stone into the tranquil " +
            "pool.\n");
        say(QCTNAME(who) + " throws a small black stone into the tranquil " +
            "pool.\n");
        write("Wizards must add the shadow and soul to themselves.\n");
        return 1;
    }
    else if (who->query_gender() != G_FEMALE)
    {
        who->catch_msg("You throw the small black stone into the tranquil " +
            "pool.\n");
        say(QCTNAME(who) + " throws a small black stone into the tranquil " +
            "pool.\n");
        who->catch_msg("You must be a female!\n");
        return 0;
    }
    /* We don't want let the dancers in */
    else if (who->query_prop("_live_i_am_dancer_of_veils"))
    {
        who->catch_msg("You throw the small black stone into the tranquil " +
            "pool.\n");
        say(QCTNAME(who) + " throws a small black stone into the tranquil " +
            "pool.\n");
        who->catch_msg("Dancers are not welcome with the Nisse.\n");
        return 0;
    }
    /* Must be at least a veteran (87) */
    else if (who->query_average_stat() < 87)
    {
        who->catch_msg("You throw the small black stone into the tranquil " +
            "pool.\n");
        say(QCTNAME(who) + " throws a small black stone into the tranquil " +
            "pool.\n");
        who->catch_msg("You are too small and unexperienced to ask for " +
            "membership here!\n");
        return 0;
    }
    /* we allow only 30 members in */
    else if (MANAGER->query_camp_fullness() >= 50)
    {
        who->catch_msg("You throw the small black stone into the tranquil " +
            "pool.\n");
        say(QCTNAME(who) + " throws a small black stone into the tranquil " +
            "pool.\n");
        who->catch_msg("We're sorry, but the camp is full. Come back later.\n");
        return 0;
    }

    /* Checks are all passed, let's update the manager. */
    MANAGER->add_nisse(name, "tan");

    gMembers = restore_map(NISSE_LOG_DIR + "members");
    if (!mappingp(gMembers))
    {
        gMembers = ([]);
    }

    gMembers[name] = age;
    save_map(gMembers, NISSE_LOG_DIR + "members");

    who->catch_msg("You throw the small black stone into the tranquil " +
        "pool.\n");
    say(QCTNAME(who) + " throws a small black stone into the tranquil " +
        "pool.\n");
    who->catch_msg("The ripples in the water lure you in and you plunge " +
        "into the tranquil pool.\n\n");
    say(QCTNAME(who) + " plunges into the tranquil pool.\n");
    set_alarm(1.0, 0.0, &who->catch_msg("You lapse into a trance " +
        "immediately.\n\n"));

    /* Now lets add the club autoshadow */

    seteuid(getuid());

    ni_shadow = clone_object(NISSE_SHADOW);
    this_player()->add_autoshadow(ni_shadow);
    ni_shadow->shadow_me(TP);
    this_player()->init_nisse_shadow();

    set_alarm(1.5, 0.0, &CEREMONY->start_ceremony());
    MANAGER->rlog(CAP(name) + " joined.");

    return 1;
}

/*
 *  Function name: leave_nisse
 *  Description  : Allows a Nisse to leave the club
 *  Arguments    : string str - the argument as entered by the player
 *  Returns      : 1 if successful, 0 if not
 */
int
leave_nisse(string str)
{
    object who = TP;
    string name;

    if (!strlen(str))
    {
        notify_fail("Abandon the sisterhood of Nisse Ohtar?\n");
        return 0;
    }

    str = lower_case(str);

    if (!parse_command(str, ({}), "[the] [sisterhood] [of] [the] [nisse] [Nisse] [ohtar] [Ohtar]"))
    {
        notify_fail("Abandon the sisterhood of Nisse Ohtar?\n");
        return 0;
    }
    else if (!NISSE_MEMBER(who))
    {
        write("You are not a member!\n");
        return 0;
    }

    name = who->query_real_name();

    write("You leave the sisterhood of Nisse Ohtar.\n");
    write("The connection to your hawk has been broken.\n");
    MANAGER->remove_nisse(name);
    who->expel_nisse("her will");
    return 1;
}

/*
 *  Function name: discharge_nisse
 *  Description  : Expel a member from the club. One must be a wizard 
 *                 to expel a member of the club.
 *  Arguments    : string str - As entered by the user, should consist of
 *                 <name> <why>, where name is the name of the Nisse to
 *                 expel and why is the reason for doing so.
 *  Returns      : 1/0 Success/Failure
 */
int
discharge_nisse(string str)
{
    object target_ob;
    string name, reason;
    int discharge_permitted;

    if (TP->query_wiz_level())
    {
        discharge_permitted = 1;
    }
     
    /* Check for wiz */
    if (!discharge_permitted)
    {
        notify_fail("Since you're not a wizard, you can't do this!\n");
        return 0;
    }

    /* No match */
    if (!strlen(str) || !parse_command(str, ({}), "%w %s", name, reason))
    {
        notify_fail("Discharge who for what reason?\n");
        return 0;
    }

    if (!strlen(reason))
    {
        notify_fail("Discharge who for what reason?\n");
        return 0;
    }

    name = CAP(name);

    /* Don't discharge non-Nisse. */
    if (!MANAGER->query_nisse_level(name))
    {
        notify_fail(name + " is not the Nisse Ohtar member.\n");
        return 0;
    }

    /* Discharge target directly if they are in the realms. */
    target_ob = find_player(lower_case(name));
    if (objectp(target_ob))
    {
        target_ob->expel_nisse(reason);
        target_ob->catch_tell("You have been discharged from the Nisse " +
            "Ohtar.\n");
        write("You discharge " + name + " " + reason + ".\n"); 
    }
    else
    {
        /* Mark the target for expelling next time they log in. */
        MANAGER->add_to_be_expelled(name, reason);
        write("You mark " + name + " to be discharged.\n");
    }

    return 1;
}

void
init()
{
    ::init();

    add_action(leave_nisse, "abandon");
    add_action(discharge_nisse, "discharge");
}
