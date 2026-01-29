#pragma strict_types

inherit "/std/guild/guild_base";

#include <macros.h>
#include <ss_types.h>

public int
query_guild_tax_race() { return 2; }

public nomask string
query_guild_type() { return "race"; }

public string
query_guild_style_race() { return "race"; }

public string
query_guild_name_race() { return "Kender"; }

public string
query_guild_title_race() { return "Burrfoot"; }

public int
query_guild_family_name() { return 1; }

public int
query_guild_not_allow_join_race(object player, string type, string style,
   string name)
{
   notify_fail("One race guild is enough.\n");
   if (type == "race")
      return 1;
   
   return 0;
}

public nomask int
query_guild_member_race() { return 1; }

public mixed
query_guild_trainer_race()
{
   return 0;
}

public nomask int
remove_guild_race()
{
   if (!shadow_who->remove_autoshadow(MASTER + ":"))
      return 0;
   
   shadow_who->set_guild_pref(SS_RACE, 2);
   remove_shadow();
   return 1;
}

public void
init_race_shadow(string arg) {}

public string
query_race_name() { return "kender"; }

public nomask void
autoload_shadow(string str)
{
   if (shadow_who)
      return; /* Already shadowing */
   
   if (query_guild_not_allow_join_guild(this_player(), "race",
            query_guild_style_race(), query_guild_name_race()))
   {
      write("Your guilds don't seem to get along. Your race guild " +
         "is removed.\n");
      this_player()->remove_autoshadow(MASTER);
      return;
   }
   
   if (!query_guild_keep_player(this_player()))
      {
      this_player()->remove_autoshadow(MASTER);
      return;
   }
   
   ::autoload_shadow(str);
   this_object()->init_race_shadow(str);
   
   this_player()->set_guild_pref(SS_RACE, query_guild_tax_race());
}
