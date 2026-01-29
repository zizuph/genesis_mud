/* An Odic(part 1), by Sarr */
// 2010/06/14 Last update
// 2011/08/09 Lavellan - Fixed attacked_by to not runtime.
/* 2017-08-19 Malus: Added set_mm_in, moving defaults to base/std file,
 * and added unarmed combat (even though it shouldn't be fighting much) */

#include "defs.h"
inherit STD_UNDEAD;
inherit "/std/combat/unarmed";

void
create_monster()
{
    ::create_monster();
    set_name("odic");
    set_race_name("mist");
    set_adj("purple");
    set_short("purple mist");
    add_prop(LIVE_I_UNDEAD, 50);
    set_long(
      "A strange purple mist that just seems to be floating in mid air.\nYet " +
      "you get a strange feeling about it. You sense something evil.\n");
    set_mm_in("seeps in out of the trees!");
    set_hitloc_unarmed(0, 0, 100, "center");
}

void
attacked_by(object ob)
{
    ob->stop_fight(TO);
    TO->stop_fight(ob);
    if (random(2))
    {
        tell_room(environment(),
          "The purple mist floats off into a nearby tree and possess it!\n");
        tell_room(environment(), "The tree starts to glow purple!\n");
        clone_object(COMMON_NPC_DIR + "odic2")->move_living("M", E(TO));
        tell_room(
          environment(), "The glowing tree rips itself out of the ground!\n");
    }
    else
    {
        tell_room(environment(),
          "The purple mist floats off into a nearby plant and possess it!\n");
        tell_room(environment(), "The vine-plant starts to glow purple!\n");
        clone_object(COMMON_NPC_DIR + "odic3")->move_living("M", E(TO));
        tell_room(environment(),
          "The glowing vine-plant rips itself out of the ground!\n");
    }
    remove_object();
}
