public void
notify_death(object killer)
{
    ::notify_death(killer);

    if (IS_MERC(killer))
    {
        MJOIN->add_warned(killer->query_real_name());
        write_file(MERC_PUNISH_LOG, extract(ctime(time()), 4, 15) + " " +
        capitalize(killer->query_real_name()) + " added to warned "+
        "list for killing "+this_object()->query_real_name()+"\n");
    }
   else
    {
        MJOIN->add_not_allowed(killer->query_real_name());
        write_file(MERC_PUNISH_LOG, extract(ctime(time()), 4, 15) + " " +   
        capitalize(killer->query_real_name()) + " added to banished "+
        "list for killing "+this_object()->query_real_name()+"\n");
    }
}