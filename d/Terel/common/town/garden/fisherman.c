/* Old Fisherman by Mecien  July 92 */
// Looking into making a member of the Krynn fisherman's club
// /d/Krynn/clubs/fishing
//  -- Lilith Mar 2022

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#define TGARDEN "/d/Terel/common/town/garden/"
#define ROD    TGARDEN + "rod"
#define HAT    TGARDEN + "hat"
#define TUNIC  TGARDEN + "tunic"

public void
create_monster()
{
   set_name("gwyvin");
   add_name("fisherman");
   add_name("human");
   add_name("man");
   add_adj("old");
   
   set_race_name("human");
   set_title("the old fisherman");
   set_long("He is very old. His face is wrinkled and he has a short " +
            "white beard. His eyes are deep blue.\n");

   set_stats(({ 40, 45, 30, 20, 20, 20}));
   set_alignment(123);
   set_skill(SS_DEFENCE, 30);
   set_skill(SS_SPELLCRAFT, 10);
   set_skill(SS_SWIM, 70);
   set_hp(9000);
   set_mana(9000);

   set_all_attack_unarmed(22, 22);
   set_all_hitloc_unarmed(20);
   
   enable_intro();

   set_act_time(5);
   add_act("@@cast");
   add_act("smile");
   add_act("ponder");
   add_act("@@pole_in");
   add_act("cough");
   add_act("@@catch_fish");

   set_chat_time(5);
   add_chat("Hello there...");
   add_chat("I fish here every day.");
   add_chat("Long time ago I caught a very large pike!\n" +
      "He got away from me though...\n" +
      "I call him Trickster, cause he is so clever!\n" +
      "He lives under the bridge now.");
   add_chat("The fish in the river are very good.");
   add_chat("Are you a minstrel?");

   add_weapon(ROD);
   add_armour(HAT);   
   add_armour(TUNIC);
}


public string
pole_in()
{
    return "emote reels his fishing pole in, but has nothing.";
}

public string
cast()
{
    return "emote casts his line out into the icy waters.";
}

public string
catch_fish()
{
    return "emote reels in a fish. But he shakes his head and " +
           "throws it back.";
}

