/*
 * anghoth_admin.c
 *
 * an invisible object cloned into a room that allows administration
 * of the Anghoth club (joining, leaving, sponsoring, expelling, etc.)
 *
 * Alto, 05 June 2002
 *
 * 06-jan-2007, Toby: Fixed an error with declare. First need to check 
 *                    if a string is passed into the function before
 *                    we try and get the object of intended target.
 *
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
#include "../anghoth_defs.h"
#include "/d/Gondor/defs.h"

/* Global Variables */
int  thrak_in_progress = 0;

/* Prototypes */
public int    join_anghoth(string str);
public int    sponsor_anghoth(string name);
public int    leave_anghoth(string str);
int           discharge_anghoth(string str);
public int    declare_ashuk(string name);
public int    claim_ashuk(string name);
public int    thraksnaga_1(string name);
public int    thraksnaga_2(string name);
public int    thraksnaga_3(string name);
public int    thraksnaga_4(string name);

void
create_object()
{
    set_short("_anghoth_admin_object");
    set_name("_anghoth_admin_object");
    set_long("A strange object that shifts and changes colours, making "
        + "it tremendously difficult to focus upon.\n");

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "You cannot focus upon this object long enough "
        + "to pick it up.\n");
    add_prop(OBJ_I_VOLUME,      10);
    add_prop(OBJ_I_WEIGHT,      10);
    add_prop(OBJ_I_VALUE,        0);

}


/* Function name: join_anghoth
 * Description  : The function called when a player tries to swear fealty
 *                to Minas Morgul.
 * Arguments    : string str - the argument as entered by the supplicant
 *                             Should be "service".
 * Returns      : 1 if successful, 0 if not
 */
public int
join_anghoth(string str)
{
    object token, ang_shadow;
    object who = this_player();
    string name = this_player()->query_real_name();
    string sponsor = MANAGER->query_inviting_sponsor(name);

    if (!strlen(str))
    {
        notify_fail("Vow service?\n");
        return 0;
    }

    str = lower_case(str);
 
    if (!parse_command(str, ({}), "'service'"))
    {
        notify_fail("Vow service?\n");
        return 0;
    }
    else if (ANGHOTH_MEMBER(who))
    {
        notify_fail("But you have already vowed service!\n");
        return 0;
    }
    else if (member_array(who->query_race_name(), BANNED_RACE) != -1)
    {
        notify_fail("Your race is not worthy to serve among the Shields!\n");
        return 0;
    }
    else if (who->query_alignment() > ALIGN_JOIN)
    {
        notify_fail("You are too pure of heart to serve dark causes!\n");
        return 0;
    }
    else if (who->query_wiz_level())
    {
        write("Wizards must add the shadow and soul to themselves.\n");
        return 1;
    }
    /* Must be at least an adventurer to join */
    else if (who->query_average_stat() < 55)
    {
        notify_fail("You are far to puny to be an effective Shield!\n");
        return 0;
    }
    /* Must have a mage sponsor to join */
    else if (!sponsor)
    {
        notify_fail("You must first be granted the honour of elevation "
            + "to Anghoth by a sponsoring mage!\n");
        return 0;
    }

    /* Checks are all passed, let's update the manager. */
    MANAGER->add_anghoth(name, "korrak", sponsor);
    MANAGER->remove_inviting_sponsor(name);

    /* Now lets add the club autoshadow */

    seteuid(getuid());

    ang_shadow=clone_object(ANGHOTH_SHADOW); 
    this_player()->add_autoshadow(ang_shadow);
    ang_shadow->shadow_me(this_player());
    this_player()->init_anghoth_shadow();

    write("You vow service and pledge your life as Anghoth, "
        + "Shield of Morgul.\n\n"
        + "You suddenly notice a shield-shaped ring in your hand.\n");
    say(QCTNAME(who) + " drops to one knee and vows eternal service "
        + "as Anghoth, Shield of Morgul. " + CAP(PRONOUN(who)) + " is "
        + "handed a shield-shaped ring.\n");

    MANAGER->rlog(capitalize(name) + " joined.");

    return 1;
}


