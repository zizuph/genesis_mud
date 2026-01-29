/*
 * Dagger maker/salesman for the Union
 *  Cirion, Aug 5th, 1996
 * Maker of Akram's Dagger for a quest and 
 *  repeatable task.
 *
 * Revisions:
 *	Lilith, Jun 2004: Found problem with add'l dagger orders
 *	Lilith, Jun 2004: Updated path Heph walks to put dagger in the case.
 * 	Lucius, Jul 2017: Re-Code.
 *
 */
#pragma strict_types

#include "../defs.h"
inherit (NPC + "npc");

inherit "/d/Avenir/inherit/quest";
inherit "/d/Avenir/inherit/shop_list";

#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <stdproperties.h>

#define NO_ALCIN      0

public int counter, quest_alarm, knife_alarm;
public string questor;
public string *mats = ({ "copper", "iron", "bronze", "steel" }),
	      *types = ({ "slender", "light", "long", "curved" }),
	      *weps = ({ "dagger", "dirk", "knife" });

public void make_knife();


public string
query_questor(void)	{ return questor; }  

public void
set_questor(string str)	{ questor = str;  }  

public void 
create_monster(void)
{
    if (!IS_CLONE)
	return;

    set_name("hephamenios");
    set_living_name("hephamenios");
    set_race_name("human");
    set_adj("dark-skinned");
    add_adj("brooding");
    add_name(({"human", "heph", "weaponsmith"}));
    set_long("Enormous muscles bulge out from "
      +"beneath his shirt, sweat forming on his "
      +"brow as he toils around the forge. His face "
      +"has many worn lines, showing his age.\n");

    set_title("the Union Weaponsmith");   
    set_gender(G_MALE);

    set_base_stat(SS_OCCUP, 85);
    set_stats(({ 198, 146, 187, 85, 71, 84 }));

    set_union_npc();
    TO->set_union_sphere(SPH_WEAPONRY);

    add_prop(CONT_I_HEIGHT, 200);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_skill(SS_LANGUAGE,      99);
    set_skill(SS_WEP_KNIFE,     99);
    set_skill(SS_PARRY,         85);
    set_skill(SS_WEP_MISSILE,   78);
    set_skill(SS_ACROBAT,       20);
    set_skill(SS_AWARENESS,     85);
    set_skill(SS_DEFENCE,       60);
    set_skill(SS_UNARM_COMBAT,  74);
    set_skill(SS_SWIM,          30);
    set_skill(SS_CLIMB,         61);
    set_skill(SS_LOC_SENSE,     80);
    set_skill(SS_HERBALISM,     91);
    set_skill(SS_LOC_SENSE,     54);
    set_skill(SS_SWAY,          40);
    set_skill(SS_APPR_OBJ,      95);
    set_skill(SS_FLING,        100);
    set_skill(SS_SLASH,        100);

    set_alignment(-400);

    set_act_time(44);
    add_act("scowl .");
    add_act(({"remove cape","wash cape","wear cape"}));
    add_act("brood");
    add_act("murmur");
    add_act("blink");
    add_act("us I can makes knives and daggers to order.");
    add_act("rub sphere");
    add_act("flex fingers");
    add_act("stretch fingers");
    add_act("tighten");

    set_cact_time(3);
    add_cact("wield all");
    add_cact("fling");
    add_cact("sway");

    add_ask(({ "alcintaron" }), "say Names have power.", 1);
    add_ask(({ "anvil" }),
      "say Upon it shall I forge the death of our enemies.", 1);
    add_ask(({ "appraise" }), 
      "say The appraisal of objects is indeed a valuable skill.", 1);
    add_ask(({ "armour", "armours" }), 
      "say Wear not any armour that is too heavy, for it will "
      +"impede the ability to fight.", 1);
    add_ask(({ "blade" }), 
      "say The blade is the symbol of strength and grace.", 1);
    add_ask(({ "blades" }), "say They shall destroy our enemies.", 1);
    add_ask(({ "[for] [a] 'crucible' / 'crucibles'"}),
      "say Crucibles are important for making the metal for weapons.", 1);
    add_ask(({ "cylinder", "cylinders" }), 
      "say It is a great aide to "
      + "have, with it your blades will stay sharp and deadly.", 1);
    add_ask(({ "daggers" }), "say I can forge daggers and knives.", 1);
    add_ask(({ "flame" }), 
      "say It binds and surrounds us, everywhere, always.", 1);
    add_ask(({ "hammer" }), "say My hammer is as an artists "
      + "brush, with it I create.", 1);
    add_ask(({ "[goddess] 'jazur'"}),
      "say She is the one I serve, with all my being, body and soul.", 1);
    add_ask(({ "[how] [to] 'join' / 'joining' / 'unity' "+
	"[guild] / [union]" }), "say Seek "
      + "within the Pendentive. May you be found worthy.", 1);
    add_ask(({ "key" }), "say The Keys are many, great "
      + "is the mind that can find them all.", 1);
    add_ask(({ "knife" }), "say Upon my anvil I shall "
      + "someday forge the great Dagger of Akram.", 1);
    add_ask(({ "knives" }), "say They are our strength, "
      + "deadly do they fly through the air.", 1);
    add_ask(({ "make" }), "say I can make you a knife. What do "+
      "you want to order?", 1);
    add_ask(({ "material", "materials" }), 
      "say I can make things from "+ COMPOSITE_WORDS(mats) + ".", 1);
    add_ask(({ "order" }), "say You may simply do it.", 1);

    add_ask(({ "problem" }), "say I have none, do you?", 1);
    add_ask(({ "'repair' / 'repairing' [weapon]" }), 
      "say I will only spend my time creating new weapons.", 1);
    add_ask(({ "sharpen" }), "say I only make new weapons.", 1);
    add_ask(({ "sphere" }), "say Mine is the Sphere of Weaponry.", 1);
    add_ask(({ "sword", "swords" }), 
      "say They are inferior to a dagger blade wielded in "+
      "a graceful hand.", 1);
    add_ask(({ "tablet", "tablets" }), 
      "usay At Jazur's altar shall you worship and call forth "+
      "a shadow by name. Only then shall the key to the tablet "+
      "be revealed unto you.", 1);
    add_ask(({ "type", "types" }), "say I can make "
      + COMPOSITE_WORDS(types) + " knives and daggers.", 1);
    add_ask(({ "union" }), 
      "say We are a great and mighty Union of Warriors, bound "+
      "in shadows by the Flame of Jazur", 1);
    add_ask(({ "vision", "visions" }), 
      "say That is a personal matter.", 1);
    add_ask(({ "weapon" }), "say The mind is the greatest of those.", 1);
    add_ask(({ "weapons" }), "say Our weapons are many, "
      + "both seen and unseen.", 1);
    add_ask(({ "forge" }), 
      "say Upon my anvil are made instruments of battle.", 1);

    /* Quest asks */
    add_ask(({ "[dagger] [of] 'akram' [dagger]" }),
	VBFC_ME("akram_dagger"));
    add_ask(({ "[for] 'crucible' 'list'"}), VBFC_ME("crucible_list"));      
    add_ask(({ "special order" }), VBFC_ME("akram_dagger"));
    add_ask(({ "[for] 'help' / 'quest' / 'task'" }),
      VBFC_ME("akram_dagger"));
    add_ask(({ "[brick] [of] 'charcoal'" }), 
      "usay It is available in the Bazaar. I am sure you "+
      "will be able to locate it.", 1);
    add_ask(({"'glass' [shards] [from] [a] [crystal] "+
	"[goblet]", "[crystal] 'goblet'"}), 
      "usay Don't tell me you can't find one! Are all the "+
      "goblets on the table gone?", 1);
    add_ask(({"'shard' / 'shards' "+
	"[of] [glass] [from] [a] [crystal] [goblet]"}), 
      "usay Don't tell me you can't find one! Are all the "+
      "goblets on the table gone?", 1);
    add_ask(({"strangleweed"}), 
      "usay That stuff grows everywhere on the Holm.", 1);
    add_ask(({"[ingot] [of] 'ukku' [steel]" }), 
      "usay That you must obtain from the smith in the Bazaar.", 1);

    config_default_trade();
    set_money_give_reduce( ({ 0, 2, 3, 3 }) );
    set_store_room(file_name(TO));

    set_maxlist(30);
    set_show_price(1);
    set_blank_lines(0);

    give(50, TO);
    enable_reset();

    equip(({OBJ+"shirt", OBJ+"boots", OBJ+"gloves", OBJ+"cape"}));
    set_alarm(itof(random(1000) + 500), 600.0, make_knife);
}

