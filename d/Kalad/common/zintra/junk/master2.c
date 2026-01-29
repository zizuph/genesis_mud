/* master2.c */

inherit "std/monster";
inherit "/d/Kalad/lib/intro";
#include <ss_types.h>
#include <stdproperties.h>
#include "../defs.h"

void
create_monster()
{
    set_name("dangar");
    add_name(({"master", "thief", "man"}));
    set_race_name("human");
    set_adj("swift");
    add_adj("well-built");
    set_long( BS("This is another powerful member of the Blackhands.  His " +
"job is to teach new members how not to get caught while thieving.  He " +
"knows quite a large number of skills and tricks.  Perhaps you could " +
"<learn> something from this man.  Or, maybe you could ask him to help " +
"you <improve> an existing skill.  You could also ask him to <hypno>tize " +
"you to help with your learning preferences.\n"));

    default_config_mobile(200);

    set_act_time(30);
    add_act("emote practices his fencing.");
    add_act("emote takes a weapon from the rack, and starts to polish it.");
    add_act("smile");

    set_chat_time(20);
    add_chat("I'm bored with this job.  Maybe I'll return to thieving.");
    add_chat("The Blackhands are getting soft these days!");
    add_chat("You look new here.  Is there something I could teach you?");

    add_prop(OBJ_I_NO_ATTACK, 1);
}

string
query_title()
{
    return "the Master-trainer of the Blackhands";
}

