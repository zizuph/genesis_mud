#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/solace/graves/local.h"
#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/common/defs.h"

inherit M_FILE

void
create_krynn_monster()
{
    set_name("skeletal guard");
    set_living_name("skeletal guard");
    set_title("guard");
    set_race_name("guard");
    set_long("The guard looks a bit skinny.\n");
    set_short("skeletal guard");
    set_adj("skeletal");
    
    default_config_npc(15);
    
    set_hp(10000);
    
    set_alignment(140);
    
    set_skill(SS_DEFENCE, 25);
    set_skill(SS_AWARENESS, 40);
    set_skill(SS_WEP_KNIFE, 45);
    
    add_act("emote shouts: CHEAT!");
    add_act("emote shouts: FRAUD!");
    add_act("emote takes his companion's head off.");
    
    set_act_time(1);
    set_chat_time(2);
    add_prop(LIVE_I_NO_CORPSE, 1);
    set_default_answer("Piss off!\n");
    
    add_ask(({"dice",}),"Guard shouts: He cheated!\n");
    add_ask(({"prison","cell","cells"}),"Guard says: We used to guard them until HE got us killed!\n");
    add_ask(({"key","keys"}),"Guard says: They got lost in the fight, but they must be in here somewhere.\n");
    
}

void
do_die(object killer)
{
    object ob = clone_object("/std/leftover");
    ob->leftover_init("bone","human");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("skull","human");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("bone","human");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("rib","human");
    ob->move(E(TO));
    ob = clone_object("/std/leftover");
    ob->leftover_init("rib","human");
    ob->move(E(TO));
    ::do_die(killer);
}
