/*
 * This is prisoner used in CAVE_DIR
 * 
 * Made by Milan
 * 
 */

inherit "/std/monster";
#include "/d/Rhovanion/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <filter_funs.h>

#define GROUP               0

#define BIT_SOLVED_ARMOUR   5
#define REWARD_ARMOUR       5000

#define BIT_SOLVED_FRIEND   6
#define REWARD_FRIEND       10000

#define BIT_SOLVED_FOOD     7
#define BIT_SOLVED_DRINK    8
#define REWARD_FOOD_DRINK   500

#define BIT_SOLVED          9
#define REWARD              25000

string *list_introduced = ({ }),
       *list_asked_help = ({ }),
       *list_nodded = ({ }),
        leader;
int filip_has_sword = 0,
    filip_has_armour = 0,
    no_of_pushes = 0;
object ob_leader;

create_monster()
{
   seteuid(getuid());

    set_name("cerindel");
    set_pname("elves");
    set_race_name("elf"); 
    set_living_name("_misty_prisoner_");
    set_adj("starved");
    add_adj("skinny");
    set_title("Experienced Traveller");
    add_prop(CONT_I_WEIGHT,48000);   /* 48 Kg */
    add_prop(CONT_I_HEIGHT,123);      /* 123 cm */

    set_stats(({ 55, 50, 65, 45, 40, 44}));
    refresh_mobile(); /* full hp, mana, fatigue */

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_skill(SS_AWARENESS, 100);

    set_alignment(500);

    set_act_time(5); 
    add_act("say Please, help me out of here."); 
    add_act("say I am starving to death!"); 
    add_act("say Goblins took all my equipment."); 
    add_act("say I hate these goblins!!!");
    add_act("say Goblin lord imprisoned us..."); 


    add_ask("help", VBFC_ME("answer_help"));
}

query_knight_prestige(){return -200;}

void add_introduced(string who)
{
  who = lower_case(who);
    if(member_array(who, list_introduced) == -1)
      list_introduced += ({ who });
  set_alarm(2.0, 0.0, "return_introduce");
}

void
return_introduce() {
 object *in_room;
 int i, met_me;
  in_room=FILTER_LIVE(all_inventory(environment()));
  met_me=1;
  for (i=0; (i < sizeof(in_room)) && met_me; i++)
    if (!in_room[i]->query_met(TO->query_real_name())) met_me=0;
  if (!met_me) {
     command("introduce me");
     command("bow");
  }
  return;
}

string
answer_help()
{
  string who_ask = TP->query_real_name();

  if(TP->test_bit("Rhovanion",GROUP,BIT_SOLVED))
  {
    command("whisper "+who_ask+" Please, let the others do the quest now.");
    command("pat "+who_ask);
    return "";
  }
  if(member_array(who_ask, list_introduced) == -1)
  {
    command("say Please introduce yourself first... I can't trust everyone.");
    return "";
  }
  if(member_array(who_ask, list_asked_help) != -1)
  {
    command("say "+capitalize(who_ask)+", are you deaf??? I have already "+
            "told you!!!");
    command("pat "+who_ask);
    return "";
  }
  if(leader)
  {
    command("whisper "+who_ask+" Thank you for your concern but now "+
            "I don't need anything.");
    command("whisper "+who_ask+" Maybe later.");
    command("smile "+who_ask);
    return "";
  }
  list_asked_help += ({ who_ask }); /* now he has asked first time */
  command("whisper "+who_ask+" I have been captured by these cursed goblins.");
  command("whisper "+who_ask+" I have tried to escape from here "+
          "but they caught me again.");
  command("whisper "+who_ask+" Next time it may be my death... ");
  command("whisper "+who_ask+" But I won't give up! Maybe you can "+
          "lead me out.");
  command("whisper "+who_ask+" Will you try it? Please!");
  command("peer "+who_ask);
  return "";
}

