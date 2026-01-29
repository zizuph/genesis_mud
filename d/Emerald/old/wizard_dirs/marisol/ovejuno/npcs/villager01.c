/* Villagers of Re Albi's village
 * Coded by Marisol (4/7/98)
 * Modified by Marisol (08/20/98) to be used in the village of
 * Ovejuno in Emerald.
 * Copyright (c) Marisol Ramos 1998 */

#pragma strict_types
inherit "/d/Emerald/std/emerald_monster";
inherit "/d/Genesis/lib/intro";
#include "/d/Emerald/sys/macros.h"     
#include <macros.h>
#include <const.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include "defs.h"

string
ask_morboses()
{
 command("emote looks at you in terror. She moves her hand swiftly "+
 "to form a protective charm against evil.");
command("say Don't ask about him! Is bad luck! Go away!\n");
 command("" + environment()->query_exit_cmds()[random(sizeof(environment()->
 query_exit_cmds()))]);
 return "";
}

void
create_emerald_monster()
{

    set_name("rosa");                                         
    add_name("woman");
    set_adj("buxom");
    set_long("This is a buxom young villager, going about "+
       "her business. She looks nice and healthy.\n");
    set_race_name("human");
    set_gender(G_FEMALE);
    set_random_move(45);
    set_restrain_path(VILLAGE);
    set_monster_home(VILLAGE+"village_ov05.c");
    set_appearance(70); 

    set_alignment(80);
    set_stats(({70,70,75,60,60,70}));

   set_skill(SS_DEFENCE,20);
   set_skill(SS_UNARM_COMBAT,30);
   set_skill(SS_BLIND_COMBAT,50);

    /* This chatter will say something every now and then... :) */

    set_chat_time(3); /* Interval between chat */

/* And the list we will run through, it will be randomized but our chatter
* won't say something he has already said from the list again until the
* whole list is gone through, and randommized again.*/


    add_chat("Welcome to our village! I hope you like our village "+
       "better than our new lord.");

    add_chat("Hi, you are a foreigner, aren't you?");

    add_chat("Be careful when visiting the Lord's castle. I believe "+
        "is haunted or worse!");

    add_chat("Our village hasn't been the same since the last lord "+
        "die horribly quite a while ago");

    set_default_answer("The buxom woman says: I don't know about such "+   
        "things, stranger.\n");

    add_ask("new lord", "The buxom woman says with distaste: He just "+
        "moves recently, and he is stuffy like any elvish noble. He "+
        "doesn't know what he is getting into moving to that castle "+
        "though.\n");

    add_ask("village", "The buxom woman says: This is our village "+
        "Ovejuno. We are all humans and our new lord is a noble elf of "+
        "Telberin. This is a really nice place to live, I hope "+
        "you like it.\n");

    add_ask("help", "The buxom woman says helpfully: You want my "+
        "help? Let see, I don't know how I can help you. I just can "+
        "tell you what I know about my village, you just need to "+
        "ask me.\n");

    add_ask("castle", "The buxom woman whispers: It is haunted! "+
        "No one has lived there since the last lord died. A cousin "+
        "of mine was forced by the new lord to work there and she "+
        "is just terrified to stay the night. Horrible things are "+
        "happening there and someone could die soon!\n");

    add_ask("last lord", "The buxom woman says: Morboses was the last "+
        "lord to live in the castle. But he did something terrible "+
        "to the king, so the king' wizards came here and attacked him. "+
        "The last thing we knew was that he died by a spell and his "+
        "body never was found.\n");

    add_ask("morboses", ask_morboses);

}                                                              
