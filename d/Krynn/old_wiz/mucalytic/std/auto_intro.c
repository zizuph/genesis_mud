// File: auto_intro.c
// Creator: Zork

auto_introduce(string who)
{
    if (present(who,environment()))
	command("introduce me to "+who);
}

init_living()
{
    object who;

    who = this_player();

    if (!who->query_npc())
	if (!who->query_met(this_object()))
    	    set_alarm(2.0,0.0,"auto_introduce",who->query_real_name());
}
