/*
   This is a cottage, suitable for a witch. Mortricia 920720

   Revised for the new Silver forest. Ragata has lost her lease
   on her quaint cottage and has sought out cheaper lodgings.
   I really feel that a hag now hag should have more modest
   surroundings..  -- Tomas  09/05
   
   Edited by Udana, added a cat, fixed random moving;] 03/2006
 */

#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"

inherit "/std/room.c";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define HARD_TO_KISS      25


object key, hag, cabinet, toad, cat;
/* A flag preventing multiply forest room adding exits to this room. */
int blocked = 0;

void unblock()
{
	blocked = 0;
}

public void set_exit(object from)
{
	if(!sizeof(query_exit()))
		add_exit(file_name(from), "out", 0);
	else if(query_exit()[0] != file_name(from))
	{
		remove_exit("out");
		add_exit(file_name(from), "out", 0);
	}
}

public int block()
{
	if(!blocked)
	{
		blocked = 1;
		return 0;
	}
	return blocked;
}
	

public void
close_and_lock()
{
    
    if (hag && present(hag) && present(key, hag))
        hag->close_shut();
}

public void
reset_room()
{
    seteuid(getuid());
    
    if (!hag) {
        hag = clone_object(HAG + "hag");
        hag->move(TO);
    }
    
    if(!cat)
    {
	cat = clone_object(HAG + "cat");
	cat->move(TO);
    }
    
    if (!key) {
        key = clone_object(HAG + "cabinet_key");
        key->move(hag);
        cabinet->set_key(key->query_key());
    }
   
    if (present(toad) ) {
        toad -> remove_object();
    }
    
    set_alarm(2.0, -1.0, close_and_lock);
}

init()
{
    add_action("kiss", "kiss");
    ::init();
}


public void
create_room()
{
    set_short("Hovel");
    set_long(
        "You are inside a drafty hovel dug halfway into the earth. " +
        "Patches of dim light shine through the badly thatched roof overhead. " +
        "The twig and branch walls offer very little protection from the harsh " +
        "elements outside. A large blackened cauldron swings gently " +
        "over a large fire pit dug into the middle of the earthen floor. Afixed " +
        "to the far wall is a sturdy wooden cabinet.\n");

    add_item(({"wall", "walls"}), "The outer walls are comprised of various " +
            "twigs and branches weaved together and strengthened with twine. " +
            "Dried mud mixed with hay and grass forms a rough mortar which " +
            "helps fill in the cracks. The walls are pitched black with soot " +
            "from the fire pit in the middle of the earthen floor and for " +
            "their modest design appear quite sturdy.\n");
    add_item(("mortar","mud"),"Mud mixed with hay and grass then dried " +
            "make up the mortar which helps seal in the cracks of the walls.\n");
    add_item(("earth","ground"),"The hovel has been partially dug beneath " +
            "the ground.\n");
    add_item(("dim light","light","rays"),"Rays of light shine through " +
            "holes in the thatched roof.\n");
    add_item(("thatched roof","thatch","roof"),"The thatched roof " +
            "is made of a twig frame, laced with reeds and covered with " +
            "a thick moss. A small hole used for ventilation has been " +
            "cut out of the roof just above the fire pit.\n");
    add_item(("hovel","cottage"),"@@set_long");
    add_item(("floor","earthen floor"),"The dirt floor has been " +
            "swept smooth. A fire pit has been dug in the middle of the floor.\n");
    add_item(("twig","branch","twigs","branches"),
            "Various twigs and branches of varied  " +
            "sizes. Mostly collected from the forest floor outside.\n");
    add_item(("earthen"),"Earthen means dirt. The floor is an 'earthen' floor.\n");
    add_item(("fire pit","pit","fire"),"A fire pit has been dug into the earthen " +
              "floor. A small fire burns heating the large cauldron hanging above.\n");
    add_item(("sturdy wooden cabinet","cabinet","wooden cabinet"),
              "A sturdy looking cabinet with a small keyhole hangs on one of the " +
              "walls.\n");
   
    add_prop(ROOM_I_INSIDE, 1);

    seteuid(getuid());
    
    clone_object(HAG + "pot")->move(TO);

    cabinet = clone_object(HAG + "cabinet");
    cabinet->move(TO);
    unblock();

    reset_room();
}

kiss(string str)
{
    object toad;

    toad = present("toad");
    if (str != "toad" || !toad)
    {
        return 0;
    }

    if (toad -> query_name() == "corpse")
    {
        write("You do not have the guts to kiss the dead toad.\n");
        say(QCTNAME(TP) + " tried to kiss the dead toad. " +
            "It's disgusting.\n");
        return 1;
    }

    if (TP -> query_skill(SS_ANI_HANDL) < 10 + random(HARD_TO_KISS))
    {
        write("You didn't have the guts to do that. " +
                 "The toad is too slimy.\n");
        say(QCTNAME(TP) + " tried to kiss the toad but failed.\n");
        return 1;
    }

    toad -> remove_object();

    write("POOF! When you kiss the toad it disappears into a dark cloud " +
             "of smoke. As the smoke disperses the contours of a human " +
             "become discernible.\n");
    say(QCTNAME(TP) + " managed to kiss the slimy toad.\n");

    clone_object(HAG + "prince") -> move(TO);

    return 1;
}
