// Dark elven foreman for Avenir dark area
// Made by Boriska@Genesis Nov 1994
// Cloned at: /d/Avenir/common/dark/l2/n6.c
/*
 * Revisions:
 * 	Cirion, Jul 1996: Made him a Shadow Union Warrior
 * 	cirion, May 1998: Had him inherit the room creator
 * 	Lilith, Jun 1999: Updated appearance and emotes.
 * 	Lilith, Feb 2015: Updated appearance, cchats, etc
 * 	Lucius, Aug 2017: Added SWORD skill.
 * 			  Fixes for union/defs.h changes.
 *      Lilith, May 2022: changed from shadow elf foreman to human foreman.
 *                     people killing dark elves are getting confused, still/ 
 */
#pragma strict_types

inherit "/std/monster";

#include <money.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Avenir/union/defs.h"
#include "/d/Avenir/include/relation.h"

int alarm_id;

string
my_long()
{
    string  str;

    str = "This foreman is supervising a team of sybarite troll miners.\n";
    str += "Like most sybarites, he is paler than his counterparts from "+
         "surface, seeing as his skin has never seen sunlight.\n";
   
    return str;
}

void
create_monster()
{
    if (!IS_CLONE)
	return;

    reset_euid();

    set_name ("foreman");
    add_name (({"supervisor", "sybarite"}));
    set_pname ("foremen");
    set_short ("human foreman is sleeping soundly");
    set_pshort ("human foremen are sleeping soundly");
    set_adj (({"sleeping","sybarite"}));
    set_long (my_long);
    set_race_name ("human");

    add_prop(LIVE_S_SOULEXTRA,"sleeping soundly");
    add_prop(CONT_I_WEIGHT, 56000);
    add_prop(CONT_I_HEIGHT, 252);

    set_appearance_offset(-40);

    set_stats(({ 80+random(60), 85+random(15), 80+random(50),
                 90+random(50), 80+random(50), 80+random(50) }));
    set_base_stat(SS_OCCUP, 85);

    set_skill(SS_LANGUAGE,      40);
    set_skill(SS_WEP_KNIFE,     50 + random(40));
    set_skill(SS_WEP_SWORD,     50 + random(40));
    set_skill(SS_UNARM_COMBAT,  100);
    set_skill(SS_ACROBAT,       100);
    set_skill(SS_AWARENESS,     71);
    set_skill(SS_DEFENCE,       100);
    set_skill(SS_LOC_SENSE,     80);
    set_skill(SS_BLIND_COMBAT,  70 + random(10));
    add_prop(LIVE_I_SEE_DARK, 1);

    set_alignment (0);

    set_act_time (30);

    if (TO->query_adj() == "sleeping")
    {
    add_act ("emote snores softly.");
    add_act ("emote rolls over onto his other side.");
    add_act ("emote mumbles angrily in his sleep.");
    }

    if (TO->query_adj() == "awake")
    {
    add_act ("say We have driven back the Ogres and the Dark Elves. "+
        "Victory is ours!");
    add_act ("say Trolls are the most lazy workers.");
    add_act ("emote examines a tunnel chart.");
    add_act ("sigh");
    add_act ("yawn");
    add_act ("emote writes something in his notepad.");
    add_act ("emote examines the wall.");
    add_act ("emote checks his timetable and frowns.");
    add_act ("say The Gods provide for us as we Deserve.");
    add_act ("murmur dignity and grace in hardship.");
    add_act ("murmur always seeking the Gods with reverence and dread.");
    add_act ("emote adds some charcoal to the brazier.");
    }

    set_cact_time(2);
    add_cact("say Ambushing me will have consequences. The Union will find you.");
    add_cact("say Surely you've had a lapse in judgement!");
    add_cact("say Leave now, and I'll not report this to the Union.");
    add_cact("say May Plalgus smite thee, fool!");
    add_cact("say I will laugh at you from my grave on the Necronisi.");
    add_cact("say Mascarvin will come for me when I die, and I will return.");
}

void
equip_me()
{
}

string race_sound()
{
   string *strs = ({ "says with a sybarite lilt" });

   return strs[random(sizeof(strs))];
}

int valid_help(object ob)
{
    if(interactive(ob) || !ob->id("troll") || ob->query_attack())
        return 0;

    return 1;
}

int special_attack(object enemy)
{
    object   *people;

    people = filter(all_inventory(ENV(TO)), valid_help);

    if (!sizeof(people))
        return 0;

    call_other(people, "command", "kill " + enemy->query_real_name());
        return 0;
}


void
return_to_normal()
{
    remove_alarm(alarm_id);
    alarm_id = 0;
    set_short ("shadow-elf foreman is sleeping soundly");
    add_prop(LIVE_S_SOULEXTRA,"sleeping soundly");
    command("unwield all");
    command("emote begins drifting off to sleep.");
    set_adj (({"sleeping","shadow-elf", "shadow", "dark"}));
//    set_act_time (30);
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);
    set_short ("sybarite foreman");
    add_prop(LIVE_S_SOULEXTRA,"growling ferociously");
    command("say You are a fool to interrupt my sleep!");

    if (alarm_id)
        return;
    alarm_id = set_alarm(100.0, 0.0, return_to_normal);
}




