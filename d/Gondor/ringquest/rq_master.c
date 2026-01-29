/*
 *	/d/Mordor/ringquest/rq_master.c
 *
 *	The Master Object for the Ring Quest of the Middle Earth domains.
 *	It is a room for the convenience of being able to go there
 *	and to be able to check the status of the Ring Quest.
 *
 *	Copyright (C) by Christian Markus 1995
 *
 *	Olorin, August 1995
 *
 *	Revision history:
 * 
 * Palmer April 24, 2006
 * Removed Rhovanian workroom exit
 *
 */
#pragma no_clone
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>

#include "/d/Gondor/ringquest/lib/defs.h"
#include "/d/Gondor/sys/clock.h"

/*
 *      Prototypes
 */
private string  long_desc();
public  string  exa_clock();
public  string  exa_ring();

/*
 *	Global variables
 */
static int     RQ_Stage;
static object  One_Ring,
               Clock;

public int
query_rq_stage()
{
    if (!objectp(Clock))
        Clock = find_object(CLOCK);

    RQ_Stage = Clock->query_rq_stage();
    return RQ_Stage;
}

public object  query_one_ring() { return One_Ring; }

/*
 * Function name: set_one_ring
 * Description:   Check if it is ok to create a new clone
 *                of the One Ring: check if there is a ring bearer
 *                active who is not idle.
 * Arguments:     ring - object pointer to the new clone
 * Returns:       0: remove new clone; 1: ok
 */
public int
set_one_ring(object ring)
{
    if (objectp(One_Ring))
        return 0;

    One_Ring = ring;

    return 1;
}

/*
 * Function name: find_one_ring
 * Description:   Try to find all clones of the One Ring that exist
 *                in the game.
 * Returns:       an array of object pointers
 */
public object *
find_one_ring()
{
    int     s;
    object  master,
           *clones;

    ONE_RING_MASTER->load_me();
    master = find_object(ONE_RING_MASTER);

    clones = object_clones(master);
    if (s = sizeof(clones))
    {
        One_Ring = clones[0];
        if (s > 1)
            log_file(RQ_ERROR_LOG, "FATAL: Found "+s+" clones of "
              + ONE_RING_MASTER + "! "+ctime(time())+".\n");
        return clones;
    }
    return 0;
}

void
ring_removed(object clone, object bearer, string name)
{
}

public int
domain_closed()
{
    write("The domain Mordor has been obliterated due to lack of active coders.\n"
        + "The purpose of the domain Mordor was to implement the Ring Quest.\n"
        + "Should at any time there be sufficient experienced and active coders\n"
        + "in the domain Gondor, it will be attempted to found the domain Mordor\n"
        + "again, so its coders can work on the Ring Quest.\n"
        + "Until such a time, there will be no work on the Ring Quest in Middle Earth.\n");
    return 1;
}

void
create_gondor()
{
    set_short("Ring Quest Master Room");

    set_long(long_desc);

    add_exit(GONDOR_DIR + "workroom", "gondor", 0, 0);
    add_exit(MORDOR_DIR + "workroom", "mordor", domain_closed, 0);
    add_exit(SHIRE_DIR  + "workroom", "shire",  0, 0);
    add_exit(ISEN_DIR   + "master",   "isengard", 0, 0);
    add_exit(MORGUL_DIR + "blackrider", "nazgul", 0, 0);

    add_item(({"clock", "time", }), exa_clock);
    add_item(({"ring", "one ring", "ring info", "info", }), exa_ring);

    CLOCK->load_me();
    Clock = find_object(CLOCK);
    query_rq_stage();
    find_one_ring();
}

/*
 * Function name: long_desc
 * Description:   long description of the room as VBFC
 * Returns:       the long description
 */
private string
long_desc()
{
    string  desc  = "From here the status of the Ring Quest can be checked. "
                  + "There is a large clock on the wall, showing the exact "
                  + "time and date in Middle Earth.";
    
    if (!objectp(Clock))
        Clock = find_object(CLOCK);

    query_rq_stage();

    switch(RQ_Stage)
    {
    case 0:
        desc += " At present, there is still peace in Middle Earth.";
        break;
    case RQ_GANDALF_IN_BAGEND:
        desc += " At present, there is still peace in Middle Earth. "
             +  "Gandalf has arrived in Bag End and identified the One "
             +  "Ring.";
        break;
    case RQ_OSGILIATH_ATTACK:
        desc += " At present, there is still peace in Middle Earth, but the "
             +  "Morgul army has made an attack on Osgiliath and the bridge "
             +  "across the Anduin is broken.";
        break;
    case RQ_LEFT_HOBBITON:
        desc += " At present, there is still peace in Middle Earth. "
             +  "The One Ring has left Hobbiton.";
        break;
    case RQ_ARRIVED_IN_RIVENDELL:
        desc += " At present, there is still peace in Middle Earth. "
             +  "The One Ring is in Rivendell.";
        break;
    case RQ_LEFT_RIVENDELL:
        desc += " At present, there is still peace in Middle Earth. "
             +  "The One Ring has left Rivendell.";
        break;
    case RQ_ARRIVED_IN_LOTHLORIEN:
        desc += " At present, there is still peace in Middle Earth. "
             +  "The One Ring is in Lothlorien.";
        break;
    case RQ_LEFT_LOTHLORIEN:
        desc += " At present, there is still peace in Middle Earth. "
             +  "The One Ring has left Lothlorien.";
        break;
    case RQ_LEFT_HENNETH_ANNUN:
        desc += " The One Ring has left the Henneth Annun. There is now war "
             +  "in Middle Earth!";
        break;
    case RQ_LEFT_HENNETH_ANNUN:
        desc += " The One Ring has entered Mordor. There is war "
             +  "in Middle Earth!";
        break;
    case RQ_QUEST_ENDED:
        desc += " The Ring Quest has failed! The Dark Lord is victorious!";
        break;
    case RQ_QUEST_FULFILLED:
        desc += " The Ring Quest has succeeded! The Dark Lord has been "
             +  "vanquished!";
        break;
    default:
        desc += " There is an undefined stage "+RQ_Stage+" of the Ring Quest!";
        break;
    }

    return BSN(desc);
}

