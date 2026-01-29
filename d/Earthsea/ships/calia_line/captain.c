#pragma strict_types

inherit "/d/Genesis/ship/captain";
inherit  "/d/Earthsea/lib/width_height";
inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include "/sys/filter_funs.h"
#include "defs.h"

inherit REMEMBER;

#define NUM sizeof(MONEY_TYPES)
#define ENV(xx) environment(xx)
#define TICKET CALIA_LINE + "ticket"


#define TASK_ASK (({"task", "about task", "job", "about job",\
"help"}))

object ship;
string flirty();

void
set_ship(object s)
{
    ship=s;
}

void
create_captain()
{
    set_name("focsle");
    add_name("captain");
    add_name("seaman");
    set_adj(({"red-bearded", "old", "lusty"}));
    set_long(break_string("You see years of experience set in "+
        "the wrinkled lines of this old seaman. "+
        "Although his hair is white, his beard is still fiery red "+
        "and wiry. He seems to be in good shape and lively for "+
        "his age.\n", 70));

    add_prop(OBJ_M_NO_ATTACK, "You feel this man is "+
      "protected by the gods of Earthsea.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "The spell falls "+
      "harmlessly on thin air.\n");
    set_height("tall");
    set_width("normal");
    set_chat_time(45);
    set_act_time(45);
    add_chat("Aye, I have always had an eye for the ladies!");
    add_act("emote bursts into song, loudly and a little off-key:\n\n"+
      "     Yo ho and then she rises,\n"+
      "     Yo ho and then she rises,\n"+
      "     Yo ho and then she rises,\n"+
      "     Ear-ly in the morning!");
    add_act("wink");
    add_act(VBFC_ME("flirty"));



    set_living_name("_CALIAN_GONT_CAPTAIN");
    set_race_name("human");
    default_config_npc(60);
    set_skill(SS_SWIM,100);
    set_skill(SS_UNARM_COMBAT,45);
    set_skill(SS_DEFENCE,34);

    heal_hp(10000);
    set_hp(50000);


    set_alignment(200);

    config_default_trade();

    setuid();
    seteuid(getuid());

    trig_new("%w 'introduces' %s", "react_introduce");

    set_hp(50000);

    set_m_in("swaggers in with a rolling sea gait");

    set_ticket(TICKET);
    set_price(24);
    set_newbie_stats(25);

}


void
intro_hook(string str)
{
    command("introduce myself");
    command("bow");
}
void
add_introduced(string str)
{

    ::add_introduced(str);
    return;
}

string
flirty()
{
    object tp = this_player();
    int ran = random(3);

    if (tp->query_gender() == G_FEMALE)
    {
        switch(ran)
        {
        case 0:
            command("ask " + lower_case(tp->query_name()) + 
              " Come meet me tonight at the pub, I'll buy ye a brew!");
            command("flirt "+lower_case(tp->query_name()));
            break;

        case 1:
            command("admire "+ lower_case(tp->query_name()));
            command("say What a fine strapping lass!");
            command("say I like me women with a bit of flesh on them!");
            command("pinch "+ lower_case(tp->query_name()) + " bottom");
            command("grin");
            break;

        case 2:
            command("emote places his hand over his heart.");
            command("say I am in awe of such beauty!");
            command("worship "+ lower_case(tp->query_name()));
            break;

        default:
            break;
        }

    }

    return "";
}