void emote_hook(string emote, object actor, string adverb)
{
  string who;
  if(emote != "nod") return;
  who = actor->query_real_name();
  if(member_array(who, list_asked_help) != -1)
  {
     if(leader && (leader != who))
     {
        call_out("command", 1,
           "whisper "+who+" Thank you but I already have another leader.");
       return;
     }
     if(member_array(who, list_nodded) != -1)
     {
       call_out("command", 1,
              "ask "+who+" Why are you nodding at me again?");
       call_out("command", 2,
              "whisper "+who+" I have already told you everything!");
       call_out("command", 3,
              "whisper "+who+" I won't repeat it! Someone may overheard us.");
       call_out("command", 4,
              "emote looks suspisiously around.");
       return;
     }
     list_nodded += ({ who }); /* now he agreed to help Cerindel */

     if(TP->test_bit("Rhovanion",GROUP,BIT_SOLVED_FRIEND))
     {
       leader = who;
       ob_leader = present(find_player(leader), environment());

       monster_act = ({ });  /* shut Cerindel up */
       /*********************************************************************/
       /***  Triggers for following leader around caves    ******************/
       /*********************************************************************/
       TO->trig_new("'"+capitalize(leader)+"' 'opens' 'the' 'door' 'and' "+
                    "'disapear' 'inside.' %s", "push_door");
       TO->trig_new("'Ooops!!!' 'Sudenly' 'you' 'realize' 'that' '"+
                    capitalize(leader)+"' 'isn't' 'here!\n'", "pull_door");
       TO->trig_new("'"+capitalize(leader)+"' %w 'the' 'wall' 'revealing' "+
                    "'small' 'opening.\n'", "push_pull_wall");
       TO->trig_new("'"+capitalize(leader)+"' %s 'Cerindel' 'do' %s", "try_to_do_s");
       TO->trig_new("'"+capitalize(leader)+"' %s", "try_to_follow");
       /*********************************************************************/
       call_out("command", 2, "ponder");
       call_out("command", 4, "think");
       call_out("command", 5, "peer "+who);
       call_out("command", 6,
                "whisper "+who+" O.K. You will be again my leader.");
       call_out("command", 7,
                "whisper "+who+" This time you must do better than you did.");
       call_out("command", 8,"pat "+who);
       call_out("command", 9,
                "whisper "+who+" I will again follow you wherever you go.");
       call_out("command", 10, "whisper "+who+
                " When you lose me, please find me as soon as possible.");
       call_out("command", 11,
                "whisper "+who+" Otherwise goblins may capture me again.");
       call_out("command", 12,
                "whisper "+who+" Moreover if you tell me 'Cerindel do ...' "+
                "then I will try to do it!");
       call_out("capture_prisoner", 2000);
       return;
     }

     call_out("command", 1, "whisper "+who+" Thank you!");
     call_out("command", 2, "whisper "+who+" But I want you to find out "+
              "what is with my friend first.");
     call_out("command", 3, "whisper "+who+" We were captured together...");
     call_out("command", 4, "whisper "+who+" and I haven't seen him since.");
     call_out("command", 5, "sigh");
     call_out("command", 6, "whisper "+who+" When you do this for me, I "+
              "will trust you in everything!");
     return;
  }
  call_out("command", 1, "ask "+who+" Why are you nodding at me?");
  call_out("command", 2, "peer "+who);
  return;
}

void
enter_inv(object what, object from)
{
   ::enter_inv(what, from);

   if (!from) /* Perhaps it was cloned and moved to me... */
      return;

   call_out("react_gift", 2, ({ from, what }));
}

