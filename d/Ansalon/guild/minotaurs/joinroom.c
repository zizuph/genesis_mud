/* A simple room where you can join this guild. 
 *
 *
 */

#pragma strict_types
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/local.h";

inherit NETHOSAK_OUT;
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

    sk_add_train(SS_DEFENSE, "dodge attacks", "defense", 0, 50);
    sk_add_train(SS_PARRY, "parry attacks", "parry", 0, 50);
    sk_add_train(SS_BLIND_COMBAT, "fight while blind",
      "blindfighting", 0, 50);
    sk_add_train(SS_APPR_MON, "appraise enemies", "appraise enemy", 0, 50);
    sk_add_train(SS_LOC_SENSE, "navigate the seas", "location sense", 0, 60);
    sk_add_train(SS_SWIM, "swim", "swim", 0, 60);
    sk_add_train(SS_WEP_AXE, "fight with an axe", "axe", 0, 50);
    sk_add_train(SS_SAILING_SKILL, "sail ships", "sail", 70, 80);
    sk_add_train(SS_GUILD_SPECIAL_SKILL, "gore foes with horns",
      "gore", 80, 100);
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
	    write("Only Bloodsea minotaurs may train here.\n");
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

    if(!(present("trainer",TO)))
    {
	write("Without a trainer, you are unable to improve " +
	  "your skills to any extent.\n");
	return 1;
    }
    if(!TP->query_guild_member(GUILD_NAME))
    {
	write("Only Bloodsea minotaurs may train here.\n");
	return 1;
    }
   
    return ::sk_improve(sk);

}

void
reset_nethosak_room()
{
    if(!objectp(trainer))
    {
	trainer = clone_object("/d/Ansalon/guild/minotaurs/trainer");
	trainer->arm_me();
	trainer->move(TO);
    }
}

void
create_nethosak_room()
{
    set_short("at the top of a cliff overlooking the sea");
    set_long("@@long_descr");

    add_item(({"bay","horned bay","bloodsea","blood sea","sea"}), 
               "Below you the Horned Bay "+
               "stretches itself towards the north, south and further out "+
               "to the west where it meets the Bloodsea.\n");
 
    add_item(({"pier","wooden pier","small pier","small wooden pier"}), 
               "Far below you can make out an "+
               "old wooden pier. Even from here it looks very unstable.\n");
    add_item(({"forest"}),
     "The forest looks ancient. Old logs and branches "+
     "fill the forest floor and the strong smell of "+
     "decay and moisture fills the air. The forest "+
     "consists of different sorts of trees, a "+
     "mixture of pines and oaktrees.\n");
 
    add_item(({"trees","oaktrees","pine trees", "pines"}),
     "The trees here consist of a mixture of pines "+
     "and oaktrees. Some of them look quite old "+
     "while others are fairly young.\n");
 
    add_item(({"underbrush","undergrowth"}),
     "The undergrowth here looks dense with different "+
     "plants and herbs. It seems like it's impossible "+
     "to enter it. \n");
 
    add_item(({"trail","path"}),
     "The forest trail twists itself further into "+
     "the forest. It's a bit overgrown with different "+
     "plants and herbs species.\n");

    add_item(({"cliff","edge","grassed edge","view"}),
     "You stand at the edge of a cliff overlooking Horned Bay. " +
     "This spot offers a fine view of the sea.\n");
    add_item(({"ships","ship","stormseeker","huge ship"}),
     "Below you a few ships are docked at the old pier. " +
     "One particularly huge ship stands out at the " +
     "end of the pier, the Stormseeker.\n"); 
 
    add_exit("/d/Ansalon/goodlund/nethosak/forest/room/forest8","east",0);

    /* configure the trainer */
    set_up_skills();
    reset_nethosak_room();

}

string
long_descr()
{
    return tod_descr1()+ " You have stepped out of the forest and " +
    "onto the grassed edge of a cliff overlooking Horned Bay on the isle of Mithas. " +
    "The view from here is impressive, with the waters of the Bloodsea " +
    "lapping against the old pier below you, rocking the ships docked there. " +
    "To your east an overgrown path leads into the forest.\n";
}


int
layjoin(string str)
{
    object sh;
    mixed why;

    if(!str)
    {
	notify_fail("Recite what? The litany of the bloodsea minotaurs?\n");
	return 0;
    }

    if(str != "the litany of the bloodsea minotaurs")
    {
	notify_fail("Syntax to become a Bloodsea minotaur: " +
	  "'Recite the litany of the bloodsea minotaurs'.\n");
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
	switch (sh->add_lay_shadow(this_player()))
	{
	case 1:
	    /* We have successfully shadowed the player, so we're set */
	    write("You raise your fists to the heavens and bellow loudly the litany " +
              "of the Bloodsea minotaurs:\n\n" +
              "    We have been enslaved but have always thrown off our shackles.\n"+
              "    We have been driven back, but always returned to the fray \n" +
              "                      Stronger than before.\n" + 
              "        We have risen to new heights when all other races\n " +
              "                     Have fallen into decay.\n" +
              "   We are the future of Krynn, the fated masters of the entire world.\n"+
              "                 We are the children of destiny.\n\n"+
              "You understand the rightful place of the minotaurs as the master race, " +
              "heir apparent to the world of Krynn! Stop at nothing to conquer that " +
              "which is rightfully yours!\nYou are gifted a golden ring with tiny runes " +
              "carved into it.\n");

	    say(QCTNAME(TP)+ " raises " + HIS(TP) + " fists to the heavens and bellows " +
              "loudly the litany of the Bloodsea minotaurs:\n\n" +
              "    We have been enslaved but have always thrown off our shackles.\n"+
              "    We have been driven back, but always returned to the fray \n" +
              "                      Stronger than before.\n" + 
              "        We have risen to new heights when all other races\n " +
              "                     Have fallen into decay.\n" +
              "   We are the future of Krynn, the fated masters of the entire world.\n"+
              "                 We are the children of destiny.\n\n");


	    log_file(JOINED, extract(ctime(time()), 4, 15) + " " +
	      TP->query_real_name() + " became a Bloodsea minotaur.\n", 500000);

	    return 1;

	case -4:
	    /* The player has a lay guild already, or one of his existing
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
layleave(string str)
{
    if(!str)
    {
	notify_fail("Forsake what? The Bloodsea minotaurs?\n");
	return 0;
    }

    if(str != "the bloodsea minotaurs")
    {
	notify_fail("Syntax to leave the Bloodsea minotaurs: " +
	  "'forsake the bloodsea minotaurs'.\n");
	return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
	write("But you aren't a member of this guild!\n");
	return 1;
    }

    this_player()->remove_lay_member();
    write("You forsake the path of the Bloodsea minotaurs!\n");
    say(QCTNAME(TP) + " forsakes the path of the Bloodsea minotaurs!\n");
    log_file(LEFT, extract(ctime(time()), 4, 15) + " " +
      TP->query_real_name() + " left the Bloodsea minotaurs.\n", 500000);

    return 1;
}


void
init()
{
    ::init();
    add_action(layjoin, "recite");
    add_action(layleave,"forsake");
    /* add the trainer's commands */
    init_skill_raise();

}
