/*
   robert.c
   --------

   Coded ........: 95/05/05
   By ...........: Jeremiah

   Latest update : 95/06/04
   By ...........: Jeremiah


   This man is a prisoner in Pax Tharkas. He is the last part of the quest 
   to free the prisoners. It's possible to ask him questions about the 
   fortress. If his wife(Maritta.c), his child(girl.c) are present, and 
   the player gives him the map from the gully ghost, the player will be 
   rewarded with xp, and alignment+.

   20110705 : Lunatari : The add_ask that tells the player to ask him about it
                         was quite broken as it did not have "say ..."

   20181229 : Arman : Removed quest xp penalties and fixed up add_ask
                      issues initiating the quest.
*/
#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
inherit M_FILE

inherit "/std/act/domove"; /* allows man to move */
inherit "/std/act/action"; /* allows man to act  */
inherit "/d/Krynn/std/act/gift";


#define XP_VALUE 25000     /* max amount of xp given to player. */


#define I_FOUND_LADDER "_i_found_pax_ladder"  
#define I_FOUND_DOLL   "_i_found_pax_doll"
#define I_FOUND_KEY    "_i_found_pax_key"
#define I_FOUND_DIARY  "_i_found_pax_diary"
#define I_FOUND_MAP    "_i_found_pax_map"


string who_gave_me_map; /* 0(empty string) = no map so far.     */


void calculate_experience(object who);
void remove_quest_props(object who);
int got_doll(object what, object who);
int got_map(object map, object who);

void
create_krynn_monster()
{
   int i;

   set_name("robert");
   set_race_name("human");
   set_long("He is a tall human with auburn hair. He looks pale, " +
            "and thin. He is dressed in ragged clothes, hanging from " +
            "his shoulders. His clothes are covered with a thin " +
            "layer of red dust.\n"); 
   set_adj("tall");
   add_adj("pale");

   for (i = 0; i < 6; i++)
      set_base_stat(i,12 + random(10));

   set_all_attack_unarmed(10, 10);
   set_all_hitloc_unarmed(10);
   set_knight_prestige(-2);
   set_alignment(150);
   
   set_gender(G_MALE);

   set_default_answer("say Hmm, I don't think I know " +
                      "anything about that.", 1);

   add_ask(({"about child", "about children", "about daughter", "child",
               "children", "daughter"}), VBFC_ME("child_hint"), 1);

   add_ask(({"about wife", "about wives", "about women", "about spouse",
                "about spouses", "wife", "wives", "women", "spouse",
                "spouses"}), VBFC_ME("wife_hint"), 1);

   add_ask(({"about nursemaid", "about nurse", "nursemaid", "nurse"}),
           VBFC_ME("nurse_hint"), 1);
   add_ask(({"about dragon","about flamestrike","about Flamestrike",
               "dragon", "flamestrike", "Flamestrike"}), 
            VBFC_ME("dragon_hint"), 1);
   add_ask(({"about prison", " about prisons", "about prison cell", 
             "about prison cells", "about cell", "about cells",
             "prison", "prisons", "prison cell", "prison cells", "cell",
             "cells", "prisoner", "about prisoner"}),
           VBFC_ME("prison_hint"), 1);
   add_ask(({"about lord", "about Lord", "about highlord", "lord",
               "Lord", "highlord"}), VBFC_ME("lord_hint"), 1);
   add_ask(({"about escape", "escape", "quest", "task", "help"}), 
           VBFC_ME("escape_hint"), 1);
   add_ask(({ "follow me", "follow" }), VBFC_ME("follow"), 1);

   set_alarm(30.0,90.0,"give_hints");
   
   add_gift("pax_quest_doll", got_doll);
   add_gift("_quest_map_", got_map);
    
   add_prop(NPC_I_NO_RUN_AWAY,1);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   
   seteuid(getuid(TO));
}

void
give_hints()
{
   switch(random(4))
   {
      case 0 : command("say I hope my wife and child are ok.");
               command("sigh");
      break;  
      case 1 : command("emote grumbles unhappily.");
      break;
      case 2 : command("I wish I could somehow escape from here.");
      break;
      case 3 : command("emote smiles sadly.");
   }
}

string
child_hint()
{
   command("say The draconians are keeping our children in a room " +
           "somewhere in the fortress. They are clever, they know we " +
           "won't attempt anything while they have our children. That " +
           "is why they keep us separated. They have found a rather " +
           "strange nursemaid for our children.");

   return"";
}

string
wife_hint()
{
   command("say My wife, and the rest of the women, are being held " +
           "in some prison cells in the low part of the fortress. " + 
           "They are forced to make uniforms for the draconians."); 

   return"";
}

string
nurse_hint()
{
   command("say The nursemaid is an old dragon. I think her name is " +
           "Flamestrike. I think the children have become very fond " +
           "of her, or so it seems from what I have heard.");

   return "";
}

string
dragon_hint()
{
   command("say She's a poor old critter, more than half mad. I've " +
           "seen her once, when we were taken here. Her own " +
           "children were killed in some great war, and now she's " +
           "got it in her head, that our children is her children. " +
           "Actually she's as much a prisoner as we are.");

   return "";
}

string
prison_hint()
{
   command ("say The prisons where they keep my wife, and the other " +
            "women from my home area, are in the lower part of the " +
            "east tower. They are kept there almost all day. Only " +
            "allowed outside once a day. That's when we can catch a " +
            "glimpse of them some times.");

   return "";
}

