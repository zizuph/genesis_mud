/*
 * luder.c
 *
 * Used in nyreese/red_bordell.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <macros.h>
#include <ss_types.h>

void hejhej(object tp);

void
create_monster()
{
    set_race_name("lady");
    set_name("helena");
    add_name("lady");
    set_adj("beautiful");
    add_adj("young");
    set_living_name("helena");
    set_title("the most beautiful one");

    /* this monster is named after Gres' commanding officer in the
       Airforce (She is rather cute, but a real bitch.) */

    set_long("This is a beautiful young lady, always prepared to please you.\n");
    add_prop(NPC_I_NO_LOOKS, 1);
    set_gender(1);

    default_config_npc(45);

    ::create_monster();

    trig_new("%w 'smiles' %s", "fonfun");
    trig_new("%w 'kisses' 'you' %s", "kissfun");
    trig_new("%w 'tries' 'to' 'seduce' 'you.\n' %s", "sedfun");
    trig_new("%w 'fondles' 'you' %s", "fonfun");
    trig_new("%w 'whispers' 'sweet' 'words' %s", "sedfun");
    trig_new("%w 'hugs' 'you.\n' %s", "hugfun");
    trig_new("%w 'licks' 'you.\n' %s", "lickfun");
    trig_new("%w 'flirts' 'outrageously' 'with' 'you.\n' %s", "ffun");
    trig_new("%w 'gropes' 'you.\n' %s", "grfun");
    trig_new("%w 'winks' %s", "winkfun");
    trig_new("%w 'cuddles' 'you' %s", "cudfun");
    trig_new("%w 'snuggles' 'up' 'to' 'you.\n' %s", "snugfun");

    add_notify_meet_interactive("met");
}

void
met()
{
    set_alarm(1.0, 0.0, &hejhej(TP));
}

int
query_knight_prestige()
{
    return -2;
}

void
hejhej(object tp)
{
    if (tp->query_real_name() == "gresolle")
    {
        command("hug gresolle");
        command("say Hi my love!");
        command("kiss gresolle");
    }
}

void
snugfun(string s, string ss)
{
    set_alarm(1.0, 0.0, &command("blush"));
}

void
cudfun(string s, string ss)
{
    set_alarm(1.0, 0.0, &command("hug " + s));
}

void
winkfun(string s, string ss)
{
    set_alarm(1.0, 0.0, &command("wink " + s));
}

void
grfun(string s, string ss)
{
    set_alarm(1.0, 0.0, &command("groan"));
}

void
ffun(string ss, string s)
{
    set_alarm(1.0, 0.0, &command("blush"));
}

void
lickfun(string s, string ss)
{
    set_alarm(1.0, 0.0, &command("moan"));
}

void
hugfun(string s, string ss)
{
    set_alarm(1.0, 0.0, &command("fondle" + s));
}

void
kissfun(string s, string ss)
{
    set_alarm(1.0, 0.0, &command("love " + s));
}

void
fonfun(string s, string ss)
{
    set_alarm(1.0, 0.0, &command("smile " + s));
}

void
sedfun(string s, string ss)
{
    set_alarm(1.0, 0.0, &command("french " + s));
}
