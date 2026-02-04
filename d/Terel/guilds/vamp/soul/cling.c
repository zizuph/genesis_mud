/* cling.c created by Shiva@Genesis
 * This file contains the code for the "cling" command
 * This file is part of the vampire guild soul
 */

#include "../guild.h"

#include <macros.h>

inherit "/lib/commands";

int cling(string arg)
{
  object who, sh, *oblist;

  notify_fail("Cling to whom?\n");

  if (!strlen(arg))
  {
    if (!(who = TP->query_attack()))
    {
      return 0;
    }
  }
  else if (!sizeof(oblist = parse_this(arg, "[to] [the] %l")))
  {
    return 0;
  }
  else if (sizeof(oblist) > 1)
  {
    notify_fail("You will have to be more specific.\n");
    return 0;
  }
  else
  {
    who = oblist[0];
  }

  who->remove_prop(VAMP_O_CLING);

  TP->catch_msg("You start to follow "+QTNAME(who)+".\n");

  setuid();
  seteuid(getuid());

  if (!who->query_cling_followers() &&
      (sh = clone_object(SHADOW_DIR + "cling_sh")))
  {
    if (!sh->shadow_me(who))
    {
      sh->remove_shadow();
    }
  }

  who->add_cling_follower(TP);
  return 1;
}

int stop_cling(object who)
{
  if (who->query_prop(VAMP_O_CLING))
  {
    who->remove_prop(VAMP_O_CLING);
    write("You stop following your prey.\n");
    return 1;
  }
  
  notify_fail("You're not following anyone.\n");
  return 0;
}
