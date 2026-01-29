/* goblin caves
 * Made it impossible to push door when you can't see it. Rohim
 *
 * Noticed in the RHov bug logs players were able to get the excellent
 * halberd without killing the goblin lord. I suspected players were
 * going linkdead and coming back after some time and taking it so I 
 * added the enter_inv check from the statue room and move the players
 * to where the goblin lord loads.
 * -Igneous-
 */

#include <filter_funs.h>
#include <ss_types.h>
#include <money.h>
#include "../local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);

    set_short("big hall");
    set_long("This big hall is very different from other parts of caves. "+
      "It is surprisingly clean and well lit by many torches. "+
      "Somehow you can guess that not every goblin is allowed "+
      "into this place. Maybe the Goblin Lord himself lives here. "+
      "To the north is a door that leads back to the tunnels.\n");

    add_item(({"torch","torches"}), "There are many torches fastened to "+
      "the walls all around.\n");
    add_item("door", "This is the other side of the secret door. Goblins "+
      "haven't even tried to hide it from this side. So you "+
      "can simply push it to get through.\n");
    add_item(({"wall","walls"}),"These walls seems to be natural. But "+
      "then again you have seen so many strange things in these "+
      "caves that you are not sure with anything you see or feel.\n");

    add_exit(CAVE_DIR+"d11", "east", "@@block_exit");
    add_prop(ROOM_I_NO_STEAL, 1);
    reset_shire_room();
}

int
block_exit(string room)
{
    if (present("_misty_goblin_", TO))
    {
	write("The Goblin Lord completely blocks the exit with his body, " +
        "preventing you from passing.\n");
	return 1;
    }
    return 0;
}

void
reset_shire_room()
{
    object goblin1, bottle, treasure_room, shout_room; 

    setuid();
    seteuid(getuid());

    call_other(CAVE_DIR+"d12", "??");
    treasure_room = find_object(CAVE_DIR+"d12");
    call_other(CAVE_DIR+"d11", "??");
    shout_room = find_object(CAVE_DIR+"d11");

    if (!present("_misty_goblin_"))
    {
	if (sizeof(FILTER_PLAYERS(all_inventory(TO))) ||
	  sizeof(FILTER_PLAYERS(all_inventory(treasure_room))) ||
	  sizeof(FILTER_PLAYERS(all_inventory(shout_room))))
	{
	    set_alarm(200.0, 0.0, reset_shire_room);
	    return;
	}
	goblin1 = clone_object(GOBLIN_NPC_DIR+"gcave_lord");
	goblin1->add_prop(LIVE_I_SEE_DARK, 4);
#ifndef LORD_WIELDS_HALBERD
	goblin1->arm_me();
#endif
	goblin1->move_living("xxx", this_object());
	clone_object(MISTY_OBJ_DIR+"mirror")->move(goblin1);

	call_other(treasure_room, "get_rune_text");

#ifndef LORD_WIELDS_HALBERD
	if (!present("_shire_strange_halberd",treasure_room))
	    clone_object(MISTY_WEP_DIR + "halberd_sup")->move(treasure_room);
#else
	if (!(present("coin", treasure_room)))
	    MONEY_MAKE_GC(50)->move(treasure_room);
#endif

#ifndef QUESTS_CLOSED	
	if (!present("_misty_prisoner_key_", treasure_room))
	    clone_object(MISTY_OBJ_DIR + "prisoner_key")->move(treasure_room);
#endif

	if (!present("_goblin_barrel_", treasure_room))
	{
	    bottle = clone_object(MISTY_OBJ_DIR+"bottle");
	    bottle->set_max(50000);
	    bottle->set_soft(20000+random(20000));
	    bottle->set_alco(bottle->query_soft() / 2);
	    bottle->set_filled_short("best whiskey");
	    bottle->set_name("barrel");
	    bottle->add_name("_goblin_barrel_");
	    bottle->set_pname("barrels");
	    bottle->set_adj("wooden");
	    bottle->set_short("wooden barrel");
	    bottle->set_pshort("wooden barrels");
	    bottle->move(treasure_room);
	}
    }
}

void
init()
{
    ::init();
    add_action("push_something", "push");
}

int
push_something(string something)
{

    if (present("_misty_goblin_", TO))
    {
	    write("The Goblin Lord completely blocks the exit with his body, " +
        "preventing you from passing.\n");
	    return 1;
    }

    
    if (!CAN_SEE_IN_ROOM(TP))
    {
	TP->catch_msg("You search and fumble in the darkness but find " +
	  "nothing!\n");
	return 1;
    }
    if(something=="door")
    {
	TP->catch_msg("The door opens. You quickly pass through it before it swings back and closes.\n");
	say(QCTNAME(TP)+" opens a door in the wall and disappears. The door swings back and closes.\n");
	tell_room(CAVE_DIR+"t25",QCTNAME(TP)+" enters the room through a "+
	  "secret door.\n");
	TP->move_living("M",CAVE_DIR+"t25");
	return 1;
    }
    return 0;
}
