/*
 * Salesman for some equipment in the Union.
 *  Cirion, August 5th, 1996
 *
 * Revisions:
 * 	Lucius, Jul 2017: Re-Code.
 *
 */
#pragma strict_types
#include "../defs.h"

inherit (NPC + "npc");
inherit "/d/Avenir/inherit/shop_list";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>


public void
create_monster()
{
    if (!IS_CLONE)
	return;

    set_name("arcadelt");
    set_living_name("arcadelt");
    set_race_name("elf");
    set_adj("tall");
    add_adj("slender");

    set_long("Tall and slender, he stands before you "+
      "with a distant look on his face. His long "+
      "black hair is one long braid that falls over "+
      "his right shoulder.\n");

    set_gender(G_MALE);
    set_stats(({ 98, 86, 47, 85, 71, 84 }));
    set_base_stat(SS_OCCUP, 65);

    set_union_npc();
    TO->set_union_sphere(SPH_MENTOR);

    set_skill(SS_LANGUAGE,      99);
    set_skill(SS_WEP_KNIFE,     69);
    set_skill(SS_PARRY,         25);
    set_skill(SS_WEP_MISSILE,   18);
    set_skill(SS_ACROBAT,       20);
    set_skill(SS_AWARENESS,     85);
    set_skill(SS_DEFENCE,       80);
    set_skill(SS_UNARM_COMBAT,  44);
    set_skill(SS_SWIM,          30);
    set_skill(SS_CLIMB,         61);
    set_skill(SS_LOC_SENSE,     80);
    set_skill(SS_HERBALISM,     91);
    set_skill(SS_LOC_SENSE,     54);
    set_skill(SS_SWAY,          40);

    set_alignment(-600);

    set_act_time(25);
    add_act("murmur");
    add_act("dignity");
    add_act("blink");
    add_act("rub sphere");

    set_cact_time(3);
    add_cact("wield all");
    add_cact("fling");
    add_cact("sway");

    add_ask(({ "hizarbin" }), "say He is of water and death.", 1);
    add_ask(({ "book" }), "say That is the domain of Sonia.", 1);
    add_ask(({ "door" }), "say Doors in this world are "+
      "many, and many through which we shall never pass.", 1);
    add_ask(({ "job" }), "say I have none.", 1);
    add_ask(({ "join" }), "say That is done whithin the Pendentive.", 1);
    add_ask(({ "key" }), "say A key? I have none of those...", 1);
    add_ask(({ "seek" }), "say We all seek something, do we not?", 1);
    add_ask(({ "shadows" }), "say They bind and protect us.", 1);
    add_ask(({ "shard" }), "say I have it not.", 1);
    add_ask(({ "shelf" }), "say Items of general use are placed upon it.", 1);
    add_ask(({ "skills" }), "say I have many skills.", 1);
    add_ask(({ "sphere" }), "say Mine is the Sphere of Shadow Mentors.", 1);
    add_ask(({ "sway" }), "say It shall draw the power "+
      "of the Flame to us, engulfing and imbuing us with grace.", 1);
    add_ask(({ "task" }), "say There are none.", 1);
    add_ask(({ "union" }), "say The Union is a state of "+
      "joining between the entities of Light and Dark, "+
      "the domain where only Shadows dwell.", 1);

    add_prop(CONT_I_HEIGHT, 200);

    config_default_trade();
    set_money_give_reduce( ({ 0, 2, 3, 3 }) );
    set_store_room(file_name(TO));

    set_maxlist(30);
    set_show_price(1);
    set_blank_lines(0);

    give(500, TO);
    enable_reset();
    equip(({OBJ+"robe", OBJ+"sandals", OBJ+"gloves"}));
}

public void
reset_monster(void)
{
    int size = NUM_ITEMS("knapsack");
    while(size < 4)
    {
	size++;
	clone_object(OBJ+"knapsack")->move(TO, 1);
    }

    size = NUM_ITEMS("torch");
    while(size < 4)
    {
	size++;
	clone_object(OBJ+"torch")->move(TO, 1);
    }

    size = NUM_ITEMS("sandals");
    while(size < 5)
    {
	size++;
	clone_object(OBJ+"sandals")->move(TO);
    }

    size = NUM_ITEMS("robe");
    while(size < 5)
    {
	size++;
	clone_object(OBJ+"robe")->move(TO);
    }

    size = NUM_ITEMS("boots");
    while(size < 4)
    {
	size++;
	clone_object(OBJ+"boots")->move(TO);
    }
}

public void
refresh_living(void)
{
    reset_monster();
    ::refresh_living();
}

public void
init_living(void)
{
    ::init_living();

    add_action(do_buy,   "buy");
    add_action(do_show,  "show");
    add_action(do_list,  "list");
    add_action(do_value, "value");
}

/* Only sell what I am supposed to */
public int
shop_hook_allow_buy(object ob)
{
    if (ob->query_worn() || ob->query_wielded())
	return 0;

    return (ob->id("knapsack") || ob->id("sandals") ||
	    ob->id("robe") || ob->id("boots") || ob->id("torch"));
}

public void
shop_hook_list_empty_store(string str)
{
    command("say I have nothing left.");
}

public string
shop_hook_list_object(object ob, int amount)
{
    if (!shop_hook_allow_buy(ob))
	return "";
    else
	return ::shop_hook_list_object(ob, amount);
}

public int
do_buy(string str)
{
    if (query_attack())
    {
	write(CAP(query_pronoun()) + " seems too busy right now.\n");
	return 1;
    }

    if (U_IS_PUNISHED(TP, U_PUNISHED_NOBUY))
    {
	command("us I have been instructed by the Elders to sell "+
	    "you nothing, " + TP->query_name() + ".");
	return 1;
    }

    if (!IS_MEMBER(TP) && !FRIEND(TP))
    {
	command("say You are not permitted to buy anything here, "+
	    TP->query_race_name() + ".");
	return 1;
    }

    return ::do_buy(str);
}

public string
category(object ob)
{
    if (ob->id("sandals"))
	return "Feet";

    if (ob->id("knapsack"))
	return "Pack";
}

public void
update_internal(int l, int w, int v)
{
    ::update_internal(l, w, v);
    force_new_list();
}
