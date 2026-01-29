/* /d/Faerun/guilds/vampires/obj/vamp_snatch.c
 *
 * Coffintoken. Rooms with this token can spawn coffins for vampires.
 *
 * Nerull, 2020
 *
 */

inherit "/std/object";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../guild.h";


object instances_room = 0;


void
remove_me()
{
	remove_object();
	
	return;
}


/*
 * Function name: add_instance_room
 * Description  : Builds the next room in the instance and adding proper
 *                exits.
 */
void
add_instance_room()
{
    instances_room = clone_object(ROOM_DIR+"in_air.c");
               
    return;
}


create_object()
{
    seteuid(getuid());
    
    set_name("vamp_snatch");
    add_name("_vamp_snatch");
    set_adj("invisible");
    set_short("vamp snatch");
    set_long("This is some weird anomality.\n");

    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_M_NO_SELL, 1);
	add_prop(OBJ_I_INVIS, 100);
    add_prop(OBJ_I_NO_STEAL, "Emh..no.\n");
    add_prop(OBJ_M_NO_GET, "Ehm..no.\n");
    
    set_no_show();
	
	//set_alarm(0.0, 0.0, &add_instance_room());
}


int
snatch_me()
{
    if (this_player()->query_race() == "human")
    {
        if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 8)
        {
            if ((this_player()->query_guild_name_race() == 0)
                && (this_player()->query_guild_name_lay() == 0))
            {
                write("\n\nSuddenly, you feel a powerful claw grasping "
                +"your neck and flies off with you into the air!\n\n");

                tell_room(instances_room, QCNAME(this_player())
                + " is hauled into the room by someone!\n", this_player());

                tell_room(environment(this_object()), QCTNAME(this_player())
                + " is suddenly snatched by a flying blurry shade, and pulled "
                +"high into the air and out of view!\n", this_player());
                
                instances_room = clone_object(ROOM_DIR+"in_air.c");

                this_player()->move_living("M", instances_room, 1);
        
                return 1;
            }	
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 9)
        {
            if ((this_player()->query_guild_name_race() == 0)
                && (this_player()->query_guild_name_lay() == 0))
            {
                write("\n\nSuddenly, you feel a powerful claw grasping "
                +"your neck and flies off with you into the air!\n\n");

                tell_room(instances_room, QCNAME(this_player())
                + " is hauled into the room by someone!\n", this_player());

                tell_room(environment(this_object()), QCTNAME(this_player())
                + " is suddenly snatched by a flying blurry shade, and pulled "
                +"high into the air and out of view!\n", this_player());

                this_player()->move_living("M", instances_room, 1);
        
                return 1;
            }
        }
    }   
    
    return 0;
}


/*
 * Function name: create_object()
 * Description  : Creates the object we wish to clone.
 */
void init()
{
    ::init();

    add_action(snatch_me, "east");
    add_action(snatch_me, "north");
    add_action(snatch_me, "west");
    add_action(snatch_me, "south");
}