/* This file is /d/Gondor/rohan/npc/westfoldorc.c         */
/*                                                     */
/* This orc will attack anyone attacking a member      */
/* of his team                                         */
/* copied in parts from /doc/examples/mobiles/troll.c  */

inherit "/d/Gondor/common/npc/std_orc";
#include <ss_types.h>

#include "/d/Gondor/defs.h"

create_monster()
{
    ::create_monster();

    set_long(BS("A most evil creature. He is big and strong, and he "
      + "looks at you with death in his eyes.\n"));
    default_config_npc(25+random(25));
    set_base_stat(SS_INT, 15+random(5));
    set_base_stat(SS_WIS, 15+random(5));
    set_base_stat(SS_DIS, 85+random(15));
    set_hp(5000);

    add_chat("It's dangerous on the plains!");
    add_chat("When the rohirrim find us, we're finished!");
    add_cchat("You'll be dead soon!");
    set_random_move(5);
    set_restrain_path(({
        ROH_DIR + "plains/j06",
        ROH_DIR + "plains/j07",
        ROH_DIR + "plains/j08",
        ROH_DIR + "plains/j09",
        ROH_DIR + "plains/j10",
        ROH_DIR + "plains/i07",
        ROH_DIR + "plains/i08",
        ROH_DIR + "plains/i09",
        ROH_DIR + "plains/i10"}));
    set_monster_home(({ROH_DIR + "plains/j06"}));
}

arm_me()
{
    object wep, arm;
    seteuid(getuid(TO));

  if(random(3))
  {
    wep = clone_object(WEP_DIR + "worcsword");
    arm = clone_object(ARM_DIR + "orcshield");
    arm->move(TO);
  }
  else wep = clone_object(WEP_DIR + "orcclub");

  wep->move(TO);
  command("wield all");

  arm = clone_object(ARM_DIR + "orcstlarm");
  arm->move(TO);
  command("wear all");

}
