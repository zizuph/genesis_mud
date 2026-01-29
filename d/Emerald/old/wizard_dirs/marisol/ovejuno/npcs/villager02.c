
/* Villagers of Ovejuno's village
 * Coded by Marisol (05/12/98)
 * Modified by Marisol (08/29/98) to be used in the village of Ovejuno
 * in Emerald.
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
  command("emote looks at you with suspicion in his eyes.");
  command("say Don't say his name, stranger! You don't know what "+
  "you are getting into!\n");
 return "";
}

void
create_emerald_monster()
{

    set_name("amadeo");
    add_name("man");
    set_adj("grizzled");               
    set_long("This is a grizzled villager, chatting with his "+
       "fellow friends. He seems to be friendly and a mischievous "+
       "spark lights his eyes.\n");
    set_race_name("human");
    set_gender(G_MALE);
    
    set_appearance(10);

    set_alignment(80);
    set_stats(({70,70,75,60,60,70}));

   set_skill(SS_DEFENCE,20);
   set_skill(SS_UNARM_COMBAT,30);
   set_skill(SS_BLIND_COMBAT,50);

    /* This chatter will say something every now and then... :) */

    set_chat_time(5); /* Interval between chat */

/* And the list we will run through, it will be randomized but our chatter
* won't say something he has already said from the list again until the
* whole list is gone through, and randommized again.*/


    add_chat("I went to the brook yesterday and the fishes were "+
        "bitting nicely.");

    add_chat("You know, I have an horrible toothache yesterday "+
        "but the sage femme cured me so fast that seems like magic.");



    add_chat("You hear about the new lord moving to the old castle? "+
        "I am sure he will regret it!");

    set_default_answer("The grizzled man says: I don't know about such "+
        "things, stranger.\n");

    add_ask("sage femme", "The grizzled man says helpfully: If you want "+
       "to find our healer, you need to go to the north end of "+
       "the village.\n");

    add_ask("lord", "The grizzled man says scornfully: He is a "+
        "fool! That castle is haunted since Morboses the old lord "+
        "died horribly fighting the king's wizards. Mark my words "+
        "people are going to die pretty soon there.\n");

    add_ask("castle", "The old grizzled man says with fear: It is "+
        "haunted! The Dark One has a hold of it, because the terrible "+
        "things Morboses did before he died.\n");


    add_ask("morboses", ask_morboses);

}                                                                      
