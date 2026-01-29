/*
 * /d/Gondor/common/guild2/npc/morandir.c
 *
 * A npc member of the Society of Morgul Mages
 *
 * Olorin, August 1997
 *
 * (c) by Christian Markus, 1997
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild2/npc/npc_mage.c";

#include <composite.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define WEP_ARRAY1 ({MORGUL_DIR + "obj/mattock", MORGUL_DIR + "obj/wraith_mace", MORGUL_DIR + "obj/halberd"})
#define ARM_ARRAY1 ({MORGUL_DIR + "obj/platehelm"})
#define ARM_ARRAY2 ({MORGUL_DIR + "obj/platemail"})

#define TOWER_GATE_IN      (MORGUL_DIR + "tower/tower_entrance")
#define TOWER_GATE_OUT     (MORGUL_DIR + "city/mmr3")

#define MAGES_MEET_SAYS ({ "Do you know Gorbag?",  "Be wary of spies and traitors!", \
			   "Do you know of the latest treachery of the WoHS?", \
			   "Elves cannot be trusted!", "Beware of hobbit trickery!", \
			   "Never listen to a dwarf!", "Fear the power of the Dark Lord!", \
			   "It would seem the Dark Lord has favoured you.", \
			   "Hast thou received any new gifts from our Lord?", \
                           "Do you know where to find frostheal?", \
                        })

#define GENERAL_SAYS1   ({ "Which quests have you solved in this area?", \
                           "Can you give me a hint on the zodiac quest?", \
                           "well, got to go.. take care and quest some...", \
                           "hmm.. you have to figure quests out on your own... :)", \
                        })

#define GENERAL_SAYS2   ({ "I've no idea, sorry", "What did you say?", \
                           "Do you have any plats to spare?", \
                           "sorry, lagged ....", "Take care", "Dost thou have a name?", \
			   "Present thyself, wretch!", "What business dost thou have here?", \
                           "Dark travels!", "Shadows keep thee!", \
			   "May the shadows protect thee!", "May the Dark Lord guide thy travels!", \
			   "May the Lidless Eye always hold thee in favour!", \
			   "The curse of Manwe besets me greatly.", \
			   "Cursed are the chains of Tulkas that slow me down!", \
                           "My movements are slowed by the curse of Manwe.", \
                           "Curse this slowness of Manwe!", \
                        })
#define KILL_ACTIONS   ({ "think the corpse isn't even worth scavenging for food", \
                          "hiss Go to hell!", "shout Die! Die!! Die!!!!", \
                          "ponder easy victims ...", \
                          "think wanting enemies, not victims", \
                          "hiss There's nothing better than an easy kill", \
                          "hiss Say hello to Lars from me", \
                          "hiss There's nothing better than an easy kill", \
                        })

public string  reply_society();
public void    default_react(object tp);
public void    reset_morandir();
       void    react_meet(object tp);

static  int     React_C,
                React_Alarm,
                def_c,
                def_alarm,
	        Tour_Alarm,
	        Tour_C,
	        Tour_Ended = 0;
static  string *Met_Names = ({ });
static mapping  Known = ([ ]),
                Met_Descs = ([ ]),
                Killed_Descs = ([ ]),
		Combat_Descs = ([ ]);

public void
create_mage()
{
    int     rnd1 = random(13),
            rnd2 = random(13);

    set_name("morandir");
    // We need to remove this name so the mage is not blocked at
    // exits that are meant to stop roving ithil monsters:
    remove_name("_morgul_monster");
    set_living_name("morandir");
    set_adj( ({ "white-haired", "red-eyed" }));
    set_alignment(MORGUL_I_ALIGN_JOIN - 200 - 20 * rnd1);

    set_stats( ({ 90 + rnd1, 
		  90 + rnd2, 
		  90 + (rnd1 + rnd2)/2, 
		  90 + (rnd1 + rnd2), 
		  80 - rnd1 + rnd2,
		  90 + rnd1 - rnd2,
	           0, 
		  90, 
		   0, 
		      }) );

    remove_prop(LIVE_I_NEVERKNOWN);

    set_skill(SS_WEP_SWORD,	MIN( 90, 70 + rnd1));
    set_skill(SS_WEP_POLEARM,	MIN( 90, 70 + rnd2));
    set_skill(SS_WEP_AXE,	MIN( 90, 70 + 2 * rnd1 - rnd2));
    set_skill(SS_WEP_KNIFE,	MIN( 90, 40 + (rnd1 + rnd2) / 2));
    set_skill(SS_WEP_CLUB,	MIN( 90, 40 - rnd1 + 2 * rnd2));
    set_skill(SS_DEFENCE,	MIN( 90, 75 + rnd1 + rnd2));
    set_skill(SS_PARRY,		MIN( 90, 60 + rnd1 + rnd2));

    set_skill(SS_HERBALISM,	40 + rnd1);
    set_skill(SS_ALCHEMY,	40 + rnd2);

    set_restrain_path( ({ MORGUL_DIR + "city",
			  MORGUL_DIR + "tower", 
			  MAGES_DIR }) );
    set_monster_home(TOWER_GATE_IN);

    add_act("eat all");
    add_act("drink all");
    add_cact(&emote_enemy("wrath"));
    add_cact("hiss I will hurt only a little bit");

    set_default_answer(default_answer);
    add_ask( ({ "society", "mages", "society of morgul mages", "morgul mages", }), 
	     reply_society);

    enable_reset();
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
    command("spit");
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

public void
return_home()
{
    object  env = ENV(TO);
    string *dirs,
	    dir;

    React_C = 0;
    React_Alarm = 0;

    if (!sizeof(dirs = env->query_exit_dirs()))
        dir = "the area";
    else
	dir = ONE_OF_LIST(dirs);
    if (dir == oke_to_move(dir))
    {
        if (file_name(env) != TOWER_GATE_IN)
        {
            move_living(dir, TOWER_GATE_IN);
        }
	command("close gate");

	if (m_sizeof(Met_Descs))
        {
            send_report("I have just returned from my patrol to Osgiliath. " +
			"I am now back at the Tower. On my tour I met " +
			COMPOSITE_WORDS(m_values(Met_Descs)) +
			(m_sizeof(Combat_Descs) ? 
			 ". During the patrol, I engaged in combat with " +
			 COMPOSITE_WORDS(m_values(Combat_Descs)) +
			 (m_sizeof(Killed_Descs) ? " and killed " +
			  COMPOSITE_WORDS(m_values(Killed_Descs)) : "") : "") + ", ");
	    Met_Descs = ([ ]);
	    Killed_Descs = ([ ]);
	    Combat_Descs = ([ ]);
        }

	set_cast_sulambar(1);
    }
}

void
query_tour()
{
    find_living("gwyneth")->catch_msg("React_C " + React_C + "\n" + 
                "React_Alarm " + React_Alarm + "\n" + 
                "def_c " + def_c + "\n" + 
                "def_alarm " + def_alarm + "\n" + 
                "Tour_Alarm " + Tour_Alarm + "\n" + 
                "Tour_C " + Tour_C + "\n" + 
                "Tour_Ended " + Tour_Ended + "\n");

}

public void
tour_osgiliath()
{
    object  obj;

    if (React_C || objectp(query_attack()))
	return;

    switch (Tour_C++)
    {
    case 1:
	if (file_name(ENV(TO)) == TOWER_GATE_IN)
	{
            command("open gate");

            /* Make sure the move is made if door is locked. */
            move_living("on his patrol", TOWER_GATE_OUT);

            /* command("ne"); */
        }
	else
	{
            move_living("to the tower", TOWER_GATE_IN);
	    Tour_C = 0;
	}
	break;
    case 2:
	if (file_name(ENV(TO)) == TOWER_GATE_OUT)
	{
	    command("close gate");
	    Met_Descs = ([ ]);
	    Killed_Descs = ([ ]);
	    Combat_Descs = ([ ]);
	}
	else
	{
            move_living("towards the tower", TOWER_GATE_IN);
	    Tour_C = 0;
	}
	break;
    case 3:
	React_C = 0;
	command("north");
	command("north");
	command("north");
	break;
    case 4:
	command("knock gate");
	command("north");
	set_cast_sulambar(0);
	break;
    case 5:
	command("northwest");
	command("northeast");
	break;
    case 6:
	command("north");
	command("west");
	break;
    case 7:
	command("northwest");
	command("west");
	break;
    case 12:
	command("west");
	command("west");
	command("west");
	break;
    case 13:
	command("climb bank");
	break;
    case 15:
	command("southeast");
	break;
    case 16:
	command("west");
	command("west");
	command("west");
	break;
    case 17:
	command("south");
	command("south");
	break;
    case 18:
	command("southwest");
	command("south");
	break;
    case 19:
	if (objectp(obj = present("spy", ENV(TO))))
	{
            command("mgaze at spy");
	    command("rasp Report what thou hast found out!");
	}
	else
	{
	    command("mwail");
	    command("rasp Where is that wretch?");
	}
	break;
    case 20:
	if (objectp(obj = present("spy", ENV(TO))))
	{
	    obj->command("cringe " + query_name());
	    obj->command("whisper to " + query_name() + " I have not found any news of the ring, my Lord.");
	}
	break;
    case 21:
	if (objectp(obj = present("spy", ENV(TO))))
	{
	    command("mglare spy");
	    command("manger spy");
	}
	break;
    case 22:
	command("south");
	command("east");
	break;
    case 23:
	command("minspect banner");
	break;
    case 24:
	command("south");
	command("south");
	break;
    case 25:
	command("west");
	command("west");
	command("west");
	break;
    case 30:
	command("west");
	command("west");
	command("west");
	break;
    case 31:
	command("north");
	command("north");
	command("north");
	break;
    case 32:
	command("east");
	command("northwest");
	command("northwest");
	break;
    case 36:
	command("west");
	command("west");
	break;
    case 37:
	command("mordor");
	break;
    case 40:
	command("east");
	command("east");
	break;
    case 41:
	command("east");
	command("east");
	command("east");
	break;
    case 42:
	command("east");
	command("east");
	command("east");
	break;
    case 43:
	command("east");
	command("east");
	command("east");
	break;
    case 50:
	command("east");
	command("southeast");
	command("east");
	break;
    case 51:
	command("south");
	command("south");
	break;
    case 52:
	command("southwest");
	command("southeast");
	break;
    case 53:
	command("knock gate");
	command("south");
	set_cast_sulambar(1);
	break;
    case 54:
	command("south");
	command("south");
	command("south");
	break;
    case 55:
	command("open gate");
        /* To ensure that the move is made, even if gate is locked. */

        if (file_name(ENV(TO)) != TOWER_GATE_IN)
        {
            move_living("towards the tower", TOWER_GATE_IN);
        }
