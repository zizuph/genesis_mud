inherit "/std/monster";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

private int armed = 0;

create_monster()
{
    if (!IS_CLONE)
	return;
    set_name(({"citizen","man"}));
    set_race_name("rohirrim"); 
    set_short("rohirrim man");
    set_long(BSN("This is a regular citizen of Edoras. He has golden hair like all people of his kin."));
    set_stats(({ 25, 25, 25, 20, 10, 5}));
    set_hp(1100);
    set_alignment(125 + random (50));
    set_skill(SS_WEP_KNIFE,20);
    set_chat_time(30);
    set_act_time(30);
    add_chat("I love this town.");
    add_chat("The best beer in the world, that's the beer you can get here!");
    add_chat("I wouldn't eat the porridge, it tastes terrible!");
    add_chat("You should try the stew, it's great!");
    add_chat("Best inn in Edoras, really!");
    add_chat("Edoras is nice.");
    add_act("@@buy_beer");
    add_act("@@buy_ale");
    add_act("@@buy_stew");
    add_prop(LIVE_I_NEVERKNOWN,1);
    
    arm_me();
}

void
arm_me()
{
    if (armed)
	return;

    FIX_EUID;
    clone_object(EDORAS_DIR + "obj/fknife")->move(TO);
    command("wield knife");

    clone_object(EDORAS_DIR + "obj/leather")->move(TO);
    command("wear armour");

    armed = 1;
}


buy_ale()
{
  make_money(10,"copper");
  command("buy ale");
  command("drink ale");
}

buy_beer()
{
  make_money(15,"copper");
  command("buy beer");
  command("drink beer");
}

buy_stew()
{
  make_money(30,"copper");
  command("buy stew");
  command("eat stew");
}

make_money(i,type)
{
  object money;

    FIX_EUID;
  money=clone_object("/std/coins");
  money->set_heap_size(i);
  money->set_coin_type(type);
  money->move(this_object(),1);
}

/* Solemnian prestige */
query_knight_prestige() {return (-5);}