public void
reset_monster(void)
{
    /* Start out with 15 knives to sell */
    int size = NUM_ITEMS("_union_heph_knife");
    while(size < 15)
    {
	size++;
	object arm = clone_object(OBJ+"u_knife");
	arm->randomize();
	arm->move(TO, 1);
    }

    size = NUM_ITEMS("cylinder");
    while(size < 3)
    {
	size++;
	clone_object(OBJ + "cylinder")->move(TO);
    }
    /*
     * Smiths items
     */
    size = NUM_ITEMS("smith_bar");
    while(size < 6)
    {
	size++;
	clone_object(DARK + "obj/ore")->move(TO);
    }

    size = NUM_ITEMS("smiths_leather");
    while(size < 6)
    {
	size++;
	clone_object(COM + "obj/sm_leather")->move(TO);
    }
}

public void
refresh_living(void)
{
    reset_monster();
    ::refresh_living();
}

private void 
return_unwanted(object what, object who)
{
    if (!objectp(what))
	return;

    if (present(who, environment()))
	command("usto "+ OB_NAME(who) +" Thank you, but I cannot accept this.");

    if (!command("give "+ OB_NAME(what) +" to "+ OB_NAME(who)))
	what->remove_object();  
}

/* for Akram's Dagger quest */
public string 
akram_dagger(void)
{  

    if (!IS_MEMBER(TP))
    {
	command("laugh");
	return "";
    }

    if (present("crucible", TP))
    {
	command("usay You should know what you need to "+
	  "put in the crucible, but if your memory is failing, "+
	  "you can ask me for the crucible list.");
	return "";
    }

    if (!IS_TORNU(TP))
    {
	command("usay When you are Tornu, then we will talk "+
	  "about such things.");
	return "";
    }

    if (TP->test_bit("Avenir", GUILD_GROUP, AKRAM_DQ))
    {
	object crucible = clone_object(OBJ +"crucible");
	//Already done the quest, lets make another dagger.
	command("usay You want another special order, do you?");
	crucible->move(TO);
	crucible->name_it(TP->query_real_name());
	command("give crucible to "+ TP->query_real_name());
	command("usay You should know what you need to "+
	  "put in the crucible, but if your memory is failing, "+
	  "you can ask me for the crucible list.");
	return "";
    }

    if (IS_TORNU(TP))    
    {
	// done guru quest, lets hint what to do next.
	command("usay Ah Tornu, so now you want a blade worthy of you?");
	command("usay You must have something for me, a stone tablet, "+
	  "perhaps?");
	return "";  
    }
    // Almost there, just needs to do guru quest.
    command("whisper to "+ TP->query_real_name() +
      " Ask me again after you have entered the Flame "+
      "and looked upon the face of Akram.");
    return "";
}

