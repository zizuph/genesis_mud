
/* 
 *   The mermaid for the sea mermaid quest
 *
 *   Coded by Amelia
 *   1/7/95
 *   Modifications by Maniac 5/9/96, 12/9/96
 *   Added acceptance of oyster shells for Thalassian Staff Quest, 
 *      Jaacar, 5/09/03
 *   ? Last update 2003/09/09 
 *   Fixed typos, Lavellan, 2010/09/01 
 */

inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <composite.h>
#include <formulas.h>
#include <cmdparse.h>
#include <language.h>
#include "defs.h"
#include SEA_QUESTS

public string
frame_answer()
{
    command("emote says: If you would bring me a shell of some sort from "+
        "the sea, I could make you a frame.");
    return "";
}

void
create_monster()
{
   set_name("callae");
   set_race_name("mermaid"); 
   set_gender(G_FEMALE);
   set_short("lovely golden-haired mermaid");
   set_adj(({"lovely", "graceful", "golden-haired"}));
   set_long("You are looking at a lovely, golden-haired mermaid. "+
      "Her hair is very long, and flows gracefully around her. She "+
      "has blue-green eyes, like the sea of Calia. From the "+
      "waist up her form is that of a lovely, curvaceous maiden. "+
      "However, below her waist, her body becomes a silver "+
      "and gold fish tail. She is very natural, and is wearing "+
      "nothing except a necklace made of pearls and seashells.\n");

   add_item((({"form", "body", "breasts"})),
      "She has a beautifully shaped body ... from the waist "+
      "up. Her breasts are round and firm, and her skin is a "+
      "lovely golden tan colour. She is athletic looking. "+
      "From the waist down, however... there is a golden and "+
      "silvery fish tail.\n");

   set_default_answer("She smiles at you, uncomprehending.\n");
   set_act_time(3);
   add_act("emote gives you a dazzling smile.");
   add_act("emote sings a beautiful, haunting melody.");
   add_act("emote twists a lock of golden hair in her fingers.");
   add_act("emote looks at you curiously.");
   add_act("emote says: I would love to make a beautiful frame. "+
        "Would you bring me some sea shells?");
   add_act("emote tosses her hair back over one shoulder.");
   add_act("emote shyly waves at you with her silvery tail.");
   add_act("emote combs her long hair.");
   add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
   add_prop(NPC_I_NO_LOOKS, 1); 

   add_prop(OBJ_M_NO_ATTACK, "@@no_attack");
   set_default_answer(VBFC_ME("default_answer"));
   add_ask(({"frame","shell","seashell"}),&frame_answer());

   add_item((({"necklace", "seashell necklace"})),
      "The necklace is made from seashells and pearls "+
      "strung together.\n");

   add_item((({"comb", "mother-of-pearl comb"})), 
      "The comb is made from an abalone shell and is pink and blue.\n");
   set_stats(({225, 250, 180, 100, 100, 150}));
   set_skill(SS_SWIM, 100); 
}

public string
default_answer()
{
    command("smile");
    return "";
}

void
drop_stuff(object ob)
{
     if (!objectp(ob))
         return;

     command("emote looks curiously at " + LANG_THESHORT(ob) + "."); 
     command("shrug");
     command("drop " + OB_NAME(ob));
}



void
accept_pearl(object tp, object pearl)
{
   string name;

   name = tp->query_real_name();
   command("smile " + name);
   command("kiss " + name);
   command("emote sets the pearl into her necklace.");

   if (tp->test_bit(MERMQ_DOMAIN, MERMQ_GROUP, MERMQ_BIT)) {
        tp->catch_msg("You have already solved this quest!\n");
        return;
   }

   if (tp->query_prop(PLAYER_I_MERMQ_FOUND_PEARL)) {
        tp->set_bit(MERMQ_GROUP, MERMQ_BIT);
        tp->add_exp(MERMQ_XP);
        tp->catch_msg("You feel more experienced!\n");
        tp->command("save");
        log_file("mermaid_quest", tp->query_real_name() +
                " " + ctime(time())+".\n");
        command("whisper to "+name+" Thank you "+
              "for this lovely gift! I shall reward you with the "+
              "secret of breath. You now need not fear water as "+
              "you can now breathe it almost as you do air. Be warned "+
              "though that only the waters of this land are safer "+
                "for you to breathe, however you can still drown! Now go "+
                "forth and seek the treasures "+
              "of the sea!");
        tp->remove_prop(PLAYER_I_MERMQ_FOUND_PEARL); 
        environment(this_object())->ring_restore(tp); 
        return;
   }

   command("whisper to " + name + " I don't think you were the " + 
           "one who found this pearl!"); 
   command("giggle"); 
}

void
accept_shell(object tp, object pearl)
{
   string name;
   object frame;

   frame=clone_object(SEA_OBJECTS+"seashell_frame");
   frame->move(TO);

   name = tp->query_real_name();
   command("smile " + name);
   command("kiss " + name);
   command("emote says: Yes, this is exactly what I need.");
   command("emote crushes the oyster shell up into little pieces with "+
        "her powerful hands.");
   command("emote places the broken pieces of shell onto some pieces "+
        "of wood she had hidden somewhere.");
   command("emote glues everything together and looks at the finished "+
        "creation.");
   command("emote says: It is very beautiful. You may have it, I can "+
        "always make more.");

   command("give frame to "+name);
}

void
do_smile()
{
    command("smile");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from); 

    if (ob->id(MERMQ_PEARL_ID))  
        set_alarm(1.0, 0.0, &accept_pearl(from, ob));
    else if (ob->id("oyster shell"))  
        set_alarm(1.0, 0.0, &accept_shell(from, ob));
    else if (ob->id("_seashell_frame_"))
        set_alarm(1.0, 0.0, &do_smile());
    else 
        set_alarm(1.0, 0.0, &drop_stuff(ob));
}


void
fall_back(object tp)
{
   tp->catch_msg("Splash!\n");
   tp->move_living("M", ROCK_ROOM, 1);
   tell_room(environment(tp), QCTNAME(tp) + " splashes in!\n", tp);
}


string
no_attack()
{
   object tp = this_player();

   tp->catch_msg("The mermaid slaps you with her tail! You fall off " +
                 "the rock!\n");
   tell_room(environment(tp), "The mermaid slaps " + QTNAME(tp) + 
      " with her tail! " + capitalize(tp->query_pronoun()) + 
      " falls off the rock!\n", tp);
   fall_back(tp); 
   return "";
}


void
huggle(object actor)
{
   command("hug " + OB_NAME(actor));
   command("snuggle " + OB_NAME(actor));
}

void
emote_hook(string emote, object actor)
{
    if (emote == "hug") 
        set_alarm(1.0, 0.0, &huggle(actor)); 
}

