/* Changed alignment to -50
 * 10 seemed rather odd for an orphan who is on the path to 
 * a evil life
 * Damaris 2/002
 */
inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("orphan");
    set_race_name("human");
    set_adj("scraggly");
    add_adj("little");
    set_long("A pitiful youth whose only foreseeable future is a life of "+
      "debauchery and excess as either a press gang member or a sailor of "+
      "the Kaladian Sea.\n");
    default_config_npc(20);
    set_skill(SS_AWARENESS,15);
    set_skill(SS_PICK_POCKET,15);
    set_alignment(-50);
    set_knight_prestige(-1);
    set_random_move(10);
    set_act_time(6);
    add_act("peek all");
    add_act("grin .");
    add_act("emote fidgets.");
    add_act("emote glances around warily.");
    add_act("smile inn");
    add_prop(LIVE_I_NEVERKNOWN,1);
    MONEY_MAKE_CC(random(25))->move(TO,1);
}
