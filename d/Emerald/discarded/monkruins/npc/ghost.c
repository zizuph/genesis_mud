inherit "/std/monster";

#include "default.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

void start_action(object ob);
void point_clue(mixed args);
void start_reward(object ob);
void give_reward(mixed args);
void reward_player(object ob);

void
create_monster()
{
   set_name("figure");
   set_living_name("_mylos_figure_");
   set_adj("flickering");
   set_race_name("human");
   set_short("flickering figure");
   set_long(break_string("This flickering figure is a wraith of "+
         "it's former living self. It appears in the clothes it was "+
         "wearing when it died, a monk's habit.\n",76));
   
   set_base_stat(SS_STR, 30);
   set_base_stat(SS_DEX, 23);
   set_base_stat(SS_CON, 29);
   set_base_stat(SS_INT, 9);
   set_base_stat(SS_WIS, 8);
   set_base_stat(SS_DIS, 30);
   
   set_skill(SS_DEFENCE, 25);
   set_skill(SS_PARRY, 22);
   set_skill(SS_UNARM_COMBAT, 30);
   set_skill(SS_ELEMENT_LIFE, 40);
   set_skill(SS_AWARENESS, 45);
   
   heal_hp(1000);
   
   add_prop(OBJ_M_NO_ATTACK, 1);
   add_prop(OBJ_I_WEIGHT, 14000);
   add_prop(CONT_I_MAX_WEIGHT, 120000);
   add_prop(OBJ_I_VOLUME, 89000);
   add_prop(CONT_I_MAX_VOLUME, 100000);
   add_prop(OBJ_S_WIZINFO, "/dThis is the quest ghost, the being which "+
      "the player needs to find the body for.\n");
   
   set_act_time(10);                    /* Set action interval           */
   add_act("smile"); 
   add_act("ponder");
}

void
start_action(object ob)
{
   if(ob)
      if(objectp(ob))
      if(present(ob, environment(this_object())))
      call_out("point_clue", 4, ({ ob, 1 }) );
}

void
point_clue(mixed args)
{
   object ob;
   int time;
   
   if (sizeof(args) != 2)
      return;
   ob = args[0];
   time = args[1];
   if (!ob || !present(ob, environment(this_object())))
      return;
   
   switch(time)
   {
      case 1:
      tell_room(ENV(ob), "The figure points at the boulder.\n");
      break;
      
      case 2:
      tell_room(ENV(ob), "The figure sighs.\n");
      break;
      
      case 3:
      tell_room(ENV(ob), "The figure stares at the floor.\n");
      break;
      
      case 4:
      tell_room(ENV(ob), "The flickering figure fades from view.\n");
      remove_object();
      break;
      
      default:
      return;
   }
   call_out("point_clue", 4, ({ ob, time+1}) );
}

void
start_reward(object ob)
{
   if(ob)
      if(objectp(ob))
      if(present(ob, environment(this_object())))
      call_out("give_reward", 4, ({ ob, 1 }));
}

void
give_reward(mixed args)
{
   object ob, clasp;
   int time;
   
   setuid();
   seteuid(getuid());

   clasp = clone_object("/d/Emerald/mylos/ruins/clasp");

   if (sizeof(args) != 2)
      return;
   ob = args[0];
   time = args[1];
   if (!ob || !present(ob, environment(this_object())))
      return;
   
   switch(time)
   {
      case 1:
      ob->catch_msg("The figure smiles at you.\n");
      tell_room(ENV(ob), "The figure smiles at "+QTNAME(this_player()) +
         ".\n", TP);
      break;
      
      case 2:
      ob->catch_msg("The figure begins to fade into smoke.\n");
      break;
      
      case 3:
      ob->catch_msg("Tendrils of smoke weave around you.\n");
      tell_room(ENV(ob), "Tendrils of smoke weave around "+
         QTNAME(this_player())+".\n", TP);
      reward_player(ob);
      break;
      
      case 4:
      ob->catch_msg("The smoke is sucked into the coffin, and the "+
         "lid slams shut.\n");
      tell_room(ENV(ob), "The smoke is sucked into the coffin and the "+
	"lid slams shut.\n", TP);
      clasp->move(TO);
      tell_room(ENV(ob), "Something falls to the floor.\n");
      remove_object();
      break;
      
      default:
      return;
   }
   call_out("give_reward", 4, ({ ob, time+1}) );
}

void
reward_player(object ob)
{
   int level, xp, cnt;
   
   if (ob) 
      if(present(ob, environment(this_object())))
      {
      if(!ob->test_bit(DOMAIN_NAME, 0, 8))
         {
         seteuid(getuid());
         ob->set_bit(0, 8);
         xp = XP_MONK_QUEST;
         ob->add_exp(xp, 0);
         WRITE_LOG(QUEST_FILE, ob, "completed the Monk Quest.");
         ob->catch_msg("You feel more experienced.\n");
         }
   }
}
