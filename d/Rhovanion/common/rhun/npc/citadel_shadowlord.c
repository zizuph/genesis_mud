
inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"
#include "/d/Rhovanion/common/rhun/sw/s_s/sw_ent_quest.h"

/* Global object for coin, since it is cloned in one func
 * and moved in another.
 */
 object ob;

create_monster() {
set_race_name("shadowlord");
set_adj("dark");
add_adj("silent");
add_adj("frightening");
set_name("shadowlord");
add_name("_citadel_shadowlord");

set_alignment(-995);
set_gender(2);
   set_long(break_string(
        "This shadowlord stands menacingly, dark and silent.  Somehow, "+
        "being near it chills you to the bone.\n",75));
add_prop(CONT_I_WEIGHT, 70*1000);
add_prop(CONT_I_VOLUME, 70*1000);
add_prop(CONT_I_HEIGHT, 168);
add_prop(NPC_M_NO_ACCEPT_GIVE,0);
set_stats(({90,90,90,80,80,100}));
set_hp(query_max_hp());


set_skill(SS_UNARM_COMBAT, 90);
set_skill(SS_DEFENCE, 90);
   set_pick_up(43);


SGT
ob=clone_object(RHUN+"npc/obsidian_coin");
ob->move(this_object(), 1);

}


enter_inv(object obj, object from)
{
    if (!from) return;
    ::enter_inv(obj,from);
    if(obj==present("_sw_ent_quest_rhosgobel_gemstone"))
    {
    command("say The gemstone.  Excellent.  Allow me to reward you.");
    write("The shadowlord passes an obsidian coin to you.\n");
	ob->move(from);
    TP->add_prop(I_DID_NOT_KILL_SHADOW_GUY,1);
    }

    else
    {
      command("say What is this?  I don't want this.");
    command("say I want the gemstone.  Bring it to me!");
    write("The shadowlord returns it forcefully to you.\n");
      obj->move(from);
      return 1;
    }
}
