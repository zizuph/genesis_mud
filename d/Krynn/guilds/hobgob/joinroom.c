/* A simple room where you can join this guild. 
 *
 *
 */

#pragma strict_types
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <language.h>
#include <money.h>
#include "/d/Krynn/common/defs.h"

inherit R_FILE
inherit "/lib/skill_raise";

#include "guild.h"

#define EXIT "/d/Krynn/throtyl/rooms/throtyl-8-11-K"
#define COIN_DUMP "/d/Ansalon/balifor/flotsam/room/bottom_of_bay"

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
    sk_add_train(SS_WEP_AXE, "fight with an axe", "axe", 0, 50);
    sk_add_train(SS_APPR_VAL, "appraise value of loot", "appraise value", 0, 40);
    sk_add_train(SS_TRADING, "sell loot", "appraise value", 0, 40);
    sk_add_train(SS_ANI_HANDL, "handle wild animals", "animal handling", 0, 40);
    sk_add_train(SS_RIDING, "ride wild animals", "riding", 0, 40);
    sk_add_train(SS_GUILD_SPECIAL_SKILL, "cause bleeding wounds",
      "bleeding wound", 80, 100);
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
	    write("Only Throtyl Raiders may train here.\n");
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
	write("Without the shaman present, you are unable to improve " +
	  "your skills to any extent.\n");
	return 1;
    }
    if(!TP->query_guild_member(GUILD_NAME))
    {
	write("Only Throtyl Raiders may train here.\n");
	return 1;
    }
   
    return ::sk_improve(sk);

}

void
reset_krynn_room()
{
    if(!objectp(trainer))
    {
	trainer = clone_object("/d/Krynn/guilds/hobgob/trainer");
	trainer->arm_me();
	trainer->move(TO);
    }
}

void
create_krynn_room()
{
    set_short("courtyard of the ruins of East Keep");
    set_long("@@long_descr");

    add_item(({"centre","courtyard","ruins","east keep","keep","citadel"}),
        "You stand in the courtyard of East Keep. Once " +
        "a citadel for the Riders of the Moors, it has since been razed " +
        "except for its outer walls. In the centre of the courtyard is " +
        "a great pit.\n");
    add_item(({"pit","great pit"}),
        "@@pit_desc");
    add_item(({"outer walls","walls","wall"}),
        "The outer walls of East Keep are the only structures still " +
        "in good repair.\n");
    add_item(({"bonfire","bonfire of bones","bones","fire","southern wall"}),
        "Before the southern wall of the ruins is a bonfire - or bonefire? - " +
        "made from the bones of the human defenders of East Keep. The flames " +
        "writhe malevolently, as if the spirits of the defenders are " +
        "trapped from release by the fire. If you <stare into the bonfire> " +
        "you may learn more about the Throtyl Raiders layman guild.\n");

    add_item(({"ruined tower","tower","remains of a ruined tower"}),
        "To your north stands the remains of a ruined tower. It is one " +
        "of the few structures still standing... barely! You could probably " +
        "enter and climb up it.\n");

    add_cmd_item(({"coins from pit","gold from pit","from pit","pit",
        "steel coins from pit","coins from great pit","loot from pit"}),
        ({"get","steal","take"}),
        "The pit is too deep to reach the coins, and the edges of the " +
        "pit too treacherous to climb down easily. You will just have " +
        "to admire the loot collected from up here!\n");

    add_cmd_item(({"ruined tower","tower","up tower","up ruined tower"}),
        ({"enter","climb"}),"@@climb_tower");

    add_exit(EXIT, "out", "@@exit_keep");
    add_exit(EXIT, "northeast", "@@exit_keep", 1, 1);

    /* configure the trainer */
    set_up_skills();
    reset_krynn_room();

}

string
long_descr()
{
    return "You stand in the courtyard of the ruins of East Keep. Once a citadel " +
        "of Throtyl's Riders of the Moors, it has since been overrun by hobgoblin " +
        "marauders, and little remains of it except its outer walls that now " +
        "provide the raiding tribes a secure place to store loot pillaged from " +
        "nearby lands. In the centre of the courtyard is a great pit, while " +
        "before the southern wall is a bonfire of bones. You could also probably " +
        "climb up the remains of a ruined tower to your north.\n";

}

