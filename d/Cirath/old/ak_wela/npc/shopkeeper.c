/* 
 * This shopkeeper blocks the exit of his shop unless players owe him
 * nothing.  This way, items can be kept in the shop.  He will attack
 * any player who attempts to leave his shop with goods picked up there,
 * and call the police to help him with the crook.  Currently, the only
 * punishment for a crime in Ak Wela is death.
 */

inherit "/std/monster";
inherit "/sys/global/money";
inherit "/lib/trade";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <money.h>
#include "/d/Cirath/common/defs.h"

int *gold_wanted, old_gold;  /* how much to still take from each player, and 
                              * the gold we had before we were given something.
                              */
string *customers;


void create_monster()
{
    int num_cust, which_cust;

    seteuid(getuid());

    victims = (({}));
    gold_wanted = (({}));

    set_name("owner");
    set_race_name("gnome");
    set_adj("shrewd");
    add_adj("burly");
    set_living_name("adiron");

    set_short("shrewd burly gnome");

    set_long("");

    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    add_prop(CONT_I_WEIGHT, 45000);     /* 45 Kg */
    add_prop(CONT_I_HEIGHT, 100);     /* 100 cm */

             /* STR DEX CON INT WIS DIS */
    set_stats(({ 50, 60, 45, 42, 40, 70}));
    set_skill(SS_WEP_CLUB, 60);

    set_pick_up(0);
    set_aggressive(0);
    set_attack_chance(0);
    set_hp(query_max_hp()); /* Heal fully */

    clone_object(STAND_WEAPON + "thief_dagger")->move(TO);
    command("wield dagger"); 

    (MONEY_MAKE_SC(random(12)))->move(TO);
    (MONEY_MAKE_CC(random(12)))->move(TO);
    old_gold = total_money(TO);

    /* Actions */
    set_act_time(5);
  add_act("smile");

  /* Triggers */
  trig_new("%w 'introduces' %s", "react_introduce");
  trig_new("%w 'died.' %s", "remove_victim");
}


string *query_customers()
{
    return customers;
}


int query_gold_wanted(string which_victim)
{
    int victim_num;

    if ((victim_num = member_array(which_victim, customers)) != -1)
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
  if (member_array(old_victim, customers) != -1)
  {
    command("wink " + old_victim);
    customers -= ({ old_victim });
    if (!sizeof(customers))
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
  { /* if they aren't in the customers array yet, put them there. */
    if ((member_array((player_name = this_player()->query_real_name()), customers)) == -1)
    {
      customers += ({ player_name }); /* place for our new victim */
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
               file_name(from) + " just gave me this: " + file_name(coins));
    return;
  }

  this_victim = member_array(from->query_real_name(), customers);
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
    remove_victim(customers[this_victim], dummy1);
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
    if ((member_array(this_player()->query_real_name(), customers) != -1) &&
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
}


int query_knight_prestige() { return -5; }