public string 
crucible_list(void)
{
    if (!IS_MEMBER(TP))
    {
	command("laugh");
	return "";
    }

    if (!IS_TORNU(TP))
    {
	command("usay When you are Tornu, then we will talk "+
	  "about such things.");
	return "";
    }

    if (IS_TORNU(TP))
    {       
	command("whisper to "+ OB_NAME(TP) +
	  " Five items will you need to place in the crucible and "+
	  "bring to me: an ingot of ukku from the smithy in the "+
	  "bazaar, a handful of thin grey weeds known as strangleweed, "+
	  "a brick of charcoal, glass shards from a crystal "+
	  "goblet, and something else, which would have been "+
	  "revealed to you in a vision.");
	return "";
    }

    command("whisper to "+ OB_NAME(TP) +
      " Ask me again after you have entered the Flame "+
      "and looked upon the face of Akram.");
    return "";
}

private void
tablet_test(object tablet, object player)
{
    object crucible;

    if (!present("_alcin_tablet",TO))
	return;

    if (!IS_MEMBER(TP))
    {
	command("say Thank you for turning that in.");
	return;
    }

    if (!IS_TORNU(TP))
    {
	command("usay However it is that you came by this tablet, "+
	  "it was not through the appropriate channels, for you "+
	  "are not yet Tornu. Thank you for turning it in, I "+
	  "will see that it is returned.");
	return;
    }

    if (NO_ALCIN)
    {
	command("say I am unable to make any ukku daggers at this time. "+
	  "Please try again another day.");       
	set_alarm(5.0, 0.0, &return_unwanted(tablet, player));
	return;
    }   

    command("emote hefts the tablet in his hands.");
    command("frown thought "+ player->query_real_name());
    set_alarm(2.0, 0.0, &command("usay My old sybarite is a bit rusty, "+
	"but lets see what this says..."));
    set_alarm(6.0, 0.0, &command("uwet"));
    set_alarm(10.0, 0.0, &command("usay Quansu Weaponsmith! The bearer "+
	"of this tablet has earned the right to carry a weapon made "+
	"in the style of Akram's dagger. You are authorized to use ukku "+
	"steel for this purpose. As always, the burden of acquiring "+
	"and paying for materials will be borne by the Warrior. "));
    set_alarm(20.0, 0.0, &command("usay With flame and steel shall we "+
	"defeat our enemies. By my own hand, Alcinta... err "+
	"the former Weaponsmith of the Union."));
    set_alarm(22.0, 0.0, &command("emote gets something from behind "+
	"the forge."));     
    tablet->remove_object();  
    crucible = clone_object(OBJ +"crucible");
    crucible->move(TO);
    crucible->name_it(player->query_real_name());
    set_alarm(24.0, 0.0, &command("give crucible to "+ OB_NAME(player)));
    set_alarm(27.0, 0.0, &command("whisper to "+ OB_NAME(player) +
	" Five items will you need to place in the crucible and "+
	"bring to me: an ingot of ukku from the smithy in the "+
	"bazaar, a handful of thin grey weeds known as strangleweed, "+
	"a brick of charcoal, glass shards from a crystal "+
	"goblet, and something else, which would have been "+
	"revealed to you in a vision."));
    set_alarm(30.0, 0.0, &command("whisper to "+ OB_NAME(player) +
	" The crucible will remain with you until such time as you are "+
	"ready to return it to me."));
}

