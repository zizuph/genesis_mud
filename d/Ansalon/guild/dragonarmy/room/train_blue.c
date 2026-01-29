/*
 * Blue Dragonarmy training room coded by Milan
 * Modified to not have endless guards by Navarre June 7th 2006
 *
 * Added secondary weapon skill functionality - Arman Dec 2019
 */
#pragma save_binary
#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include "../guild.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit "/lib/skill_raise";
inherit SANCOUTROOM;

int times_to_allow_more_guards = 2;
int number_of_guards_died = 0;

object *guards = allocate(6);
object warfare_trainer;

void summon_guards();
void summon_warfare_trainer();

#define DA_DEBUG(x)        find_player("arman")->catch_msg(x)
#define CLUB_MANAGER     ("/d/Krynn/clubs/warfare/warfare_club_manager")
#define WAR_WINNER       (CLUB_MANAGER->query_army_winner())
#define UNDEAD_TRAINER   "/d/Ansalon/guild/dragonarmy/npc/warfare_trainer"
#define CHANGE_SKILL_PROP "_da_have_chosen_to_change_secondary"
#define DA_SECOND_SKILL(x)  CLUB_MANAGER->query_dragonarmy_second_wep(x)
#define DA_SECOND_SKILL_MAX(x)  CLUB_MANAGER->query_dragonarmy_second_wep_skill_bonus(x)

/*
 *  Prototypes
 */
void set_up_skills();

void summon_guards()
{
    int i;
    for(i=0; i<sizeof(guards); i++)
    {
	if(!guards[i])
	{
	    switch(random(3))
	    {
	    case 0:
		guards[i] = clone_object(DRAGONARMY_NPC+"aurak");
		break;
	    case 1:
		guards[i] = clone_object(DRAGONARMY_NPC+"sivak");
		break;
	    default:
		guards[i] = clone_object(DRAGONARMY_NPC+"bozak");
	    }
	    guards[i]->set_color("blue");
	    guards[i]->arm_draconian();
	    if(i>1)
	    {
		guards[i]->set_hunt_enemy(1);
	    }
	    else
	    {
		guards[i]->set_pick_up_team( ({}) );
		guards[i]->set_no_team_member(1);
	    }
	    guards[i]->move_living("M", TO, 1, 1);
	    tell_room(TO, QCNAME(guards[i])+
	      " enters and takes the guard post.\n");
	}
	else if(!guards[i]->query_attack() && E(guards[i]) != TO)
	{
	    guards[i]->command("say I have to guard the sleeping quarters!");
	    tell_room(E(guards[i]), QCTNAME(guards[i])+" runs away.\n");
	    guards[i]->move_living("M", TO, 1, 1);
	    tell_room(TO, QCNAME(guards[i])+
	      " enters and takes the guard post.\n");
	}
   }
}

void
summon_warfare_trainer()
{
    if(WAR_WINNER == "Blue Dragon Army")
    {
        if(!objectp(warfare_trainer))
        {
            warfare_trainer = clone_object(UNDEAD_TRAINER);
            warfare_trainer->arm_me();
            warfare_trainer->move(TO, 1);
	    tell_room(E(warfare_trainer), "The room suddenly " +
                "chills as " +QTNAME(warfare_trainer)+
                " enters the room.\n");
           warfare_trainer->command("emote speaks with a " +
                "hollow, chilling voice: For ultimate victory " +
                "on the battlefield, the Dark Queen " +
                "favours this Dragonarmy with my undying " +
                "service as Weaponmaster.");

        }
    }
    if(WAR_WINNER != "Blue Dragon Army")
    {
        if(objectp(warfare_trainer))
        {
	    tell_room(E(warfare_trainer), QCTNAME(warfare_trainer)+
                " stares around coldly as if listening " +
                "to a dark summons, before vanishing into the " +
                "shadows.\n");
            warfare_trainer->remove_object();
        }
    }
}

void
reset_sanction_room()
{
    setuid();
    seteuid(getuid());
    summon_guards();
    summon_warfare_trainer();

    times_to_allow_more_guards = 2;
    number_of_guards_died = 0;    
}

