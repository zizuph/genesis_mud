#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>

#define A_BUTT 0
#define A_LHORN 1
#define A_RHORN 2
#define H_HEAD 0
#define H_BODY 1

public void
create_creature()
{
    set_name("goat");
    set_race_name("goat");
    set_short("long-haired horned goat");
    set_pshort("long-haired horned goats");
    set_adj(({"horned", "long-haired"}));
    add_adj("white");
    set_long("A white long-haired horned goat. He looks "+
        "at you with a very stupid expression. He has "+
        "a goatee on his chin.\n");
    set_stats(({10, 10, 10, 5, 5, 35 }));
    set_skill(SS_DEFENCE, 15);
    set_skill(SS_UNARM_COMBAT, 25);
    add_leftover("/d/Earthsea/gont/tenalders/wep/goat_horn", "horn", 2, 1, 1, 0);
    add_leftover("/d/Earthsea/gont/tenalders/obj/items/goatskin", "skin", 1, 1, 1, 0);
    set_attack_unarmed(A_BUTT, 10, 20, W_BLUDGEON, 20, "head");
    set_attack_unarmed(A_LHORN, 10, 20, W_IMPALE, 40, "left horn");
    set_attack_unarmed(A_RHORN, 10, 20, W_IMPALE, 40, "right horn");
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");
    set_act_time(80);
    add_act("emote looks at you stupidly.");
    add_act("emote goes, Beh!!");
    add_act("emote munches on some greenery.");
    add_act("emote tries to butt you from behind.");
    add_act("bounce");
    add_act("bounce");
}