/*        command("southwest");  */
	break;
    case 56:
	command("close gate");
	send_report("I have just returned from my patrol to Osgiliath. " +
		    "I am now back at the Tower" +
		    (m_sizeof(Met_Descs) ? ". On my tour I met " +
		     COMPOSITE_WORDS(m_values(Met_Descs)) : "") +
		    ", ");
	break;
    case 58:
	if (m_sizeof(Combat_Descs))
	    send_report("During the patrol, I engaged in combat with " +
			COMPOSITE_WORDS(m_values(Combat_Descs)) + 
			(m_sizeof(Killed_Descs) ? " and killed " +
			 COMPOSITE_WORDS(m_values(Killed_Descs)) : "") +
			", ");
	Met_Descs = ([ ]);
        Killed_Descs = ([ ]);
        Combat_Descs = ([ ]);
	break;
    case 60..999:
	if (file_name(ENV(TO)) != TOWER_GATE_IN)
        {
	    set_alarm(1.0, 0.0, return_home);
        }

	Tour_Ended = 1;
	Tour_C = 0;
        set_alarm(2700.0,0.0,reset_morandir);
	remove_alarm(Tour_Alarm);
	break;
    default:
	break;
    }
}

void
remote_tour()
{
    if (file_name(environment()) != TOWER_GATE_IN)
    {
        return;
    }

    if (Tour_C)
    {
        return;
    }
    else
    {
        command("msniff");
        set_alarm(1.0, 0.0, &command("mwail"));
        React_C = 0;
        remove_alarm(React_Alarm);
        Tour_C = 1;
        Tour_Alarm = set_alarm(2.0, 5.0, tour_osgiliath);
    }
}

