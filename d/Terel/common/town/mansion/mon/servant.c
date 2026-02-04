/* A ghostly servant. Mortricia 921027 */
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
#define WEP_DIR         MORTRICIADIR + "weapons/"
#define ARM_DIR         MORTRICIADIR + "armours/"
#define ALIGN           10

object tray;

void lay_table();
void serve_food();

void
create_monster()
{
    if (!IS_CLONE) return;

    set_name("servant");
    set_short("ghostly servant");
    set_long(BSN(
        "It's an old servant. You aren't quite certain whether he " +
        "is a real living servant or whether he is a ghost."
    ));
    set_adj("ghostly");
    set_race_name("human");
    set_gender(0);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_stats(({20,20,20,40,40,20}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN);

    set_skill(SS_UNARM_COMBAT, 10);
    set_skill(SS_WEP_SWORD, 20);
    set_skill(SS_AWARENESS, 40);

    set_all_hitloc_unarmed(10);
    set_all_attack_unarmed(10, 10);

    seq_new("do_first");
    seq_addfirst("do_first", "@@dress_me");
}

dress_me()
{
    object sword, cloak;

    seteuid(getuid(TO));
    cloak = clone_object(ARM_DIR + "cloak");
    cloak -> set_name("livery");
    cloak -> set_short("black livery");
    cloak -> set_long("A black livery. Normally used on state " +
                      "occasions.\n");
    cloak -> set_adj("black");
    cloak -> move(TO);
    command("wear livery");

    sword = clone_object(WEP_DIR + "plain_sword");
    sword -> set_name("sabre");
    sword -> set_short("ceremonial sabre");
    sword -> set_adj("ceremonial");
    sword -> set_long(BSN(
                 "It's a ceremonial sabre, not really suited for " +
                 "combat."
             ));
    sword -> set_hit(20);
    sword -> set_pen(15);
    sword -> move(TO);
    command("wield sabre");

    tray = clone_object(MANSION + "obj/tray");
    tray -> move(TO);
    clone_object(MANSION + "obj/plate") -> move(tray);
    clone_object(MANSION + "obj/glass") -> move(tray);
    clone_object(MANSION + "obj/cutlery") -> move(tray);
}

void
lay_table()
{
    object room, table, candle;

    room = environment(TO);
    table = present("table", room);
    if (!table) return;
    candle = present("candle", table);
    if (!candle) {
        candle = clone_object(MANSION + "obj/candle");
        candle -> move(TO);
        TO -> command("light candle");
        TO -> command("put candle in table");
    }
    if (candle && candle -> query_can_light()) {
        TO -> command("get candle from table");
        TO -> command("light candle");
        TO -> command("put candle in table");
    }
    if (present("tray", TO) &&
        present("plate", tray) &&
        present("glass", tray) &&
        present("cutlery", tray)) {
        TO -> command("get plate from tray");
        TO -> command("put plate in table");
        TO -> command("get glass from tray");
        TO -> command("put glass in table");
        TO -> command("get cutlery from tray");
        TO -> command("put cutlery in table");
    }
}

void
serve_food()
{
    object room, table;

    room = environment(TO);
    table = present("table", room);
    if (!table) return;
    if (present("plate", table) &&
        present("meal", TO)     ) {
        TO -> command("get plate from table");
        TO -> command("put meal in table");
        TO -> command("say Enjoy your dinner!");
        TO -> command("bow");
    } else {
        TO -> command("frown");
        TO -> command("say Not hungry?");
        TO -> command("eat meal");
        TO -> command("burp");
    }
}
