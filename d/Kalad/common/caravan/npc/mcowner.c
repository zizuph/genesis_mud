#include "default.h"

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

#define DO_I_TELL_RUMOURS  "_do_i_tell_rumours"

void
create_kalad_monster()
{
    add_prop(DO_I_TELL_RUMOURS, 1);
    set_name("turale");
    add_name("wizard");
    set_race_name("human");
    set_adj("weathered");
    add_adj("red-faced");
    set_long("This must be the famous money-changer himself, Turale "+
      "Arcflame. You can't quite tell what age he is, but you get the "+
      "impression he has experienced far more things than you have.\n");
    set_stats(({90, 100, 90, 150, 125, 90}));
    set_alignment(50);
    set_skill(SS_AWARENESS, 100);
    set_title("Arcflame, the retired Wizard");
    set_act_time(3);
    add_act("say I was once a great and powerful wizard, but nothing prepared "+
      "me for the tax man.");
    add_act("say I'm so glad to have survived the wrath of taxation.");
    add_act("say You had best pay your taxes. I failed to pay mine once and "+
      "you just don't want to know what vile things they did to me.");
    add_act("think the old days.");
    add_act("emote mumbles some strange words.");
    add_act("sigh");
    add_speak("Just change your money and leave.\n");
    set_knight_prestige(-50);
    add_prop(OBJ_M_NO_ATTACK, "This man was once known to have slain an entire "+
      "army with but one of his spells...you do not think it would be wise to "+
      "arouse his ire. Wisely, you decide not to attack.\n");
}
