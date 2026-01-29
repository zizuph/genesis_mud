/* A simple room where you can join this guild and train skills. */

#pragma strict_types

/* Base file for skill trainers */
inherit "/lib/skill_raise";

#include "../guild.h"
#include "/d/Krynn/qualinesti/local.h"
#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <macros.h>

inherit CAMPBASE;

// Prototype
int climb_up(string args);

object trainer;

/*
 * Function name: set_up_skills
 * Description:   Initialize the trainer and set the skills we train
 */
void
set_up_skills()
{
    create_skill_raise();

    sk_add_train(SS_GUILD_EVASION, "distance yourself in combat", "evasion", 80, 100);
    sk_add_train(SS_WEP_MISSILE, "use missile weapons", "archery", 0, 100);
    sk_add_train(SS_DEFENCE, "dodge attacks", "defence", 0, 75);
    sk_add_train(SS_SNEAK, "move silently", "sneak", 0, 90);
    sk_add_train(SS_HIDE, "remain hidden from sight", "hide", 0, 90);
    sk_add_train(SS_TRACKING, "follow the trail left by creatures", "tracking", 0, 90);
    sk_add_train(SS_HUNTING, "hunt game", "hunting", 0, 90);
    sk_add_train(SS_AWARENESS, "be more aware of surroundings", "awareness", 0, 90);
    sk_add_train(SS_LOC_SENSE, "find your bearings", "location sense", 0, 90);
    sk_add_train(SS_APPR_MON, "estimate your opponent", "appraise enemy", 0, 80);
    sk_add_train(SS_ANI_HANDL, "care for animals", "animal handling", 0, 60);
    sk_add_train(SS_FR_TRAP, "set and remove traps", "handle traps", 0, 80);
    sk_add_train(SS_CLIMB, "scale cliffs and climb trees", "climbing", 0, 75);
    sk_add_train(SS_HERBALISM, "identify plant life", "herbalism", 0, 60);
}

void
reset_qualinesti_room()
{
    if(!objectp(trainer))
    {
        trainer = clone_object(TRAINER);
        trainer->move(TO);
    }
}


void
create_camp()
{

    add_my_desc("\n");

    OUTSIDE;

    add_exit(CDIR + "camp4.c", "southeast", 0, 1);

    /* configure the trainer */
    set_up_skills();
    reset_qualinesti_room();

}

int
occjoin(string str)
{
    object sh;
    mixed why;
    int result;


    /* Clone the shadow */

    setuid();
    seteuid(getuid());

    sh = clone_object(OCC_SHADOW);

    /* See if this member is acceptable */
    if (stringp(why = sh->acceptable_member(this_player())))
    {
        write(why);
    }
    else
    {
        /* Try to add the shadow to the player */
        result = sh->add_occ_shadow(this_player());
        switch (result)
        {
            case 1:
                /* We have successfully shadowed the player, so we're set */
            write("You are handed a quiver, and are now ready to "+
                    "learn the lore of an elven archer! You notice elven " +
                    "runes stitched on the quiver that may be of interest "+
                    "as well...\n");
            this_player()->catch_msg(QCTNAME(trainer)+" whispers to you: " +
                "You can <climb up> here to enter your secret guild home.\n");
            
            int tmp = 0;
            /* Make sure that player skills dont exceed the starting limit */
            foreach(int sk: sk_query_train())
            {
                if (sk_query_max(sk, 1) < this_player()->query_skill(sk))
                {
                    tmp++;
                    this_player()->set_skill(sk, sk_query_max(sk, 1));
                }
            }
            
            if (tmp)
            {
                this_player()->catch_msg(QCTNAME(trainer) + " whispers to you: "
                + "You have to unlearn that which you think you know to "
                + "receive my training.\n");
            }
            return 1;

            case -4:
                /* The player has a lay guild already, or one of his existing
                     * guilds has blocked this one.
                     */
            write("Your other guilds don't want you in this one!\n");
            break;

            default:
                /* Some error in shadowing */
            write("An error has prevented you from joining the occ branch.\n" +
                    "Mail error report with this number: " + result +
                    " to Ansalon and Krynn. Thank you\n");
            break;
        }
    }

    /* We couldn't shadow the player, so remove the shadow */
    sh->remove_shadow();
    return 1;
}

