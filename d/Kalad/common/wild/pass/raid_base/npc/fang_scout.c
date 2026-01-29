#pragma strict_types
#pragma no_inherit

inherit "/d/Kalad/common/guilds/red_fang/obj/f_guard";

#include "../defs.h"
#include <stdproperties.h>
#include <ss_types.h>

public void reward_head(object ob, object from);
public void reject(object ob, object from);

public void
create_monster()
{
   ::create_monster();
   add_name("scout");
   set_adj( ({ "sinuous", "hunchbacked" }) );
   set_title("the Chief Scout of the Red Fang");
   set_name("grash");
   set_short(0);
   remove_prop(LIVE_M_NO_ACCEPT_GIVE);
   add_act("say We must defeat the cursed raiders!");
   add_act("say Damn the Thanar! They will not get in!");
   set_default_answer("The hunchbacked goblin snarls: My only concern is " +
     "those damn Thanars!\n");
   add_ask( ({ "thanar", "thanars", "raid", "raiders", "raider" }),
      "The hunchbacked goblin growls: Those stupid Thanars! They've set up " +
      "camp somewhere near here, thinking they can get into our beloved " +
      "caves! Some stupid Master Knight's lame brother is in charge. I'd " +
      "love to get my hands on his head!\n");
   add_ask(({"head", "brother"}), "The hunchbacked goblin hisses: His head! " +
      "Bring it to me!\n");
   add_leftover(RAID + "obj/fang_head", "head", 1, 0, 0, 1);
   set_skill(SS_AWARENESS, 100);
   set_skill(SS_HIDE, 50);
}

public void
add_introduced(string str)
{
   if(present(str, environment())->query_met(this_object()))
      return;

   command("introduce me");
}

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);

   if(!from)
      return;

   if(ob && ob->query_prop(RAID_HUMAN_LEFTOVER))
   {
      set_alarm(1.0, 0.0, &reward_head(ob, from));
      return;
   }

   if(ob->query_coin_type())
   {
      set_alarm(1.0, 0.0, &command("smile greed"));
      return;
   }

   set_alarm(1.0, 0.0, &reject(ob, from));
}

public void
reward_head(object ob, object from)
{
   object necklace;

   if(!present(from, environment()))
   {
      command("shrug");
      command("eat head");
      return;
   }

   if(present(RAID_HUMAN_REWARD, from))
   {
      command("snarl " + from->query_real_name());
      command("say Thanar scum! Die!!");
      command("kill " + from->query_real_name());
      command("eat head");
      return;
   }

   if(present(RAID_GOBLIN_REWARD, from))
   {
      command("say So he came back from the dead eh?? Well good on you " +
         "for fixing that little problem!");
      command("cackle");
      command("eat head");
      return;
   }

   command("laugh demon");
   command("say Excellent! Here... let me give you a little trinket to " +
      "remember him.");
   command("emote takes his dagger to the skull and cuts off a lock " +
      "of hair.");
   command("emote fetches a small chain from his pocket, braids the " +
      "hair and ties it to the chain.");

   necklace = clone_object(RAID + "obj/fang_necklace");
   necklace->remove_prop(OBJ_M_NO_DROP);
   necklace->move(this_object(), 1);

   command("give necklace to " + from->query_real_name());
   command("eat head");

   necklace->add_prop(OBJ_M_NO_DROP, 1);

   SCROLLING_LOG(LOG + "trinkets",
      capitalize(from->query_real_name()) + " received the Red Fang trinket"
   );
}

public void
reject(object ob, object from)
{
   command("say I don't want this!");
   command("drop " + ob->query_name());
}
