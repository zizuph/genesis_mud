/*
 * /d/Gondor/rohan/npc/borderguard.c
 *
 * Last revision: 21-Nov-1996 by Olorin
 *
 * This version:
 * Copyright (c) 1996 by Christian Markus
 */
#pragma strict_types

inherit "/std/monster.c";
inherit "/d/Gondor/common/lib/logkill.c";
inherit "/d/Gondor/rohan/friend_foe.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

// Prototypes:
public string default_answer();
public string ask_help();
public string ask_danger();

public void
create_monster()
{
    set_name(({"warden", "guard", "road-warden", "rohirrim"}));
    set_race_name("human");
    set_short("tall border guard");
    set_adj(({"tall", "rohirrim", "border", "road"}));
    set_long("One of the border guards of Rohan, keeping watch at the "
      + "borders of the realm. His duty is to prevent enemies of the "
      + "Rohirrim to enter the realm. He will help travellers by warning "
      + "them about dangers when asked. He looks quite competent in "
      + "fighting.\n");
    set_pshort("tall border guards");

    default_config_npc(70 + random(20));
    set_base_stat(SS_STR, 75 + random(10));
    set_base_stat(SS_DEX, 75 + random(10));
    set_base_stat(SS_CON, 75 + random(10));

    set_alignment(250+random(250));

    set_skill(SS_WEP_SWORD, 75 + random(10));
    set_skill(SS_DEFENCE,   50);
    set_skill(SS_PARRY,     50);
    set_skill(SS_SWIM,      40);
    set_skill(SS_CLIMB,     40);
    set_skill(SS_UNARM_COMBAT, 25);
    set_skill(SS_AWARENESS, 20 + random(30));

    set_chat_time(15);
    add_chat("I hate orcs!");
    add_chat("Keep to the road, traveller, if you don't want to run into orcs!");
    add_chat("Death to orcs!");
    add_chat("I fear that Saruman is up to no good!");
    add_chat("Elfhelm is now the Marshal of the King's Eored.");
    add_chat("If you need advice, traveller, ask me!");
    set_cchat_time(10);
    add_cchat("Die, foul servant of darkness!");
    add_cchat("Take this!");
    add_cchat("Damned fool! Die!");
    add_cchat("Stinking animal, I'll cut you up!");

    set_aggressive(1);
    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"danger","dangers"}), VBFC_ME("ask_danger"));
    add_ask(({"guild","ranger","rangers"}),VBFC_ME("ask_ranger"));
    add_ask(({"road"}),VBFC_ME("ask_road"));
    add_ask(({"bands","band","valley","valleys","dunlending","dunlendings"}),
        VBFC_ME("ask_dunlendings"));
    add_ask(({"edoras","capital"}), VBFC_ME("ask_edoras"));
    add_ask(({"plain","plains"}), VBFC_ME("ask_plains"));
    add_ask(({"advice", "help"}), VBFC_ME("ask_help"));

    add_prop(LIVE_I_NEVERKNOWN, 1);
}

public void
arm_me()
{
    FIX_EUID

    clone_object(EDORAS_DIR + "obj/rosword")->move(TO);
    command("wield sword");
    clone_object(EDORAS_DIR + "obj/roshield")->move(TO);
    clone_object(EDORAS_DIR + "obj/rohelm")->move(TO);
    command("wear all");
}

public void
do_attack(object victim)
{
    if (objectp(query_attack()))
        return;
    if (!present(victim, ENV(TO)))
        return;

    command("kill " + victim->query_real_name());
}

public void
init_attack()
{
    if (objectp(query_attack()))
        return;
    if (query_friend_or_foe(TP) < 0)
        set_alarm(1.0, 0.0, &do_attack(TP));
}

public int
enemy_check()
{
    if (objectp(query_attack()))
        return 1;
    switch (query_friend_or_foe(TP))
    {
    case -10 .. -2:
        command("say Die, foul creature!");
        return 1;
    case  -1:
        command("say You are not welcome in Rohan!");
        return 1;
    case   0 ..  10:
    default:
        return 0;
    }
}

public string
default_answer()
{
    if (enemy_check())
        return "";

    command("say I don't know what you are talking about.");
    command("say But you might ask me about help or danger.");
    return "";
}

