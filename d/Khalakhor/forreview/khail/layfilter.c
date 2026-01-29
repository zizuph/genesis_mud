object *laymen;

public void
create()
{
    laymen = ({});
}

public void
get_lay_users()
{
    laymen = filter(users(), &->query_guild_member_lay());
}

runme()
{
    string ret;
    int i;
    get_lay_users();

    for (i = 0; i < sizeof(laymen); i++)
    {
        ret = laymen[i]->query_name();
        ret += " (" + laymen[i]->query_guild_name_lay() +
            ")\n";
        write(ret);
        write("query_guild_not_allow_join_guild: " +
            laymen[i]->query_guild_not_allow_join_guild(laymen[i],
                "layman", "fighter", "Dummy") + "\n");
        write("query_guild_not_allow_join_lay: " +
            laymen[i]->query_guild_not_allow_join_lay(laymen[i],
                "layman", "fighter", "Dummy") + "\n");
        dump_array(laymen[i]->query_autoshadow_list());
        write("\n\n");
    }
}