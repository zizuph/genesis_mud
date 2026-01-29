/*
  A bit of tricky code allowing for move of a player from old guild in
  another domain here, without being kicked out. Important part of this
  code is located in the old shadow and guild item.
  
  Valen, 2004
*/
#include "/d/Raumdor/defs.h"
#include "guild.h"

#define MOVE_LOG_FILE LOG + "move_log"
#define MOVE_LOG(x) write_file(MOVE_LOG_FILE, ctime(time()) + " " + (x))
#define MOVE_OBJECT GUILD_DIR + "move_object"

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
            
    log("Move process started for player " + who + "\n");

    SERVER->remove_member(who); // temporary

    err = catch(data = SERVER->query_member(who));

    if(err)
    {
        log("Problem communicating with new guild server: " + err);
	return 0;
    }

    if(data)
    {
        log("The player " + who + " is already member, move aborted\n");
        return 0;
    }

    if(!SERVER->add_member(who, SURNAMES[random(sizeof(SURNAMES))], 0))
    {
        log("Server does not accept the new player, move aborted\n");
        return 0;
    }
    
    err = catch(sh = clone_object(SHADOW));

    if(err)
    {
        log("Problem cloning the new shadow: " + err);
	SERVER->remove_member(who);
	return 0;
    }

    /* See if this member is acceptable */
    if (stringp(err = sh->acceptable_member(ob)))
    {
        log("Moved player " + who + "refused due to: " + err + "\n");
        sh->remove_object();
        SERVER->remove_member(who);
        return 0;
    }

    /* Try to add the shadow to the player */
    if(sh->add_race_shadow(ob) != 1)
    {
        sh->remove_shadow();
        SERVER->remove_member(who);
        log("Shadowing failed, move aborted\n");
	return 0;
    }

    if (!present(OBJECT_ID, ob))
    {
        err = catch(clone_object(OBJECT)->move(ob));
        if(err)
        {
            log("Cloning of guild item failed: " + err);
        }

        err = catch(clone_object(MOVE_OBJECT)->move(ob));
        if(err)
        {
            log("Cloning of move object failed: " + err);
        }
    }

    log("Player " + who + " successfully moved\n");

    log_file("thanar_members", capitalize(TP->query_real_name()) +
         " moved " + ctime(time()) + "\n");

    return 1;
}

/* end of file */
