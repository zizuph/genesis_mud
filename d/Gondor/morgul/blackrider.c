/*
 *	/d/Gondor/morgul/blackrider.c
 *
 *	A dummy room to steer the movements of the Black Rider
 *
 */
#pragma strict_types

inherit "/d/Gondor/common/room.c";

#include <composite.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

#include "/d/Gondor/common/lib/clock.h"

/*
 *     Prototypes:
 */
public void    find_rider_loc(int rq_stage);
public void    find_rider2_loc(int rq_stage);
public string  exa_rider();

/*
 *     Global variables:
 */
static object  Rider,
               Rider2,
               Clock = find_object(CLOCK);

public void
reset_room()
{
    int     rq_stage,
            num;

    rq_stage = RING_QUEST_MASTER->query_rq_stage();

    if (!objectp(Rider))
    {
        find_rider_loc(rq_stage);
    }
    else if (!objectp(ENV(Rider)))
    {
	Rider->remove_object();
        find_rider_loc(rq_stage);
    }


    if (!objectp(Rider2))
    {
        find_rider2_loc(rq_stage);
    }
    else if (!objectp(ENV(Rider2)))
    {
	Rider2->remove_object();
        find_rider2_loc(rq_stage);
    }
}

public void
find_rider_loc(int rq_stage)
{
    mixed   restrain_path;
    string  target_room;

    Rider = clone_object(NPC_DIR + "blackrider");
    Rider->set_random_move(15);

    if (rq_stage < RQ_OSGILIATH_ATTACK)
    {
        target_room = "/d/Gondor/morgul/city/mmr3";
        restrain_path = "/d/Gondor/morgul/city";
        Rider->set_beast_type(0);
    }
    else if (rq_stage < RQ_LEFT_HOBBITON)
    {
        target_room = ITH_DIR + "osgiliath/eosg5";
        restrain_path = "/d/Gondor/ithilien";
    }
    else if (rq_stage < RQ_ARRIVED_IN_RIVENDELL)
    {
        target_room = "/d/Shire/eastroad/western/er23";
        restrain_path = "/d/Shire/eastroad/western/";
    }
    else if (rq_stage < RQ_LEFT_LOTHLORIEN)
    {
        target_room = ITH_DIR + "osgiliath/eosg5";
        restrain_path = "/d/Gondor/ithilien";
        Rider->set_beast_type(2);
    }
    else if (rq_stage < RQ_LEFT_HENNETH_ANNUN)
    {
        switch (random(4))
        {
        case 0:
            target_room = ITH_DIR + "osgiliath/eosg5";
            restrain_path = "/d/Gondor/ithilien";
            break;
        case 1:
            target_room = "/d/Gondor/dunland/road/r01";
            restrain_path = "/d/Gondor/dunland/road";
            break;
        case 2:
            target_room = "/d/Gondor/rohan/road/wr7";
            restrain_path = "/d/Gondor/rohan/road";
            break;
        case 3:
            target_room = "/d/Gondor/ithilien/dagorlad/path2";
            restrain_path = "/d/Gondor/ithilien/dagorlad";
            break;
        }
        Rider->set_beast_type(2);
    }
    else if (rq_stage < RQ_ENTERED_MORDOR)
    {
        target_room = "/d/Gondor/anorien/road/or5";
        restrain_path = "/d/Gondor/anorien/road";
        Rider->set_beast_type(2);
    }
    else if (rq_stage < RQ_QUEST_ENDED)
    {
        target_room = "/d/Gondor/ithilien/road/nr11";
        restrain_path = "/d/Gondor/ithilien/road";
        Rider->set_beast_type(2);
    }
    else
    {
        target_room = "/d/Gondor/morgul/city/mmr3";
        restrain_path = "/d/Gondor/morgul/city";
        Rider->set_beast_type(2);
    }

    catch(target_room->load_me());
    if (!objectp(find_object(target_room)))
    {
	log_file("errors", file_name(TO) + ": " +
		 "Failed to load " + target_room + " (" +
		 ctime(time()) + ").\n");
	Rider->remove_object();
    }
    else
    {
	Rider->set_restrain_path(restrain_path);
	Rider->arm_me();
	Rider->move_living("down", target_room);
    }
}