void
react_morgul(object tp = TP)
{
    if (!objectp(present(tp, ENV(TO))))
    {
	remove_alarm(React_Alarm);
	if (Tour_C)
	    React_C = 0;
	else
	{
	    React_C = 999;
	    React_Alarm = set_alarm(5.0, 0.0, return_home);
	}
    }

    switch (React_C++)
    {
    case 0:
	if (!tp->query_met(query_name()))
	    command("present me to " + tp->query_real_name());
	if (Tour_C && random(2))
	{
	    React_C = 0;
	    remove_alarm(React_Alarm);
	}
	break;
    case 1:
	if (Tour_C)
	{
	    remove_alarm(React_Alarm);
	    React_C = 0;
	    if (random(2))
            {
		command("rasp "+ONE_OF_LIST(MAGES_MEET_SAYS));
            }            
	}
	else if ((file_name(ENV(TO)) == TOWER_GATE_IN) && !Tour_Ended)
	{
	    command("rasp I have been commanded to go on a patrol to the ruins of Osgiliath.");
	    command("rasp Dark travels to thee, " + mage_address(tp) + ".");
	    React_C = 0;
	    remove_alarm(React_Alarm);
	    Tour_C = 1;
	    Tour_Alarm = set_alarm(2.0, 5.0, tour_osgiliath);
	}
	break;
    case 2:
	command("rasp "+ONE_OF_LIST(MAGES_MEET_SAYS));
	break;
    case 3:
	command("rasp "+ONE_OF_LIST(GENERAL_SAYS2));
	break;
    case 4:
	React_C = 999;
	remove_alarm(React_Alarm);
	React_Alarm = set_alarm(5.0, 0.0, return_home);
	break;
    default:
	break;
    }
}

