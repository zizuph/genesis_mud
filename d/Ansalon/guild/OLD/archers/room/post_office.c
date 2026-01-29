
/* File name: post_office.c
 * Post office in the elven archers camp in the Qualinesti forest.
 * 
 * Blizzard, 06.11.2003
 */

#pragma strict_types

inherit "/d/Genesis/lib/post";
    
#include <files.h>
#include <mail.h>    
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/qualinesti/local.h"
#include "../guild.h"

inherit  GUILD_CAMP_BASE;


void
reset_qualinesti_room()
{

}

void
create_camp()
{
    set_short_desc("on the small clearing, next to the camp");
    set_long_desc("A few trained eagles are sitting on the small tree here. " +
        "Those birds carry the mail to places all around the realms.");

    add_my_desc("\n");
    
    OUTSIDE;
    
    add_exit(GUILD_ROOM + "archer_camp7.c", "west", 0, 1);    
    add_exit(GUILD_ROOM + "archer_camp5.c", "southwest", 0, 1);
    
    reset_qualinesti_room();
    
}

void
init()
{
    ::init();
    post_init();
}

void
leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}

void
mail_message(string new)
{
    write("\nYou have " + new + " mail waiting for you in the elven " +
        "Post Office.\n\n");
        
}