private int
quest_hearers(object ob)
{
    if (!present(TOKEN_ID, ob)) 
	return 0;

    if (present(ob, ENV(TO)))
	return 0;

    return 1;
}

private void
do_dagger(void)
{
    object player, dagger;

    quest_alarm = 0;

    if (!strlen(questor))
	return;

    dagger = clone_object(OBJ +"akram_dagger");
    dagger->set_owner(questor);
    dagger->config_owner();
    dagger->set_may_recover();
    dagger->move(TO, 1);

    player = find_player(questor);
    if (!player || player->query_linkdead())
    {
	command("up");
	command("up");
	command("up");
	command("west");
	command("south");
	command("open case");
	command("put _akram_dagger in case");
	command("close case");
	command("north");
	command("east");
	command("down");
	command("down");
	command("east");
	set_questor(0);
	return;
    }

    tell_object(player, "A shadowy child arrives.\nThe shadowy child "+ 
      "grabs onto your leg and won't let go.\nHe hands you a weapon "+
      "and says: I have something for you from Hephamenios.\nThe "+
      "shadowy child runs away.\n");
    tell_room(environment(player), "A shadowy child arrives.\n"+
      "He runs up to "+ QTNAME(player) + " and clings to "+ 
      player->query_possessive()+ " leg. After catching its breath, "+
      "the child gives "+ player->query_objective() + " something.\n", 
      player);

    dagger->move(player, 1);
    set_questor(0);
}

