/*Join room for mariners */

#pragma strict_types
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/kalaman/local.h"
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <money.h>
#include "/d/Ansalon/guild/mariner/guild.h"

inherit KALAMAN_IN;
inherit "/d/Ansalon/common/cheater";
inherit "/lib/skill_raise";

#define SHIP "/d/Ansalon/goodlund/bloodsea/obj/fishing_boat"

/*
 * Function name: set_up_skills
 * Description:   Initialize the trainer and set the skills we train
 */
void
set_up_skills()
{
    create_skill_raise();


    sk_add_train(SS_LOC_SENSE, "navigate", "location sense", 0, 50);
    sk_add_train(SS_SWIM, "swim", "swim", 0, 60);
    sk_add_train(SS_GUILD_SPECIAL_SKILL, "sail ships", "sailing", 70, 100);
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
	    write("Only mariners may train their skills here.\n");
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
	write("Only mariners may train their skills here.\n");
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
    set_short("office of the harbourmaster");
    set_long("@@long_descr");

    add_item(({"harbourmaster","master","desk"}),
       "The harbourmaster sits behind a desk here, looking rather " +
       "flustered.\n");
    add_item(({"office"}),
       "The office of the harbourmaster of Kalaman, normally filled " +
       "with ship captains from all over Ansalon, now empty.\n");
    add_item(({"sign","wall"}),
       "A sign has been hurriedly penned and stuck on the wall here. " +
       "You can read it if you want.\n");

    add_cmd_item("sign","read","@@read_sign");
    add_cmd_item("fineprint","read","@@read_fineprint");

    add_exit(KROOM + "road5","east",0);

    /* configure the trainer */
    set_up_skills();
    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand within the office of the harbourmaster of Kalaman. In times " +
       "of peace, this office is normally filled with captains from all corners " +
       "of Ansalon, however with war pending this office is largely empty. A sign " +
       "has been attached to the wall here which you can read.\n";
}

int
read_sign()
{
    write("The sign contains a number of personal messages, and reads:\n\n" +
          "      By order of Lord Calof of Kalaman, free passage along the\n" +
          "      Vingaard River is prohibited until further notice.\n\n\n" +
          "      Current personal <charter>s out of Kalaman Harbour:\n\n" +
          "      Fishing boat    ---    200 gold coins\n" +
          "      Merchant ship   ---    800 gold coins\n" +
          "      Warship         ---   2000 gold coins\n\n\n" +
          "                    ForSale\n" +
          "                 GnomishSpyglass\n" +
          "              PerfectForTheIntrepid\n" +
          "              explorerWhoHasItAll!\n" +
          "                   2GoldCoins\n\n\n" +
          "      Note: Mariners wanted! For those interested in a \n" +
          "      career on the high seas, you can read the fineprint\n" +
          "      about such a career, as well as <enlist> here!\n");

    return 1;
}


int
read_fineprint()
{
    write("The fineprint at the bottom of the sign says:\n\n" +
          "      You can <enlist as a mariner> here, allowing you to\n" +
          "      train sailing skills that allow you to pilot ships of\n" +
          "      varying size, as well as train your swimming skill up\n" +
          "      to an unrivalled level.\n\n" +
          "      This guild will fill your craft slot... thats right, \n" +
          "      craft slot! Not occupational, layman, or racial! So \n" +
          "      sign up now! There is no penalty for becoming a \n" +
          "      landlubber when you leave!\n");

    return 1;
}


int
chartership(string str)
{
    if(!str)
    {
       notify_fail("Charter what?\n");
       return 0;
    }

    if((str != "fishing boat") && (str != "merchant ship") && (str != "warship"))
    {
       notify_fail("That type of charter isn't an option.\n");
       return 0;
    }

    if((str == "merchant ship") || (str == "warship"))
    {
       notify_fail("All merchant ships and warships have been commandeered " +
         "by Lord Calof of Kalaman... hopefully we'll be able to offer these " +
         "vessels to you in the future!\n");
       return 0;
    }


    if(!MONEY_ADD(TP, -28800))
    {
       notify_fail("You cannot afford to pay the charter price.\n");
       return 0;
    }

    write("You charter a ship to sail the seas of Ansalon! It is " +
          "docked at the southern pier, its captain waiting your " +
          "orders.\n");
    say(QCTNAME(TP)+ " charters a ship to sail the seas of Ansalon!\n");

    setuid();
    seteuid(getuid());

    object boat_in, ship, captain;

    ship = clone_object(SHIP);
    ship->move("/d/Ansalon/kalaman/room/dock3");
    ship->config_boat_inside();
    boat_in = ship->query_boat_in();


    captain = clone_object("/d/Ansalon/goodlund/bloodsea/living/chartered_capt1");

    boat_in->set_owner(captain);

    captain->move_living("into his ship", boat_in);
    captain->arm_me();
    captain->equip_me();
    captain->set_owner(TP);

    clone_object("/d/Calia/sea/objects/fish_net")->move(boat_in);

    return 1;

}

int
buyglass(string str)
{
    object glass, who;
    NF("Buy what did you say? spyglass?\n");
    if(!str || (str != "spyglass"))
	return 0;

    if (check_cheater(TP, TO))
        return 1;
    if(str = "spyglass")
    {
	NF("The harbourmaster says: You cannot pay the price.\n");
	if(!MONEY_ADD(TP, -288))
	    return 0;

	write("You pay the harbourmaster and he passes you a battered " +
          "gnomish spyglass.\n");
	say(QCTNAME(TP) + " buys a gnomish spyglass from the harbourmaster.\n");

	who = TP;
	glass = clone_object("/d/Ansalon/goodlund/bloodsea/obj/spyglass");
        if (glass->move(who) != 0)
        {
    	  write("Noticing that you are too burdened to carry the spyglass, the " +
    	    "harbourmaster places it on the ground before you.\n");
    	  say("The harbourmaster places the spyglass on the ground before " 
            + QCTNAME(TP) + ".\n");
    	  glass->move(environment(who));
         }
 
	return 1;
    }
    return 1;
}


int
craftjoin(string str)
{
    object sh;
    mixed why;

    if(!str)
    {
	notify_fail("Enlist as what? A mariner? Note that enlisting " +
           "will occupy your 'craft' guild slot.\n");
	return 0;
    }

    if(str != "as a mariner")
    {
	notify_fail("Syntax to become a mariner: " +
	  "'enlist as a mariner'.\n");
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
	    write("You eagerly look out to sea as you enlist as a mariner!\n");

	    say(QCTNAME(TP)+ " looks eagerly around, after enlisting as " +
             "a mariner!\n");


	    log_file(JOINED, extract(ctime(time()), 4, 15) + " " +
	      TP->query_real_name() + " became a mariner.\n", 500000);

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
	notify_fail("Become what? a landlubber?\n");
	return 0;
    }

    if(str != "a landlubber")
    {
	notify_fail("Syntax to leave the mariners: " +
	  "'become a landlubber'.\n");
	return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
	write("But you aren't a member of this guild!\n");
	return 1;
    }

    this_player()->remove_craft_member();
    write("You decide the sea is not for you, and return to being a landlubber!\n");
    say(QCTNAME(TP) + " is no longer a mariner!\n");
    log_file(LEFT, extract(ctime(time()), 4, 15) + " " +
      TP->query_real_name() + " becomes a landlubber.\n", 500000);

    return 1;
}


void
init()
{
    ::init();
    add_action(chartership, "charter");
    add_action(buyglass, "buy");
    add_action(craftjoin, "enlist");
    add_action(craftleave,"become");
    /* add the trainer's commands */
    init_skill_raise();

}
