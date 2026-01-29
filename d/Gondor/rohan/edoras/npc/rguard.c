inherit "/d/Gondor/rohan/edoras/npc/edoras_soldier";
inherit "/d/Gondor/common/lib/logkill";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_guard()
{
    ::create_guard();
    set_alignment(650 + random(150));
    set_skill(SS_2H_COMBAT,60);
    set_skill(SS_UNARM_COMBAT,60);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_default_answer("@@my_command:" + file_name(TO) + "|say I do not understand you.@@");
    add_ask("theoden", "@@my_command:" + file_name(TO) + "|say Theoden, Thengel's son, is King in Edoras and First Marshal of the Mark!@@");
    add_ask("harding",VBFC_ME("ask_harding"));
    add_ask(({"job","task","quest"}), "@@my_command:" + file_name(TO) + "|say I am just a simple soldier. I do not command. Go and ask Elfhelm!@@");
    add_ask("elfhelm", "@@my_command:" + file_name(TO) + "|say If he is not leading his Eored on the plains, he is in his office in the barracks.@@");
}

string
my_command(string x)
{
    command(x);
    return "";
}

string
ask_harding()
{
    (EDORAS_DIR + "guard_e")->load_me();
    if(present("harding",find_object(EDORAS_DIR + "guard_e")))
    {
        command("say Harding? Oh yes, he came back from the patrol "
          + "just an hour ago.");
        command("say He was dead tired. Hadn't slept for two days.");
        command("say He is resting right over there in the "
          + "guardroom.");
        command("emote points east.");
    }
    else
    {
        command("say Harding? I do not know where he is.");
        command("say Either he is off duty, or he is on patrol!");
        command("say I do not think you will find him here.");
    }
    return "";
}

/* Solemnian prestige */
query_knight_prestige() {return (-6);}
