// A npc member of the Society of Morgul Mages that hangs out in 
// the hidden outpost after Osgiliath is attacked
// Copied from Olorin's npc mage /d/Gondor/common/guild2/npc/pharazon.c
//
//  Coded by:  Morbeche Nov 9 1999

// ChangeLog:
// May 7, 2006 - Palmer reduced SEE_INVIS so he won't attack wizards and
//               removed NO_BRAWL prop someone snuck in without adding
//               to the ChangeLog.
// Jul 12, 2010 - Eowul - Won't greet mages that are invis

#pragma save_binary

inherit "/d/Gondor/common/guild2/newnpc/npc_mage";
inherit "/d/Gondor/common/lib/logkill.c";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "../defs.h"
#include "/d/Gondor/private/gondor_admin.h"

#define WEP_ARRAY1 ({MORGUL_DIR + "obj/mattock", MORGUL_DIR + "obj/wraith_mace", MORGUL_DIR + "obj/halberd"})
//#define ARM_ARRAY1 ({MORGUL_DIR + "obj/platehelm", "/d/Gondor/ithilien/camp/arm/smoldering_ring.c"})
#define ARM_ARRAY1 ({MORGUL_DIR + "obj/platehelm" })
#define ARM_ARRAY2 ({MORGUL_DIR + "obj/platemail", GUILD_DIR + "obj/morgul_boots", GUILD_DIR + "obj/morgul_gloves"})

#define MAGES_MEET_SAYS ({ "Trust nobody below your rank!",\
"No Elf is trustworthy, not even Union members!", \
"Hobbit tastes like dwarf gone bad!", \
"I do not get dwarves, what is their point?", \
"Fear the power of the Dark Lord!", \
"It would seem the Dark Lord has favoured you.", \
"I cannot believe any Mage would worship Thanar!", \
"I'm always running out of suranie." })


#define GENERAL_SAYS1   ({ "I lost my damn scabbard.", \
                           "Can you give me a hint on the zodiac quest?", \
                           "Well, got to go.. take care and quest some...", \
                           "Sorry, I don't give out quest info :)", \
                        })

#define GENERAL_SAYS2   ({ "I've no idea, sorry.", "What did you say?", \
                           "Do you have any plats to spare?", \
                           "sorry, lagged ....", "Take care", "Dost thou have a name?", \
			   "Present thyself, wretch!", "What business dost thou have here?", \
                           "Dark travels!", "Shadows keep thee!", \
			   "May the shadows protect thee!", "May the Dark Lord guide thy travels!", \
			   "May the Lidless Eye always hold thee in favour!", \
			   "I am cursed by the chains of Tulkas!", \
                           "My movements are slowed by the curse of Manwe.", \
                           "Curse this slowness of Manwe!", \
                           "Well I'm outta here.", \
                        })
#define KILL_ACTIONS   ({ "think the corpse not worth harvesting for parts.", \
                          "mhiss Oh yeah!  Bring it on!", "shout Die! Die!! Die!!!!", \
                          "ponder easy victims ...", \
                          "think wanting enemies, not victims", \
                          "hiss Say hello to Lars from me", \
                          "hiss There's nothing better than an easy kill", \
                          "ponder why would fight a Mage?!?", \
                        })

void    react_meet(object tp);

int     react_c,
react_alarm,
def_c,
def_alarm;

