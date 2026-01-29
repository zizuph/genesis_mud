/* /d/Faerun/guilds/vampires/rooms/in_air.c
 *
 * Nerull 2020
 *
 */

inherit "/d/Faerun/guilds/vampires/rooms/std/vampires_std_room";

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

void
dest_me()
{
    remove_object();
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_vampires_room()
{
    add_prop(ROOM_I_INSIDE, 0);

    set_short("Somewhere high up in the sky");
    
    set_long("Your are hanging somewhere high up in the "
    +"sky, only supported by a powerful claw clasped around your "
    +"neck! Below you see various landscape and clouds, openly "
    +"inviting you to fall into your doom! The entity "
    +"that is holding you is behind you, and you see nothing of him "
    +"or her!\n");
    
    set_alarm(3600.0, 0.0, &dest_me());

    reset_faerun_room();
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        // Security check, in case somebody ports here for some reason..
        if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 8)
        {
            setuid();
            seteuid(getuid());
            
            object join_paralyze = clone_object(VAMPIRES_GUILD_DIR
            +"obj/join_vamp_cutscene_paralyze.c")->move(this_player(), 1);
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 9)
        {
            setuid();
            seteuid(getuid());
            
            object join_paralyze = clone_object(VAMPIRES_GUILD_DIR
            +"obj/join_vamp_cutscene_paralyze.c")->move(this_player(), 1);
        }
    }
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


