/* Mortis 9.2014
 *
 * This is a magically protected and trapped safe room that holds items
 * confiscated from criminals in the city.
 *
 * Shadow veil scroll added to chest - Arman 30 June 2018
 */

#include <macros.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>
#include <ss_types.h>
#include "../../local.h"
#include CLOCKH

inherit TOA_ROOMBASE;

#define FOUND_CONFIS_TRAP1    "_i_found_confis_trap1"
#define FOUND_CONFIS_TRAP2    "_i_found_confis_trap2"

int ctrapped = 1;
object tdoor, tchest, tmag, tcal1, tcal2, tcal3, tingot, tspikes, scroll;

string my_wire();
string my_slot();

string
query_to_jail()
{
    return "west";
}

void
reset_palan_room()
{
    if (!tchest)
    {
        tchest = clone_object(TOA + "obj/confis_chest");
        tchest->move(TO);
    }
    tchest->add_prop(CONT_I_CLOSED, 1);
    tchest->add_prop(CONT_I_LOCK, 1);
    
    if (!present(tmag, tchest))
    {
        tmag = clone_object(TOA + "obj/nudie_mag");
        tmag->move(tchest, 1);
    }

    if (!present(scroll, tchest))
    {
        scroll = clone_object("/d/Krynn/common/scrolls/shadow_veil_scroll");
        scroll->move(tchest, 1);
    }
/*    if (!present(tingot, tchest))
    {
        tingot = clone_object("/d/Calia/sea/objects/corpse_cleaner");
        tingot->move(tchest, 1);
    }
    if (!present(tcal1, tchest))
    {
        tcal1 = clone_object("/d/Avenir/common/holm/obj/caltrop");
        tcal1->move(tchest, 1);
    }
    if (!present(tcal2, tchest))
    {
        tcal2 = clone_object("/d/Avenir/common/holm/obj/caltrop");
        tcal2->move(tchest, 1);
    }
    if (!present(tcal3, tchest))
    {
        tcal3 = clone_object("/d/Avenir/common/holm/obj/caltrop");
        tcal3->move(tchest, 1);
    } */
    if (!present(tspikes, tchest))
    {
        tspikes = clone_object(MONKS + "arms/brix_fist_spikes");
        tspikes->move(tchest, 1);
    }

    // Reset trap.
    ctrapped = 1;
}

void
create_palan_room()
{
    SHORT("A secure chamber in the Tower of Arms");
    LONG("A small chamber with iron-reinforcing, the distant chink of "
    + "armour and clump of bootsteps can barely be heard from the corridors "
    + "outside. An iron door is set into the west wall.\n");

    add_prop(MAGIC_AM_MAGIC,({30, "abjuration"}));
    add_prop(ROOM_M_NO_TELEPORT,"The faint silver rune on the ceiling pulses "
    + "brightly blocking your attempt to escape.\n");

    ITEM(({"corridor", "corridors"}), "Marble corridors extend from here. "
    + "To the east and west, rows of barracks extend as far as you can "
    + "see.\n");
    ITEM(({"iron", "iron-reinforcing"}), "Bands of iron are bolted into the "
    + "walls for reinforcement. You notice a large but faint silver rune on "
    + "the ceiling.\n");
    ITEM(({"rune", "faint rune", "faint silver rune", "silver rune"}), "The "
    + "faint silver rune on the ceiling feels magic. You get the sense it "
    + "would block extradimensional or other types of entry into this room "
    + "that it protects.\n");
    ITEM(({"black wire", "wire"}), "@@my_wire@@");
    ITEM(({"dark slot", "slot"}), "@@my_slot@@");

    CMD(({"wire"}), "cut", "@@cut_wire@@");
    CMD(({"lockbox", "box", "lock on box", "lock on lockbox"}), "pick",
        "@@pick_box@@");

    tdoor = clone_object(TOA + "doors/toa_confis_door42");
    tdoor->move(TO);

    reset_palan_room();
}

