int
query_is_bnumen(object x)
{
    return (x->query_guild_name_race() == GUILD_NAME);
}

int
filter_weapon(object x)
{
    return (function_exists("create_object", x) == "/std/weapon");
}

int
filter_sword(object x)
{
    return ((function_exists("create_object", x) == "/std/weapon")
           && (x->query_wt() == W_SWORD));
}

int
filter_elf(object x)
{
    return (x->query_race() == "elf");
}

int
sort_bnumen_level(object arg1, object arg2)
{
    int     wl1 = SECURITY->query_wiz_rank(arg1->query_real_name()),
            wl2 = SECURITY->query_wiz_rank(arg2->query_real_name());
    int     dl1 = arg1->query_bnumen_level(),
            dl2 = arg2->query_bnumen_level();
    string  house1 = arg1->query_bnumen_house(),
            house2 = arg2->query_bnumen_house();

    // Fix wizards first.
    if (wl1 && wl2)
    {
        if (wl1 == wl2)
            return 0;
        return - ((wl1 > wl2) * 2 - 1);
    }
    else if (wl1)
        return -1;
    else if (wl2)
        return  1;

    // Fix within one House.
    if (house1 == house2)
    {
        return ((dl1 > dl2) ? -1 : ((dl1 == dl2) ? 0 : 1));
    }

    // Fix different Houses.
    if (house1 > house2)
        return  1;
    else
        return -1;
}

