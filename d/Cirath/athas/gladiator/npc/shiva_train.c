/* shiva_train.c created by Shiva@Genesis early 1995
 * This is just a training hall with a few extras.
 */

#pragma save_binary

inherit "/lib/skill_raise";
#include <macros.h>
#include <money.h>
#include <language.h>
#include <ss_types.h>

int skill(string str);
int help(string str);

void
init_skill_raise()
{
  add_action(help, "help");
  add_action(skill, "skill");
  ::init_skill_raise();
}

int 
skill(string str)
{
  int i;

  if (str != "levels") return 0;

  write("\n");
  i = 0;
  while (i < sizeof(desc))
    write(sprintf("%-13s %-12s %-9s\n", (i == 0 ? "Main Levels:" : ""),
          desc[i++], (i < sizeof(desc) ? desc[i++] : "")));

  write("\n");
  i = 0;
  while (i < sizeof(subdesc))
    write(sprintf("%-13s %-12s %-9s\n", (i == 0 ? "Sublevels:" : ""),
          subdesc[i++], (i < sizeof(subdesc) ? subdesc[i++] : "")));
  return 1;
}

int
help(string str)
{
  if (str != "train" && str != "training" && str != "trainer")
  {
    return 0;
  }

  setuid();
  seteuid(getuid());

  str =
      "'skill levels'\n" +
      "     List the various skill levels attainable.\n\n" +
      "'learn <skill>'\n" +
      "     Learn a skill which you do not know.\n" +
      "     Ex. 'learn defence', 'learn awareness'\n\n" +
      "'improve'\n" +
      "     List all skills trainable here.\n\n" +
      "'improve <levels>'\n" +
      "     List all skills which may be trained the indicated\n" +
      "     number of levels or more.\n" +
      "     Ex. 'improve 3', 'improve 10'\n\n" +
      "'improve <skill>'\n" +
      "     Improve a desired skill one level.\n" +
      "     Ex. 'improve defence', 'improve awareness'\n\n" +
      "'improve <skill> <levels>'\n" +
      "     Improve a desired skill as many levels as indicated.\n" +
      "     Levels actually trained are limited by what you can\n" +
      "     afford and how much you can learn.\n" +
      "     Ex. 'improve defence 3', 'improve awareness 6'\n\n" +
      "'improve <skill> max'\n" +
      "     Improve a skill as high as you can, limited by what you\n" +
      "     can afford and how much you can learn.\n" +
      "     Ex. 'improve defence max', 'improve awareness max'\n\n" +
      "'improve <skill> with <number> <cointype>'\n" +
      "     Improve a skill as high as you can, using the amount of\n" +
      "     money specified.  Levels are limited by how much you\n" +
      "     can afford and how much you can learn.\n" +
      "     Ex. 'improve defence with 7 gold', 'improve awareness\n" +
      "         with 2 platinum coins and 1 gold coin'\n\n" +
      "";

  clone_object("/std/board/board_more")->more(str);

  return 1;
}

void
sk_hook_write_header(int steps)
{
  if (!steps)
    steps = 1;
  write("These are the skills you are able to " + query_verb() +
      " " + LANG_WNUM(steps) + (steps == 1 ? " step" : " steps") +
      " here.\n");
  write("  Skill:                   Cost:    "+
      "Next level:              Max level:\n"+
      "--------------------------------------"+
      "--------------------------------------\n");
}

void
sk_hook_skillisting()
{
  write("Here follow all skills we teach, and your next level in " +
      "each skill:\n");
  write("  Skill:                   Cost:    "+
      "Next level:              Max level:\n"+
      "--------------------------------------"+
      "--------------------------------------\n");
}

varargs string
sk_fix_cost(int snum, int steps)
{
  int this_level, next_level, max, cost, coins, i;
  string next_rank, max_rank, cost_string;

  if (!(max = sk_query_max(snum)))
    return "";

  this_level = this_player()->query_base_skill(snum);
  next_level = (steps ? this_level + steps : this_level + 1);
  cost_string = "";

  if (next_level > max)
    cost_string = "--- ";

  else
  {
    cost = sk_cost(snum, this_level, next_level);

    for (i = sizeof(MONEY_TYPES) - 1; i >= 0; i--)
      if (coins = cost / MONEY_VALUES[i])
      {
        cost_string += sprintf("%2d%-2s", coins,
            FCHAR(MONEY_TYPES[i]));
        cost %= MONEY_VALUES[i];
      }
  }

  if (this_level >= max)
    next_rank = "maxed";
  else
    next_rank = sk_rank(next_level);

  max_rank = sk_rank(max);

  return sprintf("%-17s %16s %-22s %-22s\n", sk_trains[snum][0],
      cost_string, next_rank, max_rank);
}

