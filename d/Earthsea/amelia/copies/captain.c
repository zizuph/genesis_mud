#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit  "/d/Earthsea/lib/width_height";
inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include "/sys/filter_funs.h"
#include "defs.h"
#include "/d/Earthsea/quest_handler/quest_handler.h"

inherit REMEMBER;

#define PLAYER_NAME "_player_s_name"
#define NOTE CALIA_LINE + "focsles_note"
#define PLAYER_I_GOT_WEATHER_TOUR "_player_i_got_weather_tour"


#define TASK_ASK (({"task", "about task", "job", "about job",\
"help"}))

object ship;
object note;



    add_ask(TASK_ASK, VBFC_ME("assign_task"));



    {

string
assign_task()
{
    object tp = this_player();

    if (QH_QUERY_QUEST_COMPLETED(tp, "weather_worker_tour"))
    {
	command("ask "+ lower_case(tp->query_name()) + " " +
	  "Hmm...I think you have helped me before, but thanks "+
	  "just the same!");
	command("smile know");
	return "";
    }

    if (tp->query_prop(PLAYER_I_GOT_WEATHER_TOUR))
    {
	command("ask "+ lower_case(tp->query_name()) + " "+
	  "Did you manage to find her? She is in Ten Alders.");
	command("nod");
	return "";
    }
    tp->add_prop(PLAYER_I_GOT_WEATHER_TOUR, 1);
    command("ask "+ lower_case(tp->query_name()) + " "+
      "Hmm...I have a task for you, if you are brave enough. "+
      "The road to Ten Alders is none too safe these days! But I "+
      "need a message to be delivered to the wise woman there. "+
      "She might be able to help me find a weather worker...one of "+
      "the local ones, not as pricey as them wizards from the "+
      "Wizard School!");
    command("nod");
    command("ask "+ lower_case(tp->query_name()) + " " +
      "Deliver this to her, and there may be a small reward fer "+
      "ye!");
    setuid();
    seteuid(getuid());
    note = clone_object(NOTE);
note->add_prop(PLAYER_NAME, tp->query_real_name());
    tp->catch_msg(QCTNAME(this_object()) + " gives you a note.\n");
    command("wink");
    note->move(tp);
    return "";
}
