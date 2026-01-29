/* Shadow for Krynn warfare Dragonslayer title */

inherit "/std/shadow";

string warfare_dragonslayer_title = "Dragonslayer";

public int
query_warfare_dragonslayer_title_shadow_active()
{
    return 1;
}

public void
remove_warfare_dragonslayer_title_shadow()
{
    remove_shadow();
}

string
query_warfare_dragonslayer_title()
{
    return warfare_dragonslayer_title;
}

public void
set_warfare_dragonslayer_title(string str)
{
    warfare_dragonslayer_title = str;
}

string
query_guild_title_race()
{
    string name;

    if (strlen(name = (string)shadow_who->query_guild_title_race()))
      return name + ", " +warfare_dragonslayer_title;
    else
      return warfare_dragonslayer_title;
}