void
react_gift(object *foo)
{
  object from,what;
  string what_thing, from_who, *adjs;

  from = foo[0];
  what = foo[1];

  adjs = what->query_adjs();
  if (!adjs) adjs = ({ });
  what_thing = implode(adjs + ({what->query_name()}), " ");
  from_who = from->query_real_name();

  if((member_array(from_who, list_nodded) != -1) &&
     (what->query_key() == "_rusty_gcaves_quest_key_"))
  {
    if(from_who == leader)
    {
      command("whisper "+from_who+" You didn't have to do this again!");
      command("pat "+from_who);
      return;
    }
    call_out("command", 2,
         "whisper "+from_who+" Yes! I know this key. My friend had it.");
    call_out("command", 3,
         "ask "+from_who+" Where did you find it? In a pot with soup?");
    call_out("command", 4,
         "whisper "+from_who+" I am afraid we can't help my friend anymore.");
    call_out("command", 5, "sigh");
    call_out("command", 6, "whisper "+from_who+" This is only one more "+
         "reason for me to try escape from here!");

    /****************************************/
    /*   HERE I REWARD FOR SOLVING FRIEND   */
    /****************************************/
    if(from->test_bit("Rhovanion", GROUP, BIT_SOLVED_FRIEND) == 0)
    {
      from->set_bit(GROUP, BIT_SOLVED_FRIEND);
      from->add_exp(REWARD_FRIEND, 0);
      from->catch_msg("\nYou feel more experienced.\n\n");
      write_file("/d/Rhovanion/log/goblin_prisoner", from->query_name() +
                " got " + REWARD_FRIEND + " exp. " + ctime(time()) + 
                "  FRIEND PART.\n");
      from->save_me(1);
    }

    leader = from_who;
    ob_leader = from;

    monster_act = ({ });  /* shut Cerindel up */
    /*********************************************************************/
    /***  Triggers for following leader around caves    ******************/
    /*********************************************************************/
    TO->trig_new("'"+capitalize(leader)+"' 'opens' 'the' 'door' 'and' "+
                 "'disapear' 'inside.' %s", "push_door");
    TO->trig_new("'Ooops!!!' 'Sudenly' 'you' 'realize' 'that' '"+
                 capitalize(leader)+"' 'isn't' 'here!\n'", "pull_door");
    TO->trig_new("'"+capitalize(leader)+"' %w 'the' 'wall' 'revealing' "+
                 "'secret' 'door' %s", "push_pull_wall");
    TO->trig_new("'"+capitalize(leader)+"' %s 'Cerindel' 'do' %s", "try_to_do_s");
    TO->trig_new("'"+capitalize(leader)+"' %s", "try_to_follow");
    /*********************************************************************/
    call_out("command", 8,
             "whisper "+from_who+" Now you will be my leader.");
    call_out("command", 9,
             "whisper "+from_who+" I will try to follow you wherever you go.");
    call_out("command", 10, "whisper "+from_who+
             " When you lose me, please find me as soon as possible.");
    call_out("command", 11,
             "whisper "+from_who+" Otherwise goblins may capture me again.");
    call_out("command", 12,
             "whisper "+from_who+" Moreover if you tell me 'Cerindel do ...' "+
             "then I will try to do it!");
    call_out("capture_prisoner", 2000);
    return;
  }

  if(from_who != leader)
  {
    call_out("give_back",2,({what_thing,from_who}));
    call_out("command",4,"say I accept things only from people I can trust.");
    return;
  }

  if(function_exists("create_food",what))
  {
    command("say Thank you! I am really starving.");
    command("eat "+what->query_names()[0]);
    /****************************************/
    /*   HERE I REWARD FOR GIVING FOOD      */
    /****************************************/
    if(from->test_bit("Rhovanion",GROUP,BIT_SOLVED_FOOD) == 0)
    {
      from->set_bit(GROUP,BIT_SOLVED_FOOD);
      from->add_exp(REWARD_FOOD_DRINK,0);
      from->catch_msg("You have nice feeling after helping him.\n");
      write_file("/d/Rhovanion/log/goblin_prisoner", from->query_name() +
                " got   " + REWARD_FOOD_DRINK + " exp. " + ctime(time()) + 
                "  FOOD PART.\n");
      from->save_me(1);
    }
    return;
  }
  if(function_exists("create_drink",what))
  {
    command("say I don't remember when I had my last drink.");
    command("drink "+what->query_names()[0]);
    /****************************************/
    /*   HERE I REWARD FOR GIVING DRINK     */
    /****************************************/
    if(from->test_bit("Rhovanion",GROUP,BIT_SOLVED_DRINK) == 0)
    {
      from->set_bit(GROUP,BIT_SOLVED_DRINK);
      from->add_exp(REWARD_FOOD_DRINK,0);
      from->catch_msg("You have nice feeling after helping him.\n");
      write_file("/d/Rhovanion/log/goblin_prisoner", from->query_name() +
                " got   " + REWARD_FOOD_DRINK + " exp. " + ctime(time()) + 
                "  DRINK PART.\n");
      from->save_me(1);
    }
    return;
  }
  if((function_exists("create_object",what)=="/std/weapon") &&
     (member_array("_filip_sword_", what->query_names()) != -1))
  {
    set_skill(SS_WEP_SWORD, 53);
    set_skill(SS_PARRY, 47);
    command("say Yes!!!  This is my sword!");
    command("wield "+what_thing);
    command("emote swings "+what_thing+" in his hand.");
    what->add_prop(OBJ_M_NO_DROP, 1);
    filip_has_sword = 1;
    /*********************************************/
    /*   HERE I REWARD FOR RETURNING ARMOUR      */
    /*********************************************/
    if((from->test_bit("Rhovanion",GROUP,BIT_SOLVED_ARMOUR) == 0) &&
       ((filip_has_sword+filip_has_armour) == 2))
    {
      from->set_bit(GROUP,BIT_SOLVED_ARMOUR);
      from->add_exp(REWARD_ARMOUR,0);
      from->catch_msg("You feel more experienced.\n");
      write_file("/d/Rhovanion/log/goblin_prisoner", from->query_name() +
                " got  " + REWARD_ARMOUR + " exp. " + ctime(time()) + 
                "  ARMOUR PART.\n");
      from->save_me(1);
    }
    return;
  }
  if((function_exists("create_object",what)=="/std/armour") &&
     (member_array("_filip_armour_", what->query_names()) != -1))
  {
    set_skill(SS_DEFENCE, 75);
    command("say Yes!!!  This is my cloak!");
    command("wear "+what_thing);
    what->add_prop(OBJ_M_NO_DROP, 1);
    filip_has_armour = 1;
    /************************************************/
    /*   OR HERE I REWARD FOR RETURNING ARMOUR      */
    /************************************************/
    if((from->test_bit("Rhovanion",GROUP,BIT_SOLVED_ARMOUR) == 0) &&
       ((filip_has_sword+filip_has_armour) == 2))
    {
      from->set_bit(GROUP,BIT_SOLVED_ARMOUR);
      from->add_exp(REWARD_ARMOUR,0);
      from->catch_msg("You feel more experienced.\n");
      write_file("/d/Rhovanion/log/goblin_prisoner", from->query_name() +
                " got  " + REWARD_ARMOUR + " exp. " + ctime(time()) + 
                "  ARMOUR PART.\n");
      from->save_me(1);
    }
    return;
  }
}

