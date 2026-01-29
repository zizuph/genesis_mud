/* Charity box base object
 * Updated by TAPAKAH,
 * 31/05/2005 to log the donations.
 * 
 * 2010/08/21 Lavellan Fixed so it doesn't make room dark, reindented,
 *                     fixed removal of corpses and flasks, uses deep inventory,
 *                     now can't donate and remove previously donated items
 *                     to be able to sell them.            
 */

#pragma save_binary
#pragma strict_types

inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>
#include <files.h>

// The donate property set in items being donated
#define DONATED_BY  "_s_donated_by"
#define DONATED_BY_FIRST  "_s_donated_by_first"
#define DONATED_LOG "CHARITY_BOX"

public void log_donation(object ob, object from, string action);

void
create_container()
{
    /* This is a wooden box, 0.8 m high and 1 m on the inside.
     * The sides are made of 3 cm thick wood which gives the box a
     * total (rigid) volume of 0.92 m^3. The internal volume will be
     * 0.8 m^3. Thus the wood itself has a volume of 0.126 m^3.
     * The density of this wood is 800Kg/m^3, giving the empty box
     * a weight of 100.8 Kg. Let's just say 100. Kg. :)
     * In short, people should not carry the box around...
     */

    add_prop(CONT_I_WEIGHT,      100000);   /* Empty box weighs 100 Kg.  */
    add_prop(CONT_I_VOLUME,      800000);   /* Max 0.8 m^3 internal volume.  */
    add_prop(CONT_I_MAX_WEIGHT, 1000000);   /* The box can max hold 1000 Kg. */
    add_prop(CONT_I_MAX_VOLUME,  980000);   /* Volume of box + content.  */
    add_prop(CONT_I_RIGID,            1);   /* This is a rigid container.*/
    add_prop(OBJ_I_NO_GET,            1);   /* Can't get it.*/
    add_prop(CONT_I_TRANSP,           1);   /* Transparent.*/

    set_name("charity box");
    add_name("box");
/*    set_long("This is a large box where donations of excess" +
      " equipment or items may be placed for lesser experienced" +
      " adventurers to use. If you donate an item by mistake, it may" +
      " be retrieved if you change your mind.\n\n");*/
    set_long("This is a large box where donations of excess" +
      " equipment or items may be placed for less experienced" +
      " adventurers to use. If you donate an item by mistake, you may" +
      " retrieved it again from the box.\n");
}

/*
 * Function name: prevent_leave
 * Description:   Called when an object is trying to leave this container
 *                to see if we allow it to leave.
 * Arguments:     object ob - the object trying to leave
 * Returns:       1 - The object is not allowed to leave
 *                0 - The object is allowed to leave
 */
public int
prevent_leave(object ob)
{
    object *player_inv;
    int i;

    // During armageddon everyone can get items and sell them
    if ( ARMAGEDDON->shutdown_active() )
    {
    	ob->remove_prop(OBJ_M_NO_SELL);
    	return 0;
    }

    // If the player donated by mistake we allow the item to be removed again
    if ( (ob->query_prop(DONATED_BY)) == (this_player()->query_name()) )
    {
    	write("You change your mind and take the " + ob->short() + " back.\n");

        if (ob->query_prop(DONATED_BY_FIRST) == this_player()->query_name())
        {
           	ob->remove_prop(OBJ_M_NO_SELL);
           	ob->remove_prop(DONATED_BY_FIRST);
        }
    
    	log_donation(ob,this_player(),"regret");
    	return 0;
    }

    // Is the player to big to use this box
    if (this_player()->query_average_stat() > 55)
    {
    	write("On second thought, you decide to leave" +
    	  " the contents of the charity box for the less" +
    	  " experienced adventurers. You should be quite" +
    	  " capable of fending for yourself now without" +
    	  " needing to rely upon the charity of others.\n");
    
    	return 1;
    }

    if ( IS_WEAPON_OBJECT(ob) )
    {
    	player_inv = deep_inventory(this_player());
    
    	// Run through the player inventory
    	for (i = 0; i < sizeof(player_inv); i++)
    	{
    	    // if the current object is the same as the one we try to take
    	    // fail.
    	    if ( IS_WEAPON_OBJECT(player_inv[i]) &&
    	      ( player_inv[i]->query_wt() == ob->query_wt() ) )
    	    {
    		write("You decide to leave the " + ob->short() + " in " +
    		  "the box for someone else to use.\n");
    		return 1;
    	    }
    	}
    }

    if ( IS_ARMOUR_OBJECT(ob) )
    {
    	for (i = 0; i < sizeof(player_inv); i++)
    	{
    	    // if the current object is the same as the one we try to take
    	    // fail.
    	    if ( IS_ARMOUR_OBJECT(player_inv[i]) &&
    	      ( player_inv[i]->query_at() == ob->query_at() ) )
    	    {
//    		write("You decide to leave the " + ob->query_short() + "in " +
    		write("You decide to leave the " + ob->short() + "in " +
    		  "the box for someone else to use.\n");
    		return 1;
    	    }
    	}
    }

    return 0;
}

/*
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 *
 *                The function donated_charity_item(object ob) is called
 *                in the object donating the object enter the inventory.
 *
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (ob->query_prop(OBJ_I_BROKEN))
    {
	set_alarm(2.0, 0.0, &tell_room(environment(),
	    capitalize(LANG_THESHORT(ob)) + " breaks up into small pieces.\n"));
	ob->remove_object();
	return;
    }

    // Mark the object being donated so we know from who
    ob->add_prop(DONATED_BY, from->query_name());
    if (!ob->query_prop(DONATED_BY_FIRST))
        ob->add_prop(DONATED_BY_FIRST, 
            from == 0 ? "The void" : from->query_name());
    
    ob->add_prop(OBJ_M_NO_SELL, "This is a charity item, it can not be sold.\n");

    // Offer a chance for shadows or souls to handle stuff when a player
    // donates stuff
    ob->donated_charity_item(ob);
    log_donation(ob,from,"donation");
}


public void
log_donation(object ob, object from, string action)
{
    log_file(DONATED_LOG, ctime(time()) + " " + ob->short() + " (" +
        file_name(ob) + ") " + from->query_name() + " " + action + "\n");
}
