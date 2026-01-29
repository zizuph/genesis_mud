#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/balifor/flotsam/local.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE

#define ARM TEMP + "obj/"
#define ARM1 ARM + "robe"
#define ARM2 ARM + "sk_helmet"
#define WEP ARM + "sickle"

void
create_krynn_monster()
{
   if(!IS_CLONE)
      return;
   
   set_name("acolyte");
   set_adj("masked");
   set_race_name("human");
   set_gender("G_MALE");
   set_short("masked acolyte");
   set_long("This masked humanoid is an acolyte, the lowliest member " +
      "of the unholy order of Chemosh, Lord of Death.\n");
   
   set_stats(({50,45,55,40,60,40}));
   set_hp(10000);
   
   set_alignment(-500);
   set_knight_prestige(200);
   set_skill(SS_WEP_KNIFE, 55);
   set_skill(SS_DEFENCE, 35);
   set_skill(SS_PARRY, 35);
   
   set_act_time(5);
   add_act("emote mumbles a prayer to the Lord of Death.");
   add_act("emote says in a hollow voice: What are you doing here?");
   
   set_cact_time(5);
   add_cact("emote calls upon the powers of Chemosh. \n" +
      "You are blasted by an unholy energy! \n" +
      "You feel yourself mentally drained.");
   add_cact("say Defilers! Leave this temple!");
   add_cact("say Chemosh! Hear my prayers!");
   
}

void
arm_me()
{
   seteuid(getuid(TO));
   clone_object(WEP)->move(TO,1);
   command("wield all");
   clone_object(ARM1)->move(TO,1);
   clone_object(ARM2)->move(TO,1);
   command("wear all");
}