/*
 * Function name: rq_stage_string
 * Description:   describes the present stage of the Ring Quest  
 * Returns:       a string describing the Ring Quest stage
 */
string
rq_stage_string()
{
    if (!objectp(Clock))
        Clock = find_object(CLOCK);

    switch (query_rq_stage())
    {
    case 0:
        return "The One Ring is still in Hobbiton.";
        break;
    case RQ_GANDALF_IN_BAGEND:
        return "Gandalf has identified the One Ring.";
        break;
    case RQ_OSGILIATH_ATTACK:
        return "Osgiliath has been attacked.";
        break;
    case RQ_LEFT_HOBBITON:
        return "The One Ring has left Hobbiton.";
        break;
    case RQ_ARRIVED_IN_RIVENDELL:
        return "The One Ring is in Rivendell.";
        break;
    case RQ_LEFT_RIVENDELL:
        return "The One Ring has left Rivendell.";
        break;
    case RQ_ARRIVED_IN_LOTHLORIEN:
        return "The One Ring is in Lothlorien.";
        break;
    case RQ_LEFT_LOTHLORIEN:
        return "The One Ring has left Lothlorien.";
        break;
    case RQ_LEFT_HENNETH_ANNUN:
        return "The One Ring has left the Henneth Annun.";
        break;
    case RQ_ENTERED_MORDOR:
        return "The One Ring has entered Mordor.";
        break;
    case RQ_QUEST_ENDED:
        return "The Ring Quest has failed!";
        break;
    case RQ_QUEST_FULFILLED:
        return "The Ring Quest has succeeded!";
        break;
    default:
        return "The Ring Quest stage is undefined!";
        break;
    }
}

/*
 * Function name: exa_clock
 * Description:   VBFC for the description of the clock in this room.
 * Returns:       the description
 */
public string
exa_clock()
{
    int     i, s;
    object  isen_master;
    string  desc = BSN("This is a big clock, showing the date in two different "
                 + "formats and the time:"),
           *isen_desc;

    if (!objectp(Clock))
        Clock = find_object(CLOCK);

    desc += sprintf("\n\t%|40s\n\n\t%|40s\n\n\t%|40s\n\n\t%|40s\n\t%|40s\n\n\t%|40s\n\t%|40s\n",
        Clock->query_date_s(), Clock->query_time(),
        Clock->query_date(), "Phase of the moon:", Clock->query_moon(),
        "Ring Quest Stage "+query_rq_stage()+".", rq_stage_string());

    catch(ISEN_MASTER->load_me());
    isen_master = find_object(ISEN_MASTER);
    if (objectp(isen_master))
    {
	desc += sprintf("\t%|40s\n", "Isen Stage " + isen_master->query_isen_stage() + ".");
	isen_desc = explode(break_string(isen_master->isen_stage_desc(), 40), "\n");
	for (i = 0, s = sizeof(isen_desc); i < s; i++)
	    desc += sprintf("\t%|40s\n", isen_desc[i]);
    }

    return desc + "\n";
}

/*
 * Function name: exa_ring
 * Description:   VBFC for the ring info in this room.
 * Returns:       the info
 */
public string
exa_ring()
{
    object  bearer;

    if (!objectp(One_Ring))
        return "At present, the One Ring is still lost.\n";

    bearer = One_Ring->query_bearer();

    if (!objectp(bearer) || !living(bearer))
        return "The One Ring is in "+ENV(One_Ring)->query_short()
          + " ("+file_name(ENV(One_Ring))+").\n";

    return "At present, "+bearer->query_name()+" is the Ringbearer!\n"
         + CAP(HE(bearer)) + " is in "+ENV(bearer)->query_short()
         + " ("+file_name(ENV(bearer))+").\n";
}

/*
 * Function name: set_rq_stage
 * Description:   Increase the Ring Quest stage value
 * Arguments:     the new stage
 * Returns:       1/0
 */
public int
set_rq_stage(int i)
{
    if (!objectp(Clock))
        Clock = find_object(CLOCK);

    if (i <= RQ_Stage)
        return 0;
    return (RQ_Stage = Clock->set_rq_stage(i));
}