void
create_sanction_room()
{
    set_short("training yard in the middle of the Blue Dragonarmy encampment");
    set_long("@@long_descr");

    add_item(({"clearing","yard","training yard"}),
      "This is the training yard for the Blue Dragonarmy. Soldiers " +
      "of that branch may <learn> and <improve> various arts of combat "+
      "here.\n");
    add_item(({"encampment","dragonarmy encampment",
	"blue dragonarmy encampment"}),
      "Surrounding this clearing are numerous tents, set up " +
      "to house the soldiers of the Blue Dragonarmy.\n");
    add_item("soldiers",
      "A number of sweaty soldiers train here in the art of warfare, .\n");
    add_item("sergeants",
      "A few sergeants oversee the training of the soldiers of the " +
      "Blue Dragonarmy here.\n");
    add_item(({"large tent","tent"}),
      "To your north is a large tent, set up to house the " +
      "soldiers of the Blue Dragonarmy while they are stationed " +
      "in Sanction.\n");

    add_exit(SBLUE + "r4","southwest",0);
    add_exit(DGUILD + "start_blue","north","@@enter_tent");

    create_skill_raise();
    set_up_skills();
    reset_sanction_room();
}

int
enter_tent()
{
    int i;
    object guard = 0;

    for(i=0; i<sizeof(guards); i++)
    {
	if(guards[i] && E(guards[i]) == TO)
	{
	    guard = guards[i];
	    break;
	}
    }
    if(guard)
    {
	if(TP->query_dragonarmy_division() != "blue" &&
           TP->query_wiz_level() == 0)
	{
	    write("The draconian on guard stays so that not even a mouse "+
	      "could sneak past him into the sleeping quarters.\n");
	    return 1;
	}
	write("The "+guard->short()+" lets you into the sleeping quarters.\n");
	tell_room(TO, "The "+guard->short()+" lets "+QTNAME(TP)+
	  " into the sleeping quarters.\n", TP, TP);
	return 0;
    }
    else
    {
      if (TP->query_dragonarmy_division() != "blue" &&
          TP->query_wiz_level() == 0)
      {
	write("You decide against going into the " +
              "sleeping area of the blue soldiers.\n");
	return 1;
      }
    }
    return 0;
}

string
long_descr()
{
    return tod_short_descr() + "You stand in the " +
    "center of a clearing, situated in the middle of the Blue " +
    "Dragonarmy encampment. Here soldiers train and practise in the " +
    "arts of warfare, with the clash of steel against " +
    "steel ringing out all around you along with grunts of pain " +
    "and reprimands from overseeing sergeants. "+
    "To your north stands a large tent, the barracks for the " +
    "soldiers stationed here. "+
    season()+ "\n";
}

void
init()
{
    init_skill_raise();
    ::init();

    add_action("select","select");
}

void
set_up_skills()
{
    sk_add_train(SS_WEP_SWORD, "fight with swords",     0,0,100);

    sk_add_train(SS_DEFENCE,   "survive in the combat", 0,0,85 );
    sk_add_train(SS_PARRY,  "parry blows with a weapon",0,0,85 );
    sk_add_train(SS_2H_COMBAT, "fight with both hands", 0,0,85 );
    sk_add_train(SS_BLIND_COMBAT, "fight while blinded",0,0,85 );   
    sk_add_train(SS_AWARENESS,"be aware of surrounding",0,0,75 );
    sk_add_train(SS_ANI_HANDL, "be able handle animals",0,0,70 );
    sk_add_train(SS_DRAGONARMY_ATTACK, "slash an enemy to pieces",
      "slash",100,100,SS_DEX,100);

// Secondary weapon skill options follow.
// Only one can be trained up to a max of 85 based on participation
// in the warfare system.

    sk_add_train(SS_WEP_KNIFE, "fight with knives",     0,0,85);
    sk_add_train(SS_WEP_POLEARM, "fight with polearms",     0,0,85);
    sk_add_train(SS_WEP_AXE, "fight with axes",     0,0,85);
    sk_add_train(SS_WEP_CLUB, "fight with clubs",     0,0,85);
    sk_add_train(SS_WEP_MISSILE, "fight with bows",     0,0,85);
}
int
sk_improve(string str)
{
    int steps;
    string skill, *tmp;

    summon_warfare_trainer();

    if (TP->query_dragonarmy_division() != BLUE_ARMY)
    {
        write("You must be a member of the Blue Dragonarmy to be able to train here.\n");
        return 1;
    }
    
    if (!str || sscanf(str, "%d", steps))
    {
        // By specifying only a number, we allow them to see what skills
        // they can train that number of skills
    	return sk_list(steps);
    }
    
    return ::sk_improve(str);
}

/*
 * Function name: sk_hook_allow_train_skill
 * Description:   Checks to see if a specific person can learn a
 *                a specific skill ( to a specific level ).
 *                ( Default is:  yes )
 * Arguments:     object - The player trying to learn
 *                skill  - The skill trying to train
 *                level  - The level trying to learn to
 * Returns:       1 - yes (default) / 0 - no
 */
