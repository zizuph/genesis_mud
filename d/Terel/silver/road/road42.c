/* File         : /d/Terel/silver/forest/road42.c
 * Creator      : Pasqua
 * Date         : March 2006         
 * Purpose      : road file for Silver Forest.
 * Related Files: /d/Terel/silver/include/road_base.c
 * Comments     : Basic Silver forest road room.
 * Modifications: 
 */


#pragma strict_types

#include <filter_funs.h>
#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"

#define PLAYER_I_ATTACKED_CARAVAN "_player_i_attacked_caravan"
#define TENT (FOREST_QZ + "tent")

inherit INCLUDE + "road_base";

int move_log(string str);
void close_way();
void open_way();

int open;

public int caravan_block(mixed attacker)
{
	if(open)
		return 0;
	/* player can prevent caravan from moving here. */
	if(objectp(attacker) && objectp(present(attacker, all_inventory(TO))))
		return 1;
	if(sizeof(filter(all_inventory(TO), &->id("_silver_forest_bandit"))))
		return 1;	
	tell_room(TO, "The log is moved to the side of the road.\n");
	return 0;
}

void pack_arrives(object target)
{
	object leader, bandit;
	int pack_size = 2 + random(2);
	
	leader = TENT->give_leader();
	leader->move_living("from the forest", TO, 0, 0);
	if(target)
		leader->command("kill " + target->query_name());
	
	for(int i = 0; i < pack_size; ++i)
	{
		bandit = clone_object(NPC + "bandit");
		bandit->move_living("from the forest", TO, 0, 0);
		if(target)
			bandit->command("kill " + target->query_name());
	}
}
/* Called by caravan, it creates an ambush of bandits.*/
public void ambush_caravan(object defender)
{
	object *caravan = FILTER_LIVE(filter(all_inventory(TO), &->is_caravan()));
	object target = 0;
	if(sizeof(caravan)>1)
		set_alarm(1.0, 0.0, &arrow_shot(caravan[random(sizeof(caravan))]));
	if(sizeof(caravan))
		target = caravan[random(sizeof(caravan))];
	else
		target = present(defender, TO);
	set_alarm(2.0, 0.0, &pack_arrives(target));
}

public void
create_room()
{
    ::create_room();

	set_short("a road in the northern silver forest");
	add_my_desc("@@extra_short");
	add_exit(ROAD + "road43", "east", "@@log_here@@", 0, 1);
	add_exit(ROAD + "road41", "north", 0);
    add_item(({"log", "wooden log"}), ("The log is placed in the middle of the road, "+
        "its purpose seem to be to block people from passing by.\n"));

    reset_room();
}

string extra_short()
{
	if(!open)
		return "A wooden log is placed in the middle of the road.\n";
	return "";
}

int
log_here()
{
    if (open)
        return 0;
    write("The log is in the way to proceed in that direction.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(move_log, "move");
}

int
move_log(string str)
{
    if(str != "log")
    {   
        write("Move what? the wooden log?\n");
        return 0;
    }
    /* player can prevent caravan from moving here. */
	if(sizeof(filter(all_inventory(TO), &->id("_silver_forest_bandit"))))
	{
		write("Bandits prevents you from moving the log.\n");
		return 0;
	}
    write("You grab the log and pushes it to the side.\n");
    say(QCTNAME(TP)+" gets a good grip of the log and pushes it to the side.\n");
    open_way();

    return 1;
}

void
open_way()
{
    if(!open)
    {
        tell_room(TO,
            "As the log is gone its now possible to proceed eastward!\n");
        open = 1;

        setuid();
        seteuid(getuid());
        
        (ROAD + "road43")->open_way();
        set_alarm(15.0, 0.0, &close_way());
    }
}

void
close_way()
{
    if (open)
    {
        tell_room(TO,"The log rolls back to its old position.\n");
        open = 0;

        (ROAD + "road43")->close_way();
    }
}
