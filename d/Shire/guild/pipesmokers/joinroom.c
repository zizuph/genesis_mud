/* A simple room where you can join this guild and train. 
 *
 * Edit to Shire room inherits.
 */

#pragma strict_types
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/kalaman/local.h";

inherit KALAMAN_IN;
inherit "/lib/skill_raise";

#include "guild.h"

object trainer;

/*
 * Function name: set_up_skills
 * Description:   Initialize the trainer and set the skills we train
 */
void
set_up_skills()
{
    create_skill_raise();

    sk_add_train(SS_LOC_SENSE, "navigational skills", "location sense", 0, 50);
    sk_add_train(SS_SWIM, "swim", "swim", 0, 60);
    sk_add_train(SS_GUILD_SPECIAL_SKILL, "pipeweed smoking", "smoking", 70, 100);
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
	    write("Only pipesmokers may train their skills here.\n");
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

    if(!TP->query_guild_member(GUILD_NAME))
    {
	write("Only pipesmokers may train their skills here.\n");
	return 1;
    }
   
    return ::sk_improve(sk);

}

void
reset_kalaman_room()
{
    return;
}

void
create_kalaman_room()
{
    set_short("Pipesmokers den for joining and training");
    set_long("@@long_descr");


    /* configure the trainer */
    set_up_skills();
    reset_kalaman_room();

}

string
long_descr()
{
    return "You are in a pipesmokers den. Here you may <join> or <leave> the pipesmokers " +
           "or train pipesmoking skills.\n";
}


int
craftjoin(string str)
{
    object sh;
    mixed why;

    if(!str)
    {
	notify_fail("Join what? The pipesmokers?\n");
	return 0;
    }

    if(str != "pipesmokers")
    {
	notify_fail("Syntax to become a pipesmoker: " +
	  "'join pipesmokers'.\n");
	return 0;
    }


    /* Clone the shadow */

    setuid();
    seteuid(getuid());

    sh = clone_object(GUILD_SHADOW);

    /* See if this member is acceptable */
    if (stringp(why = sh->acceptable_member(this_player())))
    {
	write(why);
    }
    else
    {
	/* Try to add the shadow to the player */
	switch (sh->add_craft_shadow(this_player()))
	{
	case 1:
	    /* We have successfully shadowed the player, so we're set */
	    write("Your lungs cry out in fear as you join the pipesmokers!\n");

	    say(QCTNAME(TP)+ " grabs a pipe, and his lungs let out one last " +
                "healthy weeze as " +HE(TP)+ " joins the pipesmokers!\n");


	    log_file(JOINED, extract(ctime(time()), 4, 15) + " " +
	      TP->query_real_name() + " became a pipesmoker.\n", 500000);

	    return 1;

	case -4:
	    /* The player has a craft guild already, or one of his existing
	     * guilds has blocked this one.
	     */ 
	    write("Your other guilds don't want you in this one!\n");
	    break;

	default:
	    /* Some error in shadowing */
	    write("An error has prevented you from joining.\n");
	    break;
	}
    }

    /* We couldn't shadow the player, so remove the shadow */
    sh->remove_shadow();
    return 1;
}

int
craftleave(string str)
{
    if(!str)
    {
	notify_fail("Leave what? Pipesmokers?\n");
	return 0;
    }

    if(str != "pipesmokers")
    {
	notify_fail("Syntax to leave the pipesmokers: " +
	  "'leave pipesmokers'.\n");
	return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
	write("But you aren't a member of this guild!\n");
	return 1;
    }

    this_player()->remove_craft_member();
    write("You decide tar is better on a torch them in your lungs, and leave the " +
          "pipesmokers!\n");
    say(QCTNAME(TP) + " is no longer a pipesmoker!\n");
    log_file(LEFT, extract(ctime(time()), 4, 15) + " " +
      TP->query_real_name() + " becomes a pipesmoker.\n", 500000);

    return 1;
}


void
init()
{
    ::init();
    add_action(craftjoin, "join");
    add_action(craftleave,"leave");
    /* add the trainer's commands */
    init_skill_raise();

}
