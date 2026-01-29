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
 */
#pragma strict_types

inherit "/d/Avenir/union/npc/npc";
inherit "/d/Avenir/inherit/room_creator";

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

    str = "This foreman is a member of the Shadow Union.\n";
    str += "He has the physical grace characteristic of a shadow-elf.\n"+
         "His skin is so pale as to be translucent, its whiteness tinted "+
         "blue in some places by his veins.\n";

    if (IS_SYBARITE(TP))
    {
        str += "His long dark hair is twisted in a single braid whose "+
             "end has been tied up where the braid begins, forming "+
             "the long, prominent loop of punishment that proclaims "+
             "to all his disgraced status.\n";
    }
    else
    {
        str += "His long dark hair is twisted in a single braid whose "+
             "end has been tied up where the braid begins, forming "+
             "a long, prominent loop of hair behind his head.\n";
    }

    return str;
}

void
create_monster()
{
    if (!IS_CLONE)
	return;

    reset_euid();

    set_name ("foreman");
    add_name (({"shadow-elf", "elf"}));
    set_pname ("foremen");
    set_short ("Shadow Union foreman is sleeping soundly");
    set_pshort ("Shadow Union foremen are sleeping soundly");
    set_adj (({"sleeping","shadow-elf", "shadow", "union"}));
    set_long (my_long);
    set_race_name ("elf");

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
    set_skill(SS_PARRY,         55);
    set_skill(SS_ACROBAT,       60);
    set_skill(SS_AWARENESS,     71);
    set_skill(SS_DEFENCE,       50);
    set_skill(SS_LOC_SENSE,     80);
    set_skill(SS_SWAY,          50 + random(10));
    set_skill(SS_FLING,         60 + random(10));
    set_skill(SS_SLASH,         60 + random(10));

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
    add_act ("us We have driven back the Ogres and the Dark Elves. "+
        "Victory is ours!");
    add_act ("us Trolls are the most lazy workers.");
    add_act ("us Oh, would that I had not put my pride before Service!");
    add_act ("us There is nothing quite like Unity.");
    add_act ("emote examines tunnel chart.");
    add_act ("uprepare");
    add_act ("dignity");
    add_act ("emote writes something in his notepad.");
    add_act ("emote examines the wall.");
    add_act ("emote checks his timetable and frowns.");
    add_act ("say The Gods provide for us as we Deserve.");
    add_act ("murmur dignity and grace in hardship.");
    add_act ("murmur always seeking the Gods with reverence and dread.");
    add_act ("emote adds some charcoal to the brazier.");
    add_act("brood");
    add_act("sway");
    }

	set_cact_time(2);
	add_cact("say I'm a Shadow Warrior. I'll fight you to the death, and then "+
			 "my other Selves will avenge me.");
	add_cact("say Ambushing me will have consequences. The Union will find you.");
	add_cact("say Surely you've had a lapse in judgement!");
	add_cact("say Leave now, and I'll not report this to the Union.");
	add_cact("say May Plalgus smite thee, fool!");
	add_cact("say I will laugh at you from my grave on the Necronisi.");
	add_cact("say Mascarvin will come for me when I die, and I will return.");
    add_cact("angry");
    add_cact("clash");
    add_cact("cross");
    add_cact("curse");
    add_cact("pain");
    add_cact("wrath");
}

void
equip_me()
{
    object arm;

    arm = clone_object(TOKEN_OBJ);
        arm->move(TO);

    clone_object(UNION + "obj/slash")->move(TO);

    arm = clone_object(UNION+"obj/knife");
        arm->move(TO);
    arm = clone_object(UNION+"obj/knife");
      arm->move(TO);
    arm = clone_object(UNION+"obj/knife");
        arm->move(TO);
    arm = clone_object(UNION+"obj/knife");
        arm->move(TO);
    arm = clone_object(UNION+"obj/knife");
        arm->move(TO);
    arm = clone_object(UNION+"obj/knife");
        arm->move(TO);

    arm = clone_object(UNION+"obj/shirt");
        arm->move(TO);
    arm = clone_object(UNION+"obj/boots");
        arm->move(TO);
    arm = clone_object(UNION+"obj/cape");
        arm->move(TO);

    command("wear all");

    arm = clone_object(OCC_SHADOW);
    if (arm->shadow_me(TO, OCC_TYPE, OCC_STYLE, OCC_NAME) != 1)
    {
        write("Unable to be a Shadow Warrior.\n");
        "/secure/master"->do_debug("destroy", arm);
    }
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

    switch (random(7))
    {
		clone_object(UNION+"obj/knife")->move(TO);
        case 0: command("slash");
            return 1;
        case 1: command("fling");
            return 0;
        case 2: command("usrage");
            return 0;
        case 3: command("threaten enemy");
            return 0;
        case 4: command("slash");
            return 1;
        case 5: command("fling");
            return 1;
        default:
            command("fling");
    }

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
    set_short ("Shadow Union foreman");
    add_prop(LIVE_S_SOULEXTRA,"growling ferociously");
    command("say You are a fool to interrupt my sleep!");
    command("wield sword");
    command("wield dagger");
    set_adj (({"awake","union", "shadow", "dark"}));
//    set_act_time (15);
    if (alarm_id)
        return;
    alarm_id = set_alarm(100.0, 0.0, return_to_normal);
}
