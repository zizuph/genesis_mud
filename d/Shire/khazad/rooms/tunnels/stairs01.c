/*
 * Stairs in Moria from West-gate
 * By Finwe, February 2003
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "defs.h"

#define WEST_GATE "/d/Shire/common/hollin/under_wall"
#define DOORS_PROP  "_Shire_i_push_moria_doors"

inherit BASE_ROOM;

int do_push(object player);

void
create_mine_room()
{
    LIGHTS_OFF;
    set_area("near the West-gate in");
    set_areaname("the mines");
    set_land("Khazad-dum");
    set_areatype(0);
    set_areadesc("staircase");

    
    add_my_desc("The stairs lead up into the mountain and blackness. " +
        "They look long and tiring, but are probably the only way " +
        "out of here. Corpses litter the ground here. There is one other " +
        "exit, and that is through the gate on the west wall.\n");

    set_add_battles("");
    set_add_walls("There is a faint outline of a gate on the west wall.");
    set_add_ceiling("");
    set_add_floor("");

    add_item(({"gate", "doors", "door", "gates"}),
        "The gates are large and heavy looking. They are to the west " +
        "and lead out of Moria. They are made of the same stone " +
        "as the mountain, blending into the wall perfectly. The only " +
        "way you know they are there is because of a faint outline " +
        "on the wall.\n");
    add_item(({"outline", "faint outline"}),
        "The faint outline is that of a gate. It is on the west wall, " +
        "showing the dimensions of the gate leading outside.\n");
    set_add_west_gate_stairs("Corpses lay at the bottom of the steps.");

    UP(TUN_DIR + "stairs02");

}

void
init()
{
    add_action("start_push","push");

    write("As you enter the gate-room, you remember that the doors "+
      "may be pushed to take you out of here.\n");
    ::init();

}

int
start_push(string str)
{

    if(!str)
    {
	notify_fail("Push what? The doors?\n");
	return 0;
    }
    if((str != "door") && (str != "doors"))
    {
	notify_fail("Push the " + str + "? Why?\n");
	return 0;
    }
    if (objectp(TP->query_attack()))
    {
	notify_fail("You are unable to safely operate the doors while in combat.\n");
	return 0;
    }
    if (TP->query_prop(DOORS_PROP))
    {
	NF("You push the doors again but they won't open any faster.\n");
	return 0;
    }

    say(QCTNAME(this_player())+ " pushes on the doors, and they begin "+
      "to open.\n");
    write("You push hard on the doors and they begin to open.\n");

    set_alarm(3.0, 0.0, &do_push(TP));
    TP->add_prop(DOORS_PROP, 1);
    return 1;

}

int
do_push(object player)
{
    object enemy;

    player->remove_prop(DOORS_PROP);
    if (!present(player, this_object()))
	return 1;
    if (objectp(enemy = player->query_attack()) && enemy->query_npc())
    {
	tell_room(this_object(), QCTNAME(enemy) +" slams into the "+
	  "doors which closes them tight.\n");
	enemy->command("$laugh");
	return 1;
    }
    set_this_player(player);

    write("You tumble through the doors as they open, spilling out onto "+
      "the ground outside.\n"+
      "The doors slam shut behind you.\n");
    say(QCTNAME(this_player())+ " tumbles through the open doors.\nThey "+
      "immediately slam shut again.\n");
    tell_room(WEST_GATE,QCTNAME(this_player())+ " comes tumbling out "+
      "of nowhere, you hear doors slam behind.\n");
    this_player()->move_living("M",WEST_GATE);

    return  1;

}
