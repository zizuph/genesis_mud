/* corrected typo - Amelia 6-26-98 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include "/sys/filter_funs.h"
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit "/d/Earthsea/lib/remember";
inherit STDCAPTAIN;

void
create_captain()
{
  ::create_captain();
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
    setuid();
    seteuid(getuid());

    set_hp(50000);

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
