/* Change the alignment to 100
 * From 500 which seemed kind of 
 * extreme for this NPC 
 * And removed the no attack prop
 * Damaris 2/2002
 */
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("gorumn");
    add_name("netweaver");
    set_race_name("human");
    set_adj("crabby");
    add_adj("old");
    set_long("An old man that looks like he's always having a bad day. "+
      "Even now he is looking at you grumbling about how terrible the "+
      "weather is or how horrible the world is.\n");
    set_stats(({60,60,50,90,90,55}));
    set_alignment(100);
    set_skill(SS_AWARENESS,100);
    set_title("the Netweaver");
    set_act_time(3);
    add_act("say Well, are you going to buy a net or just stand there gawking?!?");
    add_act("grumble");
    add_act("frown");
    add_act("say I hate this weather.");
    add_act("say I hate the world.");
    add_act("say Hurry up and buy something.");
    add_act("tap");
    add_speak("I wish you would stop speaking to me and just buy a net.\n");
    set_knight_prestige(-100);

}
