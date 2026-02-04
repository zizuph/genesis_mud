/* A skeleton. Mortricia 920910 */
inherit "/std/monster";
inherit "/std/act/seqaction";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)           break_string(message, 70)
#define TP                    this_player()
#define TO                    this_object()

create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("skeleton");
    set_short("bony skeleton");
    set_long("A bony skeleton.\n");
    set_adj("bony");

    set_race_name("skeleton");
    set_gender(2);

    set_stats(({ 1, 1, 1, 1, 1, 1}));
    set_hp(9999);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_NO_ATTACK, 1);
    add_prop(CONT_I_WEIGHT, 5000);
    add_prop(CONT_I_MAX_WEIGHT, 25000);
    add_prop(CONT_I_VOLUME, 1000);
    add_prop(CONT_I_MAX_VOLUME, 10000);
    add_item(({"bone", "bones"}), "The bones are white.\n");
    add_item(({"head", "skull"}), "The skull is white.\n");

    set_all_hitloc_unarmed(1);
    set_all_attack_unarmed(1, 1);
}
