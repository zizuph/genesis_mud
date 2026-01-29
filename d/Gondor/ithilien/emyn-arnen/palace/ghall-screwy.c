/* 
 * modified to load ithil_olog_out instead of ithil_olog npcs
 */

#pragma strict_types

inherit "/d/Gondor/common/room";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/ithilien/emyn-arnen/arnen_defs.h"

public int    block_me();
public int    morgul_block();
public void   reset_room();

object  cap,
        troll,
       *olog = allocate(2 + random(3)),
       *orc  = allocate(3 + random(4));

void
create_room()
{
    set_short("The Hall of Law in the House of the Stewards in Emyn Arnen");
    set_long("This is a large hall in the House of the Stewards in "
      + "Emyn Arnen. Four mighty pillars carry the roof. Between the two "
      + "pillars to the south there is a small pedestal of stone. A passage "
      + "is leading north, a doorway east, and a large arch south.\n");

    add_exit(ITH_DIR + "emyn-arnen/palace/hall1",   "north", morgul_block, 0);
    add_exit(ITH_DIR + "emyn-arnen/palace/kitchen", "east",  block_me,     0);
    add_exit(ITH_DIR + "emyn-arnen/palace/sthall",  "south", block_me,     0);

    add_item(({"hall", "large hall", "hall of law", }), 
        "This must be the Hall of Law where the House of Hurin administered "
      + "justice in the name of the King for their fief of Emyn Arnen. "
      + "The vaulted roof rests on four mighty stone pillars that stand "
      + "in the corners of a rectangle. Pillars, roof and walls were made "
      + "from stone blocks hewn from the same rock of light grey colour. "
      + "The Steward's chair was on the small pedestal between the two "
      + "south pillars. The space in front of the pedestal inside the "
      + "four pillars was where the people of Emyn Arnen could watch the "
      + "proceedings, but it was also used for large feasts.\n");

    add_item(({"pillars", "pillar", "columns", "stone pillars"}), 
        "Four mighty pillars standing in the corners of a rectangle "
      + "carry the roof. The short sides of the rectangle are north and "
      + "south. All pillars are made from large round stone slabs, each "
      + "of them three feet high, and every pillar consisting of seven "
      + "slabs. High on the southern pillars metal bands are running "
      + "around the pillars.\n");

    add_item(({"band", "bands", "metal bands", "metal band"}), 
        "When looking closer at the metal bands you notice that tied "
      + "to them are the remains of a heavy curtain that once was "
      + "hanging from the pillars behind the pedestal, dividing the "
      + "southern part of the hall from the rest.\n");

    add_item(({"curtain", "remains"}), 
        "All that is left from the curtain are a few shreds still "
      + "hanging from the metal bands running around the southern "
      + "pair of pillars.\n");

    add_item(({"pedestal", "platform", }), 
        "A low platform of about ten feet times three feet between "
      + "the southern pair of pillars. When administering justice, "
      + "the Stewards were sitting on a chair on this platform.\n");

    add_item(({"passage", }), 
        "A passage leading north into the entrance hall of the House "
      + "of the Stewards.\n");

    add_item(({"doorway", "door", }), 
        "A doorway is leading east. Through it you can see a large "
      + "fireplace in the room to the east, which probably once served "
      + "as kitchen.\n");

    add_item(({"arch", "archway", "hinges", }), 
        "In the wall behind the two pillars at the south end of the hall "
      + "opens a large archway, leading into another hall further south. "
      + "Iron hinges in the sides of the archway are all what remains "
      + "of the large gate that once must have blocked access to the "
      + "hall beyond.\n");

    PALACE_WALLS
    PALACE_FLOOR
    PALACE_ROOF
    PALACE_STONES

    reset_room();
}

void
add_uruk()
{
    if (objectp(cap))
        return;

    cap = clone_object(MORGUL_DIR + "npc/ithil_uruk");
    cap->add_prop(LIVE_I_DONT_CLING, 1);
    cap->set_restrain_path(ITH_DIR + "emyn-arnen");
    cap->set_wimpy_run(0);
    cap->arm_me();
    cap->move_living("down", TO);
}

void
add_troll()
{
    troll = clone_object(MORGUL_DIR + "npc/ithil_olog");
    troll->add_prop(LIVE_I_DONT_CLING, 1);
    troll->set_restrain_path(ITH_DIR + "emyn-arnen");
    troll->set_wimpy_run(0);
    troll->arm_me();
    troll->move_living("down", TO);
}

void
add_olog()
{
    int     i = 0;

    for (i = 0; i < sizeof(olog); i++)
        if (!objectp(olog[i]))
            break;

    if (i == sizeof(olog))
        return;

    olog[i] = clone_object(MORGUL_DIR + "npc/ithil_olog_out");
    olog[i]->set_restrain_path(ITH_DIR + "emyn-arnen");
    olog[i]->set_wimpy_run(0);
    olog[i]->set_aggressive(1);
    olog[i]->arm_me();
    olog[i]->move_living("down", TO);

    set_alarm(1.0, 0.0, add_olog);
}

void
add_orc()
{
    int     i = 0;

    for (i = 0; i < sizeof(orc); i++)
        if (!objectp(orc[i]))
            break;

    if (i == sizeof(orc))
        return;

    orc[i] = clone_object(MORGUL_DIR + "npc/ithil_orc");
    orc[i]->set_restrain_path(ITH_DIR + "emyn-arnen");
    orc[i]->set_wimpy_run(0);
    orc[i]->arm_me();
    orc[i]->move_living("down", TO);

    set_alarm(1.0, 0.0, add_orc);
}


public int
block_me()
{
    object  a;

    if (!objectp(a = TP->query_attack()) && 
        !objectp(a = present("_morgul_monster", TO)))
    {
        return morgul_block();
    }

    if (CAN_SEE_IN_ROOM(a) && CAN_SEE(a, TP))
        write("The "+a->short()+" stops you from going there.\n");
    else
        write("The "+a->short()+" is blocking that exit.\n");
    return 1;
}

public void
reset_room()
{
    if (!objectp(cap))
        add_uruk();
    set_alarm(0.0, 0.0, add_olog);
    set_alarm(0.5, 0.0, add_orc);
    set_alarm(0.5, 0.0, add_troll);
}

public int
morgul_block()
{
    if (TP->id("_morgul_monster"))
        return 1;
    return 0;
}