void
react_angmar(object tp)
{
    if (!present(tp, ENV(TO)))
    {
        React_C = 0;
        remove_alarm(React_Alarm);
    }
    
    switch(React_C++)
    {
    case 0:
	command("present me");
	break;
    case 2:
	command("pat "+tp->query_real_name());
	break;
    case 4:
	command("say "+ONE_OF_LIST(GENERAL_SAYS2));
	break;
    case 8:
	command("say "+ONE_OF_LIST(GENERAL_SAYS1));
	break;
    case 9:
	React_C = 0;
	remove_alarm(React_Alarm);
	break;
    default:
	break;
    }
}

public void
react_default(object tp)
{
    if (!objectp(tp) || !present(tp, ENV(TO)))
    {
        React_C = 0;
        remove_alarm(React_Alarm);
    }

    switch(React_C++)
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
	React_C = 0;
	remove_alarm(React_Alarm);
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

    switch (occ)
    {
    case GUILD_NAME:
	command("hail "+name);
	Met_Names += ({ name });
	if (member_array(name, Met_Names) < 0)
	{
	    mage_name = mage_address(tp);
	    command("rasp " + ONE_OF_LIST(
		({ "Greetings, " + mage_name + "! How art thou?",
		       "Greetings, " + mage_name + "! How fare thy travels?",
		       })));
	}
	React_C = 0;
	remove_alarm(React_Alarm);
        React_Alarm = set_alarm(4.0, 5.0, &react_morgul(tp));
	break;
    case "Gondorian Rangers Guild":
	command("snarl "+name);
	command("shout Death to all rangers!");
	break;
    case "Shield and Club Warriors":
	command("shout ANGMAR! ANGMAR!! ANGMAR!!!!");
	command("cackle");
	if (React_C == 0)
	{
	    remove_alarm(React_Alarm);
	    React_Alarm = set_alarm(5.5, 4.0, &react_angmar(tp));
	}
	break;
    case "Calian warrior's guild":
	command("cackle");
        command("say I'll rip Calia's colours off your dead body, "+tp->query_race_name()+"!");
	break;
    case "Solamnian Knights":
        command("say Paladine can't help you any more, "+tp->query_race_name()+"!");
	command("sneer");
	break;
    default:
	if ((!tp->query_met(query_real_name())) && (tp->query_alignment() < 0))
	    command("present me");
	if (React_C == 0)
	{
	    remove_alarm(React_Alarm);
	    React_Alarm = set_alarm(2.7, 6.0, &react_default(tp));
	}
	break;
    }
}

public string 
reply_society()
{
    command("mturn " + TP->query_real_name());
    command("hiss Why dost thou desire information on the Society of Morgul Mages, " + 
	    TP->query_race_name() + "?");
    return "";
}

string
default_answer()
{
    if (!def_c)
        def_alarm = set_alarm(2.0, 2.5, &default_react(TP));
    return "";
}