/* Function name: sponsor_anghoth
 * Description  : The function called when a mage invites someone to 
 *                become a shield.
 * Arguments    : string name - the name as entered by the sponsor
 * Returns      : 1 if successful, 0 if not
 */
public int
sponsor_anghoth(string name)
{
    object sponsor = this_player();
    object target;
    string sponsor_name = this_player()->query_real_name();
    string existing_rank = MANAGER->query_anghoth_rank(name);
    int elevation_permitted = 0;

    if (!strlen(name))
    {
        notify_fail("Elevate who?\n");
        return 0;
    }

    target = find_player(lower_case(name));
    name = lower_case(name);

    if (IS_MORGUL_MAGE(TP) || TP->query_wiz_level())
    {
        elevation_permitted = 1;
    }

    if (!elevation_permitted)
    {
        notify_fail("You presume an honour reserved only for "
            + "the Nine and their minions? Begone, imposter!\n");
        return 0;
    }
    if (!target)
    {
        notify_fail("That person is not in the realms!\n");
        return 0;
    }
    else if (MANAGER->query_inviting_sponsor(name))
    {
        notify_fail("This supplicant has already been honoured with an "
            + "invitation for elevation to Anghoth.\n");
        return 0;
    }
    else if (MANAGER->query_anghoth(name))
    {
        switch(existing_rank)
        {
            case("kriechek"):
                MANAGER->add_anghoth(name, "korrak", sponsor_name);
                write("You promote " + CAP(name) + " to the rank "
                    + "of Korrak.\n");
                target->catch_tell("You have been promoted to the "
                    + "rank of Korrak Anghoth.\n");
                target->change_tokens("korrak");
                break;
            case("korrak"):
                MANAGER->add_anghoth(name, "dath", sponsor_name);
                write("You promote " + CAP(name) + " to the rank "
                    + "of Dath.\n");
                target->catch_tell("You have been promoted to the "
                    + "rank of Dath Anghoth.\n");
                target->change_tokens("dath");
                break;
            case("dath"):
                MANAGER->add_anghoth(name, "durub", sponsor_name);
                write("You promote " + CAP(name) + " to the rank "
                    + "of Durub.\n");
                target->catch_tell("You have been promoted to the "
                    + "rank of Durub Anghoth.\n");
                target->change_tokens("durub");
                break;
            default:
                write(CAP(name) + " cannot be promoted.\n");
                break;
         }
         target->init_anghoth_shadow();
            MANAGER->rlog(capitalize(sponsor_name) + " promoted "
            + CAP(name) + " from the rank of " + CAP(existing_rank) + ".");
         return 1;
    }
    /* Checks are all passed, let's update the manager. */
    MANAGER->add_inviting_sponsor(name, sponsor_name);

    write("You say: I bring this one, known as " + capitalize(name) 
        + " to be considered for the great honour to be a Shield of "
        + "Minas Morgul. I consent to allow it to spend its life on "
        + "my behalf.\n");
    say(QCTNAME(sponsor) + " hisses in a voice mildly laced with "
        + "contempt: I bring this one, known as " + capitalize(name) 
        + " to be considered for the great honour to be a Shield of Minas "
        + "Morgul. I consent to allow it to spend its life on my behalf.\n");

    MANAGER->rlog(capitalize(sponsor_name) + " invited "
        + capitalize(name) + " to join the Anghoth.");

    return 1;
}

/* Function name: leave_anghoth
 * Description  : Allows an anghoth to leave the club
 * Arguments    : string str - the argument as entered by the player
 * Returns      : 1 if successful, 0 if not
 */
