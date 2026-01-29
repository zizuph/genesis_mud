/* Shadow for Krynn warfare titles */

inherit "/std/shadow";

string warfare_title = "";

public int
query_warfare_title_shadow_active()
{
    return 1;
}

public void
remove_warfare_title_shadow()
{
    remove_shadow();
}

string
query_warfare_title()
{
    return warfare_title;
}

public void
set_warfare_title(string str)
{
    warfare_title = str;
}

string
query_guild_title_lay()
{
    string name;

    if (strlen(name = (string)shadow_who->query_guild_title_lay()))
      return name + ", " +warfare_title;
    else
      return warfare_title;
}