public void
default_react(object tp)
{
    if (!objectp(tp) || !present(tp, ENV(TO)))
    {
        def_c = 0;
        remove_alarm(def_alarm);
    }

    switch (def_c++)
    {
    case 0:
	if (tp != query_attack())
	    command("peer "+tp->query_real_name());
	break;
    case 1:
	if (tp == query_attack())
            command("hiss ask Lars, you're going to meet him!");
	else
	    command("say hey, I'm no npc, stupid");
	break;
    case 2:
	command("cackle");
	break;
    case 3:
	if (tp != query_attack())
	    command("pat "+tp->query_real_name());
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

/*
 * Function name: oke_to_move
 * Description:   Check if it is ok to move.
 * Argument:      exit - direction
 * Returns:       command to be executed by the npc
 */
mixed
oke_to_move(string exit)
{
    if (objectp(TO->query_attack()))
        return 0;

    if (React_C || Tour_C)
	return 0;

    return exit;
}

public void
reset_morandir()
{
    Tour_Ended = 0;
    Met_Names = ({ });
}

public void
init_attack()
{
    string  name = TP->query_real_name();

    ::init_attack();

    if (interactive(TP))
    {
//	command("say " + TP->query_real_name() + ", " + LANG_ADDART(TP->query_nonmet_name()));
	if (!strlen(Met_Descs[name]))
	    Met_Descs[name] = LANG_ADDART(TP->query_nonmet_name());
    }
}

/*
 * Function name:   add_introduced
 * Description:     Add the name of a living who has introduced herself to us
 * Arguments:       str: Name of the introduced living
 */
public void
add_introduced(string str)
{
    object  who = find_player(str);

    if (!objectp(who))
	return;

    Known[str] = 1;
    Met_Descs[str] = LANG_ADDART(who->query_nonmet_name()) +
	" presenting " + who->query_objective() + "self as " +
	CAP(str);
    if (Combat_Descs[str])
	Combat_Descs[str] = CAP(str);
}

/*
 * Function name: check_attack
 * Description:   check if we attack someone we meet:
 *                Morandir shouldn't be as trigger happy as his fellow
 *                members of the Society, so he only assists if there is
 *                already combat outside the subdir morgul/
 * Argument:      player - the living we just met
 * Returns:       1/0    - attack/no attack
 */
static int
check_attack(object player)
{
    object  attacker,
           *arr;

    if (TELL_FUNCS->query_subdir(file_name(ENV(TO)))[1] == "morgul")
    {
        if (!player->query_npc() &&
            CAN_SEE(TO, player) &&
            (((query_feeling(player) > -1) &&
              !query_disguised(player)) ||
             (objectp(attacker = player->query_attack()) &&
              attacker->id("_morgul_monster"))))
	{
	    do_attack(player);
	    
	    arr = filter(all_inventory(ENV(TO)), &->id("_morgul_monster")) - ({ TO });
	    arr->order_attack_enemy(TO, player);
	    return 1;
	}
    }
    else
    {
	if (CAN_SEE(TO, player) && (
	    (objectp(attacker) && attacker->query_npc() &&
	     (attacker->query_alignment() < 0))))

	    do_attack(player);
	    
	    arr = filter(all_inventory(ENV(TO)), &->id("_morgul_monster")) - ({ TO });
	    arr->order_attack_enemy(TO, player);
	    return 1;
    }
    return 0;
}

public int
set_tour_ended(int i = 1)
{
    if (i == Tour_Ended)
	return 0;
    Tour_Ended = i;
    return 1;
}

/*
 * Function name:   attack_object
 * Description:     Start attacking, the actual attack is done in heart_beat
 * Arguments:       The object to attack
 */
public void
attack_object(object ob)
{
    string  name;

    ::attack_object(ob);

    Combat_Descs[name = ob->query_real_name()] = 
	(Known[name] ? CAP(name) : "the " + ob->query_nonmet_name());
}

/*
 * Function name:   attacked_by
 * Description:     This routine is called when we are attacked.
 * Arguments:       ob: The attacker
 */
public void
attacked_by(object ob)
{
    string  name;

    ::attacked_by(ob);

    Combat_Descs[name = ob->query_real_name()] = 
	(Known[name] ? CAP(name) : "the " + ob->query_nonmet_name());
}

public void
notify_you_killed_me(object victim)
{
    string  name;

    name = victim->query_real_name();
    Killed_Descs[name] = (Known[name] ? 
			  CAP(name) : 
			  "the " + victim->query_nonmet_name());
    /* log it */
    ::notify_you_killed_me(victim);
}
