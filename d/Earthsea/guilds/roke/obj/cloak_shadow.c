inherit "/std/shadow";

public string query_nonmet_name()
{
  return "dark-blue cloaked hooded " + 
    shadow_who->query_gender_string() + " " +
    shadow_who->query_race_name();
}