/* Reset the loot pile to zero. Should only be done after testing and when ready
   for guild to open. */
public void
reset_pit()
{
    LOOT_MANAGER->add_raider_loot(0, 0, 0, 0);
}

string
pit_desc()
{
    mapping loot = LOOT_MANAGER->query_raider_loot();
    int steel, platinum, gold, silver;

    if (!m_sizeof(loot))
        return "This pit is where Throtyl Raiders leave the loot they have " +
            "pillaged from the surrounding lands. It is empty.\n";

    steel = loot["raider_loot_tally"][0];
    platinum = loot["raider_loot_tally"][1];
    gold = loot["raider_loot_tally"][2];
    silver = loot["raider_loot_tally"][3];

    if(!steel && !platinum && !gold && !silver)
        return "This pit is where Throtyl Raiders leave the loot they have " +
            "pillaged from the surrounding lands. It sits empty, waiting " +
            "for ambitious marauders to contribute to it.\n";

    return "This pit is where Throtyl Raiders leave the loot they have " +
        "pillaged from the surrounding lands. You make out " +
        LANG_NUM2WORD(steel)+ " steel coins, " + LANG_NUM2WORD(platinum)+
        " platinum coins, " +LANG_NUM2WORD(gold)+ " gold coins, and " +
        LANG_NUM2WORD(silver)+ " silver coins contributed by Throtyl " +
        "Raiders!\n";
}

string
climb_tower()
{

    write("You enter the ruined tower and climb to an upper floor.\n");
    TP->move_living("into the ruined tower",
        "/d/Krynn/throtyl/rooms/keep_shop", 1, 0);
    return "";
}

int
exit_keep()
{
    write("The gates of the outer walls of East Keep open and let you out.\n");
    say("The gates of East Keep open, allowing " +QTNAME(TP)+ " to leave.\n");
    return 0;
}

int
layjoin(string str)
{
    object sh;
    mixed why;
    string race_name = this_player()->query_race_name();

    if(!str)
    {
	notify_fail("Claim what? Your rightful place amongst the Throtyl Raiders?\n");
	return 0;
    }

    if(str != "my rightful place amongst the throtyl raiders")
    {
	notify_fail("Syntax to become a Throtyl Raider: " +
	  "'claim my rightful place amongst the throtyl raiders'.\n");
	return 0;
    }

    if(!IN_ARRAY(race_name, HOBGOB_ELIGIBLE_RACES))
    {
        notify_fail("Only hobgoblins, goblinoids, drow, and ogres may " +
            "claim a place amongst the Throtyl Raiders! " +
            "Begone!\n");
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
	    write("You claim your rightful place amongst the Throtyl Raiders!\n");

	    say(QCTNAME(TP)+ " claims " +HIS(TP)+ " rightful place amongst the " +
              "Throtyl Raiders!\n");


	    log_file(JOINED, extract(ctime(time()), 4, 15) + " " +
	      TP->query_real_name() + " became a Throtyl Raider.\n", 500000);

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
	notify_fail("Desert what? The Throtyl Raiders?\n");
	return 0;
    }

    if(str != "the throtyl raiders")
    {
	notify_fail("Syntax to leave the Throtyl Raiders: " +
	  "'desert the throtyl raiders'.\n");
	return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
	write("But you aren't a member of this guild!\n");
	return 1;
    }

    this_player()->remove_lay_member();
    write("You decide to desert the Throtyl Raiders!\n");
    say(QCTNAME(TP) + " deserts the Throtyl Raiders!\n");
    log_file(LEFT, extract(ctime(time()), 4, 15) + " " +
      TP->query_real_name() + " deserts the Throtyl Raiders.\n", 500000);

    return 1;
}

int
layinfo(string str)
{
    if(!str)
    {
	notify_fail("Stare into what? The bonfire?\n");
	return 0;
    }

    if(str != "into the bonfire")
    {
	notify_fail("Syntax to learn more about the Throtyl Raiders: " +
	  "'stare into the bonfire'.\n");
	return 0;
    }

    setuid();
    seteuid(getuid());
    cat("/d/Krynn/guilds/hobgob/layinfo");

    return 1;
}

