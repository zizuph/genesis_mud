/*
*  Created by Znagsnuf.
*
*  Date:                      What is done:                            By whom:            
*  ----------------------------------------------------------------------------
*  01/05-17                   Started remaking it                      Znagsnuf
*
*/

inherit "/std/shadow";

#include <macros.h>
#include <stdproperties.h>

#define BALROG_TITLE "_balrog_title"

string
query_guild_title_lay()
{
    string name;
    if (strlen(name = (string)shadow_who->query_guild_title_lay()))
      return name + " and Balrog Bane";
    else
      return "Balrog Bane";
}

void
remove_me()
{
  if(this_object()->query_prop(BALROG_TITLE) + 60 > time())
    remove_me();
  else
    set_alarm(10.0,0.0,"remove_me");
      
    seteuid(getuid(this_object()));
    shadow_who->catch_msg("You can no longer call yourself 'Balrog Bane'.\n");

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

    if (this_object()->query_prop(BALROG_TITLE) + 60 > time())
      remove_me();
    else
      set_alarm(10.0,0.0,"remove_me");
}

