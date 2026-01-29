inherit "/std/object";

gnome_speak(string str)
{
	string *translated;
	translated = implode(explode(str, " "));
}

void
clone_paralyze(string fail_msg, int time)
{
    object paralyze;
    seteuid(getuid(TO));
    paralyze = clone_object("/std/paralyze");
    paralyze->set_name("_used_check_");
    paralyze->set_no_show(1);
    paralyze->set_remove_time(time);
    paralyze->set_stop_message("");
    paralyze->set_fail_message(fail_msg);
    paralyze->set_stop_verb("depart"); /* No command to stop the paralyze! */
    paralyze->set_stop_object(0);   /* Use the messages set above */
    paralyze->move(TP);       /* Now DO the paralyze */
}

void
clone_heap(object who)
{
    seteuid(getuid(TO));
    clone_object("/d/Krynn/gnome/guild/obj/heap_of_parts")->move(environment(who));
}
