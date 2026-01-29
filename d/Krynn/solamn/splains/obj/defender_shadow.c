/* the shadow that marks a player as defender of Vingaard Keep.
 * created by Aridor, 09/94.
 * idea from Mayhem, help from Mayhem and Grace.
 */

inherit "/std/shadow";

#include "/d/Krynn/common/defs.h"
#include <macros.h>

/* we shadow this function in the player. */
string
query_guild_title_lay()
{
    string name;
    if (strlen(name = (string)shadow_who->query_guild_title_lay()))
      return name + " and Defender of Vingaard Keep";
    else
      return "Defender of Vingaard Keep";
}

void
remove_me()
{
    string *str = shadow_who->query_autoshadow_list();
    int i, tme;
    if (str && sizeof(str))
      for(i=0;i<sizeof(str);i++)
	if (sscanf(str[i],"/d/Krynn/solamn/splains/obj/defender_shadow:%d",tme) == 1)
	  if (tme > time())
	    {
		set_alarm(itof(tme - time()),0.0,"remove_me");
		return;
	    }
    seteuid(getuid(TO));
    shadow_who->catch_msg("You lose the title of 'Defender of Vingaard " +
			  "Keep'.\n");
    shadow_who->remove_autoshadow(MASTER);
    remove_shadow();
}

/* make it autoloading */
void
autoload_shadow(mixed arg)
{
    int tme;
    ::autoload_shadow(arg);
    tme = atoi(arg);
    if (tme < time())
      remove_me();
    else
      set_alarm(itof(tme - time()),0.0,"remove_me");
}

