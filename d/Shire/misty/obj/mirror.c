/*
 * Changed a little here so you can see the room with the eye even with brief.
 * Rohim
 *
 * Mirror no longer recovers.
 * -- Finwe March 2004
 *
 */

inherit "/std/object.c";
inherit "/lib/keep.c";

#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "../local.h"

#define MANA_LIMIT      15 /* How much mana does it cost to look at mirror */
#define CAST_LIMIT      50 /* How wise and skilled must the caster be? */

public int     polish(string mirror);
public string  long_mirror();
public void    make_eye();

static object  eye_object;
static int     mirror_is_polished = 0;

void 
create_object()
{
    seteuid(getuid());

    set_name("mirror");
    set_pname("mirrors");
    set_adj("silver");
    set_long(long_mirror);

    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME,  300);
    add_prop(OBJ_I_VALUE,   350);

    add_prop(MAGIC_AM_MAGIC, ({ 20, "divination" }) );
    add_prop(MAGIC_AM_ID_INFO, 
      ({ "The mirror appears to possess some hidden ability.\n", 10, 
	"Polishing the mirror will have surprising results.\n", 40, 
	"Looking into the polished mirror allows to look through "
	+ "a glass eye that is magically linked to this mirror.\n", 60, }) );

    set_alarm(5.0, 0.0, make_eye);
}

public void 
make_eye()
{
    if (objectp(eye_object)) 
	return;

    eye_object = clone_object(MISTY_OBJ_DIR+"eye");
    eye_object->add_prop("_mirror_to_this_eye", file_name(TO));
    eye_object->move(CAVE_DIR + "d12");
    eye_object->add_prop(OBJ_I_HIDE, 40);
    return;
}

public string 
long_mirror()
{
    object  room, this_room, last_room,
    *objs,
    *live,
    *dead;
    int     player_has_light;
    string  desc = "";

    if (objectp(TP->query_attack()))
	return "Don't look at your possesions and fight you coward!!!\n";

    if (!mirror_is_polished)
    {
        desc = "This is is a nice little silver mirror. It's a bit dusty though.\n";
	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	    return desc + "When you look into it, no reflection can be seen.\n";
	return desc + "When you look in it you see some ugly face "+
	"looking back at you.\n";
    } 
    else
    {
	mirror_is_polished = 0;
        desc = "This is a nice, little silver mirror.\n";

	if (TP->query_mana() < MANA_LIMIT)
	    return desc + "You can't concentrate enough to focus on mirror.\n";

	TP->add_mana(-MANA_LIMIT);

	if (random(TP->query_stat(SS_WIS) +
            TP->query_stat(SS_SPELLCRAFT)) < random(CAST_LIMIT))
            return desc + "You tried to look at the mirror but can't " +
            "seem to focus. Your eyes go cross-eyed and make " +
            "faces at everyone.\n";

	if (objectp(eye_object))
	{ 
	    room = eye_object; 
	}
	else 
	    room = TO;
	while (!(room = environment(room))->query_prop(ROOM_I_IS))
	    ;

	/*
	 * Check if it is legal to use to mirror to examine the room of the eye:
	 */
	if (room->query_prop(ROOM_I_NO_MAGIC))
	    return desc + "You concentrate hard and manage to focus on the mirror.\n"
	    +  "You cannot make out anything in the mirror however.\n";

	this_room = environment(TP);

	desc += "You concentrate hard and manage to focus on the mirror. "+
	  "You see following:\n";


	/*
	 * We just calculate the long description of the target room
	 * and print it to the player.
	 * Known problems: no check for light levels.
	 */
//	if (CAN_SEE(TP, eye_object))
    if (CAN_SEE(TP, eye_object) && TP->query_prop(MIRROR_CHECK))

	{
	    desc += room->long();
/*
        if (sizeof(dead = FILTER_DEAD(objs = all_inventory(room))))
		desc += capitalize(COMPOSITE_DEAD(dead)) + ".\n";
	    if (sizeof(live = FILTER_LIVE(objs)))
		desc += capitalize(COMPOSITE_LIVE(live)) + ".\n";
*/

	}
	else
	    desc += "The mirror is completely black.\n";
	return desc;
    }
}

public void
init()
{
    ::init();
    add_action(polish, "polish");
}

public int 
polish(string mirror)
{
    if (mirror == "mirror")
    {
	write("You polish your silver mirror. It sparkles in the light.\n");
	mirror_is_polished = 1;
	return 1;
    }
    NF("Polish what?\n");
    return 0;
}

/*
string 
query_recover()
{ 
    object room; 
    room = eye_object;
    if (!objectp(room)) 
	return MASTER;
    while(environment(room)) 
	room = environment(room);
    return MASTER + ":" + file_name(room);
} 

void 
init_recover(string arg)
{ 
    string room, foobar;

    eye_object = clone_object(MISTY_OBJ_DIR+"eye");
    eye_object->add_prop("_mirror_to_this_eye", file_name(TO));
    eye_object->add_prop(OBJ_I_HIDE, 40);
    if (!eye_object->move(arg))
    {
	eye_object->remove_prop(OBJ_I_HIDE);
	eye_object->move(environment());
    }
} 
*/

void 
remove_object()
{
    object room; 
    if (eye_object)
    {
	room = eye_object; 
	while(!(room=environment(room))->query_prop(ROOM_I_IS))
	    ;
	eye_object->remove_object();
	tell_room(room, "A glass eye suddenly turns into dust.\n");
    }
    ::remove_object();
} 
