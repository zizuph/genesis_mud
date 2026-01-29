/* townhip/npc/blacksmith.c is cloned by township/forge.c */
/* Blacksmith by Halgor ??/06/93                                */
/* Thanks to lots of people whos examples I copied in order to  */
/* make this messy piece of code                                */
/* Many thanks to Percy for allowing me to look at his          */
/* Blacksmith from the Knight's guild                           */
/* Shut down by Karath until time available to change to        */
/* repairing armours only Feb 19 1997                           */
 
 
inherit "/std/monster";
inherit "/lib/trade";
 
 
#include "/d/Emerald/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <money.h>
 
#define CTNONMET "The " + TP->query_nonmet_name()
#define SAY(x) say(({TP->query_name() + x,CTNONMET + x}))
#define F_RANGE_RANDOM(orig, max, min, value) \
    ((orig) - (orig)*((min)*100 + ((max)-(min)) * (100-(value)))/10000 \
    + random(2*(orig)*((min)*100 + ((max)-(min)) * (100-(value))) / 10000))
 
 
/* The blacksmith cannot repair a weapon more dulled than the   */
/* MAX_REPAIR_LEVEL                                             */
 
 
 
#define MAX_REPAIR_LEVEL 15
#define MEND_COST        50 /* % of weapon value to mend broken weapon */
#define SHARPEN_COST     10 /* % of weapon cost to sharpen one point   */
 
 
 
int busy;
 
 
void
create_monster()
{
    if(!IS_CLONE)
        return;
 
    set_name("jack"); /* Tulix's idea */
    add_name("blacksmith");
    set_short("swarthy human");
    set_race_name("human");
    set_adj("swarthy");
    set_title("the Master Blacksmith of Emerald");
    set_long("A large, muscular human with scars all over his body from "+
        "years of work at the forge. He seems to be an extremely skilled "+
        "smith, and could probably fix some weapons for you.\n");
 
    config_default_trade();
    set_money_give_max(10000);
    set_money_give_out(({400 , 50 , 5 , 0}));
    set_money_give_reduce(({0,2,3,3}));
    set_money_greed_sell("@@discriminate");
 
    set_stats(({150,100,130,70,70,130}));

    set_alignment(120);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_PARRY,60);
    set_skill(SS_WEP_CLUB,95);
    set_skill(SS_AWARENESS,40);
 
    set_act_time(10);
    add_act("emote hammers a piece of glowing metal on his anvil.");
    add_act("emote quenches a blade in the trough.");
    add_act("emote flexes his muscles.");
 
    trig_new("%w 'introduces' %s", "react_introduce");
    trig_new("%w 'smiles' %s", "react_smile");
 
    busy = 0; /* Not working initially */
}
 
 
 
 
void
arm_me()
{
    seteuid(getuid());
 
    MONEY_MAKE_CC(400)->move(TO);
    MONEY_MAKE_SC(50)->move(TO);
    MONEY_MAKE_GC(5)->move(TO);
 
    clone_object( TOWNSHIP_DIR + "wep/smith_wep")->move(TO,1);
    command("wield all");
}
 
 
 
/* 
void
init_living()
{
    add_action("do_mend","mend");
    add_action("do_mend","repair");
    add_action("do_cost","cost");
    add_action("do_cost","assess");
}
 */
 
 
 
/* Function to distort prices                                   */
 
int
distort(int price)
{
    int trading;
 
    trading = TP->query_skill(SS_TRADING);
    if (trading > 100)
        trading = 100;
    if (trading < 0)
        trading = 0;
 
    return F_RANGE_RANDOM(price, 30, 2, trading);
}
 
 
 
 
int
mend_cost(object item)
{
    if(item->query_prop(OBJ_I_BROKEN))
    {
        command("say You should really take more care of your weapons.");
        command("poke " + TP->query_name());
        return (F_VALUE_WEAPON(item->query_pen(), item->query_hit())
            * MEND_COST / 100);
    }
    return -1;
}
 
 
 
 
int
sharpen_cost(object item)
{
    if(!(item->query_dull()) || item->query_dull() > MAX_REPAIR_LEVEL)
        return -1;
 
    return (F_VALUE_WEAPON(item->query_pen(), item->query_hit())
        * SHARPEN_COST / 100);
}
 
 
 
 
/* Checks if the inputed string is a valid item for repairing   */
 