string
my_wire()
{
    if (TP->query_prop(FOUND_CONFIS_TRAP1) != 1)
    {
        return "You find no wire.\n";
    }
    string ret;

    if (ctrapped == 1)
    { ret = "The black wire is inside the keyhole of the lockbox."; }
    else
    {
        ret = "The black wire is disconnected from the keyhole of the "
        + "lockbox.";
    }
    
    if (TP->query_skill(SS_AWARENESS) > (35 + random(50)))
    {
        ret += " However, it also runs along the side of the lid, down the "
        + "bolted iron bands, to the wall, and up to the ceiling where you "
        + "spy a dark slot.\n";
        TP->add_prop(FOUND_CONFIS_TRAP2, 1);
    }
    else
    { ret += "\n"; }
    
    return ret;
}

string
my_slot()
{
    if (TP->query_prop(FOUND_CONFIS_TRAP2) != 1)
    {
        return "You find no slot.\n";
    }
    
    string ret = "The dark slot conceals a great axe blade poised to slice in "
    + "half anyone who would disturb the black wire within the keyhole "
    + "of the lockbox.";
    
    if (ctrapped == 1)
    {
        ret += " You could try to <cut wire> to disarm it, but "
        + "you'd better have a lot of confidence in your trap disarming "
        + "skills or you're sure to get chopped.\n";
    }
    else
    {
        ret += " It looks like it's been disarmed.\n";
    }

    return ret;
}

cut_wire()
{
    if (ctrapped != 1)
    {
        write ("The black wire has already been removed from the keyhole.\n");
        return 1;
    }

    if (TP->query_skill(SS_FR_TRAP) < (20 + random(52)))
    {
        TP->set_hp(1);
        write("You tamper ineptly with the wire in the keyhole of the "
        + "lockbox. A great axe blade swings out of a dark slot in the "
        + "ceiling and cleaves lethally into you knocking you against the "
        + "wall where you collapse into a lifeless heap.\n");
        tell_room(E(TP), QCTNAME(TP)+ " tampers ineptly with something in "
        + "the keyhole of the lockbox. A great axe blade swings out of the "
        + "ceiling and cleaves " + HIM(TP) + " lethally into " + HIM(TP)
        + " knocking " + HIM(TP) + "against the wall where " + HE(TP)
        + "collapses into a lifeless heap.\n", ({TO, TP}));
        say("The great axe blade retracts into the dark slot in the "
        + "ceiling.\n");
        return 1;
    }

    ctrapped = 0;
    write("You pin the wire to the floor with a tack creating slack "
    + "and allowing you to disconnect the wire from the keyhole of the "
    + "lockbox.\n");
    tell_room(E(TP), QCTNAME(TP)+ " fiddles with the lockbox.\n", ({TO, TP}));
    return 1;
}

void
auto_door()
{
    tdoor->reset_door();
}

pick_box()
{
    if (ctrapped == 1)
    {
        TP->set_hp(1);
        write("You attempt to pick the lock but trigger a wire inside the "
        + "keyhole. A great axe blade swings out of a dark slot in the "
        + "ceiling and cleaves lethally into you knocking you against the "
        + "wall where you collapse into a lifeless heap.\n");
        tell_room(E(TP), QCTNAME(TP) + " tries to pick the lockbox. A great "
        + "axe blade swings out of the ceiling and cleaves lethally into "
        + HIM(TP) + " knocking " + HIM(TP) + "against the wall where " + HE(TP)
        + "collapses into a lifeless heap.\n", ({TO, TP}));
        say("The great axe blade retracts into the dark slot in the "
        + "ceiling.\n");
        return 1;
    }

    if (TP->query_skill(SS_OPEN_LOCK) > (40 + random(38)))
    {
        tchest->add_prop(CONT_I_LOCK, 1);
        write("You hear a satisfying \" Click\" as you pop the lock on the "
        + "iron box.\n");
        tell_room(E(TP), QCTNAME(TP) + " fiddles with the lock on the iron "
        + "box.\n", ({TO, TP}));
        return 1;
    }

    write("You fail to pick the lock.\n");
    tell_room(E(TP), QCTNAME(TP) + " fiddles with the lock on the iron "
    + "box.\n");
    return 1;
}
