/* A simple room where you can join this guild. */

#pragma strict_types

inherit "/std/room";

#include "../guild.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include <cmdparse.h>


#define ROOM1 "/d/Ansalon/taman_busuk/sanction/room/luerkhisis/r1"
#define RED_DARMY_VOUCH "_vouched_for_red_army"
#define RED_DARMY_VOUCH_WARN "_warned_vouch_for_red_army"
#define NERAKA_NPC "/d/Ansalon/taman_busuk/neraka/npc/"

int ANYONE_CAN_JOIN = 1;

object highlord;
object *ogre = allocate(5);

public void reincarnate_corpse(object ob);

void
reset_room()
{
    int i, count = 0;

    setuid();
    seteuid(getuid());

    if(!objectp(highlord))
    {
	highlord = clone_object("/d/Ansalon/taman_busuk/sanction/npc/ariakas");
	highlord->arm_me();
	highlord->move_living("M",TO,1,1);
	tell_room(TO, QCNAME(highlord)+" enters.\n");
    }
    else if(!highlord->query_attack() && E(highlord) != TO)
    {
	tell_room(E(highlord), QCNAME(highlord)+" leaves.\n");
	highlord->move_living("M",TO,1,1);
	tell_room(TO, QCNAME(highlord)+" enters.\n");
    }

    for(i=0; i<sizeof(ogre); i++)
    {
	if(objectp(ogre[i]) && !ogre[i]->query_attack())
	{
	    ogre[i]->remove_object();
	    count++;
	}
    }
    if(count)
    {
	tell_room(TO,(count > 1 ? C(LANG_WNUM(count))+" ogre guards return" :
	    "The ogre guard returns") +
	  " to the guardpost.\n");
    }
}

void
create_room()
{
    set_short("audience chamber of the Dragon Highlord, Ariakas");
    set_long("You stand in a vast audience chamber, lit in a hellish glow from " +
      "a series of blood-red, glowing columns. At the far end " +
      "of the hall is an immense throne, where the ruler of " +
      "all the dragonarmies resides.\n");

    add_item(({"audience chamber","chamber","hall"}),
      "This is the audience chamber of Highlord Ariakas. This " +
      "vast room is flanked by smooth marble columns and is bare " +
      "of any decoration.\n");
    add_item(({"blood-red glowing columns","glowing columns",
	"columns","marble columns","smooth marble columns"}),
      "The marble columns that flank the walls of this chamber " +
      "seem to have torches cleverly hidden on them, giving " +
      "them the impression that they glow with a brilliant " +
      "reddish light.\n");
    add_item(({"huge throne","throne"}),
      "A huge granite throne rests at the end of the audience chamber. " +
      "Surprisingly, it is devoid of the carvings you would expect "+
      "from someone proclaiming himself to be Emperor of Krynn.\n");
    add_item("ceiling","High above you is the ceiling to this "+
      "chamber, illuminated a brilliant reddish colour by cleverly "+
      "hidden torches.\n");
    add_item("torches","You are unable to find any torches, but figure "+
      "there must be some cleverly hidden around here.\n");

    add_exit(ROOM1,"southwest","@@exit_room");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 3);
    reset_room();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(ob->id("corpse"))
    {
	if(objectp(highlord))
	    tell_room(TO, QCTNAME(highlord)+ " starts muttering a prayer to " +
	      "Takhisis.\n", highlord);
	set_alarm(12.0, 0.0, &reincarnate_corpse(ob));
    }
}

public void
reincarnate_corpse(object ob)
{
    object skeleton;

    if(!objectp(highlord))
	return;

    if(!highlord->query_attack())
	return;

    if(!P("corpse",TO))
	return;

    tell_room(TO, QCTNAME(highlord)+ " points a finger at the "+ob->short()+
      " and declares: Arise! By the powers invested in me by the Queen " +
      "of Damnation and Darkness, arise!\n", highlord);
    tell_room(TO, "The " +ob->short()+ " begins to tremble, and " +
      "suddenly its skeleton pulls itself from its trappings!\n", highlord);
    ob->set_decay(0);
    ob->decay_fun();
    skeleton = clone_object(NERAKA_NPC + "skeleton");
    skeleton->set_all_attack_unarmed(50,35);
    skeleton->move(TO);

}

