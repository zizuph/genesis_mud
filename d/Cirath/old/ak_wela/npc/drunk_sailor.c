/* 
 * This sailor wanders about the docks of Ak Wela, looking for
 * charitable players to give him money.  Sometimes he'll get
 * in their way as they try to leave.  Not hard to kill (I hope).
 */

inherit "/std/monster";
inherit "/sys/global/money";

#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#include "/sys/money.h"
#include "/d/Cirath/common/defs.h"
#include "/d/Shire/common/monster/tobacco.h"


string *victims; // The players in this room
string *exit_cmds; // The exit commands for ENV(TO)

void create_monster()
{
    int numvictims, whichvictim; /* sizeof(victims) */

    string *poss_races = ({"human", "elf", "hobbit", "dwarf", "goblin"});
    object dagger, cloak;

    seteuid(getuid());

    victims = (({}));

    set_name("sailor");
    set_race(poss_races[random(sizeof(poss_races))]);
    if (query_race() == "hobbit")
        clone_tobacco();

    set_short("drunken, foul-smelling sailor");


    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    add_prop(CONT_I_WEIGHT, 65000);     /* 65 Kg */
    add_prop(CONT_I_HEIGHT, 173);     /* 173 cm */

              /* STR DEX CON INT WIS DIS */
    set_stats(({ 20, 12, 24, 10, 10, 40 }));
    set_skill(SS_UNARM_COMBAT, 15);
    set_skill(SS_WEP_SWORD, 30);
    set_skill(SS_WEP_CLUB, 10);
    set_skill(SS_WEP_KNIFE, 20);
    set_skill(SS_PARRY, 12);

    set_pick_up(0);
    set_aggressive(0);
  set_attack_chance(0);
  set_hp(query_max_hp()); /* Heal fully */

  (dagger = clone_object(STAND_WEAPON + "thief_dagger"))->move(TO);
/* clone(STAND_ARMOUR + "thief_cloak"); */
  command("wield dagger"); 
/* command("wear cloak"); */

  (MONEY_MAKE_CC(random(12)))->move(TO);

  /* Actions */
  set_act_time(5);
  add_act("snicker");
  add_act("wink");
  add_act("grin");
  add_act("spit");

  /* Triggers */
  trig_new("%w 'sighs' %s", "react_depressed");
  trig_new("%w 'groans' %s", "react_depressed");
  trig_new("%w 'introduces' %s", "react_introduce");
  trig_new("%w 'died.' %s", "remove_victim");
}


string *query_victims()
{
    return victims;
}


int query_gold_wanted(string which_victim)
{
    int victim_num;

    if ((victim_num = member_array(which_victim, victims)) != -1)
        return gold_wanted[victim_num];
    else return -1;
}


string friendly()
{
  if (this_player()->query_gender() == G_FEMALE)
    return "babe";
  else /* male or neuter */
    return "bub";
}


void depressed_chat()
{
  tell_room(environment(TO), "The bandit mutters, \"Sorry, " + friendly() +
                             ", but a guy's gotta make a living!\"\n");
}


void react_depressed(string dummy1, string dummy2)
{
  call_out("depressed_chat", 1);
}


void intro_chat()
{
  tell_room(environment(TO),
            break_string("His voice dripping with sarcasm, the robber says, " +
            "\"Pleased to meet you.  Now gimme your money!!\"\n", 70));
}


void react_introduce(string dummy1, string dummy2)
{
  call_out("intro_chat", 1);
}


void destruct_bandit()
{
  tell_room(environment(TO),
            "The rogue grins, waves, and disappears behind some bushes.\n");
  TO->remove_object(TO);
}


void remove_victim(string old_victim, string dummy1)
{
  old_victim = lower_case(old_victim);
  if (member_array(old_victim, victims) != -1)
  {
    command("wink " + old_victim);
    victims -= ({ old_victim });
    if (!sizeof(victims))
      call_out("destruct_bandit", 1);
  }
}


int my_total_money(object player)
{
  object *all_objects;
  int object_count, temp_count;

  temp_count = 0;
  all_objects = deep_inventory(player);
  for (object_count = 0; object_count < sizeof(all_objects); object_count++)
  {
    temp_count += total_money(all_objects[object_count]);
  }
  return (temp_count + total_money(player));
}


void grab_chat()
{
  tell_object(this_player(), "The bandit grabs you from behind!\n");
  tell_object(this_player(), "He puts a dagger to your throat, and snarls, \"Gimme all yo' money!\"\n");
  tell_room(environment(TO), "The bandit grabs " + QTNAME(this_player()) + " from behind!\n", this_player());
  tell_room(environment(TO), "Putting a dagger to " + this_player()->query_possessive() +
                             " throat, he snarls, \"Gimme all yo' money!\"\n", this_player());
}


