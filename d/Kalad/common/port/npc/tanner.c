/* Changed the alignment to 150
 * 750 seems rather extreme for this NPC
 * Also removed the no_kill prop
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
    set_name("telbruin");
    add_name("tanner");
    set_race_name("human");
    set_adj("young");
    add_adj("friendly");
    set_long("A cheerful young man that stands behind the wooden counter. "+
      "The heavy odor of leather hangs about him so you assume he must "+
      "be the tanner, owner of this quaint little shop.\n");
    set_stats(({30,30,40,45,45,30}));
    set_alignment(750);
    set_skill(SS_AWARENESS,100);
    set_title("the Tanner");
    set_act_time(3);
    add_act("smile cheer");
    add_act("say Hello there!");
    add_act("say I've got some fine leather goods for you to buy.");
    add_act("smile");
    add_act("say My, what lovely weather we're having today!");
    add_act("say Hey, are you new around here? If so, you should buy "+
      "some of my goods!");
    add_speak("I've got the finest quality leather goods in the district, "+
      "if not in the entire city!\n");
    set_knight_prestige(-100);

}
