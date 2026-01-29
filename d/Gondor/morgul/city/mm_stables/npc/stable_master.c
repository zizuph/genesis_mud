/*
 *  /d/Gondor/morgul/city/mm_stables/npc/stable_master.c
 *
 *  The Stable Master of the stables of Minas Morgul.
 *
 *  Deagol, October 2002
 */

inherit "/d/Gondor/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";
inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include <const.h>

#include "/d/Gondor/defs.h"
#include "../mm_stables.h"

#define FEE_PRICE 86400		/* 50 platinum coins */
#define BORROW_PRICE 3456	/* 2 platinum coins */
#define OATS_PRICE 50
#define BAG_PRICE 500
#define TIME_PERIOD 7200	/* 2 hours */

void		add_acts();
object		Steed;
int		hidden;
mapping         attackers = ([ ]);
mapping		steed_owners = ([ ]);
object		enemy;

void
create_gondor_monster()
{
    ::create_gondor_monster();
    
    set_name(({"morhoon", "stable master", "master"}));
    set_adj("dark-skinned");
    set_living_name("morhoon");
    set_race_name("human");
    set_title("the Stable Master of Minas Morgul");
    set_long("This dark-skinned, hefty Easterling must obviously be " +
             "a master of horsemanship, seeing how he has been entrusted " +
             "with the care and administration of the steeds of Minas " +
             "Morgul. His leather riding boots are impeccable, and his " +
             "every garment indicates that he pays much attention to " +
             "detail. The high ranking members of the Society of Morgul " +
             "Mages turn to him when they require their horses.\n" +
             "He is wielding a vicious horsewhip in his left hand.\n");

    set_base_stat(SS_STR, 110);
    set_base_stat(SS_DEX, 99);
    set_base_stat(SS_CON, 100);
    set_base_stat(SS_INT, 75);
    set_base_stat(SS_WIS, 70);
    set_base_stat(SS_DIS, 100);
    
    set_skill(SS_DEFENCE, 200);
    set_skill(SS_PARRY, 200);
    set_skill(SS_RIDING, 300);
    set_alignment(-1000);

    setuid();
    seteuid(getuid());

    config_default_trade();
    
    attackers = restore_map(MM_STABLES_LOG_DIR + "attackers");
    steed_owners = restore_map(MM_STABLES_LOG_DIR + "steed_owners");

    add_acts();
}

void
check_hidden()
{   
    hidden = 0;

    if (!CAN_SEE(this_object(), this_player()))
    {   
        hidden = 1;
        command("say I can't see you. Reveal your presence or I'm not " +
                "going to chat with you.");
        return;
    }
}

int
buy_oats(string str)
{
    int *money;
    string player;
    
    player = TP->query_real_name();

    if (str != "oats")
    {
        notify_fail("Buy what?\n");
        return 0;
    }
    if (file_name(ENV(TO)) != MM_STABLES_DIR + "office")
    {
        command("say I can't sell items here.");
        return 1;
    }
    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
    {
        command("say Who's that? Where are you? I can't see you.");
        return 1;
    }
    money = pay(OATS_PRICE, TP);
    if (sizeof(money) == 1)
    {
        command("say to " + player + " I'm afraid you cannot pay me for " +
                "the bag of oats. You should visit the bank.");
        return 1;
    }
    clone_object(MM_STABLES_OBJ_DIR + "oats.c")->move(TO);
    write("You pay for a bag of oats.\n");
    say(QCTNAME(TP) + " pays for a bag of oats.\n");
    command("give oats to " + player + "");
    return 1;
}

int
buy_saddlebag(string str)
{
    int *money;
    string player;
    
    player = TP->query_real_name();

    if (str != "saddlebag")
    {
        notify_fail("Buy what?\n");
        return 0;
    }
    if (file_name(ENV(TO)) != MM_STABLES_DIR + "office")
    {
        command("say I can't sell items here.");
        return 1;
    }
    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
    {
        command("say Who's that? Where are you? I can't see you.");
        return 1;
    }
    money = pay(BAG_PRICE, TP);
    if (sizeof(money) == 1)
    {
        command("say to " + player + " I'm afraid you cannot pay me for " +
                "a saddlebag. You should visit the bank.");
        return 1;
    }
    clone_object("/d/Terel/calathin/obj/saddlebag")->move(TO);
    write("You pay for a saddlebag.\n");
    say(QCTNAME(TP) + " pays for a saddlebag.\n");
    command("give saddlebag to " + player + "");
    return 1;
}

void
clone_horse(string name)
{
    Steed = clone_object(MM_STABLES_OBJ_DIR + "steed.c")->move(ENV(TO));
    Steed->set_horse_desc("dark_horse_of_" + name);
    Steed->move(ENV(TO));
}

void
destruct_horse()
{
    Steed = present("horse", ENV(TO));
    Steed->remove_object();
}

