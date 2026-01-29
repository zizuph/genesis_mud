inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"
#include "/d/Rhovanion/lib/binbit.h"

#define START_BIT 17
#define STOP_BIT 19
#define RHUN_TOUR "_rhun_tour"
#define REPORT    RHUN_DIR+"npc/report"
#define LOG_FILE "/d/Rhovanion/log/rhun_tours"
#define TOURNAMES ({"the report tour",     \
                    "the Easterling tour",   \
                    "the Woodcutter tour", \
                    "","","",""})
#define REWARDS ({ 150, 300, 150, 0, 0, 0, 0 })

#define CANNOT_TRUST "_player_cannot_be_trusted"
#define FIND_TOWER   "_i_have_found_the_tower_"
#define DONE_WOOD    "_player_done_woodcutter"
#define KILLED_WIFE     "_player_killed_wife"

int alarm, job_given = 0;

void reward_player(object player, int tourno);

void arm_me()
{
  seteuid(getuid());
  command("oops");
  clone_object(WEAPON_DIR+"knife_med")->move(TO);
  command("wield all");
}

void create_monster()
{

  set_alarm(10.0, 0.0, "arm_me");

  set_race_name("human");
  set_name(({"mayor","man"}));
  set_adj(({"fat","town"}));
  set_short("fat town mayor");
  set_gender(0);
  set_alignment(150);
  set_long("This is the mayor of the town.  He's a rather fat man"
                 + " dressed in moderately-fine clothes, considering the"
                 + " area he lives in.  He looks worried, as if he's got"
                 + " a problem of some sort.\n");
  add_prop(CONT_I_WEIGHT, 77 * 1000);
  add_prop(CONT_I_VOLUME, 77 * 1000);
  add_prop(CONT_I_HEIGHT, 173);
  remove_prop(NPC_M_NO_ACCEPT_GIVE);
  set_stats(({ 48, 40, 50, 50, 50, 55 }));
  set_skill(SS_WEP_KNIFE, 30);

  add_ask(({"quest","problem","task","help","job","about quest",
            "about problem","about task","about help","about job"}), 
                                                    VBFC_ME("answ_func"));
  add_ask(({"reward","about reward","for reward"}), VBFC_ME("answ_reward"));
  set_default_answer(VBFC_ME("def_answ_func"));
  set_dont_answer_unseen(1);
}

void set_job_given()
{
  job_given = 1;
  alarm = set_alarm(750.0, 0.0, "remove_job_given");
}

void remove_job_given()
{
  if(get_alarm(alarm)) remove_alarm(alarm);
  job_given = 0;
}

void get_rid_of(object obj){ obj->remove_object(); }

void enter_inv(object obj, object from)
{
  string ooo, adjs;

  adjs = obj->query_adjs();
  if (!adjs) adjs = ({ });
  ooo = implode(adjs+({obj->query_name()}), " ");

  ::enter_inv(obj, from);
  if(!living(from)) return;

/********* tour no 1 *******************************************/
  if(MASTER_OB(obj) == REPORT)
  {
    if(from->query_prop(RHUN_TOUR) == 1)
      set_alarmv(2.0, 0.0, "exa_seal", ({ from, obj }));
    else
    {
      set_alarm(1.0, 0.0,"command", "say Where did you get this?");
      set_alarm(2.0, 0.0,"command", "peer at "+from->query_real_name());
      set_alarm(3.0, 0.0,"command", "emote tears report to pieces.");
      set_alarm(0.5,0.0,"get_rid_of",obj);
    }
    return;
  }
/***************************************************************/
/********* tour no 2 *******************************************/
  if(obj->query_prop("_easterling_id_") && (from->query_prop(RHUN_TOUR) == 2))
  {
    /* ok,he gave us some evidence. */
    if(from->query_prop(FIND_TOWER))
    {
      set_alarm(2.0, 0.0, "finish_tour2", from );
      set_alarm(0.5,0.0,"get_rid_of",obj);
    }
    else
    {
      set_alarm(1.0, 0.0,"command", "say Where did you find this???");
      set_alarm(2.0, 0.0,"command", "peer at "+from->query_real_name());
      set_alarm(3.0, 0.0,"command", "drop "+ooo);
    }
    return;
  }
/***************************************************************/
/********* other fun stuff *************************************/
  if(MASTER_OB(obj) == "/std/coins")
  {
    from->catch_msg("You feel experience worth "+obj->short()+".\n");
    set_alarm(1.0, 0.0,"command", "say Gee!!!  Thanks!");
    set_alarm(2.0, 0.0,"command", "smile at "+from->query_real_name());
    set_alarm(3.0, 0.0,"command", "say Don't you have more?");
    set_alarm(0.5,0.0,"get_rid_of",obj);
  }
  else
  {
    set_alarm(1.0, 0.0,"command", "hmm");
    set_alarm(2.0, 0.0,"command", "say Did I wanted this?");
    set_alarm(3.0, 0.0,"command", "scratch");
    set_alarm(4.0, 0.0,"command", "drop "+ooo);
  }
}

