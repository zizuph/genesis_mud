inherit "/std/room";

#include <macros.h>

#define ARENA_SHADOW            "/d/Shire/guild/AA/shadow/arena_shadow"

// Global Variables
static mapping  challenge = ([]);       // The challenge settings
static mapping  contestants = ([]);     // The contestant variables
static object  *spectators = ({});      // Spectators list

public status
add_spectator(object actor)
{
    if (IN_ARRAY(actor, spectators))
        return 0;
    
    actor->set_no_show();
    spectators += ({ actor });
    return 1;
} /* add_spectator */

public status
remove_spectator(object actor)
{
    if (!IN_ARRAY(actor, spectators))
        return 0;
    
    actor->unset_no_show();
    spectators -= ({ actor });
    return 1;
} /* remove_spectator */

public void
enter_arena(object actor)
{
    if (!interactive(actor))
        return;
    
    if (!actor->inside_arena())
    {
        object shadow = clone_object(ARENA_SHADOW);
        if (shadow->shadow_me(actor) < 1)
        {
            //Move the living out of the arena because shadow failed.
            //actor->move_living();
            return;
        }
        
        actor->enter_arena();
    }
} /* enter_arena */

public void
leave_arena(object actor)
{
    if (actor->leave_arena())
    {
        if (IN_ARRAY(actor, m_indexes(contestants)))
        {
            // Disabled for now, until it is coded... :P
            //restore_contestant(actor);
            m_delkey(contestants, actor);
        }
        
        remove_spectator(actor);
    }
} /* leave_arena */

public string
short_desc()
{
    if (IN_ARRAY(this_player(), spectators))
        return "In the pit stands";
    
    return "In the pit";
} /* short_desc */

public string
long_desc()
{
    if (IN_ARRAY(this_player(), spectators))
        return "In the pit stands.\n";
    
    return "In the pit.\n";
} /* short_desc */

/*
 * Function name:   create_room
 * Description:     The basic room constructor.
 * Arguments:       None
 * Returns:         Nothing
 */
void
create_room()
{
    set_short("@@short_desc@@");
    set_long("@@long_desc@@");
    //As soon as you enter, a putrid stench of sweat, blood and something
    //indistinguishable assaults your nostrils. In the center you see a long
    //hemp rope making out the borders of a circle. The ground, originally
    //covered in sand, now stained black from all the gore and bloodshed. This
    //is ‘the Pit’, the arena of the Army of Angmar. Here battles may be fought
    //to the brink of death to determine who is the strongest. Soldiers are
    //encouraged to resolve their differences here, rather than end up bickering
    //on the battlefield. The Pit also serves as a means to determine who is
    //most fit to lead this mighty army. Apart from the east exit leading back
    //to the Old Court, there are benches all around for other soldiers to sit
    //and cheer for their champion, or simply enjoy the spectacle of battle. You
    //also see a couple of buckets containing rotten fruit and vegetables.
    //To the right you see a plaque hanging on one of the benches.
    //You suddenly realize what the indistinguishable stench is; utter shame,
    //misplaced pride and ambition forlorn.
    
    //add_exit("east");
} /* create_room */

/*
 * Function name: prevent_enter
 * Description:   Called when an object is trying to enter this container to
 *                see if we will allow it in.
 * Arguments:     (object) ob - the object that is trying to enter.
 * Returns:       1 - The object is not allowed to enter
 *                0 - The object is allowed to enter
 */
public int
prevent_enter(object ob)
{
    if (ob->query_wiz_level())
        return 0;
    
    if (m_sizeof(contestants) && !IN_ARRAY(ob, m_indexes(contestants)))
    {
        if (challenge["private"])
            return 1;
        
        ob->catch_msg("A challenge has been issued, none but the contestants "
        + "may enter the pit. You take a seat on one of the benches to "
        + "spectate.\n");
        add_spectator(ob);
        return 0;
    }
    
    return 0;
} /* prevent_enter */

/* 
 * Function name:   enter_inv
 * Description:     Called when objects enter this container or when an
 *                  object has just changed its weight/volume/light status.
 * Arguments:       (object) ob: The object that just entered this inventory
 *                  (object) from: The object from which it came.
 * Returns:         Nothing
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (!ob->query_wiz_level())
        enter_arena(ob);
} /* enter_inv */

/* 
 * Function name:   leave_inv
 * Description:     Called when objects leave this container or when an
 *                  object is about to change its weight/volume/light status.
 * Arguments:       (object) ob: The object that just left this inventory.
 *                  (object) to: Where it went.
 * Returns:         Nothing
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    
    if (!ob->query_wiz_level())
        leave_arena(ob);
} /* leave_inv */

public status
do_challenge(string str)
{
    write("challenge issued\n");
    return 1;
} /* do_challenge */

public status
do_arena_commands(string str)
{
    string *allowed;
    
    /* Wizards arent affected by command block, but also cant challenge */
    if (this_player()->query_wiz_level())
        return 0;
        
    allowed = ({    "challenge", "quit", "east",    // The essential commands.
                    "l", "look", "exa", "examine",  // Interactive commands
                    "glance", "h", "health",        // Interactive commands
                    "cheer", "shout", "clap"        // Emotes
    });
    
    /* Limit spectator commands */
    if (IN_ARRAY(this_player(), spectators))
    {
        if (!IN_ARRAY(query_verb(), allowed))
        {
            this_player()->catch_msg("The stands are for spectating the "
            + "contestants combat, if you have other business, do it "
            + "elsewhere.\n");
            return 1;
        }
        return 0;
    }
    
    return 0;
} /* do_arena_commands */

/*
 * Function name:   init
 * Description:     Add commands to the player
 * Arguments:       None
 * Returns:         Nothing
 */
public void
init()
{
    ::init();
    add_action(do_challenge, "challenge");
    add_action(do_arena_commands, "", 1);
} /* init */