public string
ask_help()
{
    if (enemy_check())
        return "";

    command("say Ask me about dangers, and I will tell you where "
      + "there are dangers in Rohan.");
    return "";
}

public string
ask_danger()
{
    string  message  = "There are many dangers in Rohan.\n" +
                       "War is drawing near!\n";
    int     i = random(4);

    if (enemy_check())
        return "";

    switch (i)
    {
    case 0:
        message += "There are many servants of the Evil One on the "
          + "plains of Rohan,\n"
          + "If you want to know more about the plains, "
          + "then ask me about them."; 
        break;
    case 1: 
        message += "Bands of dunlendings in the valleys of the White "
          + "Mountains are a great nuisance.\n"
          + "I will tell you more about them, if you ask me.";
        break;
    case 2:
        message += "If you want to evade danger, then keep to the road!";
        break;
    case 3: 
        message += "Edoras is the capital of Rohan.\n"
          + "Even though war is threatening, you might "
          + "find a haven there.";
        break;
    }
    command("say " + message);
    return "";
}

public string
ask_ranger()
{
    if (enemy_check())
        return "";

    command("say Yes, I have heard of the rangers.");
    command("say They are our comrades in the fight against the enemy.");
    command("say Somewhere in Anorien they have a hideout, "
          + "but I do not know where it is!");
    return "";
}

public string
ask_plains()
{
    if (enemy_check())
        return "";

    command("say The plains of Rohan extend north of the White Mountains.");
    command("say They stretch from the Gap of Rohan in the west "
          + "to the Anduin in the east.");
    command("say To the north, they are bounded by the Fangorn Forest "
          + "and the river Limlight.");
    command("say Close to the White Mountains, a road is running "
          + "across the plains.");
    command("say This road is guarded by the Rohirrim.");
    command("say You can travel there in comparable safety.");
    command("say The plains themselves are full of orc bands and wild "
          + "and dangerous animals.");
    command("say Be careful when journeying there!");
    return "";
}

public string
ask_dunlendings()
{
    if (enemy_check())
        return "";

    command("say Several farms in the valleys of the White Mountains "
      + "have been attacked by bands of dunlendings.");
    command("say They kill the farmers, steal the horses and the other "
      + "lifestock.");
    command("say Be careful when you turn south from the road.");
    command("say But luckily the dunlendings still fear us Rohirrim "
      + "and stay to the mountains.");
    command("say They even hide the path leading to a farm before attacking "
      + "it so that they can finish their grisly business undisturbed.");
    return "";
}

public string
ask_road()
{
    if (enemy_check())
        return "";

    command("say This road here runs from the Gap of Rohan and "
      + "the Fords of the Isen in the west to Edoras and from there "
      + "it continues through Rohan to the Mering Stream, where it "
      + "enters the Kingdom of Gondor.");
    command("say It then leads on to Mundburg, which is called Minas "
      + "Tirith by Gondorians.");
    command("say Up to now we managed to keep the road mostly free "
      + "of orcs and other vermin, but who knows what will "
      + "happen in the future?");
    return "";
}

public string
ask_edoras()
{
    if (enemy_check())
        return "";

    command("say Edoras is the capitol of Rohan.");
    command("say It lies halfway on the way from the Fords of the Isen "
      + "to the Mering Stream, south of the road where the river Snowbourn "
      + "comes out of the White Mountains.");
    command("say If you should happen to visit Edoras and if you want to "
      + "help us against the forces of the Evil, then go to Elfhelm "
      + "the Marshall.");
    command("say Perhaps he has a task for you.");
    return "";
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    object *arr  = (object *)query_team_others();
    int     i, s;

    ::attacked_by(ob);

    for (i = 0, s = sizeof(arr); i < s; i++)
        arr[i]->notify_ob_attacked_me(TO, ob);
}

/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
void
help_friend(object ob)
{
    if (objectp(ob) && !objectp(query_attack()) && present(ob, ENV(TO)))
    {
        command("say Die, foul creature!");
        command("kill " + lower_case(ob->query_real_name()));
    }
}

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *                attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
    if (objectp(query_attack()))
        return;
    if (random(10))
        set_alarm(5.0 * rnd(), 0.0, &help_friend(attacker));
}

/* Solamnian knight prestige */
public int query_knight_prestige() {return (-8);}