int
sk_list(int steps)
{
  int i, *guild_sk;

  guild_sk = sk_query_train();

  if (steps < 1 && query_verb() == "improve")
  {
    sk_hook_skillisting();
    steps = 1;
  }
  else if (query_verb() == "learn")
  {
    guild_sk = filter(guild_sk, "sk_filter_learn", this_object(), steps);
    if (!sizeof(guild_sk))
      return sk_hook_no_list_learn();
    sk_hook_write_header(steps);
  }
  else
  {
    guild_sk = filter(guild_sk, "sk_filter_improve", this_object(),
           steps);
    if (!sizeof(guild_sk))
      return sk_hook_no_list_improve();
    sk_hook_write_header(steps);
  }

  for (i = 0; i < sizeof(guild_sk); i++)
    write(sk_fix_cost(guild_sk[i], steps));

  return 1;
}

int
sk_filter_improve(int sk, int steps)
{
    return (this_player()->query_base_skill(sk) + steps <= 
        sk_query_max(sk));
}

int sk_no_list(object who)  { return 0; }

int sk_no_train(object who) { return 0; }

int
sk_improve(string str)
{
  int steps, *known_sk, snum, level, amnt,
      i, j, *coins_arr, max_steps, total;
  string skill, verb, *tmp, with;
  mixed skval;

  if (sk_no_list(this_player())) return 1;

  if (!str || sscanf(str, "%d", steps))
    return sk_list(steps);
  
  if (sk_no_train(this_player())) return 1;

  level = this_player()->query_base_skill(snum);
  verb = query_verb();
  tmp = explode(str, " ");
  if (sscanf(tmp[sizeof(tmp) - 1], "%d", steps) == 1 && sizeof(tmp) > 1)
    skill = implode(tmp[0 .. sizeof(tmp) - 2], " ");
  else
  {
    if (tmp[sizeof(tmp) - 1] == "max")
      str = implode(tmp[0..sizeof(tmp) - 2], " ") + " with " +
            implode(MONEY_TYPES, " ");

    if (sscanf(str, "%s with %s", skill, with) == 2)
    {
      coins_arr = MONEY_COINS(this_player());
      with = implode(explode(with, " and "), " ");
      with = implode(explode(with, ", "), " ");
      with = implode(explode(with, " all "), " ");
      tmp = explode(with, " ");
      i = 0;

      notify_fail(capitalize(verb) + " " + skill + " with what?\n");
      if (sizeof(tmp) < 2)
        return 0;

      while (i < sizeof(tmp))
      {
        if ((j = member_array(tmp[i], MONEY_TYPES)) < 0)
        {  
          if ((i + 1) >= sizeof(tmp) ||
              (j = member_array(tmp[i + 1], MONEY_TYPES)) < 0)
            return 0;
        
          if (!sscanf(tmp[i], "%d", amnt) && 
              !(amnt = LANG_NUMW(tmp[i])))
            return 0;

          if (amnt > coins_arr[j])
          {
            notify_fail("You don't have " + amnt + " " + MONEY_TYPES[j] +
                (amnt == 1 ? " coin" : " coins") + ".\n");
            return 0;
          }
          i++;
        }
        else 
          amnt = coins_arr[j];

        i++;
        total += amnt * MONEY_VALUES[j];
        coins_arr[j] -= amnt;

        if (sizeof(tmp) > i && (tmp[i] == "coins" || tmp[i] == "coin"))
          i++;
      }

      if ((snum = sk_find_skill(skill)) < 0)
        return sk_hook_unknown_skill(skill, verb);

      level = this_player()->query_base_skill(snum);
      while ((total -= sk_cost(snum, level, ++level)) >= 0 &&
              level <= sk_query_max(snum))
        steps++;

      if (!steps)
        steps = 1;
    }
  
    else
    {
      skill = str;
      steps = 1;
    }
  }

  known_sk = this_player()->query_all_skill_types();
  if (!known_sk)
    known_sk = ({});

  if ((snum = sk_find_skill(skill)) < 0)
    return sk_hook_unknown_skill(skill, verb);

  level = this_player()->query_base_skill(snum);

  if (level && verb == "learn")
    return sk_hook_learn_known(skill);
  
  if (steps > 1 && level + steps > sk_query_max(snum) &&
      sk_query_max(snum) > level)
    steps = sk_query_max(snum) - level;

  skval = sk_trains[snum];
  if (steps > 1 && (max_steps = skval[4] *
      this_player()->query_stat(skval[3]) / 100 - level) > 0 &&
      max_steps < steps)
    steps = max_steps;
  
  if (level + steps > sk_query_max(snum))
    return sk_hook_improved_max(skill);
  if (!sk_do_train(snum, this_player(), level + steps))
{
    return sk_hook_cant_train(skill, level + steps);
}

  amnt = sk_cost(snum, level, level + steps);

  if (!MONEY_ADD(this_player(), -amnt))
  {
    this_player()->set_skill(snum, level);
    return sk_hook_cant_pay(skill, level + steps, amnt);
  }

  sk_hook_raise_rank(snum, level + steps, amnt);
  return 1;
}

void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
  write("You improve your ability to " + sk_tdesc[snum][0] + ".\n" +
        "That cost you " + cost + " copper " + (cost == 1 ? "coin" :
        "coins") + ".\nYou achieve the rank of " + sk_rank(to_lev) +
        ".\n");

  say(QCTNAME(this_player()) + " improves " +
      this_player()->query_possessive() + " ability to " + 
      sk_tdesc[snum][1] + ".\n");
}
