inherit "/d/Gondor/pelargir/npc/pelargir_npc";

#include <ss_types.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_pelargir_npc()
{
    int     rnd1 = random(21),
            rnd2 = random(21);

    set_name(({"swashbuckler","sailor","man"}));
    set_race_name("human"); 
    set_short("swashbuckler");
    set_pshort("swashbucklers");
    set_long("A swaggering sailor of the type often found in Pelargir.\n");
    set_stats(({30 + rnd1, 30 + rnd2, 30 + (rnd1 + rnd2) / 2,
                20 + rnd1 / 2, 20 + rnd2 / 2, 5 + rnd1 + rnd2}));

    set_alignment(50);
    set_skill(SS_WEP_KNIFE, 20 + rnd1);
    set_skill(SS_WEP_SWORD, 40 + rnd2);
    set_skill(SS_DEFENCE,   20 + rnd1);
    set_skill(SS_PARRY,     30 + rnd2);
    set_skill(SS_AWARENESS, 20 + rnd1);
    set_chat_time(30);
    add_chat("Ahh! The fresh sea air!");
    add_chat("I live by the blade and the sea.");
    add_chat("You aren't a sailor? Disgusting!");
    add_chat("This is my favorite port!");
    add_chat("One day I'll captain my own ship!");
    add_chat("Arg matey!");
    add_chat("Ahoy, land lubber!");
    add_chat("A bottle of rum and a fresh sea breeze, that is living!");
}

void
arm_me()
{
    FIX_EUID
    clone_object(PELAR_DIR + "obj/swbrapier")->move(TO);
    command("wield sword");

    clone_object(MINAS_DIR + "obj/ltunic")->move(TO);
    command("wear all");

    clone_object(MINAS_DIR + "obj/ctrousers")->move(TO);
    command("wear all");
}

