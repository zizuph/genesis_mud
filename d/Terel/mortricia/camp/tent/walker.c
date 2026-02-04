/*
  A tight-rope dancer. Mortricia 920927
    
    Modified: 28 Apr 2003 by Bleys
        - She's a "slender" dancer but her height and width defaulted
            to "short" and "fat." I've specified "tall" and "lean."
 */
inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()

#define ALIGN           100
#define CAMP_DIR        MORTRICIADIR + "camp/"
#define WEP_DIR         MORTRICIADIR + "weapons/"

void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("dancer");
    set_living_name("dancer");
    set_short("slender dancer");
    set_long(BSN(
        "It's a slender tight-rope dancer."
        ));
    set_adj("slender");
    set_height_desc("tall");
    set_width_desc("lean");
    set_gender(1);
    set_race_name("human");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_stats(({12,12,12,20,30,50}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN);
 
    set_skill(SS_UNARM_COMBAT, 10);
    set_skill(SS_WEP_POLEARM,  50);
    set_skill(SS_ACROBAT,  50);

    set_all_hitloc_unarmed(10);
    set_all_attack_unarmed(10, 10);

    set_act_time(10);
    add_act(({"northwest",
	      "dance",
	      "northwest",
	      "southeast",
	      "dance",
	      "southeast"}));

    seq_new("do_first");
    seq_addfirst("do_first", "@@dress_me");
}

dress_me()
{
    object rod;

    seteuid(getuid(TO));
    rod = clone_object(WEP_DIR + "rod");
    rod -> move(TO);
    command("wield rod");
}
