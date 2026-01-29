/* 
 * Dead end tunnel, hidden exit here
 * Altrus, July 2005
 *
 * 2005/09/16 Last update
 * 2011/07/22 Lavellan - Made indoors and dark.
 * Dec 2017 Finwe, Made room non teleportable.
 */
#include "/d/Shire/sys/defs.h"

#include <stdproperties.h>

#define DID_ATTACK "_attacked_burzum"
#define IS_STUN "_stunned_by_burzum"

inherit "/d/Shire/std/room";

object large_uruk;

void create_shire_room()
{
	set_short("A dead end in a mining tunnel");

	set_long(short() + ". This dead end in the tunnel is probably where " +
        "the dwarves of old delved for Moria-silver, but the vein probably " +
        "ended in this direction. It is dark and forboding here, the " +
        "walls close in and oppressive.\n");
	
	add_item("walls", "The walls are dark, and look like they have been " +
        "chipped away with tools. There is something odd about the north " +
        "wall.\n");
	add_item("north wall", "Yes, there is indeed something odd about " +
        "the north wall, as it is not a wall, but a passage that " +
        "leads north from this room.\n");
	
	add_exit("/d/Shire/moria/mines/mining/mining.8", "south");
	add_exit("/d/Shire/moria/mines/mining/treasure_room", "north", "@@exit_check@@", 0, 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_NO_TELEPORT,"That is not possible here.\n");
	
	reset_shire_room();
}

void reset_shire_room()
{
	if(!large_uruk)
	{
		large_uruk = clone_object("/d/Shire/moria/npc/burzum");
		large_uruk->move(TO);
		tell_room(TO, capitalize(LANG_ADDART(large_uruk->query_nonmet_name()))+ 
            " stalks into the mining tunnel, growling angrily.\n");
	}
}

int exit_check()
{
	if(present("_burzum_blocks_exit", TO))
	{
		write("The hulking brutish uruk-hai blocks your way.\n");
		return 1;
	}
	
	else if(present("_uruk_ally_npc_", TO))
	{
		write("There's no getting through with orcs in the way.\n");
		return 1;
	}
	
	else
		return 0;
}

int stun_attacker(object ob)
{
	object stun;
	int damage;
	write("The hulking uruk-hai head-butts you hard, leaving you dazed.\n");
	say("The hulking uruk-hai head-butts " + QCTNAME(ob) + ", leaving " + 
        HIM_HER(ob) + " dazed.\n");
	stun = clone_object("/d/Shire/moria/obj/b_stun_obj")->move(ob);
	damage = (ob->query_hp()/10);
	ob->heal_hp(-damage);
	return 1;
}

void enter_inv(object ob, object from)
{
	::enter_inv(ob, from);
	if(ob->query_prop(DID_ATTACK))
	{
		if(large_uruk)
		{
			set_alarm(0.5, 0.0, &stun_attacker(ob));
		}
	}
}
