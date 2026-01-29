/*
   Coiney Miser, shopkeeper of the general store in Gelan, who
   lives up to his name. Special features include: putting items given
   to him in the storeroom, hiding money given to him, generally
   acting in a slimy way.
   He is also one of the npcs involved in the polymorph quest, although
   only briefly, he advises the player that a sapphire of power is probably
   available from the shopkeeper in Argos.

   Coder: Maniac

   Revised 5/9/95, 31/5/96 
*/



#pragma save_binary

inherit "/std/monster";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include "monster.h"
inherit STD_AIDED;
#include HAUNT_CODE
#include POLYMORPH_QUEST

#define ENV environment

object store;


void
create_monster() 
{
  if (!IS_CLONE)
    return;
  set_name("coiney");
  add_name("owner");
  add_name("shopkeeper");
  set_race_name("human");
  set_adj(({"beak-nosed","pale"}));
  set_title("Miser the Shopkeeper");
  set_long("Coiney Miser is a slightly shifty looking character " +
     "with a greedy twinkle in his eye and a large beaky nose. " +
     "He is also very pale and appears to be " +
     "in bad need of a holiday. Perhaps he spends all his spare moments " +
     "inside counting his money instead of going out in the sun.\n"); 
  default_config_npc(60);
  set_base_stat(SS_CON,75);
  set_hp(5000);
  set_skill(SS_UNARM_COMBAT, random(20) + 55);
  set_skill(SS_DEFENCE, random(10) + 60);
  set_skill(SS_AWARENESS, random(10) + 50);
  set_alignment(50 + random(100));
  set_gender(0);
  add_prop(NPC_M_NO_ACCEPT_GIVE,0);

  set_chat_time(12);
  add_chat("I wants t'be so rich they buries me in a gold coffin!");
  add_chat("Ello ello, what's we got 'ere then, customers or loiterers?");
  add_chat("I don't want ya love, deary. I want ya money!");
  add_chat("I prob'ly gots some nice stuff in stock, take a look!");
  add_chat("Business is a-bloomin' and a-boomin', mark my words!");

  set_cchat_time(12); 
  add_cchat("Bugger off, ya rascal! Nobody steals my 'ard earned money!");
  add_cchat("Guards! Guards! 'Elp me 'fore they chop me head off!");
  add_cchat("I've 'eard of a free market but this is takin' it too far!");
  add_cchat("Darn it, how'd the likes of you get into our nice town?");

  set_act_time(13);
  add_act("@@hand_rub");
  add_act("@@greedy");
  add_act("@@nose");
  add_act("@@coinsearch"); 

  add_ask(({"jewel", "sapphire", "sapphire of draining", 
            "magic jewel", "magic sapphire"}),
            VBFC_ME("reply"), 1);

  store = find_object(GELAN_ROOMS + "shopback");
}


/* Reply to enquiry about sapphire of draining. */
string
reply()
{
    object tp = this_player();

    if (!tp)
        return "";

    if (tp->test_bit(PQ_DOM, PQ_GROUP, PQ_BIT))
         return "ponder wastin' one's time, like.";

    if (present(CORPSE_NAME, tp))
        return ("say I sees that you has the polymorph's corpse on yer! " +
                "What the 'ell you want with another jewel, eh, deary?");

    if (tp->query_prop(LIVE_I_FOUGHT_CALIA_PQ_DEMON))
         return ("say I hasn't got a sapphire like that, they is pretty " +
                 "rare, but I knows a man whose got one.. maybe like.. " +
                 "Try askin' the shopkeeper in Argos!");

    return ("peer " + tp->query_real_name());
}


void
enter_inv(object obj, object from)
{
  ::enter_inv(obj,from);
  set_alarmv(2.0, 0.0, "react_give",({obj,from}));
}


int 
will_keep(object obj)
{
  if (obj->query_name() == "coin" || obj->query_name() == "coins")
    return 1;

  if (obj->query_prop(LIVE_I_IS) ||
      (!(obj->query_prop(OBJ_I_VALUE))) ||
      obj->query_prop(OBJ_M_NO_GIVE) ||
      obj->query_prop(OBJ_M_NO_SELL))
    {
      command("say hmm, this " + obj->short() + " is not my kind " +
              "of merchandise."); 
      return 0;
    }
  else
    return 1;
}



void 
store_away(object obj)
{

  command("say I think I'll store this " + obj->short() + " away!");

  obj->move(store);
  if (present(obj, store))  {
    tell_room(environment(this_object()), QCTNAME(this_object()) + " puts " +
              LANG_THESHORT(obj) + " in his store room.\n");
    command("grin");
  }
  else {
    tell_room(environment(this_object()), QCTNAME(this_object()) + " fails " +
             "to put " + LANG_THESHORT(obj) + " in his store room.\n");
    command("scratch"); 
  }
  
}


void 
react_give(object obj, object from)
{
  
  if (!living(from)) 
  {
     command("hmm");
     command("say I wonder where this "+obj->query_name()+
             " came from.");

    if (!will_keep(obj)) 
      command("drop "+obj->query_name());
    else if (obj->query_name() == "coin" || obj->query_name() == "coins") {
      command("say Ooh, money for nothing, thank you!");
      tell_room(environment(this_object()), QCTNAME(this_object()) + 
                " hides the money away in a secret place.\n");
      obj->remove_object();
      return;  
    }
    else store_away(obj);
 
  }
  else {
    if (!will_keep(obj)) {
      command("say You better keep that, "+from->query_nonmet_name()+".");
      command("give "+obj->query_name()+" to "+from->query_real_name());
      if (ENV(obj) == this_object()) 
        command("drop "+obj->query_name());
    }
    else if (obj->query_name() == "coin" || obj->query_name() == "coins") {
      command("say Ooh, money for nothing, thank you!");
      tell_room(environment(this_object()), QCTNAME(this_object()) + 
                " hides the money away in a secret place.\n");
      obj->remove_object();
      return;  
    } 
    else store_away(obj);
   }
}


void
hand_rub()
{
  tell_room(environment(this_object()),QCTNAME(this_object()) + 
             " rubs his hands together shiftily.\n");
}

greedy()
{
  tell_room(environment(this_object()), QCTNAME(this_object()) +
          " stares into space with a greedy twinkle in his eye.\n");
}

nose()
{
  tell_room(environment(this_object()), QCTNAME(this_object()) +
            " slowly strokes his long, beaky nose.\n");
}

coinsearch()
{
  tell_room(environment(this_object()), QCTNAME(this_object()) +
          " looks closely at the floor to see if anyone has dropped " +
          "any coins down there.\n"); 
}


void
emote_hook(string emote, object actor, string adverb)
{
    if ((emote == "bow") || (emote == "curtsey"))
        set_alarm(1.0, 0.0, &command("bow " + actor->query_real_name()));
}