/********* tour no 1 *******************************************/
void exa_seal(object player, object obj)
{
  tell_room(ENV(TO), QCTNAME(TO) + " examines the seal carefully.\n");
  if (!obj->query_prop("_seal_is_intact_"))
  {
    set_alarm(1.0, 0.0,"command", "say What!? The seal is broken! "+
                                 "It's obvious that you can't be trusted!");
    set_alarm(2.0, 0.0,"command", "spit");
    set_alarm(3.0, 0.0,"command", "emote tears report to pieces.");
    player->add_prop(CANNOT_TRUST, 1);
    player->remove_prop(RHUN_TOUR);
    set_alarm(0.5,0.0,"get_rid_of",obj);
    remove_job_given();
  }
  else
  {
    set_alarm(2.0, 0.0, "command", "break seal");
    set_alarm(5.0, 0.0, "command", "read report");
    set_alarmv(10.0, 0.0, "sigh_some", ({ player, obj }) );
  }
}

void sigh_some(object player, object obj)
{
  command("say Well done!");
  reward_player(player, 1);
  player->remove_prop(RHUN_TOUR);
  set_alarm(5.0, 0.0, "command", "sigh");
  set_alarm(0.5,0.0,"get_rid_of",obj);
  remove_job_given();
}
/***************************************************************/

/********* tour no 2 *******************************************/
void finish_tour2(object player, object obj)
{
  command("say Yes! This is the evidence I needed! "+
          "I'll give you a reward.");
  reward_player(player, 2);
  set_alarm(0.5,0.0,"get_rid_of",obj);
  set_alarm(2.0, 0.0,"command", "say What should I do now?");
  set_alarm(3.0, 0.0,"command", "despair");
  player->remove_prop(RHUN_TOUR);
  player->remove_prop(FIND_TOWER);
  remove_job_given();
}
/***************************************************************/

/********* tour no 3 *******************************************/
string answ_reward()
{
  if(TP->query_prop(RHUN_TOUR) != 3)
  {
    command("say Reward?!? First you ought to deserve it!");
    return "";
  }
  if(!TP->query_prop(DONE_WOOD))
  {
    command("say First do properly what I have asked you to do!");
    return "";
  }
  if(TP->query_prop(KILLED_WIFE))
  {
    command("say What is it on your hands? Blood???");
    set_alarm(1.0,0.0,"command","sigh");
    set_alarm(2.0,0.0,"command","say I have not send you to murder her!");
    set_alarm(3.0,0.0,"command","shout Guards!!! This is troublemaker!");
    TP->add_prop(CANNOT_TRUST, 1);
    TP->remove_prop(DONE_WOOD);
    TP->remove_prop(RHUN_TOUR);
    remove_job_given();
    return "";
  }
  command("say Thank you! It is such a relief not to see her for a while.");
  set_alarm(1.0,0.0,"command","smile");
  reward_player(TP, 3);
  TP->remove_prop(RHUN_TOUR);
  remove_job_given();
  return "";
}
/***************************************************************/