string
lord_hint()
{
   command("say The dragon highlord Verminaard, has his headquarters in " +
           "this fortress. He is a black cleric, and the leader of the " +
           "red dragon army. He is a mean bastard, he knows no mercy.");

   return "";
}

string
escape_hint()
{
   command("say I would give my life to escape this place, but I can't " +
           "leave without my wife and child. I can't just leave them " +
           "here.");

   return "";
}

string
follow()
{
    if(P("maritta", E(TO)) && P("girl", E(TO)))
    {   
        command("say Well, We can't go back north, and we don't know " +
            "the area south of here, so a map of that area would " +
            "be quite helpful.");
        return"";
    }
    
    command("say I'm not going anywhere without both my wife and " +
        "daughter.");    
    return "";
}


int
got_doll(object what, object from)
{
    command("smile " + OB_NAME(from));
    command("say Where did you find this? It looks exactly like " +
        "my daughters doll.");
    
    if (what->query_blood_stains())
    {
        command("frown");
        command("say hmmm... I don't think she will like those " +
            "blood stains though.");
    }
    else
    {
        command("say She will be very happy to get it back.");
    }
    
    command("give " + OB_NAME(what) + " to " + OB_NAME(from));
    return 1;
}

int
got_map(object map, object who)
{
    object wife, girl;
    
    wife = P("maritta", E(TO));
    girl = P("girl", E(TO));
    
    if ((wife) && (girl))
    {
        command("emote takes a close look at the map.");
        command("say thank you, this could come in very handy.");
        command("ask maritta something");
        
        if (wife->compare_i_follow(who->query_real_name()))
        {
            command("smile maritta");
            command("shake " + who->query_real_name());
            command("say With this, we can get out of here, finally.");
            command("say I don't know how we can thank you enough.");
            calculate_experience(who);
            remove_quest_props(who);
            girl->the_end();
            wife->the_end();
            command("emote leaves.");
            remove_object();
        }
        else
        {
            command("nod maritta");
            command("say I'm sorry, I can't accept this from you.");
            command("say It is a matter of trust, you will understand.");
            command("shrug");
            command("give " + OB_NAME(map) + " to " + OB_NAME(who));
        }
   }
   else
   {
       command("emote looks at the map.");
       command("say I could use this map if I was to escape from here.");
       command("say But I will not leave here without both my wife and " +
           "daughter.");
       command("say Maybe you can find them both, and bring them here ?");
       command("give " + OB_NAME(map) +" to " + OB_NAME(who));
   }
    return 1;
}

void
drop_unknown(object ob, object from)
{
    command("smile . " + OB_NAME(from));
    command("say I don't think I can use this.");
    command("give " + OB_NAME(ob) + " to " + OB_NAME(from));
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    recieve_gift(ob, from);
}


/* ********************************************** */
/* *                                            * */
/* ********* XP calculation function ************ */
/* *                                            * */
/* ********************************************** */

void
calculate_experience(object who)
{
   int xp_base = 25000;

   if(who->test_bit("krynn", 2, 3))
   {
      who->catch_msg("There is no experience second time you " +
                     "solve this quest.\n");
      return;
   }

   /* Mali for missing parts of the quest */

   /*
   xp_base -= (who->query_prop(I_FOUND_LADDER) ? 0 : 2000);
   xp_base -= (who->query_prop(I_FOUND_DOLL)   ? 0 : 2500);
   xp_base -= (who->query_prop(I_FOUND_KEY)    ? 0 : 2500);
   xp_base -= (who->query_prop(I_FOUND_DIARY)  ? 0 : 2000);
   xp_base -= (who->query_prop(I_FOUND_MAP)    ? 0 : 2200);
   */

   /*
   xp_base += (2000 * (who->query_prop(I_FOUND_LADDER) - 1));
   xp_base += (2000 * (who->query_prop(I_FOUND_DOLL) - 1));
   xp_base += (2000 * (who->query_prop(I_FOUND_KEY) - 1));
   xp_base += (2000 * (who->query_prop(I_FOUND_DIARY) - 1));
   xp_base += (2000 * (who->query_prop(I_FOUND_MAP) - 1));
   */

   /*
   if (who->query_average_stat() < 50)   
       xp_base -= (50 - who->query_average_stat()) * 250;
   */
   
   who->catch_msg("You feel more experienced.\n");
   tell_room(E(who), QCTNAME(who) + " looks more experienced.\n", who);

   
   who->add_exp_quest(xp_base);
   who->set_bit(2, 3);                               

   K_QUEST_LOG("quest", "Prisoner quest", who, xp_base);
}


void
remove_quest_props(object who)
{
   if(who->query_prop(I_FOUND_LADDER))
      who->remove_prop(I_FOUND_LADDER);

   if(who->query_prop(I_FOUND_DOLL))
      who->remove_prop(I_FOUND_DOLL);

   if(who->query_prop(I_FOUND_KEY))
      who->remove_prop(I_FOUND_KEY);

   if(who->query_prop(I_FOUND_DIARY))
      who->remove_prop(I_FOUND_DIARY);

   if(who->query_prop(I_FOUND_MAP))
       who->remove_prop(I_FOUND_MAP);
}