void
create_mage()
{
    int     rnd = random(10);

    set_name("dukano");
    set_living_name("dukano");
    remove_adj(({"dark-skinned", "red-eyed"}));
    set_adj(({"black-haired", "muscular"}));
    // This is so things won't move behind him
    remove_name(({"_ithil_monster","_morgul_monster"}));

    set_stats(({156+rnd, 176+rnd, 145+rnd, 205+rnd, 205-rnd, 146+rnd,0, 90+rnd,0}));

    remove_prop(LIVE_I_NEVERKNOWN);

    set_alignment(-800-rnd*10);
    set_skill(SS_WEP_POLEARM, 95);
    set_skill(SS_WEP_AXE , 95);
    set_skill(SS_WEP_CLUB, 95);
    set_skill(SS_PARRY,    100);
    set_skill(SS_DEFENCE,  100);
    set_skill(SS_SPELLCRAFT,  100);
    set_skill(SS_FORM_ENCHANTMENT,  100);
    set_skill(SS_FORM_CONJURATION,  100);
    set_skill(SS_FORM_TRANSMUTATION,  95);
    set_skill(SS_ELEMENT_DEATH,  100);
    set_skill(SS_ELEMENT_AIR,  100);
    set_skill(SS_ELEMENT_FIRE,  100);
    set_skill(SS_PROTECT_TEAM_MEMBER, 95);

    set_restrain_path(CAMP_ROOM_DIR);
    set_monster_home(CAMP_ROOM_DIR + "fort5");
    set_random_move(10);

    set_cact_time(5);
    add_act("eat all");
    add_act("drink all");
    add_cact(&emote_enemy("wrath"));
    add_cact("hiss Surely you're not stupid enough to fight a Mage to the death?!");
    add_cact("hiss I hope you don't mind me helping to lower your brute.");

    set_default_answer(VBFC_ME("default_answer"));

	add_prop(OBJ_I_RES_MAGIC, 50);
	add_prop(LIVE_I_SEE_DARK, 100);
	add_prop(LIVE_I_SEE_INVIS, 98);
	add_prop(LIVE_I_QUICKNESS, 100);
    TELL_ADMIN("[Dukano clone at " + ctime(time()) + "]");

}

void
set_arm_arrays()
{
    ::set_arm_arrays();
    Wep1 = WEP_ARRAY1;
    Arm1 = ARM_ARRAY1;
    Arm2 = ARM_ARRAY2;
}

void
loot_corpse()
{
    command("get all from corpse");
    command("spit corpse");
    command(ONE_OF_LIST(KILL_ACTIONS));
}

void
init_living()
{
    object  tp = TP;

    ::init_living();

    if (!interactive(tp) ||
      !CAN_SEE(TO, tp))
	return;

    set_alarm(3.0, 0.0, &react_meet(tp));
}

void
react_morgul(object tp = TP)
{
    if (!present(tp, ENV(TO)))
    {
	react_c = 0;
	remove_alarm(react_alarm);
    }

    switch(react_c++)
    {
    case 0:
	command("present me");
	break;
    case 2:
	command("rasp "+ONE_OF_LIST(MAGES_MEET_SAYS));
	break;
    case 5:
	command("rasp "+ONE_OF_LIST(GENERAL_SAYS2));
	break;
    case 9:
	react_c = 0;
	remove_alarm(react_alarm);
	break;
    default:
	break;
    }
}


void
react_default(object tp)
{
    if (!objectp(tp) || !present(tp, ENV(TO)))
    {
	react_c = 0;
	remove_alarm(react_alarm);
    }

    switch(react_c++)
    {
    case 2:
	command("mbeckon "+tp->query_real_name());
	break;
    case 5:
	command("hiss "+ONE_OF_LIST(GENERAL_SAYS1));
	break;
    case 9:
	command("hiss "+ONE_OF_LIST(GENERAL_SAYS2));
	break;
    case 10:
	react_c = 0;
	remove_alarm(react_alarm);
	break;
    default:
	break;
    }
}

