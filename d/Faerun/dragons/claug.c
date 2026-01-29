/* Claugiyliamatar, the Green Dragon of Kryptgarden.
 * Based on the dragons from Krynn
 * -- Finwe, August 2007
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

inherit FAERUN_DRAGON;
inherit KILL_LOGGER;
inherit "/std/act/attack";
inherit "/std/act/action";


void
create_dragon_npc()
{
    ::create_dragon_npc();
    set_name("claugiyliamatar");
    set_age("aged");
    add_name("green");
    add_name("claugiyliamatar");
    set_gender(G_FEMALE);
    set_colour("green");
    set_long("Before you is a tall, green dragon. This is Claugiyliamatar, " +
        "the ancient dragon of Kryptgarden. She is huge and towers over " +
        "you. Her head is covered with hornlets. She has a long neck " +
        "and legs, and large wings. Her four paws with claws, and spikes " +
        "run from the base of the head down to the tail. Most frightening " +
        "of all are its eyes, orbs of golden green slashed by vertical " +
        "pupils and bright with a cold, alien intelligence.\n");

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_SEE_DARK, 1);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 99);
    set_act_time(4);
    add_act("emote waves its long, slender tail back and forth.");
    add_act("emote watches you carefully with an evil gleam in her eyes.");
    add_act("emote flexes its enormous batlike wings in the air.");
    add_act("emote hisses dangerously at you.");
    add_act("emote stares intensely at you.");
    add_act("say Have you come to join me?");
    add_act("say There are many who have fallen under my spell.");


    set_cact_time(5);
    add_cact("emote looks at you with cold hatred in its eyes.");
    add_cact("emote opens its terrible maw and lets out a " +
      "terrifying roar!");
    add_cact("grin");

    make_gems(TP,5);
//    set_aggressive(1);
    set_kill_log_name("dragons");

}