int
layjoin(string str)
{
    object sh;
    mixed why;
    int result;


    /* Clone the shadow */

    setuid();
    seteuid(getuid());

    sh = clone_object(LAY_SHADOW);

    /* See if this member is acceptable */
    if (stringp(why = sh->acceptable_member(this_player())))
    {
        write(why);
    }
    else
    {
        /* Try to add the shadow to the player */
        result = sh->add_lay_shadow(this_player());
        switch (result)
        {
            case 1:
                /* We have successfully shadowed the player, so we're set */
            write("You are handed a quiver, and are now ready to "+
                    "learn the lore of an elven archer! You notice elven " +
                    "runes stitched on the quiver that may be of interest "+
                    "as well...\n");
            this_player()->catch_msg(QCTNAME(trainer)+" whispers to you: " +
                "You can <climb up> here to enter your secret guild home.\n");
            return 1;

            case -4:
                /* The player has a lay guild already, or one of his existing
                     * guilds has blocked this one.
                     */
            write("Your other guilds don't want you in this one!\n");
            break;

            default:
                /* Some error in shadowing */
            write("An error has prevented you from joining the lay branch.\n" +
                    "Mail error report with this number: " + result +
                    " to Ansalon and Krynn. Thank you\n");
            break;
        }
    }

    /* We couldn't shadow the player, so remove the shadow */
    sh->remove_shadow();
    return 1;
}

int
declare(string str)
{
    if (!str || (str != "loyalty as an elven archer" &&
        str != "complete loyalty as an elven archer"))
    {
        notify_fail("Declare what? [complete] loyalty as an elven archer?\n");
        return 0;
    }

    if(!objectp(trainer))
    {
        notify_fail("The Loremaster is not present. You are unable to join "+
                    "the elven archers guild.\n");
        return 0;
    }

    if(TP->query_alignment() < -100)
    {
        trainer->command("say I will not train anyone of a nature as cruel "+
                         "as yours.");
        return 1;
    }

    if(str == "complete loyalty as an elven archer")
    {
       /*
        log_file("elven_archers/joined", extract(ctime(time()), 4, 15) + " " +
                TP->query_real_name() + " joined occ archers.\n", 500000);
         */
        return occjoin(str);
    }

    if(str == "loyalty as an elven archer")
    {
        /*
        log_file("elven_archers/joined", extract(ctime(time()), 4, 15) + " " +
                TP->query_real_name() + " joined lay archers.\n", 500000);
                */
        return layjoin(str);
    }


}

int
leave(string str)
{
    if(!str)
    {
        notify_fail("Leave what? The elven archers?\n");
        return 0;
    }

    if(str != "the elven archers")
    {
        notify_fail("Syntax to leave the Elven Archers: " +
          "'leave the elven archers'.\n");
        return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
        write("But you aren't a member of this guild!\n");
        return 1;
    }

    if (this_player()->query_guild_name_occ() == GUILD_NAME)
    {
        this_player()->remove_occ_member();
    }
    else if (this_player()->query_guild_name_lay() == GUILD_NAME)
    {
        this_player()->remove_lay_member();
    }
    else
    {
        write("For some reason you are unable to leave the guild!\n");
        write("Please mail 'ansalon' and cc 'krynn' with this message:\n");
        write("The elven_archer\\joinroom.c unable to to remove the shadow " +
              "in the leave() function. Unable to recognise the GUILD_NAME.\n" +
              "\n We are truly sorry for the " +
              "inconvenience.\n");
        return 0;
    }

	string defstart = TP->query_def_start();
	TP->set_default_start_location(defstart);
    write("You return your quiver.\n");

    return 1;
}


void
remind(object player)
{
    player->catch_tell("You remember that you can <climb up> " +
                       "here to get home.\n");
}

void
init()
{
    ::init();
    add_action(declare, "declare");
    add_action(leave, "leave");
    add_action(climb_up, "climb");
    
    /* add the trainer's commands */
    init_skill_raise();

    if((TP->query_guild_name_occ() == "Ansalon Elvish Archers") ||
       (TP->query_guild_name_lay() == "Ansalon Elvish Archers"))
    {
        set_alarm(0.0, 0.0, &remind(TP));
    }
}

