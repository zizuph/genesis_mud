/* A zombie. Mortricia 921001 */
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

#define BS(xxx)         break_string(xxx, 70)
#define BSN(xxx)        break_string(xxx + "\n", 70)
#define TP              this_player()
#define TO              this_object()
#define CAMP_DIR        MORTRICIADIR + "camp/"
#define HAUN_DIR        CAMP_DIR + "house/"
#define EQUIP_DIR       HAUN_DIR + "equip/"
#define H_CLONE(xxx)    clone_object(EQUIP_DIR + xxx) -> move(TO)

#define ALIGN           1200

void haunt(object who);

void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("zombie");
    set_short("frightful zombie");
    set_long(BSN(
        "This zombie is a lost soul. Once this poor soul was a " +
        "proud and great prince. You wonder what evil he might " +
        "have done to achieve his present state; or, even more " +
        "important, who turned him into this state?"
        ));
    set_adj("frightful");
    set_race_name("soul");
    set_gender(0);

    set_stats(({80,80,80,75,75,75}));
    set_hp(9999);
    set_mana(9999);
   set_alignment(-random(ALIGN));

    set_skill(SS_2H_COMBAT, 85);
    set_skill(SS_WEP_AXE,   75);
    set_skill(SS_WEP_CLUB,  85);
    set_skill(SS_DEFENCE,   75);
    set_skill(SS_PARRY,     75);
    set_skill(SS_AWARENESS, 75);

    add_prop(LIVE_I_NO_CORPSE, 1);

    seq_new("do_first");
    seq_addfirst("do_first", "@@dress_me");
}

dress_me()
{
    int i;

    seteuid(getuid(TO));
    H_CLONE("club_z");
    H_CLONE("axe_g");
    H_CLONE("mail_z");
    H_CLONE("helmet_z");

    i = random(2);
    if (i == 0) {
        H_CLONE("cloak_z");
    }
    if (i == 1) {
        H_CLONE("leggings_z");
    }
    command("wear all");
    command("wield all");
}

haunt(object who)
{
    string name, race;

    TO -> command("scream");
    if (environment(who) == environment(TO)){
        name = lower_case(who -> query_name());
        race = capitalize(who -> query_race_name());
        TO -> command("stare at " + name);
        TO -> command("whisper " + name + " " + race + "!" +
                      " I hate your kind!"); 
    }
}