string def_answ_func()
{
  command("say Let me think...");
  set_alarm(2.0, 0.0, "command", "think");
  set_alarm(5.0, 0.0, "command", "scratch");
  set_alarm(8.0, 0.0, "command", "say Don't you want to know something else?");
  set_alarm(9.0, 0.0, "command", "peer at "+TP->query_real_name());
  return "";
}

string answ_func()
{
  /* Figure out which tours he has done depending on the bits */
  int n = query_bin_bits(0, START_BIT, STOP_BIT, TP);

  if(TP->query_prop(CANNOT_TRUST))
  {
    command("say No way! You can't be trusted.");
    return "";
  }

  if(TP->query_prop(RHUN_TOUR))
  {
    command("say But you have already a job from me!");
    command("pat "+TP->query_real_name());
    return "";
  }

  if(job_given)
  {
    command("whisper "+TP->query_real_name()+
        " Sorry, I have given the job to someone else. Come back later,"+
        " maybe I will have something for you then.");
    command("comfort "+TP->query_real_name());
    return "";
  }

  switch (n)
  {
    case 0:
            TP->add_prop(RHUN_TOUR, 1);
            command("ask "+TP->query_real_name()+" I haven't heard from "+
                    "the mayor in the village southwest of the forest for "+
                    "a long time. Could you please go and ask him for a "+
                    "report and bring it back to me?");
            set_job_given();
            break;
    case 1:
            TP->add_prop(RHUN_TOUR, 2);
            command("ask "+TP->query_real_name()+" That report mentiones "+
                    "some Easterlings in the forest.");
            command("ask "+TP->query_real_name()+" Now the question is if "+
                    "they are only spies we always seem to have around here "+
                    "or is it some serious invasion?");
            command("ask "+TP->query_real_name()+" If there is some "+
                 "Easterling officer, that would mean some serious trouble.");
            command("ask "+TP->query_real_name()+" Could you please check "+
                    "this out for me? Bring me back some evidence as well.");
            set_alarm(1.0,0.0,"command","smile hopefully at "+
                                         TP->query_real_name());
            set_job_given();
            break;
    case 2:
            TP->add_prop(RHUN_TOUR, 3);
            command("ask "+TP->query_real_name()+" There is one very annoing "+
                    "woman that comes here every so often and disturbs me "+
                    "from my work.");
            command("ask "+TP->query_real_name()+" Her husband works for me "+
                    "in the forest. He is preparing wood for rebuilding of "+
                    "our town wall. We need it now that there are troups "+
                    "of Easterlings around.");
            command("ask "+TP->query_real_name()+" Can you find her please "+
                    "and make sure that she will not bother me again?");
            set_alarm(1.0,0.0,"command","say Ask me for your reward after "+
                                        "you did it.");
            set_job_given();
            break;
    default:
            command("say I don't need any help right now, "+
                    "but thanks for asking!");
            set_alarm(1.0,0.0,"command","bow to "+TP->query_real_name());
            set_alarm(2.0,0.0,"command","oops");
            set_alarm(3.0,0.0,"command","say I nearly forgot... "+
                              "Maybe you can give me some coins?");
            set_alarm(4.0,0.0,"command","smile greedily");
  }
  return "";
}

void reward_player(object player, int tourno)
{
   player->add_exp(REWARDS[tourno-1], 0);
   write_file(LOG_FILE, player->query_name() +
                   " did " + TOURNAMES[tourno-1] + " and got " +
                  REWARDS[tourno-1] + " exp. " +
                   ctime(time()) + ".\n");
   player->catch_msg("You feel more experienced.\n");
   set_bin_bits(0, START_BIT, STOP_BIT, player, tourno);
   player->save_me(1);
   SORT_FILE(LOG_FILE);
}
