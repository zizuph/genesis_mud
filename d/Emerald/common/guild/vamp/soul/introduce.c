/* introduce.c created by Shiva@Genesis
 * This file contains the code for the "introduce" command
 * This file is part of the vampire guild shadow
 */

/* Description
 * -----------
 * This allows a vampire to introduce using any part(s)
 * of his/her title desired, including name, title, level,
 * gender, and race.
 */

#include "../guild.h"
#include <filter_funs.h>
#include <composite.h>
#include <options.h>

int introduce(string str)
{
  string *words, how, who, part1, part2, intro_str;
  string name = "", title = "", level = "", race = "", gender = "",
         vtitle = "", ptitle = "";
  int options;
  object *targets, *livings;
  int i;

  if (!strlen(str))
  {
    return 0;
  }

  if (sscanf(str, "%s to %s", how, who) != 2)
  {
    how = str;
    targets = FILTER_LIVE(all_inventory(ETP)) - ({ TP });
  }
  else
  {
    targets = parse_this(who, "[the] %l");
  }

  if (!sizeof(targets))
  {
    return 0;
  }

  if (!sizeof(words = explode(how + " ", " ")))
  {
    return 0;
  }

  for (i = sizeof(words); i--;)
  {
    switch (lower_case(words[i]))
    {
      case "name":
      case "n":
        name = TP->query_name();
        break;

      case "title":
      case "t":
        title = TP->query_title();
        options |= 1;
        break;

      case "vtitle":
      case "vamp":
      case "v":
        vtitle = TP->query_vamp_title();
        break;

      case "htitle":
      case "ptitle":
      case "personal":
      case "honourary":
      case "honorary":
      case "h":
      case "p":
        ptitle = TP->query_personal_title();
        break;

      case "level":
      case "l":
        level = TP->query_exp_title();
        options |= 2;
        break;

      case "gender":
      case "g":
        gender = TP->query_gender_string();
        options |= 4;
        break;

      case "race":
      case "r":
        race = TP->query_race_name();
        options |= 8;
        break;

      default:
        return 0;
    }
  }

  if (strlen(vtitle))
  {
    title += (strlen(title) ? ", " + vtitle : vtitle);
  }

  if (strlen(ptitle))
  {
    title += (strlen(title) ? ", " + ptitle : ptitle);
  }

  part1 = (strlen(name) ? name : "") +
      (strlen(title) ? (strlen(name) ? " " : "") + title : "");

  part2 = (strlen(level) ? level : "");

  intro_str = part1 +
      ((strlen(part1) && strlen(part2)) ? ", " : "") +
      part2;

  part2 = (strlen(gender) ? gender : "") +
      (strlen(race) ? (strlen(gender) ? " " : "") + race : "");

  intro_str = intro_str +
      ((strlen(intro_str) && strlen(part2)) ? ", " : "") +
      part2;

  if (!strlen(intro_str))
  {
    return 0;
  }

  intro_str = C(intro_str);

  TP->reveal_me(1);

  for (i = sizeof(targets); i--;)
  {
    tell_object(targets[i], TP->query_The_name(targets[i]) +
        " introduces " + OBJ(TP) + "self as:\n" + intro_str + ".\n");
  }

  if (!(options ^ 15))
  {
    targets->add_introduced(TP->query_real_name());
  }

  if (strlen(who))
  {
    livings = FILTER_LIVE(all_inventory(ETP));
    livings -= targets;
    livings -= ({ TP });

    for (i = sizeof(livings); i--;)
    {
      livings[i]->catch_msg(TP->query_The_name(livings[i]) +
          " introduces " + OBJ(TP) + "self to " +
        FO_COMPOSITE_LIVE(targets, livings[i]) + ".\n");
    }
  }

  if (TP->query_option(OPT_ECHO))
  {
    write("You " + query_verb() + " yourself to " +
        COMPOSITE_LIVE(targets) + " as:\n" +
        intro_str + ".\n");
  }
  else
  {
    write("Ok.\n");
  }

  return 1;
}