public int
leave_anghoth(string str)
{
    object who = this_player();
    string name;

    if (!strlen(str))
    {
        notify_fail("Renounce your vow of service?\n");
        return 0;
    }

    str = lower_case(str);

    if (!parse_command(str, ({}), "[my] 'vow' [of] [service]"))
    {
        notify_fail("Renounce your vow of service?\n");
        return 0;
    }
    else if (!ANGHOTH_MEMBER(who))
    {
        write("But you are not of the Anghoth! How can you renounce "
            + "that which you have not vowed?\n");
        return 0;
    }

    name = who->query_real_name();

    write("You renounce your vow of service to Minas Morgul. The "
        + "Lidless Eye will no longer look to you for service, but "
        + "be warned: when next the Eye looks upon you, He may "
        + "recall your lack of devotion.\n");
    MANAGER->remove_anghoth(name);
    who->expel_anghoth("renouncing vow voluntarily");
    return 1;
}

/* Function name: reduce_anghoth
 * Description  : The function called when a mage reduces the rank 
 *                of an existing shield.
 * Arguments    : string name - the name as entered by the sponsor
 * Returns      : 1 if successful, 0 if not
 */
public int
reduce_anghoth(string name)
{
    object sponsor = this_player();
    object target = find_player(lower_case(name));
    string sponsor_name = this_player()->query_real_name();
    string existing_rank = MANAGER->query_anghoth_rank(name);
    int reduction_permitted = 0;

    if (!strlen(name))
    {
        notify_fail("Reduce who?\n");
        return 0;
    }

    name = lower_case(name);

    if (IS_MORGUL_MAGE(TP) || TP->query_wiz_level())
    {
        reduction_permitted = 1;
    }

    if (!reduction_permitted)
    {
        notify_fail("You presume a privilege reserved only for "
            + "the Nine and their minions? Begone, imposter!\n");
        return 0;
    }
    else if (MANAGER->query_anghoth(name))
    {
        switch(existing_rank)
        {
            case("korrak"):
                MANAGER->add_anghoth(name, "kriechek", sponsor_name);
                write("You reduce " + CAP(name) + " to the rank "
                    + "of Kriechek.\n");
                target->catch_tell("You have been reduced to the "
                    + "rank of Kriechek Anghoth.\n");
                target->change_tokens("kriechek");
                target->remove_cmdsoul(ANGHOTH_SOUL);
                target->update_hooks();
                break;
            case("dath"):
                MANAGER->add_anghoth(name, "korrak", sponsor_name);
                write("You reduce " + CAP(name) + " to the rank "
                    + "of Korrak.\n");
                target->catch_tell("You have been reduced to the "
                    + "rank of Korrak Anghoth.\n");
                target->change_tokens("korrak");
                break;
            case("durub"):
                MANAGER->add_anghoth(name, "dath", sponsor_name);
                write("You reduce " + CAP(name) + " to the rank "
                    + "of Dath.\n");
                target->catch_tell("You have been reduced to the "
                    + "rank of Dath Anghoth.\n");
                target->change_tokens("dath");
                break;
            default:
                write(CAP(name) + " cannot be reduced in rank.\n");
                break;
         }
    target->init_anghoth_shadow();

    MANAGER->rlog(capitalize(sponsor_name) + " reduced "
        + capitalize(name) + " in rank.");
    return 1;
    }

    write(CAP(name) + " cannot be reduced in rank.\n");

    return 0;
}

/*
 * Function name: discharge_anghoth
 * Description  : Expel a member from the club. One must be a member of
 *                the society of Morgul Mages or a wizard to expel a
 *                member of the club.
 * Arguments    : string str - As entered by the user, should consist of
 *                <name> <why>, where name is the name of
 *                the Anghoth to expel and why is the reason for doing so.
 * Returns      : 1/0 Success/Failure
 */
