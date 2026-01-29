/* Charity box base object
 * Updated by TAPAKAH,
 * May 31, 2005 to log donations.
 *
 * Updated by Finwe,
 * Jan 16, 2006 Automatically have basic weapons and armours in box
 * Feb 26, 2006 Converted over for Middle Earth by Finwe
 * 
 * To have the box clone random items into it, add this line of code:
    
        fill_box(filename, item_name, max_num_of_items_to_clone);

    to reset_container(), for each item you want in the box, like this:


        void reset_container()
        {

            fill_box("/d/Shire/charity/jagged_knife", "knife", 4);
            fill_box("/d/Shire/charity/dagger", "dagger", 4);
            fill_box("/d/Shire/charity/shortsword", "shortsword", 4);
        }

 */

#pragma save_binary
#pragma strict_types

inherit "/std/container";
inherit "/d/Shire/lib/box_list";
inherit "/lib/shop";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <files.h>
#include <filter_funs.h>

// The donate property set in items being donated
#define DONATED_BY  "_s_donated_by"
// #define DONATED_LOG "/d/Sparkle/log/charity_box"

//public void log_donation(object ob, object from, string action);
public void show_list(object for_obj, object *obarr);
public void fill_box(string path_name, string id_name, int max_num);

void reset_container();

void
create_container()
{
    add_prop(CONT_I_WEIGHT,      100000);   /* Empty box weighs 100 Kg.  */
    add_prop(CONT_I_VOLUME,      800000);   /* Max 0.8 m^3 internal volume.  */
    add_prop(CONT_I_MAX_WEIGHT, 1000000);   /* The box can max hold 1000 Kg. */
    add_prop(CONT_I_MAX_VOLUME,  920000);   /* Volume of box + content.  */
    add_prop(CONT_I_RIGID,            1);   /* This is a rigid container.*/
    add_prop(OBJ_I_NO_GET,            1);   /* Can't get it.*/
    add_prop(CONT_I_TRANSP,           1);   /* Transparent.*/

    set_name("charity box");
    add_name("box");
    set_long("This is a large box where generous players may donate " +
        "extra equipment, weapons, or things younger players may need. " +
        "If you accidentally donate something, you may retrieve it from " +
        "the box.\n\n");

    setuid();
    seteuid(getuid());

    enable_reset();
    set_alarm(1.0, 0.0, "reset_container");
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
	write("You change your mind and take the " + ob->query_short() + " back.\n");
	ob->remove_prop(OBJ_M_NO_SELL);

//	log_donation(ob,this_player(),"regret");
	return 0;
    }

    // Is the player to big to use this box
    if (this_player()->query_average_stat() > 53)
    {
	write("On second thought, you decide to leave the contents of the " +
        "charity box for less experienced adventurers. You should be " +
        "quite capable of fending for yourself now without needing to " +
        "rely upon the charity of others.\n");

	return 1;
    }

    if ( IS_WEAPON_OBJECT(ob) )
    {
	player_inv = all_inventory(this_player());

	// Run through the player inventory
	for (i = 0; i < sizeof(player_inv); i++)
	{
	    // if the current object is the same as the one we try to take
	    // fail.
	    if ( IS_WEAPON_OBJECT(player_inv[i]) &&
	      ( player_inv[i]->query_wt() == ob->query_wt() ) )
	    {
		write("You decide to leave the " + ob->query_short() + " in " +
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
		write("You decide to leave the " + ob->query_short() + "in " +
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
    // Mark the object beind donated so we know from who
    ob->add_prop(DONATED_BY, from->query_name());
    ob->add_prop(OBJ_M_NO_SELL, "This is a charity item, it cannot be sold.\n");

    // Offer a chance for shadows or souls to handle stuff when a player
    // donates stuff
    ob->donated_charity_item(ob);
//    log_donation(ob,from, "donation");
}

/*
public void
log_donation(object ob, object from, string action)
{
  setuid();
  seteuid(getuid());
  write_file(DONATED_LOG,ctime(time())+ " " + file_name(environment()) + " "
	     +ob->short() + " "+from->query_name() + " " + action + "\n");

}
*/

/*
 * Function name: describe_contents
 * Description:   Give a description of items in this container
 * Arguments:     object for_obj - To whom to give the description
 *                object *obarr  - The items to describe
 */
public void
describe_contents(object for_obj, object *obarr)
{
    for_obj->catch_tell(show_sublocs(for_obj));

    if (TO->query_prop(CONT_I_ATTACH))
    {
        if (sizeof(obarr) > 0)
        {
            for_obj->catch_tell(capitalize(COMPOSITE_DEAD(obarr)) + 
                (sizeof(obarr) > 1 ? " are" : " is") + " on the " +
                TO->short() + ".\n");
        }
        else
        {
            for_obj->catch_tell("There is nothing on the " + 
                TO->short() + ".\n");
        }
    }
    else if (sizeof(obarr) > 0)
    {
        show_list(for_obj, obarr);
    }
    else
    {
        for_obj->catch_tell("  " + "The " + TO->short() +
            " is empty.\n");
    }
}

public void
show_list(object for_obj, object *obarr)
{
    int i, price;

    obarr = FILTER_DEAD(obarr);
    obarr = unique_array(obarr, "short", 0);
    obarr = sort_array(obarr, "sort_objects_to_list", TO);

    for_obj->catch_tell(print_shop_list(obarr));
}

public void fill_box(string path_name, string id_name, int max_num)
{
    int i = 0,
    rand_num = 4;

    setuid();
    seteuid(getuid());

    if (!present(id_name))
    {
        for(i = 0; i < random(max_num); ++i)
        {
            clone_object(path_name)->move(TO);
        }
    }
}
/*
 * Reset the charity box from time to time.
 */

void
reset_container()
{

//    fill_box("/d/Shire/charity/jagged_knife", "knife", 4);
//    fill_box("/d/Shire/charity/dagger", "dagger", 4);
//    fill_box("/d/Shire/charity/shortsword", "shortsword", 4);

/*
// weapons
    if (!present("_ch_club_"))
    {
        for(i = 0; i < random(rand_num); ++i)
        {
            clone_object(WEP_DIR + "ch_club")->move(TO);
        }
    }
    if (!present("_ch_battleaxe_"))
    {
        for(i = 0; i < random(rand_num); ++i)
        {
            clone_object(WEP_DIR + "ch_baxe")->move(TO);
        }
    }
    if (!present("_ch_dagger_"))
    {   
        for(i = 0; i < random(rand_num); ++i)
        {
            clone_object(WEP_DIR + "ch_dagger")->move(TO);
        }
    }
    if (!present("_ch_longsword_"))
    {
        for(i = 0; i < random(rand_num); ++i)
        {
            clone_object(WEP_DIR + "ch_lsword")->move(TO);
        }
    }

// armours
    if (!present("_ch_cmail_"))
    {
        for(i = 0; i < random(rand_num); ++i)
        {
            clone_object(ARM_DIR + "ch_cmail")->move(TO);
        }
    }
    if (!present("_ch_helm_"))
    {
        for(i = 0; i < random(rand_num); ++i)
        {
            clone_object(ARM_DIR + "ch_helm")->move(TO);
        }
    }
    if (!present("_ch_helmet_"))
    {
        for(i = 0; i < random(rand_num); ++i)
        {
            clone_object(ARM_DIR + "ch_helmet")->move(TO);
        }
    }
    if (!present("_ch_pmail_"))
    {
        for(i = 0; i < random(rand_num); ++i)
        {
            clone_object(ARM_DIR + "ch_pmail")->move(TO);
        }
    }
    if (!present("_ch_sgreaves_"))
    {
        for(i = 0; i < random(rand_num); ++i)
        {
            clone_object(ARM_DIR + "ch_sgreaves")->move(TO);
        }
    }
    if (!present("_ch_dgreaves_"))
    {
        for(i = 0; i < random(rand_num); ++i)
        {
            clone_object(ARM_DIR + "ch_dgreaves")->move(TO);
        }
    }
    if (!present("_ch_bracers_"))
    {
        for(i = 0; i < random(rand_num); ++i)
        {
            clone_object(ARM_DIR + "ch_bracers")->move(TO);
        }
    }
*/
}
