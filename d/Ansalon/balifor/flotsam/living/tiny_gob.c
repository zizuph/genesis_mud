#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE

void
create_krynn_monster()
{
   if (!IS_CLONE)
      return;
   
   set_name("goblin");
   set_race_name("goblin");
   set_adj("tiny");
   set_gender("G_MALE");
   set_long("This would be one of the smallest " +
      "goblins you have ever seen. Standing about " +
      "three feet tall, he does not seem very " +
      "intimidating. \n");
   set_stats(({11,8,13,5,5,8}));
   set_hp(10000);
   
   set_alignment(-20);
   set_knight_prestige(1);
   
   set_random_move(35);
   set_restrain_path(FROOM);
   
   set_skill(SS_WEP_KNIFE, 5);
   set_skill(SS_DEFENCE, 5);
   
   
   set_act_time(5);
   add_act("emote snarls SMeG OFF!");
   add_act("growl");
   add_act("emote mumbles Wat u SMegIN' at?");
   add_act("emote looks at you suspiciously.");
   
   seq_new("do_things");
   seq_addfirst("do_things","@@arm_me");
}

void
arm_me()
{
   seteuid(getuid(this_object()));
   clone_object(FOBJ + "weapon/g_knife")->move(TO,1);
   command("wield all");
}
