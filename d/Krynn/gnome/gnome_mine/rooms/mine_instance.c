/*
 	Mine instanceroom.
 
 	Original code (used for an instanced dungeon): Nerull, 15.04-15
 	Modified by: Maelstrom, 2016/01

    Updated: 
    Maelstrom, 2016/05
    Maelstrom, 2017/01
    Maelstrom, 2017/04

 */


/*

	TODO:

	add caveins (?) (a tunnel collapses behind you) (or several) (random chance on moving?)
	add random monsters (?) (cave mole?)
	we could add black powder. (coal, sulfur, nitre) (into a container to make explosive for mining), and have it explode a few rooms at once xD


	add lava powered messages when mining. (not sure about this yet)
    "Aided by the power of the diamond edged lava powered pickaxe you smash through the rocks."
    "With the help of the diamond edged lava powered pickaxe you cut through rock like butter."
	


	ohhhh i just had the best idea for such a monster, make it attach to ur face, 
	then ur blind, right? so then, if you try to remove it and wield a sword, without 
	specifing remove with sword, you'll be all clumsy and drop ur sword while trying to
	get it off with ur hands, and as ur blind, you cant pick it back up.
	so then you'll have to punch ur face against something or with something till it falls off.
	with a skill check if you try to remove with sword, to see if you damage urself.
	and if you punch yourself you get damaged as well.



    if you are climbing wielding something, % of dropping it deppending on your climbing skill.




    make mining/climbing/lockpicking/trap disarming more interactive, using skill to direct the player to the best choice.
    ex: you start lockpicking, you need to move the lockpick inside/outside/up/down. and hold the torque to the side.
    your instict tells you....
    your expertice as a XXXXX makes you suspect the best would be....

*/

inherit "/std/room";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>


inherit "/d/Sparkle/area/city/rooms/delay_room";

#include "/d/Genesis/gems/gem.h"
#include "../defs.h"
#include "../ores/ore_dispenser.c"

#include "mine_instance_actions/mine_instance_definitions.c"

#include "mine_instance_actions/mine_instance_rope.c"

#include "mine_instance_actions/mine_instance_dig.c"
#include "mine_instance_actions/mine_instance_climb.c"

#include "mine_instance_actions/mine_instance_desc_mine.c"
#include "mine_instance_actions/mine_instance_desc_cave.c"
#include "mine_instance_actions/mine_instance_desc_dung.c"

/*	Function name: create_room
	Description: creates the room and gives it attributes, the room is inside and with no light.

*/
void
create_room()
{
    setuid();
    seteuid(getuid());

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -1);

    reset_room();
}


/*
 * Function name: init
 * Description  : When a player arrives, the dungeon keeps building 
 * more rooms until the limit is met. you can dig/mine/excavate in all 4 cardinal directions 
 * and also keep going down.
 */
void
init()
{
    ::init();
    add_action(do_dig, "dig");
    add_action(do_dig, "mine");
    add_action(do_dig, "excavate");

    add_action(do_throw, "throw");
    add_action(do_pull, "pull");

    add_action(do_climb, "climb");
}


/*
 * Function name: reset_room
 * Description  : Resets the room/states/npc spawns.
 */
void
reset_room()
{
}

