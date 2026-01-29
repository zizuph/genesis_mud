inherit "/d/Gondor/pelargir/npc/pelargir_npc";

#include <ss_types.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_pelargir_npc()
{
    int     rnd1 = random(21),
            rnd2 = random(21);

   set_name(({"sailor","man"}));
   set_race_name("human"); 
   set_short("sailor");
   set_pshort("sailors");
   set_long(BSN("A swaggering sailor of the type often found in "+
      "Pelargir."));
   set_stats(({15 + rnd1, 15 + rnd2, 15 + (rnd1 + rnd2) / 2,
               20 + rnd2 / 2, 20 + rnd1 / 2, 5 + rnd1 + rnd2}));

   set_alignment(150);
   set_skill(SS_WEP_KNIFE,20 + rnd2);
   set_skill(SS_DEFENCE,  20 + rnd1);
   set_skill(SS_PARRY,    20 + (rnd1 + rnd2) / 2);
   set_skill(SS_AWARENESS,10 + rnd1/2 + rnd2);
   set_chat_time(30);
   add_chat("Ahh! The fresh sea air!");
   add_chat("This is my favorite port!");
   add_chat("One day I'll captain my own ship!");
   add_chat("Arg matey!");
   add_chat("Ahoy, land lubber!");
   add_chat("A bottle of rum and a fresh sea breeze, that is living!");
   add_chat("I love this town.");
}
   
void
arm_me()
{
   FIX_EUID
   clone_object(WEP_DIR + "knife")->move(TO);
   command("wield knife");
   
   clone_object(MINAS_DIR + "obj/ltunic")->move(TO);
   
   clone_object(MINAS_DIR + "obj/ctrousers")->move(TO);
   command("wear all");
}

