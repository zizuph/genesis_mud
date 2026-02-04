/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * smiley.c
 *
 *  This is an NPC named "Argarn".  He is called by shop.c as a        
 *  shopkeeper.  If he is killed, the shop will not function.  
 *
 *  Coded by Vader on 10/18/93
 *  modified by Sorgum 12/4/94
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/d/Terel/include/log_asks";

#include <ss_types.h>
#include <money.h>

void add_introduced(string swho);


#define HUNTING_TREVIN "_i_hunting_trevin"

public string
reply_assassin()
{
    if(TP->query_prop(HUNTING_TREVIN))
    {
          command("say Ahh, tall dark and gruesome...");
          command("say He was staying in the northeast room, but he's gone now.");
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

    set_name("argarn");
    set_living_name("argarn");
    set_race_name("half-elf");
    set_title("Half-Elven, Innkeeper of the White Dragon Inn");
    set_adj("attentive");
    set_long("This half-elf runs this fine establishment. He will take care of"+
             " your needs as far as lodging is concerned.\n");

     /* Average stat: 170
     */
     default_config_npc(80);

    /* But we want it to have more hitpoints
     */
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_UNARM_COMBAT, 60);
    set_hp(5500);

    set_all_hitloc_unarmed(15);

    set_chat_time(15);
    add_chat("Welcome to the White Dragon Inn");
    add_chat("I can provide you with a warm room and a good nights rest.");
    add_chat("Thankfully we have Gwailin to protect us, so there are rarely"+
             " problems with violence in the town.");
    set_act_time(10);
    add_act("smile all");
    add_act("emote straightens up the room.");
    add_ask("tall wiry male human", reply_assassin, 1);
    add_ask("pickle","say I don't have a pickle!", 1);

}

public void add_introduced(string s_who)
{
    object o_who = find_player(s_who);


    if(o_who &&
       !o_who->query_met(this_object()))
        set_alarm(itof(random(5) + 1), 0.0, "command",
                  "introduce myself to "+ s_who);

}

