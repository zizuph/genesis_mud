/* Dragon by percy*/
/* modified by Stevenson to be a White Dragon for Icewall */
/* modified by Teth, to use the Krynn/std/dragon_base and also placed in the
   common dir, Feb 1997 */

#include "/d/Krynn/common/defs.h"

inherit DRAGONBASE

void
create_dragon_npc()
{
    set_name("sleet");
    set_living_name("sleet");
    set_title("the White Dragon of the Highlord Feal-thas");

    set_colour("white");
    set_age("adult");

    set_introduce(1);

    set_knight_prestige(1000);

    set_gender(1);
    set_long("This adult white dragon is slim and vicious. She has " +
      "a menacing look, and wouldn't back down from a fight. Her entire " +
      "body is covered with white scales. The cold environment seems " +
      "perfectly suited to her.\n");

    CUTLEFTOVER("tooth");
    CUTLEFTOVER("tooth");
    LEFTOVER("claw");

    set_act_time(4);
    add_act("emote hisses dangerously.");
    add_act("emote stares at you with a mix of hatred and bewilderment.");
    add_act("emote snarls viciously.");
    add_act("emote coils her neck back, then stares northwards.");
    add_act("emote screeches loudly!");
    add_act("emote stretches out her wings.");

    add_prop(CONT_I_VOLUME, 5679000);
    add_prop(CONT_I_WEIGHT, 5784000);
}


public int
second_life(object killer)
{
    K_KILL_LOG("kills", "Sleet", killer);
    return 0;
}
