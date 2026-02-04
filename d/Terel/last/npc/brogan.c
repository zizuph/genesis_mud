/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * brogan.c
 *
 * Smith of Last
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
    command("say The last time they came, I was able to slay three "+
                   "before they even reached the town!");
    return "";
}

public string
reply_goblin()
{
    command("say Goblins are the worst, the leave a smell that could "+
                   "kill a dragon.");
    command("say They live up north and northwest, three seperate tribes.");
    command("say The Black Fang, Grim Claw, and Red Talon clans.");
    return "";
}

public string
reply_dragon()
{
    command("say Siralan, I entered his lair once when I was younger.... ");
    command("say He lives in the mountain, we've renamed after him.");
    command("say Never again will I make that foolhardy journey.");
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

create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
					return;

    set_living_name("brogan");
    set_name("brogan");
    set_race_name("dwarf");
    set_title("Battlehammer, Smith of the Town of Last");
    set_adj("gruff");
    add_adj("muscular");
    set_long("He stands no more then 4 ft, but looks powerful enough to throw"+
                  " you through the wall.  Long hours at the forge hammering have "+
                  "strengthen his arms and scorched his skin. \n");

     /* Average stat: 60     */
     default_config_npc(60);


    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_UNARM_COMBAT, 60);
    set_hp(5500);

    set_all_hitloc_unarmed(15);

    set_chat_time(15);
    add_chat("Welcome to my Smithy!");
    add_chat("I only fix Weapons, anything else you'll have to find some other"+
                   " place.");
    add_chat("Getting time to hit the Snowhouse, I'm betting Lanc will meet me "+
                   "there on his third or fourth.");
    set_act_time(10);
    add_act("emote picks up a steel longsword and quickly sharpens the blade.");
    add_act("emote mutters something about pathetic stinking goblins.");
    add_act("emote fans the flames of his forge.");
    add_ask(({"siralan","Siralan","white","White","the White","dragon"}), 
                      reply_dragon, 1);
    add_ask(({"giants","giant","frost giants"}), reply_giants, 1);
    add_ask(({"goblins","goblin"}),reply_goblin, 1);
    add_ask(({"calathin","Calathin"}), reply_calathin, 1);
}

public void add_introduced(string s_who)
{
    object o_who = find_player(s_who);


    if(o_who &&
       !o_who->query_met(this_object()))
        set_alarm(itof(random(5) + 1), 0.0, "command",
                  "introduce myself to "+ s_who);

}


