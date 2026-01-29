#include "../default.h"

inherit (STD + "monster");
inherit (STD + "shop_list");

#include <composite.h>
#include <money.h>
#include <ss_types.h>

#define STORE	(CVAN + "shop/clmsack")
#define AXE	(WEP + "clmaxe")
#define MAIL	(ARM + "clmmail")

static object store;

void
create_monster()
{
    ::create_monster();

    set_name("grumbar");
    add_name("merchant");
    add_name(({"owner", "shopkeeper", "keeper"}));
    add_name("_wandering_merchant");
    set_race_name("dwarf");
    set_adj("grumpy");
    add_adj("weathered");
    set_long("A dwarf that looks like he's in his middle years, but you "+
      "can't really tell, maybe he's just unusually wrinkly. He is patiently "+
      "standing here, selling and buying wares.\n");

    set_title("Ironfist, the Travelling Merchant of Kabal");

    set_stats(({130, 80, 130, 80, 80, 105}));
    set_alignment(333);
    set_skill(SS_WEP_AXE, 90);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 60);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_AWARENESS, 30);

    set_act_time(3);
    add_act("say Do you have any nice wares on ya?");
    add_act("grumble");
    add_act("swear");
    add_act("spit");
    add_act("emote grumbles something about people always attacking him.");
    add_act("say These here elite soldiers have been assigned to me because those bastard elite guards "+
      "were always runnin off when I needed them da most!");
    add_act("say The Sheriff-captain will get you if you cause me any trouble!!");
    add_act("say That half-ogre started ta steal from me! Got him "+
      "chased outa town did I!");

    add_speak("Buy my wares!\n");
    set_knight_prestige(-3);
    add_prop(LIVE_I_ALWAYSKNOWN, 1);
    add_prop(OBJ_S_WIZINFO, "This merchant carries a special "+
      "sack that is his store-room. Every object he buys ends up in this "+
      "sack and he sells what he has in the sack.\n");
    config_default_trade();
    set_money_give_max(1000);
    seteuid(getuid(TO));
    store = clone_object(STORE);
    store->move(TO, 1);
    set_store_room(STORE);
}

void
arm_shopkeeper()
{
    clone_object(AXE)->move(this_object(), 1);
    clone_object(MAIL)->move(this_object(), 1);
    command("wield all");
    command("wear all");
    MONEY_MAKE_PC(random(5))->move(TO, 1);
    MONEY_MAKE_GC(random(20))->move(this_object(), 1);
    MONEY_MAKE_SC(random(30))->move(this_object(), 1);
    MONEY_MAKE_CC(random(40))->move(this_object(), 1);
}

void
init_living()
{
    ::init_living();
    init_shop();
}

int
shop_hook_sold_items(object *item)
{
    write(break_string("You sold " + COMPOSITE_DEAD(item) + ".\n", 75));
    say(QCTNAME(this_player()) + " sold " + QCOMPDEAD + ".\n");
    tell_room(environment(), QCTNAME(this_object()) + " puts the things "+
      "in his sack.\n");
    return 1;
}

int
shop_hook_bought_items(object *arr)
{
    write(break_string("You bought " + COMPOSITE_DEAD(arr) + ".\n", 75));
    say(QCTNAME(this_player()) + " bought " + QCOMPDEAD + ".\n");
    tell_room(environment(), QCTNAME(this_object()) + " rummages around in "+
      "his sack.\n");
    return 1;
}

int
shop_hook_value_no_match(string str)
{
    notify_fail("I have no '" + str + "' in my sack.\n");
}

void
shop_hook_list_empty_store(string str)
{
    notify_fail("I have nothing to sell right now.\n");
}

int
shop_hook_list_no_match(string str)
{
    notify_fail("I have no '" + str + "' in my sack.\n");
}

int
do_read(string str)
{
    return 0;
}

/* removed bc a wierd bug
do_die(object killer)
{
   string text;
   if (query_hp() > 0) return;

   killer->catch_msg("A large group of city guardsmen arrives.\n");
   say("A large group of city guardsmen arrives.\n");
   killer->catch_msg("Shouts of MURDERER!!! echo around the lot!!!\n");
   say("Shouts of MURDERER!!! echo around the lot!!!\n");
   killer->catch_msg("You are bodily dragged to jail!!!\n");
   killer->move_living("towards jail, accompanied by several guardsmen", "/d/Kalad/common/trade/jail");

   text = "and "+capitalize(killer->query_real_name())+" has been "+
   "put in jail for crimes unspeakable.";
   call_other(CENTRAL(high-circle-south), "patrol_text", text);

   ::do_die(killer);
}
 this end the remark. Korat */