void grab_newcomer()
{
  int player_gold, percent;
  string player_name;

  if (!interactive(this_player()) || this_player()->query_wiz_level())
    return; /* Don't trap wizzes or NPC's */

  player_gold = TO->my_total_money(this_player());

  if (!player_gold || this_player()->query_average_stat() <= 25)
    return; /* Don't trap anyone without money. */
  else
  { /* if they aren't in the victims array yet, put them there. */
    if ((member_array((player_name = this_player()->query_real_name()), victims)) == -1)
    {
      victims += ({ player_name }); /* place for our new victim */
      percent = this_player()->query_average_stat() - 20;
      gold_wanted += ({ ((percent > 0 ? percent : 0) * player_gold) / 100 });
/* wants percentage of gold based on their stats. */
      call_out("grab_chat", 1);
    }
  }
}


void not_enuf_chat()
{
  int chat_num;

  chat_num = random(3);
  
  switch (chat_num)
  {
    case 0:
        tell_room(environment(TO),
          "The bandit hisses, \"That's not enough, buddy!\"\n");
        return;
    case 1:
        tell_room(environment(TO), "The bandit glares at " + QTNAME(this_player()) + "\n", this_player());
        tell_room(environment(TO), "and says, \"Come on now, cough it up!\"\n", this_player());
        tell_object(this_player(),
          "The bandit glares at you and says, \"Come on now, cough it up!\"\n");
        return;
    case 2:
        tell_room(environment(TO),
          "The mugger growls, \"I know you have more than that!\"\n");
        return;
  }
}


void trash(string drop_name)
{
  int chat_num;

  chat_num = random(6);

  switch (chat_num)
  {
    case 0:
      tell_room(environment(TO),
                "The bandit snarls, " +
                "\"What do you expect me to do with this junk?!\"\n");
      return;
    case 1:
      tell_room(environment(TO),
                "The bandit threatens, " +
                "\"Don't try to pass this stuff off on me!\"\n");
      return;
    case 2:
      tell_room(environment(TO),
                "The thief grumbles, " +
                "\"This is a piece of crap.\"\n");
      return;
    case 3:
      tell_room(environment(TO),
                "The bandit asks, " +
                "\"Don't you have anything better?\"\n");
      return;
    case 4:
      tell_room(environment(TO),
                "The rogue snaps, \"Don't toy with me!!  " +
                "I'll squash you like a cockroach!!\"\n");
      return;
    case 5:
      tell_room(environment(TO),
                "The mugger roars, " +
                "\"Gimme money, not this shit!!\"\n");
  }
  call_out("drop_an_object", 1, drop_name);
}


void thank_chat()
{
  int chat_num;

  chat_num = random(3);
  switch (chat_num)
  {
    case 0:
      tell_room(environment(TO),
                "The thief shouts, \"YEAH!\"\n");
    case 1:
      tell_room(environment(TO),
                "The thief says, \"Thanks, " + friendly() + "!\"\n");
      return;
    case 2:
      tell_room(environment(TO),
                "The bandit gasps, \"For me??  How kind of you!\"\n");
      return;
  }
}


/* 
 * NOTE: This is not a straight comparison of ac/wc value.  The thief,
 * being what he is, is influenced by the value of the object.  The more
 * the objects' worth, the more his judgement is off.  Mathematical
 * method of doing this still undecided.
 */

int compare_armour(object armour0, object *armour1)
{
  /* if armour0 is better return 0;
   * else return 1;
   */
  return random(2);
}


int compare_weapon(object weapon0, object weapon1)
{
  /* if weapon0 is better return 0;
   * else return 1;
   */
  return random(2);
}


int wear_an_armour(string arm_name)
{
  return (command("wear " + arm_name));
}


int remove_an_armour(string arm_name)
{
  return (command("remove " + arm_name));
}


int drop_an_object(string ob_name)
{
  return (command("drop " + ob_name));
}


int wield_a_weapon(string weapon_name)
{
  return (command("wield " + weapon_name));
}


int unwield_a_weapon(string weapon_name)
{
  return (command("unwield " + weapon_name));
}


