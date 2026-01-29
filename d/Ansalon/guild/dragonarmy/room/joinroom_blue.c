/* A simple room where you can join this guild. */

#pragma strict_types

inherit "/std/room";

#include "../guild.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

inherit "/d/Krynn/common/warfare/warfare_map";

#define BLUE_DARMY_VOUCH  "_vouched_for_blue_army"
#define BLUE_DARMY_VOUCH  "_vouched_for_blue_army"
#define BLUE_DARMY_VOUCH_WARN  "_warn_vouch_for_blue_army"

int ANYONE_CAN_JOIN = 1;

object officer;

void 
reset_room()
{
    if(!objectp(officer))
    {
	setuid();
	seteuid(getuid());
	officer = clone_object("/d/Ansalon/taman_busuk/sanction/npc/bakaris");
	officer->arm_me();
	officer->move_living("M", TO, 1, 1);
	tell_room(TO, QCNAME(officer)+" paces into the room.\n");
    }
    else if(E(officer) != TO)
    {
	officer->command("say I do not have time to play!");
	tell_room(E(officer), QCTNAME(officer)+" runs away.\n");
	officer->move_living("M", TO, 1, 1);
	tell_room(TO, QCNAME(officer)+" paces into the room.\n");
    }
}

int
block_exit()
{
    if(objectp(officer) && officer->query_prop(BAKARIS_BLOCKS))
    {
	if (E(officer) == TO && officer->query_attack())
	{
	    TP->catch_tell(officer->query_The_name(TP)+" blocks exit with his body.\n");
	    return 1;
	}
	officer->remove_prop(BAKARIS_BLOCKS);
    }
    return 0;
}

void
create_room()
{
    set_short("command center for the Blue Dragonarmy");

    set_long("You stand within one of the larger tents in " +
      "the Blue Dragonarmy encampment. The large table here " +
      "covered with maps of Ansalon make it perfectly " +
      "clear that this tent is being used as the armies war room.\n");

    add_item(({"large table","table"}),
      "A large table in the center of the tent is covered " +
      "with war maps of Ansalon, with miniature " +
      "soldiers of various armies arrayed across them indicating " +
      "who controls which battlefield.\n");
    add_item(({"maps","map","maps of ansalon","war maps","war map"}),
      "@@exa_maps");
    add_item(({"soldiers","miniature soldiers", "armies"}), "Across " +
      "the map of Krynn miniature soldiers have been arrayed, " +
      "indicating the armies vying for control of these lands.\n");

    add_exit(SBLUE + "r4","west",block_exit);
    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}


string
exa_maps()
{
    say(QCTNAME(TP)+ " examines the soldiers arrayed on the war " +
        "table with interest.\n");
    return "You look at the map on the war table, examining the " +
        "locations of the various armies vying for control of " +
        "Krynn...\n" + exa_warmap();
}

int
vouch(string str)
{
    object *ob;
    object obj;

    if(!strlen(str))
    {
	NF("Vouch for who?\n");
	return 0;
    }

    ob = PARSE_THIS(str, "[for] [the] %l");
    if(!sizeof(ob))
    {
	NF("Vouch for who?\n");
	return 0;
    }

    if(sizeof(ob) > 1)
    {
	NF("Be more specific! You can vouch only for one at a time!\n");
	return 0;
    }
    obj = ob[0];

    if(!present(officer, TO))
    {
	NF("Bakaris is not here. You will have to wait until he returns.\n");
	return 0;
    }

    TP->command("say to bakaris I vouch on my reputation for "+
      obj->query_the_name(TP)+" to join the Blue Dragonarmy.");

    if (TP->query_dragonarmy_division() != "blue" ||
      TP->query_dragonarmy_promotions() < 3)
    {
	officer->command("say Your word means nothing to me!");
	officer->command("say Only a High Officer of the Blue Dragonarmy "+
	  "may vouch for new recruits.");
	return 1;
    }

    if(!TP->query_met(obj))
    {
	officer->command("say To hell with your reputation!");
	officer->command("say You do not even know "+HIS(obj)+" name!");
	return 1;
    }

/*  With RDA numbers being so low this function is commented out

    if (10 * MANAGER->query_member_count(4,"blue") >
	14 * MANAGER->query_member_count(4,"red"))
    {
	officer->command("say Recruitment is stopped until "+
		"I get word back from Kitiara on troop displacement.");
	officer->command("shrug");
    }
    else

*/
    {
	officer->command("say O.K... If you say so...");
	officer->command("emote grins evilly.");
	obj->add_prop(BLUE_DARMY_VOUCH, TP->query_real_name());
    }
    return 1;
}

