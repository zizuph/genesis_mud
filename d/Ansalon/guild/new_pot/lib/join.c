/* Ashlar, 30 Sep 97 */


#pragma strict_types
#pragma no_clone

#include "../guild.h"
#include "../admin/admin.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include "/d/Ansalon/common/defs.h"
#include "../obj/living/npc.h"
#include <macros.h>
#include <composite.h>
#include <const.h>
#include <login.h>

#define A_JOIN_LOG(f, j, w) (log_file(f, sprintf("%s %15s %s the guild (%3d)\n",\
                    extract(ctime(time()), 4), \
                    w->query_name(), \
                    j, \
                    w->query_average_stat() \
                         ), 200000))

#define POT_WANT_TO_LEAVE  "_pot_want_to_leave"
#define POT_CAN_PLEDGE     "_pot_can_pledge"
#define POT_HAS_PLEDGED    "_pot_has_pledged"
#define POT_IS_SPEAKER     "_pot_is_speaker"

object gMaster, gInitiate, gMentor;

/* Prototypes
 */
void perform_initiate(object pl, object tp, int round);
/*
 */

void
set_initiate(object who)
{
    gInitiate = who;
}

object query_initiate() { return gInitiate; }

void
set_master(object who)
{
    gMaster = who;
}

object
query_master()
{
    return gMaster;
}

void
set_mentor(object who)
{
    gMentor = who;
}

object
query_mentor()
{
    return gMentor;
}

void
reset_initiate_vars()
{
    if (objectp(gMaster))
        gMaster->unset_busy(B_SPEAKING);
    gMentor = 0;
    gInitiate = 0;
}

int
sanity_check(object pl, object tp)
{
    string who_left;

    if (!pl || environment(pl) != this_object())
        who_left = "The prospective initiate has left the room, ";
    else if (!tp || environment(tp) != this_object())
        who_left = "The priest performing the initiation has left " +
            "the room, ";
    else if (!gMaster || environment(gMaster) != this_object())
        who_left = "The Master of Rituals has left the room, ";
    
    if (who_left)
    {
        tell_room(this_object(), who_left + "and the initiation is " +
            "aborted.\n");
        reset_initiate_vars();
        return 0;
    }

    return 1;
}

void
finish_initiate(object pl, object tp)
{
    object sh;
    int i, size;

    if (!sanity_check(pl, tp))
        return;

    setuid();
    seteuid(getuid());
    sh = clone_object(POTSHADOW);

    switch (sh->add_occ_shadow(pl))
    {
        case 1:
            pl->catch_tell("You are now a member of the Dark Queen's " +
                "Priesthood!\n");
            tell_room(TO, QCTNAME(pl) + " is now a member of the " +
                "Dark Queen's Priesthood!\n", ({ pl }));
            tp->catch_tell("You successfully initiated " +
                pl->query_the_name(tp) + " into the guild.\n");

            for (i = 0, size = sizeof(PS_NUM) ; i < size ; i++)
                pl->remove_skill(PS_NUM[i]);

            pl->clear_guild_stat(SS_OCCUP);
            pl->set_skill(PS_STANDING, -99);

            if (ATTACKERS_ADMIN->remove_attacker(pl->query_real_name(),
                "joined the PoT") == "Ok.\n")
            {
                pl->catch_msg("As you join the guild, you are forgiven " +
                    "your past transgressions against the guards of " +
                    "Neraka.\n");
            }

            (GUILD_ADMIN)->log(tp, "join", "Initated " +
                pl->query_real_name() + " into the guild");
            (GUILD_ADMIN)->add_priest(pl, query_mentor());
            (NERAKA_ADMIN)->tell_neraka("temple/","You hear the muted " +
                "sound of the bells of the temple tolling.\n", 2);
            (NERAKA_ADMIN)->tell_neraka(({"temple/","inner/","outer/"}),
                "You hear the bells of the temple tolling, a low, " +
                "omnious sound.\n",1);
            (GUILD_ADMIN)->remove_priest_punishment(pl, P_TRAINING_RESTRICTED);

            reset_initiate_vars();
            
            return;

        case -4:
            /* The player has an occ guild already, or one of his
             * existing guilds has blocked this one.
             */
            pl->catch_msg("Your other guilds don't want you in this one!\n");
            tell_room(this_object(), QCTNAME(pl) + " is split in " +
                "loyalties, and cannot finish the initiation.\n", pl);
            break;

        default:
            /* Some error in shadowing */
            tell_room(this_object(), "An error occured that prevented " +
                "a successful initiation. Report this to the responsible " +
                "wizards " + COMPOSITE_WORDS(map(GUILDMASTERS, capitalize)) +
                "!\n");
            break;
    }

    sh->remove_object();
    reset_initiate_vars();    
}

