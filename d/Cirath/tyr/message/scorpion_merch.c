inherit "/d/Cirath/std/monster";
inherit "/lib/trade";
#include "/d/Cirath/common/introfnc.h"
#include "/d/Cirath/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"
#define NUM sizeof(MONEY_TYPES)

create_monster()
{
    ::create_monster();
    set_name("bartok");
    add_name("scorpion trainer");
    set_race_name("half-elf");
    set_adj("tall");
   set_adj("palid");
    set_long("This pale half-elf has started up a business "
	+"training scorpions to deliver messages.  If you have "
	+"the money you can hire one.\n");
    set_stats(({30,30,50,20,20,50}));
    set_alignment(-10);
    set_skill(SS_UNARM_COMBAT,40);
    set_skill(SS_DEFENCE,30);
    set_skill(SS_AWARENESS,30);
    config_default_trade();

    add_prop(NPC_M_NO_ACCEPT_GIVE,1); /* won't accept gifts */
    add_prop(CONT_I_WEIGHT, 60000); /* weights 60 kilo's */
    add_prop(CONT_I_HEIGHT, 175);    /* 175 cm high */
    set_hp(query_max_hp()); /* heal fully */
    set_title("the Master of Scorpions");
    add_ask("scorpion","I sell scorpions that deliver messages "+
      "for you.  If you want to hire one its only a silver.\n");

    set_act_time(5);
   add_act("emote lovingly scratches his scorpion's belly.");
    add_act("emote whispers something to a scorpion perched on "+
    "his shoulder.");

}


void
init_living()
{
    add_action("buy_scorpion","hire");
}

int
buy_scorpion(string str)
{
    object buy_ob;
    string what, for_c, get_c, change;

    int *result, m_res, price;
    if (!str) {
        notify_fail("Hire what?\n");
        return 0;
    }
    if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
        if (sscanf(str, "%s with %s", what, for_c) != 2)
            what = str;
    if (what != "scorpion") {
        notify_fail("All I have are scorpions. Hire that or nothing.\n");
        return 0;
    }
   buy_ob=clone_object("/d/Cirath/tyr/message/scorpion_mess");
    if (!buy_ob) {
        notify_fail("There is none left. Sorry for that...\n");
        return 0;
    }
    price=12;
    result=pay(price,this_player(),for_c,0,0,get_c);
    if (sizeof(result)==1) {
        buy_ob->remove_object();
        return 0;
    }
    if (buy_ob->move(this_player())) {
        write("You drop the " + buy_ob->short() + " on the ground.\n");
        say(QCTNAME(this_player()) + " drops one " + buy_ob->short() +
          " on the ground.\n");
        buy_ob->move(environment(this_player()));
    }
    else {
    write("You get your "+buy_ob->short()+".\n");
   say(QCTNAME(TP)+" buys a "+buy_ob->short()+".\n");
    }
    write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
    if (change)
        write("You get " + change + " as change.\n");
    return 1;
}