public void
find_rider2_loc(int rq_stage)
{
    int     beast_type = 1,
            aggressive = 0;
    mixed   restrain_path,
            other_path;
    string  target_room;

    if (rq_stage < RQ_LEFT_HOBBITON)
        return; 

    if (rq_stage < RQ_ARRIVED_IN_RIVENDELL)
    {
        target_room = "/d/Gondor/cardolan/road/r36";
        restrain_path = "/d/Gondor/cardolan/road";
    }
    else if (rq_stage < RQ_LEFT_LOTHLORIEN)
        return;
    else if (rq_stage < RQ_LEFT_HENNETH_ANNUN)
    {
        if (objectp(Rider))
            other_path = Rider->query_restrain_path();

        restrain_path = other_path;

        while (restrain_path == other_path)
        {
            switch (random(4))
            {
            case 0:
                target_room = ITH_DIR + "osgiliath/eosg5";
                restrain_path = ITH_DIR;
                break;
            case 1:
                target_room = DUN_DIR + "road/r01";
                restrain_path = DUN_DIR + "road";
                break;
            case 2:
                target_room = ROH_DIR + "road/wr7";
                restrain_path = ROH_DIR + "road";
                break;
            case 3:
                target_room = ITH_DIR + "dagorlad/path2";
                restrain_path = ITH_DIR + "dagorlad";
                break;
            }
        }
        beast_type = 2;
    }
    else if (rq_stage < RQ_ENTERED_MORDOR)
    {
        target_room = "/d/Gondor/ithilien/forest/orccamp1";
        restrain_path = "/d/Gondor/ithilien/forest";
        beast_type = 2;
        aggressive = 1;
    }
    else
        return;

    catch(target_room->load_me());
    if (!objectp(find_object(target_room)))
    {
	log_file("errors", file_name(TO) + ": " +
		 "Failed to load " + target_room + " (" +
		 ctime(time()) + ").\n");
    }
    else
    {
	Rider2 = clone_object(NPC_DIR + "blackrider");
	Rider2->arm_me();
	Rider2->set_random_move(15);
	Rider2->set_restrain_path(restrain_path);
	Rider2->set_beast_type(beast_type);
	if (aggressive)
	{
	    Rider2->set_agressive(1);
	    Rider2->set_attack_chance(33);
	}
	Rider2->move_living("down", target_room);
    }
}

public void
create_room()
{
    set_short("the Black Rider control room");

    set_long("This room controls the movements of the Black Riders.\n"
      +  BSN("On the wall is a clock showing the time in Middle Earth, "
      +      "and the stage of the Quest of the One Ring. Another wall "
      +      "has a small sign that shows the location of the Black "
      +      "Rider."));

    add_item(({"clock", "time", }), &RING_QUEST_MASTER->exa_clock());
    add_item(({"nazgul", "rider", "black rider", "sign", "small sign", }),
        exa_rider);
    add_cmd_item(({"nazgul", "rider", "black rider", "sign", "small sign", }),
        "read", exa_rider);

    add_exit(GONDOR_DIR + "workroom", "gondor", 0, 0);
    add_exit(MORDOR_DOM + "workroom", "mordor", 
	     &RING_QUEST_MASTER->domain_closed(), 0);
    add_exit(SHIRE_DIR  + "workroom", "shire",  0, 0);
    add_exit("/d/Rhovanion/" + "workroom", "rho",    0, 0);
    add_exit(MORDOR_DOM + "ringquest/rq_master", "quest", 0, 0);
    add_exit(OSG_DIR + "bridge_master", "osgiliath", 0, 0);

    reset_room();
}

public string
exa_rider()
{
    object *enemies;
    string  desc = "";

    if (objectp(Rider) && objectp(ENV(Rider)))
    {
        desc += "A Black Rider is in: ";
        desc += file_name(ENV(Rider));
        desc += "\n"
             +  CAP(ENV(Rider)->short()) + ".\n";
        if (sizeof(enemies = Rider->query_enemy(-1)))
            desc += "He is fighting "+COMPOSITE_LIVE(enemies)+".\n";
    }
    if (objectp(Rider2) && objectp(ENV(Rider2)))
    {
        desc += (objectp(Rider) ? "Another" : "A") + " Black Rider is in: ";
        desc += file_name(ENV(Rider2));
        desc += "\n"
             +  CAP(ENV(Rider2)->short()) + ".\n";
        if (sizeof(enemies = Rider2->query_enemy(-1)))
            desc += "He is fighting "+COMPOSITE_LIVE(enemies)+".\n";
    }

    if (!strlen(desc))
        return "There is no Black Rider within the realms of Middle Earth!\n";

    return desc;
}

