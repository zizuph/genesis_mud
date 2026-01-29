inherit "/d/Gondor/minas/npc/mtirith_monster";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_monster() 
{
    set_living_name("brandir");
    set_name("brandir");
    add_name(({"owner", "shopkeeper", "shopowner"}));
    set_race_name("human");
    set_adj(({"slender","young"}));

    set_long(BSN("This is Brandir the shopkeeper, who runs the General "
      + "Store in Minas Tirith. He is surprisingly young for his job, "
      + "but he looks quite competent and a little shrewed."));
    default_config_npc(32);
    set_base_stat(SS_CON,75);

    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    set_skill(SS_WEP_SWORD, random(10)+50);
    set_skill(SS_DEFENCE, random(10)+30);
    set_skill(SS_PARRY, random(10)+30);
    set_skill(SS_AWARENESS, random(10)+60);
    set_skill(SS_TRADING, random(10)+80);
    set_alignment(50 + random(100));
    set_chat_time(12);
    add_chat("Can I help you?");
    add_chat("Welcome to my shop!");
    add_chat("My name is Brandir.");
    add_chat("Have you got anything nice to sell?");
    add_chat("Perhaps you want to buy some excellent equipment?");
    add_cchat("Get out of here, you thieving scoundrel!");
    add_cchat("You won't get away with this, you know!");
    add_cchat("Guards! Help!");
    trig_new("%s 'bows' %s","react_bow");
}

void
arm_me()
{
    FIX_EUID
    clone_object(WEP_DIR + "rndsword")->move(TO);
    command("wield sword");
    clone_object(ARM_DIR + "rndarmour")->move(TO);
    command("wear armour");
}

void
do_introduce(object pl, string name)
{
    if (!present(pl, ENV(TO)))
    {
        command("shrug");
        return;
    }

    command("say My name is Brandir. I run the best shop in Minas Tirith!");
    command("introduce me to "+name);
    command("say How can I do help you?");
}

public void
add_introduced(string who)
{
    object  pl;

    if (!objectp(pl = find_player(who)) ||
        pl->query_met(query_real_name()))
        return;
    set_alarm(5.0, 0.0, &do_introduce(pl, who));
}

void
do_bow(object tp)
{
    if (!tp->query_npc() && CAN_SEE_IN_ROOM(TO) && CAN_SEE(TO, tp))
    command("bow " + tp->query_real_name());
    command("say What can I do for you?");
    command("say Perhaps you want to buy some excellent equipment?");
}

void
react_bow()
{
    set_alarm(2.0, 0.0, &do_bow(TP));
}

public int query_knight_prestige() { return -5; }


void
return_object(object obj, object to)
{
    if (obj->id("coin"))
    {
        command("say Why, thank you!");
        command("smile " + OB_NAME(to));
        return;
    }

    command("say Thanks, but I don't think I need that.");
    command("give " + OB_NAME(obj) + " to " + OB_NAME(to));
    if (ENV(obj) == TO)
    {
       command("drop " + OB_NAME(obj));
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (objectp(ob) && objectp(from) && living(from))
    {
    	set_alarm(0.5, 0.0, &return_object(ob, from));
    }
}

