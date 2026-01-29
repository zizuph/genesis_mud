/*
 *  /d/Gondor/minas/houses/stable1.c
 *
 *  Courtyard of the Royal Stables of Minas Tirith
 *
 *  Alto, 10 April 2001
 * Finwe April 2019: Fixed ring quest stage time so it calls rq_stage() 
 *   instead of rq_stage_stored.
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/drink_water.c";


#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/clock.h"

#define INNER_MINAS "/d/Gondor/minas"

object  bench;
static  object  Stablemaster;
//int     rq_stage_stored = rq_stage();


public int
query_igard_broken()
{
//    if (rq_stage_stored < RQ_LEFT_HENNETH_ANNUN)
    if (rq_stage() < RQ_LEFT_HENNETH_ANNUN)
    {
        return 0;
    }

    return 1;
}


public void
create_gondor()
{
    set_short("The Courtyard of the Royal Stables");
    set_long("This large fenced-in area is the courtyard of the "
        + "Royal Stables of Minas Tirith. There are several fair "
        + "stables here, where a few swift horses are kept for "
        + "the errand-riders "
        + "of the Lord Steward. At present all the riders are "
        + "out and away, but there are horses in some of the stables. "
        + "There is a large wooden bench near the entrance and a square "
        + "trough in one corner.\n");

    add_item(({"fence", "coral"}), "The courtyard is surrounded by a tall "
        + "fence made of great blocks of stone, but otherwise is open "
        + "to the sky. It is broken only "
        + "by the gates to the various stables and the main gate "
        + "leading back to Stable Street to the south.\n");
    add_item(({"courtyard", "ground", "yard"}), "The wide coral is carpeted "
        + "mostly in dust, the product of many years of horses running "
        + "about the yard. In one corner is a large trough.\n");
    add_item(({"trough"}), "A large square trough made of stone. It is "
        + "presently half-filled with water. You may drink out of it if "
        + "the horse hair floating on the surface does not quench your "
        + "desire to do so.\n");
    add_item(({"horse hair", "hair", "film"}), "It seems to be everywhere. "
        + "There is "
        + "a particularly revolting film of it floating in the trough.\n");
    add_item(({"water"}), "The water in the trough does not look especially "
        + "inviting, but you may drink some if you wish.\n");
    add_item(({"dust"}), "It seems to be everywhere. Horses kick up "
        + "large quantities of it while cantering about the courtyard.\n");
    add_item(({"insignia", "insignias"}), "Which insignia? There is the "
        + "insignia of the House of Stewards on the west gate and the "
        + "insignia of the House of Elendil on the north gate.\n");
    add_item(({"insignia of the house of stewards"}), "This is also "
        + "the insignia of the House of Hurin, who founded the House "
        + "of Stewards. All the Stewards, including Lord Denethor II "
        + "are descended in direct line from Hurin.\n");
    add_item(({"insignia of the house of elendil"}), "Seven white "
        + "stars over a white tree.\n");
    add_item(({"star", "stars"}), "The stars on the insignia of the House "
        + "of Elendil are white and many-rayed.\n");
    add_item(({"tree"}), "The tree on the insignia of the House of Elendil "
        + "is a symbol of the trees descended from Nimloth the Fair "
        + "which grew in Numenor of old.\n");
    add_item(({"blocks", "stone", "slabs"}), "These huge slabs of "
        + "stone were quarried "
        + "long ago by Dwarves. The manner in which they were moved up to "
        + "this height in the city is no longer remember, save perhaps in "
        + "the secret archives in the Library of Minas Tirith.\n");
    add_item(({"sky", "clouds"}), "The walls and buildings block much of "
        + "the sky from view. The western sky, however, is dominated by "
        + "Mount Mindolluin. The eastern sky seems filled with black "
        + "clouds.\n");
    add_item(({"mountain", "mount mindolluin"}), "The city of Minas Tirith "
        + "is built upon its eastern knee. It dominates the western sky.\n");
    add_item(({"stable street"}), "It is difficult to see the street "
        + "over the tall fence.\n");
    add_item(({"corner"}), "The octagonal courtyard had eight of them, but "
        + "the only one with anything interesting to look at is the one "
        + "containing the trough.\n");
    add_item(({"gate", "gates"}), "Which one? There are four of them: a "
        + "bronzed gate, a gilded gate, a wooden gate, and a brass gate.\n");
    add_item(({"stables", "stable"}), "There are three stables accessable "
        + "from the courtyard, to the west, north and east.\n");



    set_drink_from("trough");

    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_prop(ROOM_I_INSIDE, 0);

    bench = clone_object(INNER_MINAS + "/obj/stable_bench.c");
    bench->move(TO);

    clone_object(INNER_MINAS +"/doors/stablegate_e2")->move(TO);
    clone_object(INNER_MINAS +"/doors/stablegate_n2")->move(TO);
    clone_object(INNER_MINAS +"/doors/stablegate_w2")->move(TO);
    clone_object(INNER_MINAS +"/doors/stablegate_s2")->move(TO);


    reset_room();
}

public void
init()
{
    ::init();
    init_drink();
}


public void
reset_room()
{
    /* This room was coded incorrectly. It assumes that there will
     * be an Armageddon each day (as there was at the time it was
     * originally coded.) Code should *never* count on a specific
     * time for Armageddon cycle length. What happened, as a
     * result, is that if the Ringquest cycle did not happen to
     * be a the correct stage when the room was first loaded, then
     * the quest would remain unavailable for the duration of the
     * Armageddon uptime, which has (at time of this writing) become
     * more than two weeks. The simple fix is to reclone the npc
     * each room reset, thus performing a fresh check for the
     * Ringquest stage. - Gorboth
     */
     
//    rq_stage_stored = rq_stage();
    
    Stablemaster->remove_object();

    if (!query_igard_broken())
    {
Stablemaster = clone_npc(Stablemaster, INNER_MINAS + "/npc/stablemaster_noquest");
    }

    if (query_igard_broken())
    {
       Stablemaster = clone_npc(Stablemaster, INNER_MINAS + "/npc/stablemaster");
    }
}

