/* knight.c */

inherit "std/monster";
inherit "/d/Kalad/lib/intro";
#include <ss_types.h>
#include <stdproperties.h>
#include "../defs.h"


void
create_monster()
{
    set_name("bosco");
    add_name("knight");
    set_race_name("human");
    set_adj("old");
    add_adj("weak");
    set_long( break_string (
"He is a very sorry sight.  A once proud Knight of the Rose, now shackled" +
"to the wall.  He was captured long ago, and is now here for your" +
"pleasure.  Enjoy!\n", 78));
    default_config_mobile(15);

    set_act_time(20);
    add_act("emote makes a strange gurgling noise.");
    add_act("moan");
    add_act("emote whimpers in pain.");
    add_act(({"emote dies.", "emote snores loudly.", "echo Oops, false " +
        "alarm.  He was only sleeping."})); 

    set_chat_time(20);
    add_chat("I miss my family.");
    add_chat("Are you a kind person, or are you going to torture me?");
    add_chat("Wait until Cindy hears about this!");
    add_chat("I never should have come to Kalad.  This place is dangerous.");

    add_prop(OBJ_I_NO_ATTACK, 1);
}

string
query_title()
{
    return "the Knight of the Rose";
  
}

public void
introduce_me(string who)
{
    command("introduce myself");
    command("say I'd shake your hand, but I'm a little tied up, right now.");
    command("giggle");
}