/* Function name: wait_for_step
 * Description:   Awaits the player who will be the initiates mentor
 *                to perform the step forward command as to have him
 *                or her take an active part in the initiation
 * Arguments:     object pl - the initiate
 *                object tp - the initiater
 *                int round - at what 3 second delay we are at
 */
varargs void
wait_for_step(object pl, object tp, int round = 1)
{
    /* The mentor has stepped forward, let us continue with the initation */
    if (query_mentor())
    {
        set_alarm(2.0, 0.0, &perform_initiate(pl, tp, 10));
        return;
    }
    
    /* 1 minute has passed since we asked the would-be mentor to step forward
     * We give him no more and end the initation.
     */
    if (round >= 20)
    {
        gMaster->command("say My patience is only so long. Do not try " +
            "it again.");

        reset_initiate_vars();

        return;
    }

    /* Every 9 seconds our master of rites will remind the would-be
     * mentor to step forward
     */
    if (!(round % 3))
    {
        switch (random(3))
        {
            case 0:
                gMaster->command("say Is there no one who speaks for " +
                    "this " + (pl->query_gender() == G_FEMALE ? "woman" :
                    "man") + "!?");
                break;
            case 1:
                gMaster->command("say Step forward, you who would speak " +
                    "for this " + (pl->query_gender() == G_FEMALE ?
                    "woman" : "man") + ".");
                break;
            case 2:
                gMaster->command("say to " + OB_NAME(tp) + " I am soon " +
                    "running out of patience. Will someone step forward!");
                break;
        }
    }
    
    set_alarm(3.0, 0.0, &wait_for_step(pl, tp, round + 1));
}

/* Function name: wait_for_pledge
 * Description:   Awaits the player who is initiated to perform the
 *                command pledge as to have him take an active part
 *                in the initation.
 * Arguments:     object pl - the initiate
 *                object tp - the initiater
 *                int round - at what 3 second delay we are at
 */
varargs void
wait_for_pledge(object pl, object tp, int round = 1)
{
    /* The initate has pledged, let us continue with the initation */
    if (pl->query_prop(POT_HAS_PLEDGED))
    {
        set_alarm(2.0, 0.0, &perform_initiate(pl, tp, 3));
        return;
    }
    
    /* 1 minute has passed since we asked the initate to make a pledge.
     * We give him no more and end the initation.
     */
    if (round >= 20)
    {
        gMaster->command("say My patience is only so long. Do not try " +
            "it again.");

        pl->remove_prop(POT_CAN_PLEDGE);

        reset_initiate_vars();

        return;
    }

    /* Every 9 seconds our master of rites will remind the initate to
     * make a pledge
     */
    if (!(round % 3))
    {
        switch (random(3))
        {
            case 0:
                gMaster->command("say to " + OB_NAME(pl) + " Your pledge, " +
                    "young one. I am waiting.");
                break;
            case 1:
                gMaster->command("say to " + OB_NAME(pl) + " I still " +
                    "await your pledge.");
                break;
            case 2:
                gMaster->command("say to " + OB_NAME(pl) + " I am soon " +
                    "running out of patience. Your pledge if you will!");
                break;
        }
    }
    
    set_alarm(3.0, 0.0, &wait_for_pledge(pl, tp, round + 1));
}

