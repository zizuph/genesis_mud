#include "/d/Ansalon/guild/society/guild.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>

inherit "/std/room.c";


void
create_room()
{
    set_short("Curious cluttered room");
    set_long("'follow kender ways' to join.\n");
}

  
int
occjoin(string str)
{
    object sh;
    mixed why;

    notify_fail("Follow what? Kender ways?\n");
    if (!str)
        return 0;

    if (str != "kender ways")
        return 0;

    setuid();
    seteuid(getuid());

    /* Clone the shadow */
    sh = clone_object(KENDERG_SHADOW);

    /* Try to add the shadow to the player */
    switch (sh->shadow_me(this_player(), "occupational", GUILD_STYLE, GUILD_NAME))
    {
    case 1:
        write("Welcome to the Secret Society of Uncle Trapspringer!\n");
        return 1;

    case -4:
        /* The player has an occ guild already, or one of his existing
        * guilds has blocked this one.
        */
        write("Your other guilds prohibit your joining this one!\n");
        break;

    default:
        /* Some error in shadowing */
        write("An error has prevented you from joining.\n");
        break;
    }

    /* We couldn't shadow the player, so remove the shadow */
    sh->remove_shadow();
    
    return 1;
}

void
init()
{
    ::init();
    add_action(occjoin, "follow");
}