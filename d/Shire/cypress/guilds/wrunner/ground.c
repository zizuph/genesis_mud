/* ground.c created by Shiva@Genesis
 * This file contains the code for the "ground" command
 * This file is part of the wildrunner guild soul
 * Updated for Cypress by Finwe, Jul 2001
 */

#include "wrunner_defs.h"
#include "/d/Shire/cypress/sys/defs.h"
#include <macros.h>
#include <tasks.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit "/cmd/std/command_driver";

int order_members(object a, object b);

int ground(string str)
{
  string name, title, str1, str2, list;
  int i, size, cnt = 0;
  object *wrunners;

  wrunners = sort_array(filter(users(),
      &->query_guild_member(GUILD_NAME)), "order_members", TO);

  list = "You can hear all of the following:\n";

  size = sizeof(wrunners);
  i = -1;
  while (++i < size)
  {
    str1 = "";
    str2 = "";

    if (((wrunners[i]->query_invis() && IS_WIZ(wrunners[i])) ||
        extract(wrunners[i]->query_name(), -2) == "jr") &&
        !IS_WIZ(TP))
    {
      continue;
    }

    if (name = wrunners[i]->query_name())
    {
      if (wrunners[i]->query_invis() && IS_WIZ(TP))
      {
        name = "(" + name + ")";
      }

      str1 += name;
    }

    if (title = wrunners[i]->query_title())
    {
    str1 += (strlen(str1) ? " " + title : CAP(title));
    }

    if (IS_WIZ(TP))
    {
      str2 = "(" + (IS_WIZ(wrunners[i]) ? "wiz" :
          wrunners[i]->query_average()) + ")";
    }

    cnt++;
    list += sprintf("- %=-68s %-5s\n", str1, str2);
  }

  list += "======================================================="+
           "===================\n";
  list += "Total number of active Wild Elves is " + cnt + ".\n";

  if (FCHAR(query_verb()) == "m")
  {
    setuid();
    seteuid(getuid());
    clone_object("/std/board/board_more")->more(list, 0, 0);
  }
  else
  {
    write(list);
  }

  all (" carefully listens for fellow wild elves.");
  return 1;
}

int order_members(object a, object b)
{
  string aname = a->query_name();
  string bname = b->query_name();

  return (aname < bname ? -1 : (aname == bname ? 0 : 1));
}
