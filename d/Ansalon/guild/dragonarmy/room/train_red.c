/*
 * Red Dragonarmy training room coded by Milan
 *
 * Modified February 2009 to support the new Dragonarmy Skill
 * manager by Petros
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
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit "/lib/skill_raise";
inherit SANCINROOM;

object warfare_trainer;

void summon_warfare_trainer();

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

void
summon_warfare_trainer()
{
    if(WAR_WINNER == "Red Dragon Army")
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
    if(WAR_WINNER != "Red Dragon Army")
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

    summon_warfare_trainer();   
}


void
create_sanction_room()
{
    set_short("training hall for the Red Dragonarmy");
    set_long("You stand within a long hall made from sturdy " +
      "timber where soldiers of the red dragonarmy train in " +
      "the arts of warfare. Grizzled sergeants oversee such training, " +
      "where recruits <learn> new skills, and soldiers " +
      "<improve> what skills they have.\n");

    add_item(({"hall","long hall","timber"}),
      "The hall you stand in is of grand size, with a lofty " +
      "ceiling and walls of sturdy timber.\n");
    add_item(({"ceiling","lofty ceiling","chandelier",
	"iron chandelier"}),
      "High above you is the ceiling, lit by an iron chandelier.\n");
    add_item(({"walls","wall","timber walls","sturdy walls"}),
      "The timber walls are of a dark rusty-brown " +
      "colour, and are mostly unadorned.\n");
    add_item(({"soldiers","recruits"}),
      "Soldiers and recruits train around you here, filling " +
      "the hall with the sounds of combat.\n");
    add_item(({"grizzled sergeant","sergeant","sergeants",
	"grizzled sergeants"}),
      "You look over to a grizzled sergeant. He notices your stare and " +
      "glares back with steely cold eyes.\n");

    add_exit("/d/Ansalon/taman_busuk/sanction/room/red/r2","south",0);

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    create_skill_raise();
    set_up_skills();
    reset_sanction_room();
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
    sk_add_train(SS_WEP_POLEARM,  "fight with polearms",0,0,100);
    sk_add_train(SS_DEFENCE,    "survive in the combat",0,0,85 );
    sk_add_train(SS_PARRY,  "parry blows with a weapon",0,0,85 );
    sk_add_train(SS_APPR_MON,        "estimate oponent",0,0,70 );
    sk_add_train(SS_AWARENESS,"be aware of surrounding",0,0,75 );
    sk_add_train(SS_ANI_HANDL, "be able handle animals",0,0,70 );
    sk_add_train(SS_BLIND_COMBAT, "fight while blinded",0,0,75 );   
    sk_add_train(SS_DRAGONARMY_ATTACK, "impale an enemy",
                 "impale", 100, 100, SS_DEX, 100);


// Secondary weapon skill options follow.
// Only one can be trained up to a max of 85 based on participation
// in the warfare system.

    sk_add_train(SS_WEP_KNIFE, "fight with knives",     0,0,85);
    sk_add_train(SS_WEP_SWORD, "fight with swords",     0,0,85);
    sk_add_train(SS_WEP_AXE, "fight with axes",     0,0,85);
    sk_add_train(SS_WEP_CLUB, "fight with clubs",     0,0,85);
    sk_add_train(SS_WEP_MISSILE, "fight with bows",     0,0,85);
    sk_add_train(SS_2H_COMBAT, "fight with both hands", 0,0,90 );
}

int
sk_improve(string str)
{
    int steps;
    string skill, *tmp;

    summon_warfare_trainer();

    if (TP->query_dragonarmy_division() != RED_ARMY)
    {
        write("You must be a member of the Red Dragonarmy to be able to train here.\n");
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
        case "sword":
            if(!objectp(warfare_trainer))
                return 0;
            if (DA_SECOND_SKILL(who) == "sword")
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
        case "two handed combat":
            if(!objectp(warfare_trainer))
                return 0;
            else
                return 1;
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

    return SKILL_MANAGER->query_skill_max(TP, snum);
}

int
select(string str)
{
    string weapon;
    int skill_num;

    if(WAR_WINNER != "Red Dragon Army")
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