int
borrow_horse(string str)
{
    int *money;
    string player;

    player = TP->query_real_name();

    if (!strlen(str) || !parse_command(str, ({}),
        "[a] [steed] [horse]"))
    {   
        notify_fail("Borrow what? Maybe a horse?\n");
        return 0;
    }
    if (file_name(ENV(TO)) != MM_STABLES_DIR + "office")
    {   
        command("say I can't bring the horse since I'm not in my office.");
        return 1;
    }
    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
    {   
        command("say Who's that? Where are you? I can't see you.");
        return 1;
    }
    if (attackers[TP->query_real_name()] + TIME_PERIOD > time())
    {   
        command("frown angrily " + player + "");
        command("say to " + player + " You tried to kill me. Leave this " +
                "place or I'm going to call the guards.");
        return 1;
    }
    if (!TP->query_wiz_level() && !IS_MORGUL_MAGE(TP))
    {
        command("say to " + player + " How do you dare to come here and " +
                "ask me such things? Shut your filthy mouth and begone!");
        return 1;
    }
    if (!steed_owners[TP->query_real_name()])
    {
        if (TP->query_gender() == G_MALE)
        {
            command("say to " + player + " You didn't pay me a fee yet, " +
                    "Master.");
            return 1;
        }
        command("say to " + player + " You didn't pay me a fee yet, " +
                "Mistress.");
        return 1;
    }
    money = pay(BORROW_PRICE, TP);
    if (sizeof(money) == 1)
    {   
        command("say to " + player + " I'm afraid you cannot pay me for " +
                "the steed. You should visit the bank.");
        return 1;
    }
    if (TP->query_gender() == G_MALE)
    {
        command("say to " + player + " As you command, Master.");
        set_alarm(0.5, 0.0, &command("bow humbly to " + player));
        set_alarm(2.0, 0.0, &command("south"));
        set_alarm(2.1, 0.0, &clone_horse(player));
        set_alarm(2.5, 0.0, &command("lead horse"));
        set_alarm(6.0, 0.0, &command("north"));
        set_alarm(6.5, 0.0, &command("unlead horse"));
        set_alarm(7.0, 0.0, &command("say to " + player + " Here is your " +
                  "steed, Master."));
        return 1;
    }
    command("say to " + player + " As you command, Mistress.");
    set_alarm(0.5, 0.0, &command("bow humbly to " + player));
    set_alarm(2.0, 0.0, &command("south"));
    set_alarm(2.1, 0.0, &clone_horse(player));
    set_alarm(2.5, 0.0, &command("lead horse"));
    set_alarm(6.0, 0.0, &command("north"));
    set_alarm(6.5, 0.0, &command("unlead horse"));
    set_alarm(7.0, 0.0, &command("say to " + player + " Here is your " +
              "steed, Mistress."));
    return 1;
}

int
stable_horse(string str)
{
    int player;
    Steed = present("horse", environment(this_object()));
    
    player = TP->query_real_name();
    
    if (str != "horse" && str != "steed")
    {
        notify_fail("Stable what? Maybe a horse?\n");
        return 0;
    }
    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
    {
        command("say Who's that? Where are you? I can't see you.");
        return 1;
    }
    if (!Steed)
    {
        command("say to " + player + " I don't see a horse that I should " +
                "stable. Can you bring me some spectacles.");
        command("grin");
        return 1;
    }
    if (Steed->query_has_riders())
    {
        command("say to " + player + " Please, dismount your steed first.");
        return 1;
    }
    if (Steed->query_leader())
    {
        command("say to " + player + " You're leading the horse, I cannot " +
                "stable him. Please, unlead him first.");
        return 1;
    }
    if (TP->query_gender() == G_MALE)
    {
        command("say to " + player + " Master, let me relieve you of your " +
                "steed. I shall see to it that it is fed and watered right " +
                "away. It will be clean and rested upon your return.");
        set_alarm(0.5, 0.0, &command("pet horse"));
        set_alarm(1.5, 0.0, &command("lead horse"));
        set_alarm(2.0, 0.0, &command("south"));
        set_alarm(2.1, 0.0, &command("unlead horse"));
        set_alarm(2.2, 0.0, &destruct_horse());
        set_alarm(5.0, 0.0, &command("north"));
        return 1;
    }
    command("say to " + player + " Mistress, let me relieve you of your " +
            "steed. I shall see to it that it is fed and watered right " +
            "away. It will be clean and rested upon your return.");
    set_alarm(0.5, 0.0, &command("pet horse"));
    set_alarm(1.5, 0.0, &command("lead horse"));
    set_alarm(2.0, 0.0, &command("south"));
    set_alarm(2.1, 0.0, &command("unlead horse"));
    set_alarm(2.2, 0.0, &destruct_horse());
    set_alarm(5.0, 0.0, &command("north"));
    return 1;
}