private void
all_clear(void)
{
    if (quest_alarm)
	return;

    command("emote summons arcane magics.");
    quest_alarm = set_alarm(itof(1000 + random(1000)), 0.0, do_dagger);
    filter(users(), quest_hearers)->catch_tell("A current of heat "+
      "flows through your sphere, and a vision of Hephamenios "+
      "forging a weapon with arcane magic comes to mind.\n");
}

public void
check_room(void)
{
    quest_alarm = 0;

    // Am I making the dagger for someone?
    if (!strlen(questor))
	return;

    // someone is here and I have to wait.
    command("usay What I do next must be done in secrecy.");
    command("usay I will not begin until you leave.");       
    command("patient");

    // I am making the dagger but I haven't started
    // yet, wating to make sure no-one is around.
    all_clear();
}

private int
crucible_test(object crucible, object player)
{
    if (!present("_union_crucible", TO))
	return 0;

    if (!IS_MEMBER(TP))
    {
	command("say Thank you for turning that in.");
	command("bow");
	return 1;
    }

    if (!IS_TORNU(TP))
    {
	command("usay However it is that you came by this crucible, "+
	  "it was not through the appropriate channels, for you "+
	  "are not yet Tornu. Thank you for returning it to me.");
	return 1;
    }

    if (NO_ALCIN)
    {
	command("say I am unable to make any ukku daggers at this time. "+
	  "Please try again another day.");       
	set_alarm(5.0, 0.0, &return_unwanted(crucible, player));
	return 1;
    }   

    if (quest_alarm)
    {
	command("say I am unable to make any ukku daggers at this time. "+
	  "Please try again later.");       
	set_alarm(2.0, 0.0, &return_unwanted(crucible, player));
	return 1;
    }   

    if (crucible->test_it() < 1)
    {
	command("frown");
	set_alarm(3.0, 0.0, &command("usay There should be five items "+
	    "in the crucible. Bring it back when you have everything."));
	set_alarm(5.0, 0.0, &return_unwanted(crucible, player));
	return 1;
    }

    command("joy");
    command("usay Its all here! Excellent!");

    if (!player->test_bit("Avenir",GUILD_GROUP,AKRAM_DQ))
    {
	reward_quest("Akram's Dagger", player,
	    GUILD_GROUP, AKRAM_DQ, AKRAM_EXP);
    }

    command("usay This is going to take quite some time. Leave me "+
      "to my work.");
    command("usay I shall send a message when I have finished. "+
      "If you are unavailable, I will put it in the case.");
    set_alarm(6.0, 0.0, &command("emote takes a moment to reflect "+
	"upon this momentous undertaking, then springs into action."));     

    crucible->remove_object();
    set_questor(player->query_real_name());

    /* Are you still here?!?! */
    quest_alarm = set_alarm(30.0, 0.0, check_room);
    return 1;
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!living(from))
	return;

    if (obj->id("_union_crucible"))
    {
	crucible_test(obj, from);
	return;
    }

    if (obj->id("_alcin_tablet"))
    {
	tablet_test(obj, from);
	return;
    }

    set_alarm(2.0, 0.0, &return_unwanted(obj, from));
}

private void
finish(string *stuff)
{
    object knife = clone_object(OBJ + "u_knife");
    knife->set_type(stuff[0]);
    knife->set_mat(stuff[1]);
    knife->set_wep(stuff[2]);
    knife->init_knife();

    knife_alarm = 0;
    knife->move(TO, 1);
    command("emote finishes work on "+ LANG_ADDART(knife->short()) +".");
}

