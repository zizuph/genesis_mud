public void
replace_sticks()
{
    object *a;
    int b;

    a = users();
    b = sizeof(a);
    while(b--)
    {
        if (a[b]->query_guild_name_race() != "Traveller guild")
            continue;
        present("_stickly_", a[b])->remove_object();
        clone_object("/d/Roke/varl/atuan/cape/guild/insignia")->move(a[b]);
        tell_object(a[b], "*** Quetzl tells you: I am replacing all sticks " +
            "right now for the new commands. Examine your sticks, and if you have any questions, you can reply to me. ***\n");
        a[b]->add_prop("_reply_wizard", "quetzl");
    }
}