void
add_acts()
{
    set_act_time(30);
    add_act("emote says: There is nothing to calm a horse like a " +
            "long, quiet ride. But of course, having it whipped and " +
            "goaded saves you the time.");
    add_act("emote emphatically says: I would break a meara quicker " +
            "than Shelob could devour a snaga, mark my words.");
    add_act("emote amusedly says: Apparently, the orcs call Rohan " +
            "horse-country.");
    add_act("emote advisingly says: If you want your horse to look " +
            "stately, you should avoid pulling its mouth with the bits.");
    add_act("emote says from experience: A disobedient servant and a " +
            "disobedient army are of course useless, a disobedient horse " +
            "is not only useless, but often behaves just like a traitor.");
}

void
react_intro(object tp)
{
    if (!objectp(tp))
        return;

    command("introduce me to " + tp->query_real_name() + "");
    command("say to " + tp->query_real_name() + " What are you doing here, " +
            tp->query_name() + "?");
    return;
}

void
react_intro_to_mage(object tp)
{
    command("introduce me to " + tp->query_real_name() + "");
    if (tp->query_gender() == G_MALE)
    {
        command("say to " + tp->query_real_name() + " Greetings Master, " +
                "what can I do for you?");
        return;
    }
    command("say to " + tp->query_real_name() + " Greetings Mistress, " +
            "what can I do for you?");
    return;
}

public void
add_introduced(string str)
{
    if (!interactive(TP) ||
        TP->query_met(query_name()))
    {
        return;
    }
    if (IS_MORGUL_MAGE(TP))
    {
        set_alarm(1.0 + 3.0 * rnd(), 0.0, &react_intro_to_mage(TP));
        return;
    }
    set_alarm(1.0 + 3.0 * rnd(), 0.0, &react_intro(TP));
}

void
enter_env(object to, object from)
{   
    ::enter_env(to, from);

    if (!mappingp(attackers))
    {
        attackers = ([ ]);
    }
    if (!mappingp(steed_owners))
    {
        steed_owners = ([ ]);
    }
}

void
stop_fighting()
{
    enemy->stop_fight(TO);
    TO->stop_fight(enemy);
}

void
attacked_by(object attacker)
{
    int count_hp;
    
    ::attacked_by(attacker);

    if (!IS_MORGUL_MAGE(attacker))
    {
        enemy = attacker;
        attackers[attacker->query_real_name()] = time();
        save_map(attackers, MM_STABLES_LOG_DIR + "attackers");
        set_alarm(0.5, 0.0, &command("shout You fool!"));
        set_alarm(3.0, 0.0, &stop_fighting());
        set_alarm(3.1, 0.0, &command("south"));
        set_alarm(10.0, 0.0, &command("north"));
    }
}

int
pay_fee(string str)
{
    int *money;
    string player;

    player = TP->query_real_name();

    if (str != "fee")
    {   
        notify_fail("Pay what? A fee?\n");
        return 0;
    }
    if (file_name(ENV(TO)) != MM_STABLES_DIR + "office")
    {   
        command("say I can't get money from you here.");
        return 1;
    }
    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
    {   
        command("say Do you want to pay a fee? Then let me see your face.");
        return 1;
    }
    if (attackers[TP->query_real_name()] + TIME_PERIOD > time())
    {   
        command("frown angrily " + player + "");
        command("say to " + player + " You tried to kill me. Leave this " +
                "place or I'm going to call the guards.");
        return 1;
    }
    if (steed_owners[TP->query_real_name()])
    {
        command("say to " + player + " You've already paid me. I remember " +
                "your face. Do you want me to bring you a horse?");
        return 1;
    }
    if (!TP->query_wiz_level() && !IS_MORGUL_MAGE(TP))
    {
        command("say to " + player + " I don't need your money. And I'm " +
                "not going to borrow you any of my steeds.");
        return 1;
    }
    money = pay(FEE_PRICE, TP);
    if (sizeof(money) == 1)
    {   
        command("say to " + player + " I'm afraid you are too poor to " +
                "pay me the fee. You should visit the bank.");
        return 1;
    }
    steed_owners[TP->query_real_name()] = 1;
    save_map(steed_owners, MM_STABLES_LOG_DIR + "steed_owners");
    say(QCTNAME(TP) + " pays the fee.\n");
    write("You pay the fee.\n");
    if (TP->query_gender() == G_MALE)
    {
        command("say to " + player + " Thank you very much. From now on " +
                "I can lend you a horse whenever you want, Master.");
        return 1;
    }
    command("say to " + player + " Thank you very much. From now on " +
            "I can lend you a horse whenever you want, Mistress.");
    return 1;
}

void
init_living()
{
    ::init_living();
    
    add_action(stable_horse, "stable");
    add_action(borrow_horse, "borrow");
    add_action(pay_fee, "pay");
    add_action(buy_oats, "buy");
//    add_action(buy_saddlebag, "buy");
}