void
perform_initiate(object pl, object tp, int round)
{
    string str;
    
    if (!sanity_check(pl,tp))
        return;
        
    switch(round)
    {
        case 0:
            gMaster->set_busy(B_SPEAKING);
            gMaster->command("say Here we are gathered; to bring into " +
                "the Priesthood...");
            break;
        case 1:
            gMaster->command("say One who is bold and daring, and serves " +
                "the Queen.");
            break;
        case 2:
            gMaster->command("say Now, young " + pl->query_name() +
                ", your pledge.");
            break;
#ifdef 0
        /* Taken care of in the pledge command */
         case 3:
            str = "To the Queen of Darkness\nWith my soul, precious, " +
                "priceless, do I pledge my life.\n";
            pl->catch_tell("You pledge: " + str);
            tell_room(this_object(), QCTNAME(pl) + " pledges: " + str, pl);
            break;
#endif
         case 5:
            gMaster->command("say A great responsibility will be laid " +
                "upon one in this very room. To mentor you, " +
                pl->query_name() + ", into the Priesthood should you be " +
                "deemed fit for service.");
            break;
         case 7:
            gMaster->command("say Will the one who speaks for this " +
                (pl->query_gender() == 1 ? "woman" : "man") + " step " +
                "forward?");
            break;
#ifdef 0
        /* Taken care of in the step forward command */
         case 9:
            str = "I do - \nAnd I serve the Queen; that I bring this " +
                "new member\nTo serve, and to prosper - to bring glory " +
                "and victory - \nWhich is forseen by the Queen herself - " +
                "to our guild.\n";
            tp->catch_tell("You declare: " + str);
            tell_room(this_object(), QCTNAME(tp) + " declares: " + str, tp);
            break;
#endif
         case 12:
            str = "Victory and glory for the Dark Queen of Krynn!\n";
            if (query_mentor() != tp)
            {
                tp->catch_tell("Together with " +
                    gMaster->query_the_name(tp) + " and " +
                    query_mentor()->query_the_name(tp) + ", you chant: " + str);
                query_mentor()->catch_tell("Together with " +
                    gMaster->query_the_name(query_mentor()) + " and " +
                    tp->query_the_name(query_mentor()) + ", you chant: " + str);
                tell_room(this_object(), QCTNAME(tp) + ", " +
                    QTNAME(query_mentor()) + " and " + QTNAME(gMaster) +
                    " chants: " + str, ({ tp, query_mentor() }));
            }
            else
            {
                tp->catch_tell("Together with " + gMaster->query_the_name(tp) +
                    ", you chant: " + str);
                tell_room(this_object(), QCTNAME(tp) + " and " +
                    QTNAME(gMaster) + " chants: " + str, tp);
            }
            
            break;
         case 15:
            tp->catch_tell("You close your eyes and whisper a prayer to " +
                "the Queen of Darkness.\n");
            if (query_mentor() != tp)
                query_mentor()->catch_tell("You close your eyes and " +
                    "whisper a prayer to the Queen of Darkness.\n");
            
            if (query_mentor() != tp)
                tell_room(this_object(), QCTNAME(tp) + " and " +
                    QTNAME(query_mentor()) + " closes their eyes " +
                    "in silent prayer.\n", ({ tp, query_mentor() }));
            else
                tell_room(this_object(), QCTNAME(tp) + " closes " + HIS(tp) +
                    " eyes in silent prayer.\n", tp);
            break;
        case 16:
            gMaster->command("say Listen well; upon your arm will be " +
                "marked...");
            break;
        case 17:
            gMaster->command("say The likeness of a dragon, for like " +
                "dragons we are.");
            break;
        case 18:
            gMaster->command("say And here - ");
            break;
        case 19:
            str = "In the name of the Queen!\n";
            tp->catch_tell("You cast your spell and shout: " + str);
            tell_room(this_object(), QCTNAME(tp) + " shouts: " + str, tp);

            tell_room(this_object(), "A light flashes and a medallion " +
                "appears on the altar.\n");
            break;
        case 20:
            gMaster->command("say The symbol of the Queen's power.");
            break;
        case 21:
            gMaster->command("emote picks up the medallion from the altar.");
            break;
        case 22:
            pl->catch_msg(QCTNAME(gMaster) + " gives you a black " +
                "medallion.\n");
            tell_room(this_object(), QCTNAME(gMaster) + " gives a black " +
                "medallion to " + QTNAME(pl) + ".\n", pl);
            break;
        case 24:
            gMaster->command("say Wear it with pride, Cleric of Takhisis!");
            break;
        case 25:
            (NERAKA_ADMIN)->tell_neraka("temple/","The walls of the temple " +
                "shake as a loud thunderclap is heard!\n",3);
            (NERAKA_ADMIN)->tell_neraka(({"inner/","outer/"}),"A loud " +
                "thunderclap is heard from the direction of the temple.\n");
            break;
    }

    if (round < 25)
    {
        /* When reaching 2 we need to pledge */
        if (round == 2)
        {
            pl->add_prop(POT_CAN_PLEDGE, 1);
            set_alarm(3.0, 0.0, &wait_for_pledge(pl, tp));
            return;
        }
        
        /* When reaching 7 we need to step forward */
        if (round == 7)
        {
            set_alarm(3.0, 0.0, &wait_for_step(pl, tp));
            return;
        }

        set_alarm(3.0, 0.0, &perform_initiate(pl, tp, round + 1));
    }
    else
        set_alarm(3.0, 0.0, &finish_initiate(pl, tp));
}