object
check_valid_repair_item(string str)
{
    object item;
 
    if (!str)
    {
        NF(capitalize(query_verb()) + " what?\n");
        return 0;
    }
 
    if (busy)
    {
        NF("The blacksmith is busy at the moment, and asks you to wait " +
            "until he is finished.\n");
        return 0;
    }
 
    if (!(item = present(str, TP)))
    {
        NF("You don't have a " + str + ".\n");
        return 0;
    }
 
    if (function_exists("create_object", item) != "/std/weapon")
    {
        NF("The blacksmith can only repair weapons.\n");
        return 0;
    }
 
    if (item->query_wt() == W_CLUB)
    {
        command("glare " + TP->query_name());
        command("say And how do you expect me to fix that??");
        NF("");
        return 0;
    }
 
    return item;
}
 
 
 
 
int
do_cost(string str)
{
    object item;
    int price_mend, price_sharpen;
 
    item = check_valid_repair_item(str);
 
    if (!item)
        return 1;
 
    if (TP->query_met(TO))
        write("You show your " + check_call(item->short()) + " to " +
            TO->query_met_name() + ".\n");
    else
        write("You show your " + check_call(item->short()) + " to " +
            "the " + TO->query_nonmet_name() + ".\n");
 
    SAY(" shows " + TP->query_possessive() + " " +
        check_call(item->short()) + " to the " +
        TO->query_nonmet_name() + ".\n");
 
    command("emote studies the " + check_call(item->short()) +
        " carefully.");
 
    price_mend = mend_cost(item);
    price_sharpen = sharpen_cost(item);
 
    if (price_mend != -1)
    {
        command("say It will cost about " + distort(price_mend) + " coppers " +
            "to mend your " + check_call(item->short()) + ", " +
            TP->query_nonmet_name() + ".");
        return 1;
    }
 
    if (price_sharpen != -1)
    {
        command("say It will cost about " + distort(price_sharpen) +
            " coppers to sharpen your " + check_call(item->short()) +
            ", " + TP->query_nonmet_name() + ".");
        return 1;
    }
 
    if (item->query_dull() > MAX_REPAIR_LEVEL)
    {
        command("say Sorry, but I can't sharpen your " +
            check_call(item->short()) + " any more, " +
            TP->query_nonmet_name() + ".");
        return 1;
    }
 
    command("say That " + check_call(item->short()) +
        " looks fine to me, " + TP->query_nonmet_name() + ".");
    return 1;
}
 
 
 
 
void
give_back_weapon(object item)
{
        say("The " + TO->query_nonmet_name() +  " takes the finished "
            + check_call(item->short()) + " and hands it to " +
            QNAME(TP) + ".\n");
 
        if (TP->query_met(TO))
            write(TO->query_met_name() + " hands you back your " +
                check_call(item->short()) + ".\n");
        else
            write("The " + TO->query_nonmet_name() + " hands you back " +
                "your " + check_call(item->short()) + ".\n");
 
 
        item->move(TP);
        return;
}
 
 
 
 
/* I had some trouble with the blacksmith shortchanging customers in */
/* in testing, so I'll try and make sure he always has enough money  */
/* to offer change for a platinum. (shortchanging blacksmiths are    */
/* what I'd expect from Kalad, not Emerald)                          */
 
