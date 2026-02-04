/*
  A bearded woman. Mortricia 920927
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
#define CAMP_DIR       MORTRICIADIR + "camp/"

void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("woman");
    set_short("woman");
    set_pshort("women");
    set_long(BSN(
        "It's an ordinary woman."
        ));
    set_adj("ordinary");
    set_gender(1);
    set_race_name("human");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_stats(({12,12,12,15,15,12}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN);
}
