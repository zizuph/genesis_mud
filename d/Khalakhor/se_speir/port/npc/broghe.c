/*
 * broghe.c
 *
 * Captain of the prison for Port MacDunn.
 * 
 * Khail - June 15/97
 */
#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <language.h>
#include <time.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/random.h"
#include "npc.h"

#define PRISON_TIMER_NAME "_prison_timer"

inherit BASE_NPC;

/*
 * Function name: arm_me
 * Description  : Clones in the guard's equipment
 *                and has him wear/wield it.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
arm_me ()
{
  armours = ({ "/d/Khalakhor/common/arm/targe",
               "/d/Khalakhor/common/arm/vest_hard_leather",
               "/d/Khalakhor/common/arm/belt",
               "/d/Khalakhor/common/kilts/kilt_macdunn",
               "/d/Khalakhor/common/arm/bracers_scale" });
  weapons = ({ WEP + "basket_sword" });
  misc = ({ OBJ + "cell_1_key",
            OBJ + "cell_2_key",
            OBJ + "cell_3_key" });
  ::arm_me();
  command("lace vest");
}


object *
filter_prisoners_by_cell (object ob)
{
  object *arr;
  arr = FILTER_PLAYERS(all_inventory(ob));
  return filter(arr, objectp @ &present(PRISON_TIMER_NAME));
}

mixed
query_prisoners ()
{
  object *cells;
  mixed prisoners;
  int i;

  cells = ({ROOM + "jail_cell_1", ROOM + "jail_cell_2",
            ROOM + "jail_cell_3"})->get_this_object();
 
  prisoners = map(cells, filter_prisoners_by_cell);
  prisoners = prisoners[0] | prisoners[1] | prisoners[2];
  
  return prisoners;
}

string
reply_prisoners ()
{
  object *prisoners;
  string resp;
  int i;

  prisoners = query_prisoners();

  if (!sizeof(prisoners))
    return "say Actually, the cells are completely empty at " +
      "the moment.";

  resp = sizeof(prisoners) == 1 ?
    "say The only person in jail at the moment is " +
    (prisoners[0]->query_name()) + ". " :
    "say At the moment I've got " +
    COMPOSITE_WORDS(prisoners->query_name()) + " locked up. ";

  resp += "You can 'inquire' about their sentence and bail " +
    "if you want.";

  return resp;
}

string
act_1 ()
{
  object *arr;

  arr = filter(all_inventory(environment()), &->id("guard"));
  arr -= ({TO});

  if (!sizeof(arr))
    return "say Where the blazes did the guards go?";

  if (sizeof(arr) == 1)
    {
      command("say You there, where did the other guards go?");
      arr[0]->command("shrug");
      arr[0]->command("say Out on patrol, maybe.");
      return "nod und";
    }

  command("say You " + LANG_WNUM(sizeof(arr)) + ", see if " +
          "you can pick up any new rumours about those goblins " +
          "that have been seen near the piers.");
  arr[0]->command("say Aye Broghe, but don't get your hopes " +
                  "up, there's been nothing new for at least a week.");
  return "say I know, I know. Maybe we'll get lucky today.";
}

string
act_2 ()
{
  object *arr;

  arr = filter(all_inventory(environment()), &->id("guard"));
  arr -= ({TO});

  if (!sizeof(arr)) {
    command("grumble angr");
    command("say Why is there never a guard around when I want one.");
    return "shout Guards!";
  }

  if (sizeof(arr) == 1) {
    if (!sizeof(query_prisoners())) {
      command("say Hmm, quiet day in here, isn't it?");
      arr[0]->command("say Aye, but is that a bad thing?");
      command("chuckle");
      return "say No, I suppose not.";
    }
    else {
      command("say Have you checked in on " +
              COMPOSITE_WORDS(query_prisoners()->query_name()) +
              " recently?");
      arr[0]->command("nod");
      arr[0]->command("say Aye, still alive and pissed off.");
      arr[0]->command("chuckle");
      return "grin";
    }
  }
  else {
    if (!sizeof(query_prisoners())) {
      command("say Hmm, quiet day in here, isn't it?");
      arr[0]->command("say Aye, but is that a bad thing?");
      arr[0]->command("grin " + OB_NAME(arr[1]));
      arr[1]->command("chuckle");
      return "say No, I suppose not.";
    }
    else {
      command("say Has anyone checked in on " +
              COMPOSITE_WORDS(query_prisoners()->query_name()) +
              " recently?");
      arr[0]->command("nod");
      arr[0]->command("say Aye, still alive and pissed off.");
      arr[1]->command("say Nothing new there.");
      arr[1]->command("grin");
      return "chuckle";
    }
  }
  return "";
}

string
act_3 ()
{
  object *arr;

  arr = filter(all_inventory(environment()), &->id("guard"));
  arr -= ({TO});
  if (!sizeof(arr)) {
    command("say I wonder if there's been any word on " +
            "those poachers in the forest...");
    return "say Where the blazes are the guards?";
  }

  command("say Hmm, has there been any word on those " +
          "poachers in the forest?");
  arr[0]->command("say Not that I've heard.");

  if (sizeof(arr) > 1)
    arr[0]->command("say I heard the wardens have begun " +
                    "suspecting one of the clans from the east shore, " +
                    "but that's it.");

  return "frown";
}
            
/*
 * Function name: create_khalakhor_human
 * Description  : Turns this object into a shopkeeper.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
create_khalakhor_human ()
{
  ::create_khalakhor_human();
  add_name("man");
  add_name("guard");
  add_name("captain");
  add_name("_macdunn_jail_captain");
  set_adj("lean");
  add_adj("muscular");
  set_long("This man is the captain of the prison here in " +
           "Port Macdunn, as well as of the town guard. Several " +
           "scars and a harsh glint in his eye are evidence of " +
           "a fairly harsh life, and he undoubtedly bears the " +
           "skill to match.\n");

  default_config_npc(60);
  set_team_follower();
  set_team_name("village_patrol_1");
  set_autoassist();
  set_skill(SS_AWARENESS, 50);
  set_skill(SS_UNARM_COMBAT, 50);
  set_skill(SS_DEFENCE, 50);
  set_skill(SS_PARRY, 50);
  set_skill(SS_WEP_SWORD, 70);

  set_alignment(200 + random(200));
  set_exp_factor(50);

  add_ask(({"prisoners", "about prisoners"}), reply_prisoners, 1);
  set_act_time(25);
  add_act("ponder");
  add_act("emote glances through this week's patrol schedules.");
  add_act("say I wonder if these rumours of goblins in the " +
          "village are true.");
  add_act(act_1);
  add_act(act_2);
  add_act(act_3);
 
  set_size_descs("tall", "of normal width");
}
    
int
give_keys_to_guard (object guard)
{
  command("give keys to " + OB_NAME(guard));
  return 1;
}

void
store_equip (object who, object *inv, object guard)
{
  reset_euid();
  (ROOM + "jail_storage")->load_me();
  (ROOM + "jail_storage")->add_equipment(inv, who);
  tell_room(environment(TO), QCTNAME(guard) + " strips " +
            QTNAME(who) + " of " + COMPOSITE_DEAD(inv) + " and " +
            "hands it all to " + QTNAME(TO) + ", who stashes " +
            "it away out of sight.\n", ({who}));
}

object *
check_inquire_bail (string str)
{
  string *psarr;
  object  prisoner, timer;
  
  if (!str || !strlen(str)) {
    command("say Who are you inquiring about?");
    return 0;
  }

  parse_command(str, TP, "[about] %s", str);
  
  str = lower_case(str);
  psarr = query_prisoners()->query_real_name();
  
  if (!sizeof(psarr)) {
    command("say Actually, the cells are empty at the moment.");
    return 0;
  }
  
  if (member_array(str, psarr) < 0 || !(prisoner = find_player(str))) {
    command("say Sorry, I don't have anyone named " + 
            capitalize(str) + " in jail.");
    return 0;
  }

  if (!(timer = present("_prison_timer", prisoner))) {
    command("blink");
    command("say Actually I guess " + HE_SHE(prisoner) +
            "'s free to go.");
    command("shout Guard! Release " + prisoner->query_name() +
            "!");
    reset_euid();
    timer = clone_object(OBJ + "prison_timer");
    timer->move(prisoner, 1);
    timer->release_me(prisoner);
    return 0;
  }
  return ({prisoner, timer});
}

int
do_inquire (string str)
{
  object *p_t, prisoner, timer;
  int time, bail;


  p_t = check_inquire_bail(str);
  if (! p_t)
    return 1;
  prisoner = p_t[0];
  timer = p_t[1];
  time = timer->query_time_left();
  bail = timer->query_bail();

  command("say " + prisoner->query_name() + "? " +
          capitalize(HE_SHE(prisoner)) + " has about " +
          CONVTIME(time / 60 * 60) + " left in " + HIS_HER(prisoner) +
          " sentence, but can be bailed out for " + LANG_WNUM(bail) +
          " platinum coins.");
  return 1;
}

int
do_bail (string str)
{
  object *p_t, prisoner, timer, coin;
  int bail;

  p_t = check_inquire_bail(str);
  if (! p_t)
    return 1;
  prisoner = p_t[0];
  timer = p_t[1];

  bail = timer->query_bail();

  if (!(coin = present("platinum coin", TP))) {
    command("say Sorry, I only accept platinum coins for " +
            "bail. We don't have enough room to store smaller " +
            "coinage nor the time to run to the bank continually.");
    return 1;
  }

  if (coin->num_heap() < bail) {
    command("say Bail is set at " + LANG_WNUM(bail) + 
            " platinum coins, come back when you have enough.");
    return 1;
  }

  write("You hand over " + LANG_WNUM(bail) + " platinum coins " +
        "to " + query_the_name(TP) + " as bail.\n");
  say(QCTNAME(TP) + " hands over some platinum coins to " +
      QTNAME(TO) + ".\n");
  command("emote does a quick count to check the amount then " +
          "nods in satisfaction.");
  command("shout Guard! Release " + prisoner->query_name() + "!");
  timer->release_me(prisoner);
  return 1;
}

void
init_living ()
{
  ::init_living();
  add_action(do_inquire, "inquire");
  add_action(do_bail, "bail");
}

void
hook_return_intro_new (string str)
{
  command("say Good day to you, " + capitalize(str) +
          ", I'm " + query_name() + " " + query_title() + 
          ". Remember to behave in our town!");
  command("bow " + str);
}

void
hook_return_intro_bad (string str)
{
  command("smirk");
  command("say did you like our jail?");
}

void
hook_return_intro_good (string str)
{
  command("chuckle");
  command("say Ahh, yes, of course, I remember you from " +
          "your last visit, " + capitalize(str) + ", what " +
          "can I do for you this time?");
}
