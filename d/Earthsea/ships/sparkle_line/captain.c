/* corrected typo - Amelia 6-26-98 */
#pragma strict_types

inherit "/d/Genesis/ship/captain";
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
#define TICKET SPARK_LINE + "ticket"


object ship;

void
set_ship(object s)
{
    ship=s;
}

void
create_captain()
{
    set_name("yorlis");
    add_name("captain");
    add_name("_yorlis_");
    add_name("wizard");
    set_adj(({"tall", "grey-haired", "sea" }));
    set_race_name("wizard");
    set_long("The captain is a tall grey-haired "+
      "Gontish man. From the staff he is carrying you deduce that "+
      "he is a wizard.\nHe is wearing a midnight-blue hooded robe.\n"+
      "He is wielding a long yew staff.\n");
    set_ticket(TICKET);
    add_prop(OBJ_M_NO_ATTACK, "You feel this man is "+
      "protected by the gods of Earthsea.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "The spell falls "+
      "harmlessly on thin air.\n");
    set_chat_time(45);
    set_act_time(45);
    add_act("emote looks to sea with a weather eye.");
    add_act("emote mutters a spell of binding to hold the "+
      "ship together.");

    set_living_name("_GONT_SPARKLE_CAPTAIN_");
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
    object tp;

    ::add_introduced(str);
    if (stringp(str))
        if (tp = present(str, environment(this_object())) &&
          interactive(tp))
        {
            set_alarm(2.0, -1.0, &intro_hook(str));
        }
    return;
}
