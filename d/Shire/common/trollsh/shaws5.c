/* File: /d/Shire/common/trollsh/shaws5.c */
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/
#include "defs.h"
#include <language.h>
#include <stdproperties.h>
#include <macros.h>

#define MAX_TROLLS 4
int num_trolls, alarm_id;
void add_stuff();
object *troll;

create_shawrom()
{
    set_short("Northeast on a small ridge.");
    set_extraline("You are on the northeast edge of one "
	+"of the ridges here in the Trollshaw. This place is "
	+"overgrown with very dense bush. In the north a pine "
	+"forest makes you wonder if this place is a very "
	+"safe place to be. To the northeast there is a small path "
	+"leading down through the bushes. But they are so dense you can't "
	+"see where the path leads. Walking west or south will take you "
	+"to another part of this ridge. ");

	troll = allocate(MAX_TROLLS);	
	enable_reset();
	add_stuff();
	add_prop(ROOM_I_NO_CLEANUP,1);

    add_item("path","The path winds it's way among the bushes.\n");

	NORTH("shaws6");
	WEST("shaws2");
	SOUTH("shaws4");
	NORTHEAST("shaws7");
       
    
}

void
add_stuff()
{
    alarm_id = set_alarm(2.0,0.0,"make_trolls");
}

reset_shawrom()
{
    add_stuff();
}

make_trolls()
{
    if(!troll[num_trolls])
    {
        troll[num_trolls] = clone_object(TROLLSH_DIR + "npc/trollguard");
        troll[num_trolls]->move(TO);
        tell_room(TO, CAP(LANG_ADDART(troll[num_trolls]->query_nonmet_name())) +
        " comes lurking trough the forest.\n");
    }
    num_trolls++;
    if(num_trolls == MAX_TROLLS)
    {
        num_trolls = 0;
        return;
    }
    alarm_id = set_alarm(2.0,0.0,"make_trolls");
}
