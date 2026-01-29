inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
 
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "defs.h"
 
#define A_CLAWS 0
#define A_TEETH 1
 
#define H_HEAD 0
#define H_BODY 1
 
void
create_creature()
{
    set_name(({"large timberwolf","large wolf","timberwolf","wolf"}));
    set_short("large timberwolf");
    set_pshort("large timberwolves");
    set_race_name("timberwolf");
    set_adj(({"large","dark"}));
    set_long(BS(
        "He is a rather large timberwolf with a shaggy dark coat and " +
        "sharp teeth. His mysterious yellow eyes seem to portrude evil " +
        "into your soul.\n"));
 
    set_alignment(-300);
    set_stats(({ 30, 30, 30, 30, 30, 30}));
 
    set_hp(8000);
 
    set_skill(SS_DEFENCE, 30);
 
    set_attack_unarmed(A_CLAWS, 30, 30, W_SLASH, 10, "claws");
    set_attack_unarmed(A_TEETH, 30, 30, W_SLASH, 10, "sharp teeth");
 
    set_hitloc_unarmed(H_HEAD, ({30, 30, 30, 30 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({30, 30, 30, 30 }), 80, "body");
 
    set_act_time(10);
    add_act("emote glares at you with his evil yellow eyes.");
    add_act("emote howls into the forest.");
    add_act("crawl through branches");
}
