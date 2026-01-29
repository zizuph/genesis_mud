/* Villagers of Ovejuno's village
 * Coded by Marisol (05/13/98)
 * Modified by Marisol (08/30/98) to be used in Ovejuno, Emerald
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
 command("emote looks at you with suspiction in his eyes.");
 command("say Don't say his name, stranger! It will bring you bad "+
 "luck. Mark my words!\n");
 return "";
}

void
create_emerald_monster()
{

    set_name("ribalto");
    add_name("man");   
    set_adj("sturdy");
    set_long("This is a sturdy villager, chatting with his "+
       "fellow friends. He seems to be friendly but at the "+
       "same time stern.\n");
    set_race_name("human");
    set_gender(G_MALE);

    set_appearance(90);

    set_alignment(80);
    set_stats(({90,90,95,70,70,80}));

   set_skill(SS_DEFENCE,40);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_BLIND_COMBAT,50);

    /* This chatter will say something every now and then... :) */

    set_chat_time(5); /* Interval between chat */

/* And the list we will run through, it will be randomized but our chatter
* won't say something he has already said from the list again until the
* whole list is gone through, and randommized again.*/


    add_chat("Hmm, nothing good will come from the new lord. He is "+
        "doom living in that castle!");

    add_chat("We should have burnt the castle after the old lord "+
        "die! Then we shouldn't worry about the curse.\n");

    add_chat("A foreigner, ahh?");

    set_default_answer("The sturdy man says: I don't know about such "+
       "things, stranger.\n");

    add_ask("new lord", "The sturdy man says angrily: That elf "+
        "doesn't know what to do with his title. He doesn't care "+
        "about us, like all the previous lords of Ovejuno. He just "+
        "wants our taxes to send it to the capital. But doesn't he "+
        "care about the curse? Not a bit! I tell you. He will die "+
        "horribly when the time comes, mark my words.\n");

    add_ask("castle", "It is up to the north of our village. The old "+
        "stories said that it was really beautiful like a fairy "+
        "castle. But now, there is not way that I will put my feet "+
        "there!\n");

    add_ask("curse", "You want to know about the curse, ah? Well "+
        "is just that people die mysteriously in that castle. I mean "+
        "not blood or visible wounds or anything. People seems to die "+
        "with fright during the night. Now our people have to work "+
        "under duress in the castle because the new lord. And he "+
        "doesn't care or even want to exorcise the curse! These are bad "+
        "time for us.\n");

    add_ask("old lord", "The sturdy man whispers to you: That was "+
        "Morboses, curse his name.\n");

    add_ask("morboses", ask_morboses);

}                                     
