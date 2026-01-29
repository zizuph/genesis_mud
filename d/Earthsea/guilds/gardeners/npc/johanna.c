#pragma strict_types
#pragma no_inherit

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/intro";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Earthsea/quest_handler/quest_handler.h"
#include "../defs.h"

#define DOING_TASK "_doing_earthsea_garden_task"
#define TASKS ({ "pindan_task" })
#define TASK_MAP ([ \
   "pindan_task" :\
       "I am looking for a moss that will help me find my way around." + \
       " There is but one place where it may be found." + \
       " Beneath the ground where terrible drums sound" + \
       " lies the smell I seek - grab it!", \
])
#define TASK_THANK ([ \
   "pindan_task" : "Thank you! Now I can find my way around better.", \
])

public int
query_done_all_tasks(object tp)
{
   int i, sz = sizeof(TASKS);
   string task;

   for(i = 0; i < sz; i++)
   {
      task = TASKS[i];

      if(!QH_QUERY_QUEST_COMPLETED(tp, task))
      {
         return 0;
      }
   }

   return 1;
}

private string
answer_questions()
{
   object tp = this_player();
   int i, sz = sizeof(TASKS);
   string task;

   for(i = 0; i < sz; i++)
   {
      task = TASKS[i];

      if(!QH_QUERY_QUEST_COMPLETED(tp, task))
      {
         tp->add_prop(DOING_TASK, task);
         command("$say " + TASK_MAP[task]);
         return "";
      }
   }

   if(tp->query_guild_name_lay() != GARDENER_NAME && 
      tp->query_guild_name_craft() != GARDENER_NAME)
   {
      command("$say You seem to be a good gardener!");
      command("$say I don't happen to need anything at the moment, " +
         "but perhaps you might consider joining the Gardening guild?");
      command("$smile happily");
      return "";
   }

   command("$say Good day, fellow gardener!");
   command("$say I don't have anything for you at the moment, but " +
      "I am glad to see that all is well.");
   command("$shrug happily");

   return "";
}

public string
answer_guild()
{
   object tp = this_player();
   int i, sz = sizeof(TASKS);
   string task;

   for(i = 0; i < sz; i++)
   {
      task = TASKS[i];

      if(!QH_QUERY_QUEST_COMPLETED(tp, task))
      {
         tp->add_prop(DOING_TASK, task);
         command("$say " + TASK_MAP[task]);
         return "";
      }
   }

   if(tp->query_guild_name_lay() == GARDENER_NAME ||
      tp->query_guild_name_craft() == GARDENER_NAME)
   {
      command("$say Hello, gardener!");
      command("$say I don't really have anything to tell you about " +
         "the guild that you cannot learn yourself.");
      command("$say Of course if you want to 'leave the guild', you " +
         "may do that here any time.");
      command("$say Good luck, and good gardening!");
      command("$twinkle");
      return "";
   }

   command("$say Perhaps you are interested in joining the " +
      "Gardeners of Gont?");
   command("$say We are a simple guild, interested purely in the " +
      "pursuit of happiness through good gardening.");
   command("$say If you'd be so kind as to run a few errands, I'd " +
      "be more than happy to help you 'join the guild'.");
   command("$smile kindly");
   return "";
}

public void
create_earthsea_monster()
{
   set_name("johanna");
   set_living_name("_gardener_guild_master_");
   set_adj(({"dirty", "lithe"}));
   set_race_name("human");
   set_gender(G_FEMALE);
   default_config_npc(50);
   set_title("the Famed Gardener of Gont");
   remove_prop(NPC_M_NO_ACCEPT_GIVE);
   add_prop(OBJ_M_NO_ATTACK, "You cannot bring yourself to hurt " +
      "someone who might be so helpful.\n");
   add_prop(OBJ_M_NO_MAGIC_ATTACK, "You cannot bring yourself to hurt " +
      "someone who might be so helpful.\n");
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   set_default_answer(&answer_questions());
   add_ask(({"guild", "gardeners", "gardeners guild", "about guild",
      "about the guild", "about gardeners guild", "gardening guild",
      "about the gardeners guild", "about the gardening guild",
      "gardeners of gont", "about the gardeners of gont",
      "about gardeners of gont"}),
      "@@answer_guild");
   set_act_time(40);
   set_chat_time(60);
   add_act("emote carefully picks dirt from a small garden trowl.");
   add_act("emote thumbs through a small leather book she carries.");
   add_act("emote blinks, turns her head and quickly writes " +
      "something on a scroll she is carrying.");
   add_act("smile kindly");
   add_chat("I am looking for a few good gardeners!");
   add_chat("Maybe you can help me find a few things?");
   add_chat("There are plants out there that even I cannot manage " +
      "to grow.");
}

public void
reward_pindan(object player)
{
    command("$say " + TASK_THANK["pindan_task"]);
    player->catch_tell("You feel a little more experienced.\n");
}

public void
enter_inv(object ob, object from)
{
   string task;

   ::enter_inv(ob, from);

   if(interactive(from) && (task = from->query_prop(DOING_TASK)) &&
      !QH_QUERY_QUEST_COMPLETED(from, task))
   {
      if(task == "pindan_task" &&
         ob->query_herb_name() == "pindan")
      {
         // making sure pindan is a registered herb
         GARDENER_HERBS->add_herb(ob);

         QH_QUEST_COMPLETED(from, task);
         set_alarm(0.0, 0.0, &ob->remove_object());
         set_alarm(1.0, 0.0, &reward_pindan(from));
         return;
      }
   }

   command("$say I don't want that!");
   set_alarm(1.0, 0.0, &command("$emote drops the " + ob->short() + "."));
   ob->move(environment(this_object()), 1);
}
