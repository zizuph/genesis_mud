// file name:   /d/Avenir/common/outpost/mon/intro_new.c
// creator(s):  Denis, Jul'96
// last update: 
// purpose: 	provides a good intro_me() for all npc's
// note:	based on old /d/Avenir/common/outpost/intro.c by Kazz
//		(Will we ever see him again?)
// bug(s):	
// to-do:	

# pragma strict_types
# pragma no_clone

public void add_introduced(string s_who)
{
    object o_who = find_player(s_who);

    if(o_who &&
       !o_who->query_met(this_object()))
        set_alarm(itof(random(5) + 1), 0.0, "command",
		  "introduce myself to " + s_who);
}