void
update_held_coins()
{
    object ccoins, scoins, gcoins, pcoins;
    int change_value;
 
    ccoins = present("copper coin", TO);
    scoins = present("silver coin", TO);
    gcoins = present("gold coin", TO);
    pcoins = present("platinum coin", TO);
 
    change_value = gcoins->num_heap() * 144 + scoins->num_heap() * 12 +
        ccoins->num_heap();
 
    if (1728 - change_value > 0)
        MONEY_MAKE_CC(1728 - change_value)->move(TO);
 
    return;
}
 
 
 
 
int
do_mend(string str)
{
    object item;
    int price;
    int *pay_result;
    string pay_text, get_text;
 
    item = check_valid_repair_item(str);
 
    if (!item)
        return 1;
 
    if (item->query_prop(OBJ_I_BROKEN))
        price = mend_cost(item);
    else
        if ((price = sharpen_cost(item)) == -1)
        {
            if (item->query_dull() > MAX_REPAIR_LEVEL)
            {
                command("say Sorry, but I can't sharpen your "
                    + check_call(item->short()) + " any more, " +
                    TP->query_nonmet_name() + ".");
                return 1;
            }
            NF("That weapon doesn't need repairing.\n");
            return 0;
        }
 
 
    pay_result = pay(price, TP, "", 0, TO, "");
    if (sizeof(pay_result) == 1)
        {
            command("say I think getting that " +
                check_call(item->short()) + " repaired is a little " +
                "too expensive for you, " + TP->query_nonmet_name() + ".");
            return 1;
        }
 
    pay_text = text(exclude_array(pay_result, sizeof(MONEY_TYPES),
        sizeof(MONEY_TYPES) * 2 - 1));
    get_text = text(exclude_array(pay_result, 0, sizeof(MONEY_TYPES) - 1));
 
    write("You pay " + pay_text + ".\n");
 
    if (get_text)
    {
        write("You get " + get_text + " in return.\n");
        update_held_coins();
    }
 
    if (TP->query_met(TO))
        write("You hand your " + check_call(item->short()) + " to " +
            TO->query_met_name() + ", who begins work on it immediately.\n");
    else
        write("You hand your " + check_call(item->short()) + " to " +
            "the " + TO->query_nonmet_name() + ", who begins work on it " +
            "immediately.\n");
 
    SAY(" hands " + TP->query_possessive() + " " +
        check_call(item->short()) + " to " + "the " +
        TO->query_nonmet_name() + ", who begins working on it.\n");
 
    busy = 1;                     /* start working */
    item->move(TO);
 
    if (item->query_prop(OBJ_I_BROKEN))
        set_alarm( 14.0,0.0,"finished",item);
    else
    {
        item->set_repair_dull(item->query_repair_dull() + 1);
        busy = 0;
        give_back_weapon(item);
    }
    return 1;
}
 
 
 
 
void
finished(object item)
{
    item->remove_prop(OBJ_I_BROKEN);
 
    busy = 0;             /* Stop working */
 
    if(present(TP,environment()))
    {
        give_back_weapon(item);
        return;
    }
 
    command("emote notices that the " + TP->query_nonmet_name() + " has left.");
 
    command("sigh");
    command("put " + item->query_name() + " in rack");
    return;
}
 
 
 
 
int
react_introduce(string who, string dummy)
{
    if (who)
    {
        who = lower_case(who);
        set_alarm( 4.0,0.0,"return_intro",who);
        return 1;
    }
}
 
 
 
 
void
return_intro(string who)
{
    int ran;
 
    if (!(present(who, environment())))
        return;
 
    command("introduce myself");
    ran = random(4);
 
    if (ran == 0)
        command("bow to " + who);
    if (ran == 1)
        command("greet " + who);
    if (ran == 2)
        command("smile at " + who);
    if (ran == 3)
        command("say Welcome, young " + TP->query_race() + ".");
}
 
 
 
 
int
react_smile(string who, string dummy)
{
    if (who)
    {
        set_alarm( 4.0,0.0,"return_smile",who);
        return 1;
    }
}
 
 
 
 
void
return_smile(string who)
{
    int ran;
 
    if (!(present(lower_case(who), environment())))
        return;
 
    ran = random(3);
 
    if (ran == 0)
        command("emote chuckles heartily.");
    if (ran == 1)
        command("smile at " + lower_case(who));
    if (ran == 2)
        command("say It's good to see you're happy, " + TP->query_nonmet_name() + ".");
}
 
 
 
 
int
discriminate()
{
    string race;
 
    race = TP->query_race();
 
    if (race == "dwarf" || race == "goblin")
        return 115;
 
    if (race == "elf")
        return 95;
 
    return 101;
}