int
occjoin(string str)
{
    object sh;
    mixed why;
    string color;

    if (!str)
    {
	NF("Sign up to what? One of the dragonarmies?\n");
	return 0;
    }

    if (!sscanf(str, "up to the %s dragonarmy", color))
    {
	NF("The syntax to join is 'sign up to the <colour> dragonarmy.'\n");
	return 0;
    }

    if (!present(officer, TO))
    {
	write("Bakaris isn't here to recruit you. Wait until he returns.\n");
	return 1;
    }

    color = lower_case(color);
    TP->command("say to bakaris I want to sign up to the "+C(color)+" Dragonarmy.");

    if (color != "red" && color != "blue" && color != "green" &&
      color != "black" && color != "white")
    {
	officer->command("kick "+TP->query_real_name());
	officer->command("say There is no army of that colour!");
	return 1;
    }

    if (color != "blue")
    {
	officer->command("say I am recruiting only for Blue Dragonarmy!");
	return 1;
    }

    if (!TP->query_prop(BLUE_DARMY_VOUCH) && !TP->query_prop(BLUE_DARMY_VOUCH_WARN))
    {
        if (ANYONE_CAN_JOIN) {
            officer->command("say You have noone who has vouched for you!  "+
                "If you ask again I'll allow you to join, but only under "+
                "restricted access - or you can find a High Officer "+
                "to vouch for you and join with full access from day one.  ");
            TP->add_prop(BLUE_DARMY_VOUCH_WARN,1);
        } else {
	        officer->command("say Who are you???");
	        officer->command("say Is there anyone who would vouch for you?");
	        officer->command("emote peers around.");
        }
	return 1;
    }

    setuid();
    seteuid(getuid());

    sh = clone_object(BLUE_SHADOW);

    /* See if this member is acceptable */
    if(stringp(why = sh->query_acceptable_occ_dragonarmy_member(TP)))
    {
	officer->command("say "+why);
    }
    else
    {
        mixed the_voucher = TP->query_prop(BLUE_DARMY_VOUCH);
	
	if (!the_voucher)
	{
	  the_voucher = officer;
	}

	/* Try to add the shadow to the player */
	switch(sh->join_dragonarmy(TP, color, the_voucher))
	{
	case 1:
	    /* We have successfully shadowed the player, so we're set */
	    officer->command("say Yes, I think you will make great fodder "+
	      "for the knights lances.");
	    officer->command("laugh cruel");
	    officer->command("say Very well, our barracks are to the north. "+
	      "Make yourself at home recruit!");
        /*Nobody vouched, so punish!*/
        if (!TP->query_prop(BLUE_DARMY_VOUCH)) {
            officer->command("say Since you have nobody to vouch for you, "+
                "I'm going to restrict your access until a High Officer "+
                "or General accepts you fully.");
            MANAGER->add_punishment(TP->query_real_name(), PUN_NOWHO);
            MANAGER->add_punishment(TP->query_real_name(), PUN_NOBOARD);
            MANAGER->add_punishment(TP->query_real_name(), PUN_NOARMOURY);
        }
	    officer->command("emote notes something down on the recruitment list.");
	    return 1;

	case -4:
	    /* The player has an occ guild already, or one of his existing
	     * guilds has blocked this one.
	     */ 
	    officer->command("say I do not like your other guilds!");
	    break;

	default:
	    /* Some error in shadowing */
	    officer->command("say Not now. Maybe later...");
	}
    }

    /* We couldn't shadow the player, so remove the shadow */
    sh->remove_shadow();
    return 1;
}

int
occleave(string str)
{
    if (!strlen(str))
    {
	NF("Discharge yourself from what? The dragonarmy?\n");
	return 0;
    }

    if(str != "myself from the dragonarmy")
    {
	NF("The syntax is 'discharge myself from the dragonarmy'.\n");
	return 0;
    }

    if (TP->query_dragonarmy_division() != "blue")
    {
	write("But you aren't a member of Blue Dragonarmy!\n");
	return 1;
    }

    say(QCTNAME(TP)+" discharges "+HIM(TP)+"self from the Blue Dragonarmy!\n");
    write("You discharge yourself from the Blue Dragonarmy and realize " +
          "you are about to face the Dark Queen's deadly anger. You are going to die!\n");
    if(present(officer, TO))
    {
	officer->command("snarl");
	officer->command("say Coward! Can't handle a bit of blood on your "+
                         "sword eh?");
	officer->command("spit");
	officer->command("say Fine. We don't need your kind anyway. Begone!");
	officer->command("emote furiously crosses a name from the " +
	  "recruitment list.");
    }
    TP->remove_dragonarmy_member();
    return 1;
}

void
init()
{
    ::init();
    add_action(occjoin, "sign");
    add_action(occleave, "discharge");
    add_action(vouch, "vouch");
}
