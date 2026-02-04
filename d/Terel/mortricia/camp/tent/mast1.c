/*
  A tent room. Mortricia 920927
 */
inherit "/std/room";

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

#define CAMP_DIR        MORTRICIADIR + "camp/"
#define TENT_DIR        CAMP_DIR + "tent/"

void
create_room()
{
    set_short("Top of northern mast");
    set_long(BSN(
        "You have reached a platform up in the northern mast. " +
        "Up here you have quite an excellent view of the tent " +
        "interiors. There is a wire going southeast from here."
    ));
    
    add_item(({"view"}), BSN(
        "Some 30 feet below you see people, and several of them " +
        "have spotted you. They are certainly keen on what your " +
        "plans up there are."
    ));
    add_item(({"wire"}), BSN(
        "The wire has been stretched between this mast and another " +
        "mast further southeast. And, most important of all, there " +
        "is no safety net below on the manege."
    ));
    add_item(({"manege"}), BSN(
        "You estimate the distance down to the manage to be " +
        "about 30 feet."
    ));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TENT_DIR + "tent_06", "down", 0);
    add_exit(TENT_DIR + "wire"   , "southeast", "@@to_wire");
}

to_wire()
{
    int tp_dis, tp_wis;

    if (TP -> query_wiz_level() > 0)
        return 0;

    tp_dis = (TP->query_stats(SS_DIS)) + random(5);
    tp_wis = (TP->query_stats(SS_WIS)) + random(5);

    if (tp_wis < 20) {
        write(BSN(
	    
            "Since you obviously lack common sense you stride " +
            "out on the wire."
        ));
        say(QCTNAME(TP) + " decides to walk out on the wire.\n");
        return 0;
    }
    if (tp_dis > 20) {
        write(BSN(
             "You feel that you have, at least some, of the " +
             "capabilities necessary to be a tight-rope " +
             "dancer. Hence, slowly you proceed out on the wire."
        ));
        return 0;
    }
    write(BSN(
        "You realise that walking out on the wire is far above " +
        "your capabilities and will certainly result in your " +
        "premature death."
    ));
    return 1;
}
