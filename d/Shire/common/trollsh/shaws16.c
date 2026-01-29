/* File: /d/Shire/common/trollsh/shaws16.c */
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
    set_short("On a ridge deep in the Trollshaws.");
    set_extraline("You are on the northeast ridge of the " +
        "Trollshaws. To the east is a path going through some " +
        "bushes while to the south and west the ridge continues. " +
        "Northeast and northwest there are some narrow paths that " +
        "would take lead down from this ridge.\n");

    
    troll = allocate(MAX_TROLLS);	
    enable_reset();
    add_stuff();
    add_prop(ROOM_I_NO_CLEANUP,1);
    
    add_exit(TROLLSH_DIR + "shaws19", "east", 0);
    add_exit(TROLLSH_DIR + "shaws15", "south", 0);
    add_exit(TROLLSH_DIR + "shaws25", "west", 0, 1);
    add_exit(TROLLSH_DIR + "shaws20", "northeast", 0);
    add_exit(TROLLSH_DIR + "shaws22", "northwest", 0);
    
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
           " comes screaming trough the forest towards you!\n");
    }
    num_trolls++;
    if(num_trolls == MAX_TROLLS)
    {
        num_trolls = 0;
        return;
    }
    alarm_id = set_alarm(2.0,0.0,"make_trolls");
}
