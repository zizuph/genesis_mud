/*
 * - murray.c
 *
 * Lucius, Dec 2017: Self-destruct upon entering Sparkle church.
 * 		     It is a designated "quiet" zone.
 *
 */
#pragma save_binary
//#pragma strict_types

inherit "/std/monster";

#include <composite.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <filter_funs.h>

// Delay of the skull movement check.
#define DELAY  3.0
// How many tries before we go poof?
#define TRIES  5
// Delay to drain mana.
#define MANA_DELAY  300.0
// Mana drain / skull.
#define MANA_DRAIN  10
// How much damage we do on death.
#define DEATH_DAMAGE  (random(201) + 100)
// The prop we add to players.
#define THRALL_ACTIVE       "_thrall_active"
// Unique identifier for the skulls.
#define THRALL_LINK_OBJ_ID  "vthrall::thrall_link_obj"

#define MAST_THRALL_LINK_OBJ   "_mast_thrall_link_obj"
#define SLAV_THRALL_LINK_OBJ   "_slav_thrall_link_obj"

private static object player, *other_thrall_link_objs = ({ });
private static int master, muted, tries, alarm1, alarm2;

/*
 * Create the basic skull.
 */
void
create_monster()
{
    set_gender(2);   
    set_race_name("thrall_link_obj");
    set_name("_thrall_link_obj");

    add_prop(OBJ_I_INVIS,         100);  // testing parameter.
    add_prop(LIVE_I_NO_ACCEPT_GIVE, 1);
    add_prop(LIVE_I_NO_GENDER_DESC, 1);
    add_prop(LIVE_I_NO_FOOTPRINTS,  1);
    add_prop(LIVE_I_NO_CORPSE,      1);
    add_prop(LIVE_I_NO_BODY,        1);
    add_prop(LIVE_I_SEE_INVIS,     99);
    add_prop(LIVE_I_NEVERKNOWN,     1);
    
    add_prop(OBJ_M_NO_ATTACK, "\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "\n");

    set_stats(({ 30, 30, 30, 30, 30, 30 }));
    set_skill(SS_AWARENESS, 99);

    /* Command questions. */
    add_ask("thrallend", this_object()->dismiss_thrall_link_obj, 1);
    add_ask("thrallreport", this_object()->report_thrall_link_objs, 1);
    add_ask("thrallmute", this_object()->mute_thrall_link_obj, 1);
    add_ask("thrallscrutinize", this_object()->see_envi, 1);
    add_ask("thrallsay", this_object()->do_sksay, 1);

    set_no_show_composite(1);
}


/*
 * This is how we sound to others.
 */
public string
race_sound(void)
{
    return "intones";
}


/*
 * Skull removal.
 */
public void
remove_object(void)
{
    /* Remove alarms. */
    if (alarm1) remove_alarm(alarm1);
    if (alarm2) remove_alarm(alarm2);

    /* Nuke slave skulls. */
    if (master)
    {
        //other_skulls->command("emote vanishes into noting.");
        other_thrall_link_objs->remove_object();
    }

    /* Let us know we have been nuked. */
    /*tell_room(environment(),
	capitalize(LANG_THESHORT(this_object())) +
	" vanishes into the shadows.\n", this_object());*/

    /* Remove reference prop. */
    player->remove_prop(THRALL_ACTIVE);

    /* Nuks us. */
    ::remove_object();
}


/*
 * Default reply for non-owners asking the skull things.
 */
private string
not_my_thrall_link_obj(void)
{
   /* write(capitalize(LANG_THESHORT(this_object())) +
	" glares at you with baleful malevolence.\n");

    say(capitalize(LANG_THESHORT(this_object())) +
	" glares at "+ QTNAME(this_player()) +
	" with baleful malevolence.\n",
	({ this_object(),  this_player() }));*/

    return "";
}


void describe_room(object room)
{  
    write(room->long());
    write(capitalize(FO_COMPOSITE_LIVE(FILTER_CAN_SEE(FILTER_LIVE(all_inventory(room)),this_player()),this_player()))+"\n");
    write(capitalize(FO_COMPOSITE_DEAD(FILTER_CAN_SEE(FILTER_DEAD(all_inventory(room)),this_player()),this_player())+"\n")); 
}


/*
 * This is where the skull relays the received messages.
 */
public void
broadcast_msg(mixed str, object from)
{
    /* Just in case. */
    if (muted)
	return;
	
    if (this_object()->query_prop(SLAV_THRALL_LINK_OBJ))
    {
    	//tell_room(environment(),
        //"\n", this_object(), from);
        //tell_room(environment(), str, this_object(), from);
        return;
    }
    
    if (this_object()->query_prop(MAST_THRALL_LINK_OBJ))
    {
    	/* This needs to be split to function properly. */   
        //tell_room(environment(),
        //"//The "+ query_short() +" emits: ", this_object(), from);
        
        //tell_room(environment(), str, this_object(), from);
        
        player->catch_tell(environment(),
        "You sense through your thrall: ", this_object(), from);
        
        player->catch_tell(environment(), str, this_object(), from);
        
        
        return;
    }

    return;
}


int
do_sksay(string str)
{
   // if (this_player() != player)
	//return 0;
    
    if(!str)
    { 
        write("thrallsay what?\n");
        
        return 0;
    }
 
    tell_room(environment(other_thrall_link_objs[0]), "A whisper echoes: "+str+"\n"); 
    
    return 1;
}


public void
see_envi(string str)
{
	object dest;
	
	if (this_player() != player)
	return;
	
	dest = environment(other_thrall_link_objs[0]);
	 
	//command("ask "+ OB_NAME(player) + " " +
	//"Master, this is what I see:");
    
    //player->catch_tell("Through thrall-link, you see:\n");
     command("ask "+ OB_NAME(player) + " " +
	 "Master, this is what I see:");
    
	set_alarm(0.0,0.0, &describe_room(dest));
}


/*
 * Masked to capture room spam.
 * Anything captured is then broadcast to
 * the other linked skulls.
 */
public void
catch_msg(mixed str, object from_player)
{
    object *thrall_link_objs, dest, room, place;

    if (!str)
	return;


    /* Filter out muted skulls. */
    thrall_link_objs = filter(other_thrall_link_objs, not @ &->query_muted());
    
    /* Filter out skulls in same room. */
    thrall_link_objs = filter(thrall_link_objs, objectp);
    
    thrall_link_objs = filter(thrall_link_objs, &operator(!=)(environment()) @ environment);
    
    thrall_link_objs->broadcast_msg(str, this_object());
}


/*
 * Mute / unmute the skull.
 */
public string
mute_thrall_link_obj(void)
{
    if (this_player() != player)
	return not_my_thrall_link_obj();

    if (muted = !muted)
    {
       // command("ask "+ OB_NAME(player) + " " +
         //   "Master, I shall hush my grisly self.");
            
        //player->catch_tell("Thrall-link muted.\n");
    }
    else
    {
       // command("ask "+ OB_NAME(player) + " " +
         //   "Master, I shall speak freely now.");
            
        //player->catch_tell("Thrall-link unmuted.\n");
    }

    return "";
}


/*
 * Ask the skull to report on it's linked skulls.
 */
public string
report_thrall_link_objs(void)
{
    string *arr;

    if (this_player() != player)
	return not_my_thrall_link_obj();

    if (!master)
    {
        arr = ({ other_thrall_link_objs[0]->query_linkage()->query_name() });
    }
    else
    {
        arr = map(map(other_thrall_link_objs, &->query_linkage()),
                    &->query_name());
    }

    //command("ask "+ OB_NAME(player) +
	//" Master, I am linked to the following:");
    
    //command("ask "+ OB_NAME(player) + " " +
	//COMPOSITE_WORDS(sort_array(arr)));
    
   // player->catch_tell("You are thrall-linked to the following: "
    //+COMPOSITE_WORDS(sort_array(arr)));

    return "";
}


/*
 * Add a skull to the chain.
 */
public void
link_thrall_link_obj(object thrall_link_obj)
{
    /* If we are the master skull, and we already
     * have links to other skulls, connect new skulls
     * to the existing network. */
    if (master)
    {
        int size = sizeof(other_thrall_link_objs);

        while(size--)
            thrall_link_obj->link_thrall_link_obj(other_thrall_link_objs[size]);
    }

    other_thrall_link_objs += ({ thrall_link_obj });
}


/*
 * Unlink a skull from the chain.
 */
public void
unlink_thrall_link_obj(object thrall_link_obj)
{
    other_thrall_link_objs -= ({ thrall_link_obj });

    if (master)
    {
        int size = sizeof(other_thrall_link_objs);

        if (!size)
        {
            /* The network is gone, remove the master. */
            //command("say Master, my other selves are no more.");
            
            //player->catch_tell("Thrall-link disconnected.\n");
            set_alarm(0.0, 0.0, &remove_object());
        }
        else
        {
            /* Let the caster know the network has shrunk. */
            //command("say Master, I have lost contact with one "+
            //"of my other selves.");
            
            //player->catch_tell("Thrall-link shrunk.\n");
        }
    }
}


/*
 * Used to dismiss a skull.
 */
public string
dismiss_thrall_link_obj(string str)
{
    int index;
    string *arr = ({ "thrall_link_obj" });

    /* Only the owner may dismiss, or the master skull. */
    if (this_player() != player)
    {
        if (calling_object() != other_thrall_link_objs[0])
            return not_my_thrall_link_obj();
        else
            command("say Master, I have been instructed to depart.");
            //player->catch_tell("Thrall-link ended.\n");
    }

    if (!strlen(str))
    {
        /* This is for the 'add_ask' bit. */
        str = "thrall_link_obj";
    }
    else if (master)
    {
        /* Add in a list of linked skulls to the master. */
        arr += map(map(other_thrall_link_objs, &->query_linkage()),
                    &->query_real_name());
    }

    /* Invalid choice. */
    if ((index = member_array(str, arr)) == -1)
    {
        //command("grimace helpless");
        return ""; 
    }

    /* Are we dismissing our own skull? */
    if (str == "thrall_link_obj")
    {
        if (this_player() == player)
            //command("say Master, it shall be as you command.");
            //command("emote vanishes.");
            //player->catch_tell("Thrall-link ended by request.\n");

        other_thrall_link_objs->unlink_thrall_link_obj(this_object());
        set_alarm(0.0, 0.0, &remove_object());
    }
    else
    {
        /* The master has dismissed a slave skull. */
       object thrall_link_obj = other_thrall_link_objs[--index];

       player->catch_tell("Thrall-link ended by request2.\n");
        thrall_link_obj->dismiss_thrall_link_obj("thrall_link_obj");
    }

    return "\n";
}


/*
 * Allow you to selectively dismiss skulls.
 */
public void
catch_question(string str)
{
    string who;

    if (!sscanf(str, "end %s", who))
	::catch_question(str);

    else
	dismiss_thrall_link_obj(who);
}


/*
 * This keeps the skull in range of the player.
 */
public void
move_thrall_link_obj(void)
{
    if (!present(player, environment()))
    {
        move_living("X", environment(player), 1, 1);
        /*
         * In case the obj gets stuck, we will
         * try a few times, then auto-dest.
         */
        if (!present(player, environment()))
        {
            if (++tries <= TRIES)
            return;

            other_thrall_link_objs->unlink_thrall_link_obj(this_object());
            
            remove_object();
            
            return;
        }
    }
    
    tries = 0;
}


/*
 * Initializes the skull.
 */
public void
init_thrall_link_obj(object who, int flag)
{
    player = who;
    master = flag;

    if (master)
    {
        /* The master skull. */
        set_name(({ "thrall_link_obj", "master_thrall", THRALL_LINK_OBJ_ID }));
        set_adj(({ "link", "thrall" }));
        set_short("vampire thrall link obj1");
        set_long("_vampire_thrall_link_object1.\n");
        add_prop(MAST_THRALL_LINK_OBJ, 1);
    }
    else
    {
        /* The slave skulls. */
        set_name(({ "thrall_link_obj", "slave_thrall", THRALL_LINK_OBJ_ID }));
        set_adj(({ "link", "thrall" }));
        set_short("vampire thrall link obj2");
        set_long("_vampire_thrall_link_object2.\n");
        
        add_prop(SLAV_THRALL_LINK_OBJ, 1);
        add_prop(OBJ_I_INVIS,          100);
        set_no_show();
        set_no_show_composite(1);
    }

    /* Add a reference prop to this player. */
    //player->add_prop(THRALL_ACTIVE, this_object());

    /* Start up alarms as necessary. */
    alarm1 = set_alarm(2.0, 2.0, move_thrall_link_obj);
}


/*
 * Returns if a skull is muted or not.
 */
public int
query_muted(void)
{
    return muted;
}


/*
 * Returns the player we are linked to.
 */
public object
query_linkage(void)
{
    return player;
}


/*
 * Returns the skulls we are linked to.
 */
public object *
query_other_thrall_link_objs(void)
{
    return other_thrall_link_objs;
}


void
init_living()
{
        ::init_living();
        
        add_action(do_sksay, "thrallsay");      
}
