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

/*
  Gardener rank derived from the number of different herb varieties
  found by member
*/
public int
query_gardener_rank()
{
    int found_herbs = query_gardener_member_herbs_count();
    int adjusted_val = MIN(GARDENER_MAX_HERBS, MAX(0, found_herbs));

    return MIN(GARDENER_MAX_RANK, MAX(0, adjusted_val / GARDENER_RANK_MOD));
}

/*
  Gardener subrank based on member guild stat
*/
public int
query_gardener_subrank()
{
    int stat = (query_gardener_type() == GARDENER_TYPE_LAY
        ? shadow_who->query_base_stat(SS_LAYMAN)
        : shadow_who->query_base_stat(SS_CRAFT)
    );

  return MIN(GARDENER_MAX_RANK, MAX(0, stat / GARDENER_RANK_MOD));
}

public string
query_gardener_title()
{
    return GARDENER_TITLES[query_gardener_rank()];
}
