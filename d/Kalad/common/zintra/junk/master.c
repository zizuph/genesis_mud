/* master.c */

inherit "std/monster";
inherit "/d/Kalad/lib/intro";
#include <ss_types.h>
#include <stdproperties.h>
#include "../defs.h"

void
create_monster()
{
    set_name("stragar");
    add_name(({"master", "thief", "man"}));
    set_race_name("human");
    set_adj("old");
    add_adj("gnarled");
    set_long( break_string (
"Even though this man is ancient, there is something about him...  He is a " +
"master thief, and leader of the Blackhands.  This man has forgotten more " +
"dirty tricks than you will ever learn.  But now, he holds an administrative" +
" position with the guild, and has retired from thievery.  Still, he knows " +
"quite a bit about the world.  Maybe you could ask him for more 'info?'\n",
        78));
    default_config_mobile(200);

    set_act_time(20);
    add_act("emote polishes a plaque on his desk.");
    add_act("yawn");
    add_act("sigh");

    set_chat_time(20);
    add_chat("I'm bored with this job.  Maybe I'll return to thieving.");
    add_chat("The Blackhands are getting soft these days!");
    add_chat("I love Kalad!  The murders, the robbberies!   " +
        "Anarchy, I love it!");

    add_ask(({"about info", "info"}), 
"I can provide additional information of the following subjects.\n" + "\n" +
"     info                    - This list.\n"+
"     guild info              - Information about the Blackhands guild.\n" +
"     features                - Features of the guild.\n" +
"     skills                  - Skills the guild will provide.\n" + "\n" +
"If you decide you'd like to join, type 'join guild' in this room.\n" + "\n" +
"Warning:  If you don't join, leave the guild hall, or face the " +
"consequences.\n");

    add_prop(OBJ_I_NO_ATTACK, 1);
}

string
query_title()
{
    return "the Master-thief of the Blackhands";
  
}



