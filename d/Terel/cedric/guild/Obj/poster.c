#pragma save_binary

inherit "/std/object.c";
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Terel/cedric/guild/guild_defs.h"

/*
 * Wanted Poster: these posters, which appear in the Guildmaster's office, 
 * show the names and faces of those wanted by the Minstrels guild for some
 * terrible crime. The guildmaster shall take no action concerning these
 * people but mortal Minstrels are encouraged to form and execute their 
 * own sentences upon the wretched criminals.
 * 
 * NOTE: At the moment, the only way to get a poster made of yourself is 
 * to kill one of the guild NPCs. This will soon be extended so that any 
 * player who kills a Minstrel will get their face on a poster, at least 
 * until the next time the game reboots. 
 */

void 
create_object()
{
    set_name("poster");
    set_short("wanted poster");
    set_pshort("wanted posters");  
}

void
set_post(object killer, string dead)
{
    set_long(BS("The poster shows the face of "
    + LANG_ADDART(killer->query_nonmet_name())
    + ". Underneath is written: "+killer->query_name()+"!\n")
    + BS("This "+killer->query_race_name()+" has killed our beloved comrade "
    + dead+ " in cold blood. Visit upon "+killer->query_objective()
    + " what justice you see fit.\n"));
}