public int
order(string str)
{
    string str1, str2, *stuff;

    if (!IS_MEMBER(TP))
	return NF("He ignores you.\n");

    if (knife_alarm)
	return NF("He seems to be busy making another knife right now.\n");

    NF("Order what? Order <type> <material> <weapon>\n");
    if (!str || !strlen(str))
	return 0;

    stuff = explode(str, " ");
    if (sizeof(stuff) != 3)
	return 0;

    if (member_array(stuff[0], types) == -1)
    {
	write("I cannot make that type. Possible type are "+
	  COMPOSITE_WORDS(types) +".\n");
	return 1;
    }

    if (member_array(stuff[1], mats) == -1)
    {
	write("I do not use that material. Possible materials are "+
	  COMPOSITE_WORDS(mats) +".\n");
	return 1;
    }

    if (member_array(stuff[2], weps) == -1)
    {
	write("I cannot make that sort of weapon. Possible weapons are "+
	  COMPOSITE_WORDS(weps) +".\n");
	return 1;
    }

    command("us I will begin work on the weapon immediately.");
    command("emote takes " + LANG_ADDART(stuff[1]) +
      " blade from the rack and begins hammering it.");

    knife_alarm = set_alarm(itof(20 + random(40)), 0.0, &finish(stuff));
    return 1;
}

private void
make_knife(void)
{
    if (NUM_ITEMS("_union_heph_knife") > 30)
    {
	counter = 0;
	return;
    }

    switch(++counter)
    {
    case 1:
	command("emote stokes the forge and begins work on a new knife.");
	break;
    case 2:
	command("emote continues work on a knife.");
	break;
    case 3:
	command("emote places some hot metal in the "+
	  "water to cool with a pair of tongs.");
	break;
    case 4:
	command("emote remove some metal from the water "+
	  "and begins pounding it on the anvil.");
	break;
    case 5:
	command("emote attatches a handle to the newly formed blade.");
	break;
    case 6:
	command("emote sharpens the knife of a small whetstone.");
	break;
    case 7:
      {
	command("emote polishes the knife, completing it.");
	object arm = clone_object(OBJ+"u_knife");
	arm->randomize();
	arm->move(TO, 1);
	counter = 0;
	break;
      }
    }
}

/* Shop function redefinitions */

/* Only sell what I am supposed to */
public int
shop_hook_allow_buy(object ob)
{
    if (ob->query_worn() || ob->query_wielded())
	return 0;

    return (ob->id("knife") || ob->id("cylinder") ||
	    ob->id("smith_bar") || ob->id("smiths_leather"));
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

#if 0
public int
shop_hook_bought_items(object *obs)
{
    /* Maybe replenish smith items early. */
    foreach(object ob : obs)
    {
	if (!random(3))
	    break;

	if (ob->id("smith_bar"))
	    clone_object(DARK + "obj/ore")->move(TO);

	if (ob->id("smiths_leather"))
	    clone_object(COM + "obj/sm_leather")->move(TO);
    }

    return ::shop_hook_bought_items(obs);
}
#endif

public string
category(object ob)
{
    if (ob->id("smith_bar") ||  ob->id("smiths_leather"))
	return "Smithy";
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
	command("us I have been instructed by the Elders to sell "
	  + "you nothing, " + TP->query_name() + ".");
	return 1;
    }

    if (!IS_MEMBER(TP) && !FRIEND(TP))
    {
	command("say I will sell you nothing, "+ TP->query_race_name() +".");
	return 1;
    }

    if (FRIEND(TP))
	command("say Since you are an ally, you may purchase from me.");

    return ::do_buy(str);
}

public void
init_living(void)
{
    ::init_living();

    add_action(do_list,  "list");
    add_action(do_buy,   "buy");
    add_action(do_show,  "show");
    add_action(do_value, "value");
    add_action(order,    "order");
}

public void
update_internal(int l, int w, int v)
{
    ::update_internal(l, w, v);
    force_new_list();
}
