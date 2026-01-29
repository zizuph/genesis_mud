/*
 * functions copied and modified from /lib/skill_raise.c for Lothmir.
 * Olorin, September 1993
 */

#define HERB_LIST ({"angurth","astaldo","athelas","attanar","basil",\
     "black potato","blueberry","blung",\
     "caraway","catnip",\
     "chervil","clove","curugwath","dill","fennel","foxglove",\
     "frostheal","fungiarbo","garlic",\
     "ginger","green onion","handasse","hemlock","holly berry",\
     "huckleberry","laurel","lissuin","lothore","madwort",\
     "marjoram",\
     "mint","morgurth","myrtleberry","oregano","parsley","pawnrose",\
     "red potato","redweed","rosemary","saffron","sage",\
     "savory","seregon","sumac","suranie",\
     "tarragon","thyme","tuo","tyelka","ungolestel",\
     })
#define LOTHMIR_S_HERB "_lothmir_s_herb"
#define LOTHMIR_S_HERB_SOLD "_lothmir_s_herb_sold"
#define GUILD_NAME      "Gondorian Rangers Guild"
#define RECRUITHALL     "/d/Gondor/common/guild/recruithall"

string
missing_herb()
{
  string *missing;
  int i;

  missing = ({});
  for(i = 0; i < sizeof(HERB_LIST); i++)
  {
    if(member_array(HERB_LIST[i],herbs) == -1)
      missing += ({ HERB_LIST[i] });
  }
  if(!sizeof(missing)) return 0;
  return missing[random(sizeof(missing))];
}

void
tell_herb(object player)
{
  string sherb;

  TO->command("hmm");
  TO->command("peer " + player->query_name());
  TO->command("say Why should I teach you anything?");
  TO->command("say I'm a busy man!");
  sherb = missing_herb();
  if(!sherb) return 0;
  TO->command("say On the other hand, I need "+sherb+".");
  TO->command("say Sell me some, and I will teach you one lesson.");
  TP->add_prop(LOTHMIR_S_HERB,sherb);
}

/*
 * Function name: sk_hook_raise_rank
 * Description:   The player trains and pays, write something
 * Arguments:     snum  - The skill he trained
 *                to_lev - Wich level he reached
 *                cost   - How much he payed
 */
void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string rank, long_str;

    rank = sk_rank(to_lev);


    write(process_string(QCTNAME(TO))+" teaches you " + sk_tdesc[snum][0] + ".\n");
    write("You achieve the rank of " + rank + ".\n");
    LSAY(process_string(QCTNAME(TO)) + " teaches ", " " + sk_tdesc[snum][1] +
      " and helps him to reach the rank of " + rank + ".");
}

/*
 * Function name: sk_hook_write_header
 * Description:   Write the header to the improve or learn list
 * Arguments:     lessons - How many steps we are talking about
 */
void
sk_hook_write_header(int lessons)
{
    if (!lessons)
        lessons = 1;
    TO->command("say These are the skills in which I can teach you");
    TO->command("say " + LANG_WNUM(lessons) +  (lessons == 1 ? " lesson" : " lessons") + " or more.");
    write("  Skill:                Cost:      "+
          "Next level:           Max level:\n"+
          "--------------------------------------"+
          "--------------------------------------\n");
}
/*
 * Function name: sk_hook_no_list_learn
 * Description:   No more unknown skills for the player in this guild
 * Returns:       1
 */
int
sk_hook_no_list_learn()
{
    TO->command("say I cannot teach you any new skill!");
    TO->command("say You might try to improve skills that you have.");
    TO->command("say Or you will have to seek other teachers elsewhere.");
    return 1;
}

/*
 * Function name: sk_hook_no_list_improve
 * Description:   No more skills that the player can improve
 * Returns:       1
 */
int
sk_hook_no_list_improve()
{
    TO->command("say There are no skills that I can teach you anymore.");
    TO->command("say Perhaps you would feel like learning a new skill?");
    TO->command("say Or you will have to seek other teachers elsewhere.");
    return 1;
}

/*
 * Function name: sk_hook_improved_max
 * Description:   Player can't improve this skill any higer
 * Arguments:     skill - The skill player wanted to improve
 * Returns:       0
 */
int
sk_hook_improved_max(string skill)
{
    NF("You cannot raise this skill any further here, you have to\n" +
      "seek knowledge elsewhere.\n");
    return 0;
}

/*
 * Function name: sk_improve
 * Description:   Function called when player tries to do the improve command
 * Arguments:     str - The rest of the command player made
 * Returns:       1/0
 */
int
sk_improve(string str)
{
  string *tmp;
  int steps, success, old_skill;

  if(TP->query_guild_name_occ() == GUILD_NAME &&
    RECRUITHALL->query_ranger(capitalize(TP->query_real_name())))
  {
    TO->command("peer " + TP->query_name());
    TO->command("say Why don't you train in the Rangers' Guild?");
    TO->command("shrug");
  }
  if(TP->query_skill(SS_HERBALISM) > 10)
  {
    if(!TP->query_prop(LOTHMIR_S_HERB))
    {
      tell_herb(TP);
      return 1;
    }
    if(TP->query_prop(LOTHMIR_S_HERB) != LOTHMIR_S_HERB_SOLD)
    {
      TO->command("say Go and bring me some " +TP->query_prop(LOTHMIR_S_HERB) + ".");
      TO->command("say You sell me that herb, I teach you something.");
      TO->command("say You don't, I don't.");
      TO->command("say Understood?");
      TO->command("peer " + TP->query_name());
      return 1;
    }
  }

/* Lothmir teaches only one level at a time */
  if(str)
  {
    tmp = explode(str, " ");
    if (sscanf(tmp[sizeof(tmp) - 1], "%d", steps) == 1 && sizeof(tmp) > 1)
    {
      TO->command("say I teach only one lesson at a time.");
      TO->command("say Don't be so hasty, my friend!");
      TO->command("say It took me a long time to learn what I know!");
      TO->command("smile " + TP->query_name());
      return 1;
    }
  }

  success = 0;
  old_skill = TP->query_skill(SS_HERBALISM);
  success = ::sk_improve(str);
  if(success && TP->query_skill(SS_HERBALISM) > old_skill)
    TP->remove_prop(LOTHMIR_S_HERB);
  return success;
}
