/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * lanc.c
 *
 * Weaponshop Keeper of Last
 * 
 *
 *  Shinto of Terel, 7-18-98
 *  
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/d/Terel/include/log_asks";

#include <ss_types.h>
#include <money.h>
public string
reply_giants()
{
    command("say The frost giants come down from the far north");
    command("say The good thing about them is, they don't like the goblins"+
                   " much either.");
    return "";
}

public string
reply_goblin()
{
    command("say Goblins are by far the filthiest of our attackers.");
    command("say They live up north and northwest in three tribes.");
    return "";
}

public string
reply_dragon()
{
    command("say The great White, he covers us with snow when he gets a "+
                   "stomach ache!");
    command("say He lives in the mountain, we've renamed after him.");
    return "";
}

public string
reply_calathin()
{
    command("say Calathin lies southwest from here, "+
        "another small trading town likes ours. Head west till you "+
        "reach the cornerstone, then make your way south through "+
        "the Silver forest.");
    return "";
}
#define HUNTING_TREVIN "_i_hunting_trevin"

public string
reply_assassin()
{
    if(TP->query_prop(HUNTING_TREVIN))
    {
          command("say Tall wiry male human...");
          command("say I believe I saw him a day or so ago, leaving town.");
          command("say Looked as if he was heading towards Calathin.");
          command("say That guy though, he's come through here before.");
          return "";
    }
    return "";
}


create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
					return;

    set_name("lanc");
    set_living_name("lanc");
    set_race_name("dwarf");
    set_title("Firehammer, Owner of the Weapon Shop of Last");
    set_adj("grimacing");
    set_long("  \n");

     /* Average stat: 60     */
     default_config_npc(60);

    /* But we want it to have more hitpoints
     */
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_UNARM_COMBAT, 60);
    set_hp(5500);

    set_all_hitloc_unarmed(15);

    set_chat_time(15);
    add_chat("Welcome to my shop!");
    add_chat("I only deal in Weapons, anything else you'll have to find some other"+
                   " place.");
    add_chat("Nearly closing time, think I'll slip over to the Snowhouse and see "+
                   "if that halfling, Brownshort, can find something worth drinking.");
    set_act_time(10);
    add_act("emote picks up a steel longsword and quickly sharpens the blade.");
    add_act("emote mutters something about filthy goblins.");
    add_act("emote folds his arms across his chest and leans against the wall.");
    add_ask(({"siralan","Siralan","white","White","the White","dragon"}), 
                      reply_dragon, 1);
    add_ask(({"giants","giant","frost giants"}), reply_giants, 1);
    add_ask(({"goblins","goblin"}),reply_goblin, 1);
    add_ask(({"calathin","Calathin"}), reply_calathin, 1);
    add_ask("tall wiry male human", reply_assassin, 1);
}

public void add_introduced(string s_who)
{
    object o_who = find_player(s_who);


    if(o_who &&
       !o_who->query_met(this_object()))
        set_alarm(itof(random(5) + 1), 0.0, "command",
                  "introduce myself to "+ s_who);

}