void
react_meet(object tp)
{
    string  occ,
    name = tp->query_real_name(),
    mage_name;

    if (!objectp(tp) || !present(tp, ENV(TO)))
	return;

    occ = tp->query_guild_name_occ();

    switch(occ)
    {
    case GUILD_NAME:
    if (tp->query_prop(OBJ_I_INVIS)) break;
	command("hail "+name);
	/*
	mage_name = MORGUL_MASTER->query_mage_name(tp->query_real_name());
	if (strlen(mage_name))
	{
	    if (tp->query_nazgul())
		mage_name = ", " + (tp->query_gender() == 1 ? "Lady " : "Lord ") + mage_name;
	    else
		mage_name = ", " + mage_name;
	}
	else
	    mage_name = "";
	    */
	mage_name = mage_address(tp);
	command("rasp " + ONE_OF_LIST(
	    ({ "Greetings, " + mage_name + "! How art thou?",
	      "Greetings, " + mage_name + "! How fare thy travels?",
	      "Greetings, " + mage_name + "! What news from the Tower?",
	    })));
	react_c = 0;
	remove_alarm(react_alarm);
	react_alarm = set_alarm(4.0, 5.0, &react_morgul(tp));
	break;
    case "Gondorian Rangers Guild":
	command("snarl "+name);
	command("shout " + ONE_OF_LIST(
	    ({ "Death to all rangers!",
	      "Prepare to be sent West, whelp!",
	      "Finally one of you thieves raises your ugly head!",
	    })));
	break;
    case "Calian warrior's guild":
	command("cackle");
	command("hiss " + ONE_OF_LIST(
	    ({ "I'll rip Calia's colours off your dead body, "+tp->query_name()+"!",
	      "A bit far from Vingaard aren't you, wannabe?",
	      "Rangers are hiring mercenaries to fight their battles now, eh?",
	    })));
	command("snicker");
	break;
    case "Ancient Kaheda Order":
	command("hiss "+ ONE_OF_LIST(
	    ({ "Yeee-Haw, Monks rock!",
	      "Couldn't get into the calians eh, "+tp->query_real_name()+"?",
	    })));
	command("snicker");
	break;
    case "Dragonarmy":
	command("hiss "+ ONE_OF_LIST(
	    ({ "Out causing trouble, eh "+tp->query_real_name()+"?",
	      "Vingaard looted so soon, "+tp->query_real_name()+"?",
	    })));
	command("emote salutes.");
	break;
    case "Dwarven Warriors of the Neidar Clan":
	command("hiss " + ONE_OF_LIST(
	    ({ "The only thing lower than dwarf IQ is dwarf fighting ability!",
	      "Not smart enough to be a gladiator, "+tp->query_real_name()+"?",
	    })));
	command("sneer");
	break;
    case "Solamnian Knights":
	command("hiss " + ONE_OF_LIST(
	    ({ "Paladine can't help you any more, "+tp->query_name()+"!",
	      "The only thing more cowardly than a Knight is a ranger!",
	    })));
	command("sneer");
	break;
    default:
	if ((!tp->query_met(query_real_name())) && (tp->query_alignment() < 0))
	    command("present me");
	if (react_c == 0)
	{
	    remove_alarm(react_alarm);
	    react_alarm = set_alarm(2.7, 6.0, &react_default(tp));
	}
	break;
    }
}

string
default_answer()
{
    if (!def_c)
	def_alarm = set_alarm(2.0, 2.5, "default_react", TP);
    return "";
}

void
default_react(object tp)
{
    if (!objectp(tp) || !present(tp, ENV(TO)))
    {
	def_c = 0;
	remove_alarm(def_alarm);
    }

    switch(def_c++)
    {
    case 0:
	if (tp != query_attack())
	    command("peer "+tp->query_real_name());
	break;
    case 1:
	if (tp == query_attack())
	    command("hiss " + ONE_OF_LIST(
		({ "Your blood will look good as a pool on the ground.",
		   "You cannot defeat me!",
		   "Feel the wrath of the Dark Lord now!",
		})));
	else
	    command("hiss " + ONE_OF_LIST(
		({ "Bow to the power of the Dark Lord!", 
		   "Come to the dark side ...",
		   "You're weak compared to me.",
		   "The Dark Lord's power is increasing. Join him or fail!",
		})));
	break;
    case 2:
	command(ONE_OF_LIST(({"cackle","snicker","smile amus","twinkle amus"})));
	break;
    case 3:
	if (tp != query_attack())
	    command(ONE_OF_LIST(({ "pat "+tp->query_real_name(),
		  "nudge "+tp->query_real_name(),
		  "wink "+tp->query_real_name()
		})));
	def_c = 0;
	remove_alarm(def_alarm);
	break;
    default:
	break;
    }
    if (tp = query_attack())
    {
	return;
    }

}

attacked_by(object ob)
{
    object *arr;

    ::attacked_by(ob);
    TELL_ADMIN("[Dukano attacked by " + ob->query_cap_name() + "("+ob->query_average_stat()+") at " + ctime(time()) + "]");
}