void
give_back(string *foo)
{
  if(!command("give "+foo[0]+" to "+foo[1]))
     command("drop "+foo[0]);
  return;
}

string
try_to_do_s(string dummy, string what) {
  what = explode(what, "\n")[0];
  call_out("do_what",0,what);
  return "";
}

void
do_what(string what){
  string verb,
         *directions;

  directions = ({"up","down","u","d","e","n","w","s","ne","nw","se","sw"})+
               environment()->query_exit_cmds();
  verb = explode(what+" ", " ")[0];

  if(member_array(verb, directions) != -1)
  {
    command("say I am not going anywhere alone! I am scared!!!");
    return;
  }
  if((verb == "pull")  || (verb == "push"))
  {
    command("say No!!! You do it! I will do it with you.");
    return;
  }
  if(verb == "search")
  {
    command("say I don't think we should waste time by searching here.");
    return;
  }
  if(verb == "kill")
  {
    command("say No! I have had enough of violence!");
    return;
  }
  if(verb == "throw")
  {
    command("say No! I don't like to throw things!");
    return;
  }
  if(verb == "get" || verb == "pick")
  {
    command("say I am not going to "+verb+" all rubbish here!");
    return;
  }
  if(verb == "wear" || verb == "wield")
  {
    command("say I "+verb+" only my own things!");
    return;
  }
  if(verb == "remove" || verb == "unwield")
  {
    command("say Why should I "+verb+" it?");
    return;
  }

  if(!command(what))
    command("say I don't know how to do '"+what+"'");
  return;
}

string
try_to_follow(string arg) {
  string *arr_direction,
         *exp_dir,
         direction;

  arr_direction = explode(arg+" ", " ");
  direction = arr_direction[sizeof(arr_direction)-1];
  exp_dir = explode(direction, "");
  if((sizeof(exp_dir) > 1) && (exp_dir[sizeof(exp_dir)-2] == "."))
  {
    direction = explode(direction, ".\n")[0];
    call_out("follow_now",0,direction);
  }
  return "";
}

void
follow_now(string direction) {
  string *directions;

  directions = ({"up","down"}) + environment()->query_exit_cmds();
  if((member_array(direction, directions) != -1) &&
     (!present(ob_leader, environment())))
      command(direction);
  return;
}

void
push_pull_wall(string what, string foo) {
  if(what == "pulls") command("pull wall");
  if(what == "pushes")
  {
    command("push wall");
    no_of_pushes += 1;
  }
  return;
}

void
pull_door() {
  command("pull door");
  return;
}

void
push_door(string foo) {
  command("push door");
  return;
}

void
capture_prisoner() {
  command("shout Oh NO!!! Goblins! They are after me!!!");
  command("panic");
  tell_room(environment(), "Great bunch of goblins come running in.\n"+
            "The leader goblin says: Here is the prisoner! Get him!!!\n"+
            "Goblins jump on "+QTNAME(TO)+", knock him down "+
            "and carry him quickly away.\n", TO);
  call_out("remove_object",0);
  return;
}

void
enter_env(object dest, object old)
{
  int reward;

  if(function_exists("end_of_prisoner_quest", dest))
  {
    /* quest finished */
    if(present(ob_leader, environment()))
    {
      reward = REWARD;
      if(no_of_pushes < 3) reward -= 5000*(3-no_of_pushes);
      call_out("command",1,
               "say Thank you for saving me from those horrible goblins.");
      call_out("command",2,
               "say Now I will run home as fast as I can and I will never "+
               "return here!");
      call_out("command",3,"wave "+leader);
      call_out("command",4, 
                "emote runs away with a big smile on his face.");
      /********************************************/
      /*   HERE I REWARD FOR FINISHING QUEST      */
      /********************************************/
      if(ob_leader->test_bit("Rhovanion",GROUP,BIT_SOLVED) == 0)
      {
        ob_leader->set_bit(GROUP,BIT_SOLVED);
        ob_leader->add_exp(reward,0);
        ob_leader->catch_msg("You feel more experienced.\n");
        write_file("/d/Rhovanion/log/goblin_prisoner", 
                ob_leader->query_name() +
                " got " + reward + " exp. " + ctime(time()) + 
                "  FINAL PART.\n");
        ob_leader->save_me(1);
      }
    }
    call_out("remove_object",5);
  }
  return;
}
