public int
query_gardener_type()
{
   if(function_exists("query_guild_name_lay", this_object()))
   {
      return GARDENER_TYPE_LAY;
   } else if(function_exists("query_guild_name_craft", this_object())) {
      return GARDENER_TYPE_CFT;
   }

   return 0;
}

public string
query_gardener_title()
{
   int type = query_gardener_type();
   int stat = (
      type == GARDENER_TYPE_LAY
         ? shadow_who->query_base_stat(SS_LAYMAN)
         : shadow_who->query_base_stat(SS_CRAFT)
   );

   return GARDENER_TITLES[MAX(0, MIN(GARDENER_NUM_TITLES-1,
      stat / (GARDENER_MAX_STAT / GARDENER_NUM_TITLES)
   ))];
}

public int
query_gardener_display_title()
{
    int display = this_object()->query_skill(GARDENER_SKILL_TITLE);
    if (display == 0)
    {
        return GARDENER_TITLE_PRES;
    }

    return display;
}

public void
set_gardener_display_title(int display)
{
    this_object()->set_skill(GARDENER_SKILL_TITLE, display);
}