int
exit_room()
{
    if(P("ogre",TO) && !TP->query_dragonarmy_occ_member())
    {
	if(random(TP->query_stat(SS_STR)) > 150)
	{
	    write("You manage to force your way past the ogre "+
	      "guards!\n");
	    say("With a mighty charge, "+QTNAME(TP)+ " manages to "+
	      "force "+HIS(TP)+ " way past the ogre guards!\n");
	    return 0;
	}
	write("An elite ogre guard is in the way! You cannot get out!\n");
	say(QCTNAME(TP)+ " tries to leave out the door, but is blocked " +
	  "by an elite ogre guard.\n");
	return 1;
    }
    write("You step out of the audience chamber of Lord Ariakas.\n");
    return 0;
}

void
summon_guards(object ob)
{
    int i, summon = 1;

    for(i=0; i<sizeof(ogre) && summon; i++)
	if(objectp(ogre[1]))
	    summon = 0;
    if(summon)
    {
	setuid();
	seteuid(getuid());
	tell_room(TO,"Five elite ogre guards rush into the audience chamber!\n",highlord);
	for(i=0; i<sizeof(ogre); i++)
	{
	    ogre[i] = clone_object(SNPC + "ogre_guard");
	    ogre[i]->arm_me();
	    ogre[i]->move_living("M", TO);
	    ogre[i]->command("kill "+OB_NAME(ob));
	}
    }
}

int
vouch(string str)
{
    object *ob, obj;

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
	NF("Be more specific! You can vouch for one at a time!\n");
	return 0;
    }
    obj = ob[0];

    if(!present(highlord, TO))
    {
	NF("Ariakas is not here. You will have to wait until he returns.\n");
	return 0;
    }

    TP->command("say to ariakas I vouch on my reputation for "+
      obj->query_the_name(TP)+" to join the Red Dragonarmy.");

    if(TP->query_dragonarmy_division() != "red" ||
      TP->query_dragonarmy_promotions() < 3)
    {
	highlord->command("say Your word means nothing to me!");
	highlord->command("say Only a High Officer of the Red Dragonarmy "+
	  "may vouch for new recruits.  Otherwise you can just join under "+
      "restricted access without someone vouching.");
	return 1;
    }

    if(!TP->query_met(obj))
    {
	highlord->command("say You expect me to allow someone you " +
	  "don't even know into my army?");
	highlord->command("eyebrow incred");
	return 1;
    }

    if (10 * MANAGER->query_member_count(4,"red") >
      19 * MANAGER->query_member_count(4,"blue"))
    {
	highlord->command("say What? You don't think my "+
	  "army can crush our enemies with the glorious "+
	  "numbers we have? Begone!");
	highlord->command("emote dismisses you.");
    }
    else
    {
	highlord->command("say Very well then.");
	highlord->command("emote smiles imperiously.");
	obj->catch_tell("You have been vouched for.\n");
	obj->add_prop(RED_DARMY_VOUCH, TP->query_real_name());
    }
    return 1;
}