int
contribute(string str)
{
    int coin_no, in, loot_level;
    string coin_type, coin_string;
    object st_coin;

    if(!str)
    {
	notify_fail("Contribute how many of what coins?\n");
	return 0;
    }

    //sscanf(str, "%d %s coins", coin_no, coin_type);
    sscanf(str, "%d %s %s", coin_no, coin_type, coin_string);

    if(coin_string != "coin" && coin_string != "coins")
    {
	notify_fail("You can only contribute coins to the hoard!\n");
	return 0;
    }

    if(coin_no > 1)
        coin_string = "coins";
    else
        coin_string = "coin";

    if(!coin_type && !coin_no)
    {
	notify_fail("You can't contribute " +str+ "! You can only " +
            "contribute steel, platinum, gold, or silver coins to the " +
            "hoard!\n");
	return 0;
    }

    if(!coin_no)
    {
	notify_fail("Contribute how many? State a number to contribute!\n");
	return 0;
    }

    if(coin_type == "copper")
    {
	notify_fail("Copper is as worthless as dirt! Your spittle would " +
            "contribute more to the hoard than a handful of copper coins!\n");
	return 0;
    }

    if((coin_type != "steel") && (coin_type != "platinum") &&
        (coin_type != "gold") && (coin_type != "silver"))
    {
	notify_fail("You can't contribute " +coin_type+ "! You can only " +
            "contribute steel, platinum, gold, or silver coins to the " +
            "hoard!\n");
	return 0;
    }

    if(coin_type == "steel")
    {
        if (!objectp(st_coin = present("_krynn_warfare_token", TP)))
        {
	    notify_fail("You don't have steel coins to contribute " +
                "to the hoard!\n");
	    return 0; 
        }

        if ((in = st_coin->num_heap()) < coin_no)
        {
	    notify_fail("You don't have " +coin_no+ " steel coins to " +
                "contribute to the hoard!\n");
	    return 0; 
        }

        if (in > coin_no)
            st_coin->set_heap_size(in - coin_no);
        else
            st_coin->remove_object();

        write("You contribute " +LANG_NUM2WORD(coin_no)+ " " +
            coin_type+ " " +coin_string+ " to the Throtyl Raider hoard!\n");
        say(QCTNAME(TP) + " hurls " +LANG_NUM2WORD(coin_no)+ " " +
            coin_type+ " " +coin_string+ " into the great pit!\n");

        if(MEMBER(TP))
        {
            loot_level = TP->query_skill(SS_RAIDERS_LOOT_VALUE);
            // loot_level += (5000 * coin_no);
            loot_level += (1000 * coin_no);
            TP->set_skill(SS_RAIDERS_LOOT_VALUE, loot_level);
        }
        LOOT_MANAGER->increase_coin(coin_type, coin_no);

        return 1;
    }

    if(MONEY_MOVE(coin_no, coin_type, TP, COIN_DUMP) != 0)
    {
        notify_fail("You don't have " +coin_no+ " " +coin_type+ 
            " " +coin_string+ " to contribute to the hoard!\n");
        return 0; 
    }

    LOOT_MANAGER->increase_coin(coin_type, coin_no);

    if(MEMBER(TP))
    {
        loot_level = TP->query_skill(SS_RAIDERS_LOOT_VALUE);

        switch(coin_type)
        {
            case "platinum":
                // loot_level += (1728 * coin_no);
                loot_level += (172 * coin_no);
                break;
            case "gold":
                // loot_level += (144 * coin_no);
                loot_level += (14 * coin_no);
                break;
            default:
                // loot_level += (12 * coin_no);
                loot_level += (1 * coin_no);
                break;
        }

        TP->set_skill(SS_RAIDERS_LOOT_VALUE, loot_level);
    }

    write("You contribute " +LANG_NUM2WORD(coin_no)+ " " +
        coin_type+ " " +coin_string+ " to the Throtyl Raider hoard!\n");
    say(QCTNAME(TP) + " hurls " +LANG_NUM2WORD(coin_no)+ " " +
        coin_type+ " " +coin_string+ " into the great pit!\n");

    return 1;
}


void
init()
{
    ::init();
    add_action(layjoin, "claim");
    add_action(layleave,"desert");
    add_action(layinfo,"stare");
    add_action(contribute, "contribute");
    /* add the trainer's commands */
    init_skill_raise();

}
