/*
 *  /d/Gondor/guilds/rangers/npc/fredegar.c
 *
 *  Fredegar, the shopkeeper of Ranger Central Headquarters
 *
 *  Coded by Elessar
 *    Modified by Alto, 29 June 2001, changed to fit CH theme
 *    Modified by Gwyneth, 24 May 2004
 *
 */
inherit "/d/Gondor/common/dunedain/npc/npc_dunadan.c";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "../rangers.h"
#include "/d/Gondor/defs.h"

static int     Inn_Stage = 0,
               Inn_Alarm,
               Inn_Time,
               Inn_Switch;

public void
do_introduce(object pl)
{
    string name;

    if (!present(pl, ENV(TO)))
    {
        command("shrug");
        return;
    }

    name = OB_NAME(pl);
    if (IS_DUNADAN(pl))
        command("wellmet " + name);
    else if (pl->query_race() == "elf")
        command("elfhail " + name);
    else
        command("dsalute " + name);

    command("say How nice to meet you, " + pl->query_name() + ".");
    command("introduce me to " + name);
    command("say What can I do for you?");
}

public void
create_dunadan() 
{
    set_living_name("fredegar");
    set_name("fredegar");
    add_name(({"owner", "ranger", "shopkeeper", "shopowner"}));
    set_race_name("human");
    set_adj(({"slender", "young", "dunadan"}));
    set_title("Shopkeeper of the Rangers of the Westlands");
    set_dunedain_house("Thalion");
    set_long("This is the shopkeeper, a Dunadan who runs the Equipment " +
        "Store in the Rangers' Guild. He is probably quite competent with " +
        "numbers - trade is his speciality.\n");
    default_config_npc(75);

    set_base_stat(SS_CON, 98);
    set_skill(SS_WEP_SWORD, 60 + random(31));
    set_skill(SS_DEFENSE, 55);
    set_skill(SS_PARRY,   55);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_TRADING, 80);

    set_alignment(900);
    set_chat_time(12);
    add_chat("Can I help you?");
    add_chat("Welcome to my shop!");
    add_chat("My name is Fredegar.");
    add_chat("Have you got anything nice to sell?");
    add_chat("Perhaps you want to buy some excellent equipment?");
    add_cchat("Get out of here, you thieving scoundrel!");
    add_cchat("You won't get away with this, you know!");
    add_cchat("Guards! Help!");

    set_act_time(30);
    add_act("whistle merrily");

    set_equipment( ({ WEP_DIR + "rndsword", ARM_DIR + "rndarmour", }) );
    set_intro(5.0, do_introduce);
}

int
second_life(object killer)
{
    FIX_EUID
    MANAGER->add_outlaw(killer->query_real_name());
    return 0;
}

public void
visit_inn(int stage = 0)
{
    if (!stage)
    {
        if (Inn_Alarm && sizeof(get_alarm(Inn_Alarm)))
            return;
        else if ( (time() - Inn_Time) < 1800 )
            return;

        Inn_Stage = 0;
        Inn_Switch = random(3);
    }

    switch (Inn_Stage++)
    {
    case 0:
        Inn_Alarm = set_alarm(2.0 + rnd() * 4.0, 4.0, &visit_inn(1));
        Inn_Time = time();
        break;
    case 1:
        command("sigh");
        command("say Sorry, I didn't manage to eat a single bite all day.");
        break;
    case 2:
        command("say I'll be right back.");
        command("say I'll just go and fetch some food.");
        break;
    case 3:
        command("south");
        break;
    case 4:
        command("south");
        break;
    case 5:
        command("say Hello!");
        break;
    case 6:
        command("wellmet");
        command("elfhail");
        break;
    case 7:
        command("say I just need a quick snack.");
        break;
    case 8:
        command("say Customers are waiting.");
        break;
    case 9:
        MONEY_MAKE_SC(15)->move(TO);
        break;
    case 10:
        command("buy bacon");
        break;
    case 11:
        command("buy stew");
        break;
    case 12:
        switch (Inn_Switch)
        {
        case 0:
        case 2:
            command("buy 3 beer");
            break;
        case 1:
            command("buy 3 water");
            break;
        }
        break;
    case 13:
        switch (Inn_Switch)
        {
        case 0:
        case 2:
            command("drink beer");
            break;
        case 1:
            command("drink water");
            break;
        }
        command("sigh deeply");
        break;
    case 14:
    case 15:
        break;
    case 16:
        command("wave");
        break;
    case 17:
        command("north");
        break;
    case 18:
        command("north");
        break;
    case 19:
        command("say I'm back.");
        break;
    case 20:
        command("say What can I do for you?");
        command("smile all");
        break;
    case 21:
    case 22:
    case 23:
        break;
    case 24:
        command("silence");
        break;
    case 25:
        command("eat stew");
        break;
    case 26:
        command("say My business never stops, so I have to eat in the shop.");
        break;
    case 27:
        command("smile");
        command("say I hope you don't mind.");
        break;
    case 28:
        break;
    case 29:
        switch (Inn_Switch)
        {
        case 0:
        case 2:
            command("drink beer");
            command("sigh thirstily");
            break;
        case 1:
            command("drink water");
            command("grumble unhappily");
            break;
        }
        break;
    case 30:
        switch (Inn_Switch)
        {
        case 0:
            break;
        case 1:
        case 2:
            command("say Can you imagine that there are some rangers " +
                "who complained that I was drinking beer here in the shop?");
            break;
        }
        break;
    case 31:
        command("eat bacon");
        break;
    case 32:
        switch (Inn_Switch)
        {
        case 0:
        case 1:
            break;
        case 2:
            command("spit");
            break;
        }
        break;
    case 33:
        switch (Inn_Switch)
        {
        case 0:
        case 2:
            command("drink beer");
            break;
        case 1:
            command("drink water");
            break;
        }
        break;
    case 34:
        switch (Inn_Switch)
        {
        case 0:
            break;
        case 1:
            command("say Now, the barkeeper will not serve me beer any " +
                "more and I have to drink water!");
            break;
        case 2:
            command("say Fortunately, the good Captain of the Ithilien " +
                "Company put in a good word for me with the barkeeper.");
            break;
        }
        break;
    case 35:
        switch (Inn_Switch)
        {
        case 0:
        case 1:
            break;
        case 2:
            command("smile happily");
            break;
        }
        break;
    case 36:
        switch (Inn_Switch)
        {
        case 0:
        case 1:
            break;
        case 2:
            command("say I tell you, that Captain is a fine person!");
            break;
        }
        break;
    case 37:
        switch (Inn_Switch)
        {
        case 0:
        case 1:
            break;
        case 2:
            command("say I mean, what harm can a little beer do?");
            break;
        }
        break;
    case 38:
        command("burp");
        break;
    case 39:
        command("blush");
        break;
    case 40:
        command("say Excuse me.");
        break;
    default:
        remove_alarm(Inn_Alarm);
        Inn_Alarm = 0;
        if (file_name(ENV(TO)) != RANGERS_HQ_DIR + "hq_shop")
            move_living("back to his shop", RANGERS_HQ_DIR + "hq_shop");
        break;
    }
}