int
occjoin(string str)
{
    object sh;
    mixed why;
    string color;

    if(!str)
    {
	NF("Sign up to what? One of the dragonarmies?\n");
	return 0;
    }

    /* Clone the shadow */
    if(!sscanf(str, "up to the %s dragonarmy", color))
    {
	write("The syntax to join is 'sign up to the <colour> dragonarmy'.\n");
	return 1;
    }

    if(!present(highlord, TO))
    {
	write("Ariakas isn't here to recruit you. Wait until he returns.\n");
	return 1;
    }

    color = lower_case(color);
    TP->command("say to ariakas I want to sign up to the "+C(color)+
      " Dragonarmy.");

    if(color != "red" && color != "blue" && color != "green" &&
      color != "black" && color != "white")
    {
	highlord->command("eyebrow incred");
	highlord->command("say Fool! There is no army of that colour!");
	return 1;
    }

    if(color != "red")
    {
	highlord->command("say I don't recruit for that army! Begone!");
	return 1;
    }

    if(!TP->query_prop(RED_DARMY_VOUCH) && !TP->query_prop(RED_DARMY_VOUCH_WARN))
    {
	highlord->command("eyebrow distrust");
    if (ANYONE_CAN_JOIN) {
        highlord->command("say For all I know, you could be a "+
            "spy!  I'll let you in under restricted access if you ask "+
            "again, or you could have a High Officer or General vouch "+
            "for you to join with full access from day one.\n");
        TP->add_prop(RED_DARMY_VOUCH_WARN, 1);
    } else {
        highlord->command("say For all I know, you could "+
	        "be a spy! If you want to join, find "+
	        "someone to vouch for you.");
    }

	return 1;
    }

    setuid();
    seteuid(getuid());

    sh = clone_object(RED_SHADOW);

    /* See if this member is acceptable */
    if(stringp(why = sh->query_acceptable_occ_dragonarmy_member(TP)))
    {
	highlord->command("say " +why);
    }
    else
    {
        mixed the_voucher = TP->query_prop(RED_DARMY_VOUCH);
      
	if (!the_voucher)
	{
	    the_voucher = highlord;
	}

	/* Try to add the shadow to the player */
	switch(sh->join_dragonarmy(TP, color, the_voucher))
	{
	case 1:
	    /* We have successfully shadowed the player, so we're set */
	    highlord->command("say And my army keeps getting stronger!");
	    highlord->command("cackle");
	    highlord->command("say Excellent... this will annoy the other "+
	      "Highlords to no end...");
	    highlord->command("say The barracks are in the northwestern " +
	      "corner of the Red Dragonarmy encampment. Make yourself at " +
	      "home recruit!");
        /*Nobody vouched, so punish!*/
        if (!TP->query_prop(RED_DARMY_VOUCH)) {
            highlord->command("say But since you have nobody to vouch for you, "+
                "I'm going to restrict your access until a High Officer "+
                "or General accepts you.");
            MANAGER->add_punishment(TP->query_real_name(), PUN_NOWHO);
            MANAGER->add_punishment(TP->query_real_name(), PUN_NOBOARD);
            MANAGER->add_punishment(TP->query_real_name(), PUN_NOARMOURY);
        }
	    highlord->command("emote dismisses everyone with a wave of " +
	      "his hand.");
	    return 1;

	case -4:
	    /* The player has an occ guild already, or one of his existing
	     * guilds has blocked this one.
	     */ 
	    highlord->command("say Your other guilds are not acceptable. " +
	      "Rectify that problem before you return to me!");
	    break;

	default:
	    /* Some error in shadowing */
	    highlord->command("say There are strange things afoot. Return " +
	      "later, I must consult my priests.");
	    break;
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

    if(TP->query_dragonarmy_division() != "red")
    {
	write("But you aren't a member of the Red Dragonarmy.\n");
	return 1;
    }

    write("You discharge yourself from the Red Dragonarmy and realize " +
          "you are about to face the Dark Queen's deadly anger. You are going to die!\n");
    say(QCTNAME(TP)+ " discharges " +HIM(TP)+"self from the Red "+
        "Dragonarmy.\n");
    if(present(highlord, TO))
    {
	highlord->command("emote rises in fury.");
	highlord->command("say So. Unable to handle a military life?");
	highlord->command("say Or could it be you were simply here " +
                          "to spy on my doings?");
	highlord->command("growl");
	highlord->command("shout Guards! Get this dying worm out of my presence!");
	write("You are suddenly grabbed by a pair of elite ogre " +
	  "guards, who proceed to physically escort you out " +
	  "of the temple.\n");
	tell_room(TO, QCTNAME(TP) + " is suddenly grabbed by two elite "+
	  "ogre guards, and is physically escorted out of the chamber.\n", TP);
	TP->move_living("M", SRED + "r6",1,0);
	tell_room(E(TP), "Two elite ogre guards arrive escorting "+QNAME(TP)+
	  " from the audience chamber. They leave "+HIM(TP)+
	  " here and return back.\n", TP);
    }
    TP->remove_dragonarmy_member();
    return 1;
}

void
init()
{
    ::init();
    add_action(vouch, "vouch");
    add_action(occjoin, "sign");
    add_action(occleave, "discharge");
}