public varargs int
sk_hook_allow_train_skill(object who, string skill, int level)
{
    switch(skill)
    {
        case "polearm":
            if(!objectp(warfare_trainer))
                return 0;
            if (DA_SECOND_SKILL(who) == "polearm")
                return 1;
            break;  
        case "axe":
            if(!objectp(warfare_trainer))
                return 0;
            if (DA_SECOND_SKILL(who) == "axe")
                return 1;
            break;  
        case "knife":
            if(!objectp(warfare_trainer))
                return 0;
            if (DA_SECOND_SKILL(who) == "knife")
                return 1;
            break;   
        case "club":
            if(!objectp(warfare_trainer))
                return 0;
            if (DA_SECOND_SKILL(who) == "club")
                return 1;
            break; 
        case "missiles":
            if(!objectp(warfare_trainer))
                return 0;
            if (DA_SECOND_SKILL(who) == "missiles")
                return 1;
            break;
        default:    
            return 1;
    }

    return 1;
}

public varargs int
sk_query_max(int snum, int silent)
{
    int day;
    int max_skill = ::sk_query_max(snum, silent);

    setuid();
    seteuid(getuid());

    // DA_DEBUG("Blue trainroom called sk_query_max for " +snum+ ".");

    return SKILL_MANAGER->query_skill_max(TP, snum);
}


/*
 * This insanity of endless guards ends now!
 * Found by Cotillion, 2006-06-02.
 * Navarre limited the endless guards Cot found.
 */
void
draconian_guard_died()
{
    number_of_guards_died++;
    if(times_to_allow_more_guards>0 && number_of_guards_died >4)
    {
      tell_room(this_object(), "Someone shouts: More guards to protect the bunks!\n");
      set_alarm(itof(2+random(6)), 0.0, &summon_guards());
      times_to_allow_more_guards--;
      number_of_guards_died = 0;
    }
}

int
select(string str)
{
    string weapon;
    int skill_num;

    if(WAR_WINNER != "Blue Dragon Army")
        return 0;

    if(!objectp(warfare_trainer))
        return 0;

    NF("Select <weapon type> as secondary weapon?\n");
    if (!str)
	return 0;

    parse_command(str, TO, "%s 'as' 'secondary' 'weapon'", weapon);

    weapon = lower_case(weapon);

    if(!weapon)
    {
        notify_fail("Select what as secondary weapon?\n");
        return 0;
    }

    if((weapon != "sword") && (weapon != "polearm") && (weapon != "axe") &&
       (weapon != "knife") && (weapon != "club") && (weapon != "bow")) 
    {
        notify_fail(capitalize(weapon)+ " is not a valid weapon type to " +
            "train as a secondary weapon skill.\n");
        return 0;
    }

    if((TP->query_dragonarmy_division() == BLUE_ARMY) && (weapon == "sword"))
    {
        notify_fail(capitalize(weapon)+ " is your Dragonarmy's primary " +
            "weapon. You cannot select it as your secondary!\n");
        return 0;
    }

    if((TP->query_dragonarmy_division() == RED_ARMY) && (weapon == "polearm"))
    {
        notify_fail(capitalize(weapon)+ " is your Dragonarmy's primary " +
            "weapon. You cannot select it as your secondary!\n");
        return 0;
    }

    if(CLUB_MANAGER->query_dragonarmy_second_wep(TP) &&
       !(TP->query_prop(CHANGE_SKILL_PROP)))
    {
        write("Are you sure you wish to change your secondary weapon from " +
            CLUB_MANAGER->query_dragonarmy_second_wep(TP)+ " to " +weapon+
            "? If so repeat your command.\n");
        TP->add_prop(CHANGE_SKILL_PROP, 1);
        return 1;
    }

    if(CLUB_MANAGER->query_dragonarmy_second_wep(TP))
    {
        skill_num = CLUB_MANAGER->query_dragonarmy_ss_wep_type(TP);
        TP->remove_skill(skill_num);
        CLUB_MANAGER->clear_dragonarmy_second_wep(TP);
        write("You feel drained of all knowledge of " +
            CLUB_MANAGER->query_dragonarmy_second_wep(TP)+ " skill.\n");
    } 

    write("You choose to train " +weapon+ " as your secondary weapon " +
        "skill.\n");
    say(QCTNAME(TP)+ " chooses to train " +weapon+ " as " +HIS(TP)+
        " secondary weapon skill.\n");
    CLUB_MANAGER->set_dragonarmy_second_wep(TP, weapon);

    return 1;   

}