int
discharge_anghoth(string str)
{
    object target_ob;
    string name, reason;
    int discharge_permitted;

    if (IS_MORGUL_MAGE(TP) || TP->query_wiz_level())
    {
        discharge_permitted = 1;
    }
     
    /* Check for wiz or mage. */
    if (!discharge_permitted)
    {
        notify_fail("Worm! Who are you to go about discharging "
            + "Shields of Morgul? Begone, imposter!\n");
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

    name = capitalize(name);

    /* Don't discharge non-Anghoth. */
    if (!MANAGER->query_anghoth_level(name))
    {
        notify_fail(name + " is not of the Anghoth.\n");
        return 0;
    }

    /* Discharge target directly if they are in the realms. */
    target_ob = find_player(lower_case(name));
    if (objectp(target_ob))
    {
        target_ob->expel_anghoth(reason);
        target_ob->catch_tell("You have been discharged from the Shields "
            + "of Morgul. You no longer deserve the honourific "
            + "of Anghoth.\n");
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

/* Function name: claim_ashuk
 * Description  : The function called when a mage claims someone who
 *                is already in the club, but Ashuk (without a sponsor).
 * Arguments    : string name - the name as entered by the sponsor
 * Returns      : 1 if successful, 0 if not
 */
public int
claim_ashuk(string name)
{
    object sponsor = this_player();
    object target;
    string sponsor_name = this_player()->query_real_name();
    string existing_rank = MANAGER->query_anghoth_rank(name);
    int claiming_permitted = 0;

    if (!strlen(name))
    {
        notify_fail("Claim who?\n");
        return 0;
    }

    target = find_player(lower_case(name));
    name = lower_case(name);

    if (IS_MORGUL_MAGE(TP) || TP->query_wiz_level())
    {
        claiming_permitted = 1;
    }

    if (!claiming_permitted)
    {
        notify_fail("You presume an honour reserved only for "
            + "the Nine and their minions? Begone, imposter!\n");
        return 0;
    }
    if (!target)
    {
        notify_fail("That person is not in the realms!\n");
        return 0;
    }
    if (!MANAGER->query_ashuk(name))
    {
        notify_fail("That person is not ashuk!\n");
        return 0;
    }
    /* Checks are all passed, let's update the manager. */
    MANAGER->remove_anghoth(name);
    MANAGER->add_anghoth(name, existing_rank, sponsor_name);

    write("You claim " + capitalize(name) + " as your living Shield.\n");
    say(QCTNAME(sponsor) + " hisses in a voice mildly laced with "
        + "contempt: I claim this one, known as " + capitalize(name) 
        + " to be my living Shield and spend its life on my behalf.\n");

    target->change_tokens(existing_rank);

    MANAGER->rlog(capitalize(sponsor_name) + " claimed "
        + capitalize(name) + " as its sponsor.");

    return 1;
}


/* Function name: declare_ashuk
 * Description  : The function called when a mage declares a sponsored
 *                club member to be without a sponsor (ashuk).
 * Arguments    : string name - the name as entered by the sponsor
 * Returns      : 1 if successful, 0 if not
 */
public int
declare_ashuk(string name)
{
    object sponsor;
    object target;
    string sponsor_name;
    string existing_rank;
    int declaring_permitted = 0;

    if (!strlen(name))
    {
        notify_fail("Declare who?\n");
        return 0;
    }
    
    sponsor = this_player();
    target = find_player(lower_case(name));
    sponsor_name = this_player()->query_real_name();
    existing_rank = MANAGER->query_anghoth_rank(name);

    name = lower_case(name);

    if (IS_MORGUL_MAGE(TP) || TP->query_wiz_level())
    {
        declaring_permitted = 1;
    }

    if (!declaring_permitted)
    {
        notify_fail("Who do you think you are to declare a Shield of "
            + "Morgul lost? Flee, ere the wrath of the Tower fall upon "
            + "your head!\n");
        return 0;
    }
    if (!MANAGER->query_anghoth(name))
    {
        notify_fail("That person is not anghoth! How can they be made "
            + "ashuk?\n");
        return 0;
    }

    if (MANAGER->query_ashuk(name))
    {
        notify_fail("That person is already ashuk!\n");
        return 0;
    }
    /* Checks are all passed, let's update the manager. */
    MANAGER->remove_anghoth(name);
    MANAGER->add_anghoth(name, existing_rank, "nobody");

    write("You declare " + capitalize(name) + " to be Ashuk, lost and "
        + "without a Lord Mage.\n");
    say(QCTNAME(sponsor) + " hisses in a voice mildly laced with "
        + "contempt: I declare that the snaga known as " + capitalize(name) 
        + " be Ashuk, lost and without a Lord Mage to serve.\n");

    MANAGER->rlog(capitalize(sponsor_name) + " declared "
        + capitalize(name) + " to be Ashuk.");

    if (target)
    {
        target->change_tokens("ashuk");
    }

    return 1;
}


/*
 * Function name: end_thraksnaga
 * Description  : Ends restriction on another part of the thraksnaga 
 *                ceremony from occurring.
 */
public void
end_thraksnaga()
{
    thrak_in_progress = 0;
}

/*
 * Function name: thraksnaga_1
 * Description  : Begins first stage of thraksnaga ceremony.
 * Arguments    : string name - As entered by the user, should consist of
 *                <name>, where name is the name of
 *                the mage who will sponsor the new Anghoth.
 * Returns      : 1/0 Success/Failure
 */
public int
thraksnaga_1(string name)
{
    object sponsor;
    int thraksnaga_permitted, legitimate_sponsor;
    object actor = this_player();

    if (IS_MORGUL_MAGE(TP) || TP->query_wiz_level())
    {
        thraksnaga_permitted = 1;
    }
     
    /* Check for wiz or mage. */
    if (!thraksnaga_permitted)
    {
        notify_fail("Worm! Who are you to go about dispensing the "
            + "the duties of the Nine? Begone, imposter!\n");
        return 1;
    }

    if (!strlen(name))
    {
        write("You must specify the mage who will be the sponsor.\n");
        return 1;
    }

    sponsor = find_player(lower_case(name));

    if (!present(sponsor, ENV(TP)))
    {
        NFN0("Which mage do you wish to be the sponsor?");
    }

    if (IS_MORGUL_MAGE(sponsor) || sponsor->query_wiz_level())
    {
        legitimate_sponsor = 1;
    }
     
    /* Check for wiz or mage. */
    if (!legitimate_sponsor)
    {
        notify_fail("That person is not of the Society!\n");
        return 0;
    }

    if (thrak_in_progress)
    {
        notify_fail("A Thraksnaga ceremony is already in progress!\n");
        return 0;
    }

    thrak_in_progress = 1;

    set_alarm(1.0, 0.0, &tell_room(environment(actor), "A huge, blazing Red "
        + "Eye appears.\n", 0));

    set_alarm(5.0, 0.0, &tell_room(environment(actor), "You tremble before "
        + "the power of the Eye.\n", 0));

    set_alarm(10.0, 0.0, &tell_object(sponsor, "A deep, powerful voice intones "
        + "to you: So you have found one who is worthy of serving you as a "
        + "Shield of flesh.....\n"));
    set_alarm(10.0, 0.0, &tell_room(environment(actor), "A deep, powerful "
        + "voice intones to " + QTNAME(sponsor) + ": So you have found one "
        + "who "
        + "is worthy of serving you as a Shield of flesh......\n", sponsor));

    set_alarm(15.0, 0.0, &tell_room(environment(actor), "The huge, blazing Red "
        + "Eye flickers, betraying its Dark amusement.\n", 0));

    set_alarm(20.0, 0.0, &tell_room(environment(actor), "A deep, powerful "
        + "voice intones: And I see that the Nine have approved of this "
        + "decision...\n", 0));

    set_alarm(25.0, 0.0, &tell_object(sponsor, "The huge, blazing Red Eye "
        + "focuses on you. You fall on your knees before it.\n"));
    set_alarm(25.0, 0.0, &tell_room(environment(actor), "The huge, blazing Red "
        + "Eye focuses on " + QTNAME(sponsor) + " and " 
        + PRONOUN(sponsor) + " falls to " + POSSESSIVE(sponsor) 
        + " knees before it.\n", sponsor));

    set_alarm(30.0, 0.0, &tell_object(sponsor, "A deep, powerful voice intones "
        + "to you: Very well. But know this...\n"));
    set_alarm(30.0, 0.0, &tell_room(environment(actor), "A deep, powerful "
        + "voice intones to " + QTNAME(sponsor) + ": Very well. But "
        + "know this...\n", sponsor));

    set_alarm(35.0, 0.0, &tell_object(sponsor, "A deep, powerful voice intones "
        + "to you: This ceremony "
        + "will bond the wretch to you. It will be required to serve you, "
        + "the Nine, and me faithfully. This is not to be a decision that "
        + "is taken lightly. Should you wish to choose another Shield, "
        + "you will need to kill the first or have the permission of the "
        + "Nine to do so. Its failures are now yours to beat out of it.\n"));
    set_alarm(35.0, 0.0, &tell_room(environment(actor), "A deep, powerful "
        + "voice intones to " + QTNAME(sponsor) + ": This ceremony "
        + "will bond the wretch to you. It will be required to serve you, "
        + "the Nine, and me faithfully. This is not to be a decision that "
        + "is taken lightly. Should you wish to choose another Shield, "
        + "you will need to kill the first or have the permission of the "
        + "Nine to do so. Its failures are now yours to beat out of "
        + "it.\n", sponsor));

    set_alarm(50.0, 0.0, &tell_room(environment(actor), "The deep, powerful "
        + "voice emits a sound that you recognize, "
        + "to your horror, as laughter.\n", 0));

    set_alarm(55.0, 0.0, &tell_room(environment(actor), "A deep, powerful "
        + "voice intones: Very well. Bring the "
        + "wretch before the Nine and present them. Shadows keep "
        + "you all.\n", 0));

    set_alarm(60.0, 0.0, &tell_room(environment(actor), "The huge, blazing "
        + "Red Eye slowly fades and disappears, "
        + "but you hear an echo of laughter retreat with the "
        + "presence.\n", 0));

    set_alarm(65.0, 0.0, &tell_room(environment(actor), "You feel calm "
        + "again.\n", 0));

    set_alarm(66.0, 0.0, &end_thraksnaga());

    return 1;
}

/*
 * Function name: thraksnaga_2
 * Description  : Begins second stage of thraksnaga ceremony.
 * Arguments    : string name - As entered by the user, should consist of
 *                <name>, where name is the name of the person joining.
 * Returns      : 1/0 Success/Failure
 */
public int    
thraksnaga_2(string name)
{
    object anghoth;
    int thraksnaga_permitted, legitimate_anghoth;
    object nazgul = this_player();

    legitimate_anghoth = 1;

    if (IS_MORGUL_MAGE(TP) || TP->query_wiz_level())
    {
        thraksnaga_permitted = 1;
    }
     
    /* Check for wiz or mage. */
    if (!thraksnaga_permitted)
    {
        notify_fail("Worm! Who are you to go about dispensing the "
            + "the duties of the Nine? Begone, imposter!\n");
        return 1;
    }

    if (!strlen(name))
    {
        write("You must specify the creature who will be made Anghoth.\n");
        return 1;
    }

    anghoth = find_player(lower_case(name));

    if (!present(anghoth, ENV(TP)))
    {
        NFN0("Which creature do you wish to be made Anghoth?");
    }

    if (ANGHOTH_MEMBER(anghoth))
    {
        legitimate_anghoth = 0;
    }
     
    /* Check if player has already been inducted. */
    if (!legitimate_anghoth)
    {
        notify_fail("That person is already Anghoth!\n");
        return 0;
    }

    if (thrak_in_progress)
    {
        notify_fail("A Thraksnaga ceremony is already in progress!\n");
        return 0;
    }

    thrak_in_progress = 1;

    set_alarm(1.0, 0.0, &tell_room(environment(nazgul), QCTPNAME(nazgul)
        + " hood moves as if in a breeze and a deep, "
        + "powerful voice comes from underneath it hissing:\n"
        + "\tLet the Mage that brings this one before the Terrible\n "
        + "\tAttention of the Nine present them for elevation!\n", nazgul));
    set_alarm(1.0, 0.0, &write("You say: Let the Mage that brings this one "
        + "before the Terrible Attention of the Nine present them for "
        + "elevation!\n"));

    set_alarm(2.0, 0.0, &end_thraksnaga());

    return 1;
}

/*
 * Function name: thraksnaga_3
 * Description  : Begins third stage of thraksnaga ceremony.
 * Arguments    : string name - As entered by the user, should consist of
 *                <name>, where name is the name of the person joining.
 * Returns      : 1/0 Success/Failure
 */
public int    
thraksnaga_3(string name)
{
    object anghoth;
    int thraksnaga_permitted, legitimate_anghoth;
    object nazgul = this_player();

    legitimate_anghoth = 1;

    if (IS_MORGUL_MAGE(TP) || TP->query_wiz_level())
    {
        thraksnaga_permitted = 1;
    }
     
    /* Check for wiz or mage. */
    if (!thraksnaga_permitted)
    {
        notify_fail("Worm! Who are you to go about dispensing the "
            + "the duties of the Nine? Begone, imposter!\n");
        return 1;
    }

    if (!strlen(name))
    {
        write("You must specify the creature who will be made Anghoth.\n");
        return 1;
    }

    anghoth = find_player(lower_case(name));

    if (!present(anghoth, ENV(TP)))
    {
        NFN0("Which creature do you wish to be made Anghoth?");
    }

    if (ANGHOTH_MEMBER(anghoth))
    {
        legitimate_anghoth = 0;
    }
     
    /* Check if player has already been inducted. */
    if (!legitimate_anghoth)
    {
        notify_fail("That person is already Anghoth!\n");
        return 0;
    }

    if (thrak_in_progress)
    {
        notify_fail("A Thraksnaga ceremony is already in progress!\n");
        return 0;
    }

    thrak_in_progress = 1;

    set_alarm(1.0, 0.0, &tell_room(environment(nazgul), "The voice hisses "
        + "from " + QTPNAME(nazgul) + " hood: Very well. Know this "
        + CAP(name) + "....\n", nazgul));
    set_alarm(1.0, 0.0, &write("You say: Very well. Know this, "
        + CAP(name) + "....\n"));

    set_alarm(5.0, 0.0, &tell_room(environment(nazgul), "The voice hisses "
        + "from " + QTPNAME(nazgul) + " hood: You are now "
        + "entering the service of a Lord Mage. You will answer to your Lord "
        + "and the Nine. It is your duty now to protect your Lord's life and to "
        + "faithfully work on the krakgor!\n", nazgul));
    set_alarm(5.0, 0.0, &write("You say: You are now entering the service "
        + "of a Lord Mage. You will "
        + "answer to your Lord and the Nine. It is your duty now to protect "
        + "the life of your Lord and to faithfully work on the krakgor!\n"));

    set_alarm(10.0, 0.0, &tell_room(environment(nazgul), "The voice hisses "
        + "from " + QTPNAME(nazgul) + " hood: Now, "
        + CAP(name) + ", do you accept this responsibility and "
        + "vow service? If so, vow this instant!\n", nazgul));
    set_alarm(10.0, 0.0, &write("You say: Now, "
        + CAP(name) + ", do you accept this responsibility "
        + "and vow service? If so, vow this instant!\n"));

    set_alarm(11.0, 0.0, &end_thraksnaga());

    return 1;
}

/*
 * Function name: thraksnaga_4
 * Description  : Begins fourth stage of thraksnaga ceremony.
 * Arguments    : string name - As entered by the user, should consist of
 *                <name>, where name is the name of the person joining.
 * Returns      : 1/0 Success/Failure
 */
public int    
thraksnaga_4(string name)
{
    object anghoth;
    int thraksnaga_permitted;
    object nazgul = this_player();

    if (IS_MORGUL_MAGE(TP) || TP->query_wiz_level())
    {
        thraksnaga_permitted = 1;
    }
     
    /* Check for wiz or mage. */
    if (!thraksnaga_permitted)
    {
        notify_fail("Worm! Who are you to go about dispensing the "
            + "the duties of the Nine? Begone, imposter!\n");
        return 1;
    }

    if (!strlen(name))
    {
        write("You must specify the creature who will be made Anghoth.\n");
        return 1;
    }

    anghoth = find_player(lower_case(name));

    if (!present(anghoth, ENV(TP)))
    {
        NFN0("Which creature do you wish to be made Anghoth?");
    }

    if (!ANGHOTH_MEMBER(anghoth))
    {
        notify_fail("That person is not yet granted the ring of the "
           + "Anghoth!\n");
        return 0;
    }

    if (thrak_in_progress)
    {
        notify_fail("A Thraksnaga ceremony is already in progress!\n");
        return 0;
    }

    thrak_in_progress = 1;

    set_alarm(1.0, 0.0, &tell_room(environment(nazgul), "The voice hisses "
        + "from " + QTPNAME(nazgul) + " hood: This ring "
        + "is a reminder of your bond to your Liege. You are now "
        + "Anghoth, a member of the Iron Horde. Failure is not an "
        + "option.\n", nazgul));
     set_alarm(1.0, 0.0, &write("You say: This ring is a reminder of your "
        + "bond to your Liege. You are now Anghoth, a member of the Iron "
        + "Horde. Failure is not an option.\n"));

    set_alarm(5.0, 0.0, &tell_room(environment(nazgul), "The voice hisses "
        + "from " + QTPNAME(nazgul) + " hood: And " + CAP(name) 
        + "...\n", nazgul));
    set_alarm(5.0, 0.0, &write("You say: And " + CAP(name) + "...\n"));

    set_alarm(10.0, 0.0, &tell_room(environment(nazgul), "The voice hisses "
        + "from " + QTPNAME(nazgul) + " hood: Understand that this bond is "
        + "eternal!\n", nazgul));
    set_alarm(10.0, 0.0, &write("You say: Understand that this "
        + "bond is eternal!\n"));

    set_alarm(15.0, 0.0, &tell_room(environment(nazgul), "The voice hisses "
        + "from " + QTPNAME(nazgul) + " hood: Let us exalt, this Thraksnaga "
        + "is at an end!\n", nazgul));
    set_alarm(15.0, 0.0, &write("You say: Let us exalt, this Thraksnaga "
        + "is at an end!\n"));

    set_alarm(16.0, 0.0, &end_thraksnaga());

    return 1;
}

public void
init()
{
    ::init();
    add_action(join_anghoth, "vow");
    add_action(sponsor_anghoth, "elevate");
    add_action(leave_anghoth, "renounce");
    add_action(discharge_anghoth, "discharge");
    add_action(reduce_anghoth, "reduce");
    add_action(claim_ashuk, "claim");
    add_action(declare_ashuk, "declare");
    add_action(thraksnaga_1, "thraksnaga1");
    add_action(thraksnaga_2, "thraksnaga2");
    add_action(thraksnaga_3, "thraksnaga3");
    add_action(thraksnaga_4, "thraksnaga4");

}

