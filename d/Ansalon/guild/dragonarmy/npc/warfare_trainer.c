#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <options.h>
#include <ss_types.h>

#include "/d/Ansalon/common/defs.h";

inherit AM_FILE

#define CLUB_MANAGER     ("/d/Krynn/clubs/warfare/warfare_club_manager")
#define WAR_WINNER       (CLUB_MANAGER->query_army_winner())

#define ARM1 "/d/Krynn/guilds/knights/guildhall/armours/full_armour"
#define ARM2 "/d/Krynn/guilds/knights/guildhall/armours/s_helm"
#define WEP  "/d/Krynn/guilds/knights/guildhall/weapons/two_handed_sword"

void
create_krynn_monster()
{
    set_race_name("undead human"); 
    set_name("colm");
    set_living_name("colm");
    set_title("Farold of Dargaard Keep, Knight of the Black Rose, " +
        "Weaponmaster");  
    add_name("knight");
    add_prop(LIVE_I_UNDEAD, 100);
    set_adj("greater");
    add_adj("death");
    add_adj("heavily-armoured");
    add_adj("armoured");
    set_short("heavily-armoured death knight");
    set_long("Before you stands a dark figure heavily armoured in " +
        "ancient Solamnic plate that is blackened, charred, and " +
        "melted - as if it had been in a fire. The great helm " +
        "is open, revealing nothing but shadows and two eyes that " +
        "glow like the flames of hell! A death knight! Sent by the " +
        "goddess Takhisis as a reward to the Dragonarmy victorious " +
        "in conquering the battlefields of Krynn to train participating " +
        "soldiers in additional weaponry skills.\n");

    set_default_answer("emote does not respond to your question.", 1);
    add_ask(({"skills","training","train","weaponry skills","weaponry"}),
        VBFC_ME("skills_hint"));
    add_ask(({"dargaard keep","lord soth","soth"}),
        "emote speaks with a hollow, chilling voice: Death claimed " +
        "me when the Cataclysm struck in the flames of Dargaard Keep. " +
        "Pledged to Lord Loren Soth of the Rose, I rose in death at " +
        "his call to serve out an eternal punishment for my role in " +
        "his grim deeds.", 1);
    add_ask(({"weapon","weapon skill","weapons"}),
        "emote speaks with a hollow, chilling voice: I can train " +
        "sword, polearm, axe, knife, club, or bow.", 1);
    add_ask(({"takhisis","reward"}),
        "emote speaks with a hollow, chilling voice: As a reward for " +
        "your Dragonarmy's victory in conquering Krynn, I have been " +
        "summoned as a reward to train you in additional weaponry " +
        "skills.", 1);

    set_stats(({300,160,400,1800,190,280}));

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 80);


    set_alignment(-1200);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_HEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 35000);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(OBJ_M_NO_ATTACK,"As you attack " +short()+ ", he turns " +
        "ethereal, foiling your attempt.\n");

    set_act_time(40);
    add_act("emote turns his flaming eyes towards you.");
    add_act("emote inspects his ancient tarnished greatsword carefully.");
    add_act("emote speaks with a hollow, chilling voice: Honour " +
        "was my life. Now meaningless in death.");
    add_act("emote leans upon his ancient tarnished greatsword, waiting " +
        "with the patience of one who has long been dead.");

    trig_new("%w 'introduces' %s","react_to_intro");
}

string
skills_hint()
{
    command("emote speaks with a hollow, chilling voice: As the victorious " +
        "Dragonarmy upon the battlefields of Krynn, the dark goddess " +
        "Takhisis has summoned me to your training halls as as a reward " +
        "for the glory achieved in her name.");
    command("emote speaks with a hollow, chilling voice: I offer martial " +
        "training in any weapon skill. Simply <select> [weapon] <as " +
        "secondary weapon> and you may train that weapon with me " +
        "up to the rank of confident master.");
    command("emote speaks with a hollow, chilling voice: How far towards " +
        "that rank I train you will depend on the glory you have achieved " +
        "on the battlefield.");
    command("emote speaks with a hollow, chilling voice: The more " +
        "combatants you have slain and the more battlefields you have " +
        "conquered will dictate that.");
    command("emote speaks with a hollow, chilling voice: If you wish to " +
        "change your secondary weapon, you may simply <select> a different " +
        "weapon, however be warned that I will drain all knowledge of " +
        "your previous secondary weapon skill as my due. So choose wisely!");
    command("emote leans on his ancient tarnished greatsword and waits " +
        "with the patience of the dead.");
    return "";
}

void
react_to_intro(string who,string garbage)
{
    set_alarm(2.0,0.0,"return_intro",who);
}

void
return_intro(string who) 
{
    who = L(who);

    if (P(who,E(TO)))
    {
	command("introduce myself");
    }
}

void
arm_me()
{
    object wep, arm1, arm2;

    seteuid(getuid(TO));

    wep = clone_object(WEP);
    wep->set_short("ancient tarnished greatsword");
    wep->set_long("A solamnian greatsword hundreds of years old, " +
         "tarnished with age.\n");
    wep->move(TO, 1);

    command("wield all");

    arm1 = clone_object(ARM1);
    arm1->set_short("blackened solamnic platemail");
    arm1->set_long("A suit of Solamnic full body armour, now blackened " +
        "as if burnt in a fire.\n");
    arm1->move(TO, 1);
    arm2 = clone_object(ARM2);
    arm2->set_short("solamnic great helm");
    arm2->set_long("A solamnic great helm.\n");
    arm2->move(TO, 1);

    command("wear all");

}
