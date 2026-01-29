#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
inherit "/d/Krynn/std/dragon_base";
inherit "/std/act/attack";
inherit "/std/act/action";
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

#define PLAYER_I_HELPED_DRAGON  "_player_i_aided_dragon"

void
create_dragon_npc()
{
    ::create_dragon_npc();
    set_adj("wounded"); 
    set_age("young");
    set_colour("red");
    add_name("firestar");
    set_gender(G_FEMALE);
    set_short("wounded young red dragon");
    set_long("Before you lies a young winged " +
      "dragon. Twenty feet in length from snout to tail tip, " +
      "darkly beautiful and exceedingly graceful, it is far from " +
      "the hulking and ponderous monster you had visualised " +
      "from fairy tales. Normaly dragons would "+
      "attack anyone at site, however this one is passive. You "+
      "can hear it's troubled deep breath, echoing through the "+
      "forest. Looking closer you notice a big gash on the side of "+
      "it's chest.\n");
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_act_time(10);
    add_act("emote deep breath echoes through the forest.");
    add_act("emote carefully licks it's lethal wound.");
    add_act("emote growls slightly.");
}


int
special_attack(object enemy)
{
    int     attacktype,
    pen,
    att,
    wloc;

    mixed hitres;

    string *hitloc,
    *attack,
    how,
    weapon;

    enemy->catch_msg(QCTNAME(TO) + 
        " suddenly folds out her great wings, and with the "+
        "last of it's energy it flies away.\n",({enemy, TO}));
        remove_object();
    return 1;

    return 0;
}