void examine_object(object heavy_ob)
{
  int armour_num, worn_arm_type, given_arm_type, arm_list_cnt;
  int in_pwr_cnt, out_pwr_cnt, keep_current;
  object *worn_armour, *take_off_list, current_weapon;

  if (function_exists("create_armour", heavy_ob)) /* he has armour */
  {
    worn_armour = ({}); /* assume he's naked */
    given_arm_type = heavy_ob->query_at();

    armour_num = 1;
    if (TO->query_armour(armour_num))
        worn_armour += ({ TO->query_armour(armour_num) });
    for (out_pwr_cnt = 1;
         out_pwr_cnt <= 16; /* 2^16 = 65536, largest tool-slot # */
         out_pwr_cnt++)
    {
        armour_num *= 2;
        if (TO->query_armour(armour_num))
            worn_armour += ({ TO->query_armour(armour_num) });
    }
    if (!sizeof(worn_armour))
    {
      call_out("thank_chat", 1);
      call_out("wear_an_armour", 1, heavy_ob->query_name());
    } /* no previous armour */
    else
    {
      take_off_list = ({}); /* assume no conflicts */
      for (arm_list_cnt = 0;
           arm_list_cnt < sizeof(worn_armour);
           arm_list_cnt++)
      {
        worn_arm_type = worn_armour[arm_list_cnt]->query_at();
        if (worn_arm_type & given_arm_type) /* if any 2 pieces share slots */
          take_off_list += ({ worn_armour[arm_list_cnt] }); /* then this piece 
                                                             * may come off.
                                                             */
      }
      if (sizeof(take_off_list))
      {
        keep_current = compare_armour(heavy_ob, take_off_list);
        if (keep_current)
          call_out("trash", 1, heavy_ob->query_name()); /*original was better*/
        else
        {
          call_out("thank_chat", 1); /* take off all conflicting old armours */
          for (arm_list_cnt = 0;
               arm_list_cnt < sizeof(take_off_list);
               arm_list_cnt++)
            call_out("remove_an_armour", 1,
                     take_off_list[arm_list_cnt]->query_name());
          call_out("wear_an_armour", 1, heavy_ob->query_name());
          for (arm_list_cnt = 0;
               arm_list_cnt < sizeof(take_off_list);
               arm_list_cnt++)
            call_out("drop_an_object", 1,
                     take_off_list[arm_list_cnt]->query_name());
        } /* thought his new was better */
      } /* had conflicting armours */
      else
      {
/*        if (!call_out("wear_an_armour", 1, heavy_ob->query_name()))) */
        call_out("wear_an_armour", 1, heavy_ob->query_name());
      } /* no conflict in armours */
    } /* had some armour on */
  } /* object is armour */
  else if (function_exists("create_weapon", heavy_ob))
  {
    current_weapon = TO->query_weapon(TS_RWEAPON);
    keep_current = compare_weapon(heavy_ob, current_weapon);
    if (keep_current)
      call_out("trash", 1, heavy_ob->query_name()); /* original was better */
    else
    {
      call_out("thank_chat", 1);
      call_out("unwield_a_weapon", 1, current_weapon->query_name());
/*      if (command("wield " + heavy_ob->query_name())) */
      call_out("wield_a_weapon", 1, heavy_ob->query_name());
      call_out("drop_an_object", 1, current_weapon->query_name());
/*      else
        command("drop " + heavy_ob->query_name()); */ /* commented out */
    } /* thought his new was better */
  } /* object is a weapon */
  else /* neither armour nor weapon */
    call_out("trash", 1, heavy_ob->query_name()); /* not useful */
}


void enter_inv(object coins, object from)
{
  int diff, this_victim, current_gold;
  string dummy1;

  ::enter_inv(coins, from);

  if (!from)
    return;
  if (from != this_player())
  {
    write_file("/d/Shire/log/strange", file_name(TO) + "\n" +
               file_name(from) + " just gave me this: " + file_name(coins) + "\n");
    return;
  }

  this_victim = member_array(from->query_real_name(), victims);
  current_gold = TO->my_total_money(TO);
  if (current_gold == old_gold)
  {
    examine_object(coins);
  }
  else if (this_victim == -1) return;
  else if ((diff = (current_gold - old_gold)) < gold_wanted[this_victim])
  {
    call_out("not_enuf_chat", 1, this_player());
    gold_wanted[this_victim] -= (diff - random(144));
    gold_wanted[this_victim] = MIN(gold_wanted[this_victim], TO->my_total_money(this_player()));
  }
  else
  {
    remove_victim(victims[this_victim], dummy1);
  }
  old_gold = current_gold;
}


void no_go_chat()
{
  int chat_num;

  chat_num = random(3);
  switch (chat_num)
  {
    case 0:
        tell_room(environment(TO),
                  "The bandit yells, \"You're not going anywhere, chump!\"\n");
        return;
    case 1:
        tell_room(environment(TO),
                  "The bandit says, \"Where do ya think you're going?\"\n");
        return;
    case 2:
        tell_room(environment(TO),
                  "The bandit growls, \"Ya gotta pay the toll-keeper, and dat's me!\"\n");
        return;
  }
}


int catch_all(string cmd)
{
  string action;

  action = query_verb();
  if (member_array(action, exit_cmds) != -1)
  {
    if ((member_array(this_player()->query_real_name(), victims) != -1) &&
        (CAN_SEE(TO, this_player()) && CAN_SEE_IN_ROOM(TO)))
    {
      write("The bandit blocks your path!\n");
      say ("The bandit blocks " + QTNAME(this_player()) + "'s path!\n");
      no_go_chat();
      return 1;
    }
    else return 0;
  }
  else return 0;
}


void init_living()
{
  int exit_arrays_counter;

  ::init_living();
  grab_newcomer();
  exit_cmds = environment(TO)->query_exit_cmds();
  add_action("catch_all", "", 1);
}


int query_knight_prestige() { return 75; }
