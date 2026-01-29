/*
 * A bit of tricky code allowing for move of a player from old guild in
 * another domain here, without being kicked out. Important part of this
 * code is located in the old shadow and guild item.
 * 
 * Valen, 2004
 *
 * Altered by Lunatari to allowed the Mercenaries to move into the new
 * Sparkle domain 2006.
 *
 *
 */
#include "merc.h"

#define NEW_DIR       "/d/Sparkle/guilds/mercs/"
#define OLD_DIR       "/d/Genesis/guilds/merc/"
#define OLD_MASTER    (OLD_DIR + "room/join")
#define OLD_START_LOC (OLD_DIR + "room/start")
#define NEW_START_LOC (NEW_DIR + "room/start")
#define NEW_SHADOW    (NEW_DIR + "lib/merc_shadow")
#define NEW_LOG       (NEW_DIR + "log/shadow_move.log")
#define MOVE_LOG(x)   write_file(NEW_LOG, ctime(time()) + " " + (x))

public void
create(void)
{
    setuid();
    seteuid(getuid());
}

public string
short()
{
    return "guild move agent";
}

public void
log(string str)
{
    MOVE_LOG(str);
}

int move(object ob)
{
    string who = capitalize(ob->query_real_name());
    mixed err;
    mixed data;
    object sh;
            
    log("Move process started for player " + who + ".\n");

    setuid();
    seteuid(getuid());

    if(!MJOIN->query_member(who))
    {
        log("Problem player "+ who +" is not a member.\n");
	    return 0;
    }

    log("Passed member check.\n");

    err = catch(sh = clone_object(NEW_SHADOW));

    if(err)
    {
        log("Problem cloning the new shadow: " + err +"\n");
	// SERVER->remove_member(who);
	return 0;
    }

    if(ob->query_default_start_location() == OLD_START_LOC) 
    {
        if(!ob->set_default_start_location(NEW_START_LOC)) 
	{

	    log("Problem setting the new startloc.\n");
            return 0;
        }

        log("New startlocation successfully added.\n");
    }

    log("Passed shadow cloning.\n");

    /* Try to add the shadow to the player */
    if(sh->add_occ_shadow(ob) != 1)
    {
        sh->remove_shadow();
        //SERVER->remove_member(who);
        log("Shadowing failed, move aborted\n");
	return 0;
    }

    log("Passed adding shadow.\n");

    log("Player " + who + " successfully moved.\n");

    OLD_MASTER->remove_member(ob->query_real_name());

    return 1;
}

/* end of file */
