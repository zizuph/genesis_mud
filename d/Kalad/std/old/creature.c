/*
   kcreature.c
   
   New Kalad standard monster,
   includes and speaking.
   
   Fysix@Genesis, Nov 1997
 */
#pragma strict_types
#pragma save_binary

inherit "/d/Kalad/std/bcreature";
inherit "/d/Kalad/lib/speak";

void
init_living()
{
    ::init_living();
    init_speak();
}

// --- Obsolete ---

// Changed add_speak to set_speak
void add_speak(string s)
{
    set_speak(s);
}

void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
        return;

    if (member_array(friend, (object*)query_team_others()) >= 0)
        set_alarm(1.0, 0.0, "help_friend", attacker);
}