int
query_initiating_in_progress()
{
    return !(!query_initiate());
}

void
prepare_initiation(object pl, object tp)
{
    if (objectp(gMaster) && gMaster->query_busy(B_SPEAKING))
        gMaster->command("say to " + OB_NAME(tp) + " I am in the middle " +
            "of something here.");
    else
    {
        tp->catch_tell("You prepare to initiate " + pl->query_name() + ".\n");
        set_initiate(pl);
        set_alarm(2.0, 0.0, &perform_initiate(pl, tp, 0));
    }
}

int
do_pledge(string arg)
{
    string str;

    // comment the following two lines out after opening
/*
    set_alarm(1.0, 0.0, &finish_initiate(TP, TP));
    return 1;
*/

    if (!TP->query_prop(POT_CAN_PLEDGE))
        return 0;
    
    str = "To the Queen of Darkness\nWith my soul, precious, " +
          "priceless, do I pledge my life.\n";
    write("You pledge: " + str);
    tell_room(this_object(), QCTNAME(TP) + " pledges: " + str, TP);

    TP->remove_prop(POT_CAN_PLEDGE);
    TP->add_prop(POT_HAS_PLEDGED, 1);

    return 1;
}

int
do_step_forward(string arg)
{
    string str;

    if (!query_initiating_in_progress())
        return 0;

    if (query_mentor())
        return 0;
    
    if (!arg || arg != "forward")
    {
        notify_fail("Step where? Forward?\n");
        return 0;
    }

    if (TP == query_initiate())
    {
        gMaster->command("say to " + OB_NAME(TP) + " Do not interrupt " +
            "the ritual, young one!");
        return 1;
    }

    str = "I do - \nAnd I serve the Queen; in bringing this " +
          "new member\nTo serve, and to prosper - to bring glory " +
          "and victory - \nWhich is forseen by the Queen herself - " +
          "to our guild.\n";
    write("You declare: " + str);
    tell_room(this_object(), QCTNAME(TP) + " declares: " + str, TP);

    set_mentor(TP);
    
    return 1;
}

int
do_leave(string str)
{
    int ratio;

    if (!stringp(str) || (str != "the priesthood"))
    {
        notify_fail("In order to leave you must betray the priesthood.\n");
        return 0;
    }

    if ((time() - this_player()->query_prop(POT_WANT_TO_LEAVE)) > 60)
    {
        // Double-check. If the player wants to leave, he must repeat
        // the command within one minute.
        write("Are you sure you want to betray the Priests of Takhisis? " +
            "If you are, enter the same command once more!\n");
        this_player()->add_prop(POT_WANT_TO_LEAVE, time());
        return 1;
    }

    this_player()->remove_prop(POT_WANT_TO_LEAVE);        

    write("You renounce your vows to Takhisis, Queen of Darkness!\n");
    tell_room(this_object(), QCTNAME(TP) + " renounces " +
        HIS(this_player()) + " vows to the Queen of Darkness!\n",
        this_player());

    setuid();
    seteuid(getuid());
    GUILD_ADMIN->log(TP, "left", "Left the guild on " + HIS(TP) +
        " own accord");
    GUILD_ADMIN->log(TP, "council", "Betrayed our priesthood");

    write("You sink down to your knees as you feel the wrath of the " +
        "Dark Queen center upon you. An agony like worms feeding on " +
        "your soul course through your body, leaving you with an " +
        "empty feeling, as if something is lost.\n");
    tell_room(TO, QCTNAME(TP) + " sinks down to " + HIS(TP) + " knees " +
        "and screams in agony.\n", TP);

    /* punish_for_leaving defined in the shadow, it is NOT called from
       the remove_occ_member function */

    switch (GUILD_ADMIN->query_days_in_guild(TP->query_real_name()))
    {
        case 0..50:
            ratio = 4;
            break;
        case 51..99:
            ratio = 5;
            break;
        case 100..199:
            ratio = 6;
            break;
        default:
            ratio = 7;
            break;
    }

    TP->punish_for_leaving(ratio);
    TP->remove_occ_member();

    write("A booming voice in your mind thunders: \"Begone from my " +
        "temple infidel\".\n");
    TP->set_default_start_location(RACESTART[TP->query_race()]);
    TP->move_living("X", TP->query_default_start_location());
    
    return 1;
}

public void
init_lib_join()
{
    add_action(do_pledge,   "pledge");
    add_action(do_step_forward, "step");
    add_action(do_leave,    "betray");
}
