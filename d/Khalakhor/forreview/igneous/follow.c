/*
 * A follow shadow
 *
 * Activate it with a call to the function 'follow'
 *
 * Taken from Krynn's follow shadow and modified alot by Igneous 
 * to suite my needs :)
 * April 10th 1997
 *
 */

#include "/d/Shire/common/defs.h"
#include <config.h>
#include <macros.h>
#include <stdproperties.h>

#define MASTER_FOLLOW_SUBLOC "_master_following_subloc"

//  Debugging defs
#define DEBUGGING

#ifdef DEBUGGING
#define DEBUG_WHO  find_player("igneous")
#define DEBUG(s)   DEBUG_WHO->catch_msg(FOLLOW:  "+ s +"\n")
#else
#define DEBUG(s)
#endif


inherit "/std/shadow";

object gFollower;
int gFollow_stop = 0;

/*
 * Function name : follow_master
 * Arguments     : master - the master of the follower
 *                 follower - the follower who follows the master
 * Description   : Sets up this shadow on the master.
 */
public void
follow_master(object master, object follower)
{
    gFollower = follower;
    if (shadow_me(master) != 1)
	remove_shadow();
    else
	master->add_subloc(MASTER_FOLLOW_SUBLOC,TO);
}

/*
 * Function name : Remove_master_follow_shadow
 * Description   : removes this shadow.
 */
public void
remove_master_follow_shadow()
{
    remove_shadow();
}

/*
 * Function name : Query_follow_master
 * Description   : Querys if the gFollower is following shadow_who
 * Returns       : 0/1 
 */
public int
query_follow_master()
{
    return gFollow_stop;
}

public int
query_dog_follow_shadow()
{
    return 1;
}

/*
 * Function name : Start_following_master
 * Description   : Enables the gFollower to follow the shadow_who
 */
public void
start_following_master()
{
    gFollow_stop = 0;
}

/*
 * Function name : Stop_following master
 * Description   : disables the gFollower from following shadow_who
 */
public void
stop_following_master()
{
    gFollow_stop = 1;
}

/*
 * Function name : Show_subloc
 * Arguments     : see sman show_subloc
 * Description   : Adds a sublaction to the Followed player
 * Returns       : the sublocation string
 */
public string
show_subloc(string subloc,object who,object for_obj)
{
    if (who->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
      subloc != MASTER_FOLLOW_SUBLOC)
    {
	return shadow_who->show_subloc(subloc,who,for_obj);
    }
    if (!present(gFollower, environment(shadow_who)))
	return "";

    if (who == for_obj)
    {
	return "Your pet "+gFollower->query_name()+" is playing "+
	"about your feet.\n";
    }
    else
    {
	return CAP(HE_SHE(shadow_who))+" has a "+
	gFollower->query_nonmet_name()+" playing about "+
	HIS_HER(shadow_who)+" feet.\n";
    }
}

/*
 * Function name : Move living (MASKED)
 * Arguments     : See sman move_living for details
 * Description   : Makes sure gFollower follows whomever this shadow is 
 *                 stuck to.
 * Returns       : See sman move_living for details
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    string cmd;
    int flag, is_seen;

    cmd = query_verb();


    is_seen = CAN_SEE(gFollower, shadow_who);
    flag = shadow_who->move_living(how, to_dest, dont_follow, no_glance);

    if (gFollow_stop)
    {
	return flag;
    }

    if (!gFollower)
    {
	remove_shadow();
	return flag;
    }

    //  If we can't see our master why do we follow them?
    if (!is_seen)
	return flag;

    //  If we can see our master sneak after him otherwise just walk there
    if (shadow_who->query_prop(OBJ_I_HIDE))
	gFollower->command("$sneak "+ cmd);
    else
	gFollower->command("$" + cmd);

    //  Mmmm master got away from us somehow, better follow directly
    if (!present(gFollower, environment(shadow_who)))
    {
	//  Dogs can't magically teleport themselves 
	//  Unless it's master is a wizard of course ;)
	if (how == "X" && shadow_who->query_wiz_level())
	{

	    gFollower->move_living(how,to_dest,0,1);
	    return flag;
	}

	//  Don't want our dog here to follow people to the statue room.
	if (how == "M" && file_name(environment(shadow_who)) == OWN_STATUE)
	{
	    gFollower->notify_master_linkdead();
	    return flag;
	}

	if (how == "M" && gFollower->query_fatigue() >= 5)
	{
	    how = "direction "+HIS_HER(TO)+" master just left";
	    gFollower->move_living(how,to_dest,0,1);
	}
    }

    return flag;
}

/*
 * Function name : second_life (MASKED)
 * Description   : notify the puppy that it's master has been killed
 */
public int
second_life(object killer)
{
    gFollower->notify_master_died();
    return shadow_who->second_life(killer);
}

/*
 * Function name : remove_object (MASKED)
 * Description   : notify the puppy that it's master has been removed
 *                 from the game.
 */
public int
remove_object()
{
    gFollower->notify_master_removed();
    return shadow_who->remove_object();
}