public varargs int
sk_query_max(int snum, int silent)
{
    string  name = this_player()->query_real_name();
    int     max_skill, value, guru, guild_num;

    max_skill = ::sk_query_max(snum, silent);

    if (this_player()->query_guild_name_occ() != GUILD_NAME)
    {
        if (member_array(snum, ({   SS_AWARENESS,   SS_SNEAK,     SS_HIDE,
                                    SS_LOC_SENSE,   SS_HUNTING,   SS_TRACKING,
                                    SS_WEP_MISSILE  })) > -1)
            return 60;
        
        return 0;
    }
    
    if (IN_ARRAY(snum, GUILD_SKILLS))
        return max_skill;
    
    value = 60 + ((max_skill - 60) * this_player()->query_stat(SS_OCCUP) / 120);
    max_skill = min(max_skill, max(value, 60));
    
    if (snum != SS_WEP_MISSILE)
        return max_skill;
    
    guru = OPTIONS_MANAGER->query_option("LoreMasterTraining", name);
    value = min(guru, value);
    if (!this_player()->test_bit("krynn", GROUP, Q_BIT))
        return max(70, value);
    
    return ::sk_query_max(snum, silent);
}

private int
can_train_this_skill(string skill, int step)
{
    /* we allow to forget anything he wants */
    if (step < 0)
        return 1;
    
    if (this_player()->query_guild_name_occ() == GUILD_NAME)
        return 1;
    
    if (this_player()->query_guild_name_lay() == GUILD_NAME)
    {
        string *tmp = explode(lower_case(skill), " ");
        if (tmp[-1] == "max")
            skill = implode(tmp[0..-2], " ");
        
        if (member_array(skill, ({  "awareness",        "sneak",    "hide",
                                    "location sense",   "hunting",  "tracking",
                                    "archery",          "missiles"  })) > -1)
            return 1;
        
        write("You are not allowed to train " + (skill ? "the skill "
        + skill : "that skill" ) + " here.\n" );
        return 0;
    }
    
    write("Only Ansalon Archers can train here.\n");
    return 0;
}

public int
sk_improve(string sk)
{
    int steps;
    string skill, *tmp;

    if (!sk || sscanf(sk, "%d", steps))
    {
        if (!TP->query_guild_member(GUILD_NAME))
        {
            write("You are not welcome to train skills here.\n");
            return 1;
        }
        return sk_list(steps);
    }


    tmp = explode(sk, " ");
    if(sscanf(tmp[sizeof(tmp) -1], "%d", steps) == 1 && sizeof(tmp) > 1)
        skill = implode(tmp[0 .. sizeof(tmp) -2], " ");
    else
    {
        skill = sk;
        steps = 1;
    }

    if(!objectp(trainer))
    {
        write("Without the loremaster, you are unable to improve " +
          "your skills to any extent.\n");
        return 1;
    }

    if(!TP->query_guild_member(GUILD_NAME))
    {
        write("You are not welcome to train any skills here.\n");
        return 1;
    }

	if (can_train_this_skill(skill, steps))
	    return ::sk_improve(sk);
	
    return 1;
}

/**
 * The function that lets the player climb down to the ground
 */
int climb_up(string args)
{
    if(!args)
    {
        if((TP->query_guild_name_occ() == "Ansalon Elvish Archers") ||
           (TP->query_guild_name_lay() == "Ansalon Elvish Archers"))
        {
            notify_fail("Climb what? Up?\n");
        }
        return 0;
    }
    
    if(!(TP->query_guild_name_occ() == "Ansalon Elvish Archers") &&
       !(TP->query_guild_name_lay() == "Ansalon Elvish Archers"))
    {
        return 0;
    }
    
    if(args != "up" && args != "up tree")
    {
        notify_fail("Climb what? Up?\n");
        return 0;
    }
    TP->catch_tell("You climb up the tree.\n");
    tell_room(environment(TP), QCTNAME(TP)+" climbs up a tree.\n", TP);
    TP->move_living("M", ROOMS + "entrance", 1, 0);
    return 1;
}