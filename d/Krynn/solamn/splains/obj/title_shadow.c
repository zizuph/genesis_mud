/* created by Aridor to give the bonus title of Defender 
   idea from Mayhem, help from Mayhem and Grace */

inherit "/std/shadow";

string
query_guild_title_lay()
{
    string name;
    if (strlen(name = (string)shadow_who->query_guild_title_lay()))
      return name + " and Defender of Vingaard Keep";
    else
      return "Defender of Vingaard Keep";
}

