/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * join_room.c
 *
 * Temporary room where one may join the gypsy guild.
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include "gypsy_defs.h"

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    set_short("Guild Chamber");
    set_long("You are in the Gypsy guild.\n");
}

/*
 * Function name: init
 * Description:   lfun called when this object first comes in contact
 *                with a player
 */
public void
init()
{
    ::init();
    add_action("drink", "drink");
    add_action("sash", "sash");
    add_action("slide", "slide");
    add_action("renounce", "renounce");
    add_action("list", "list");
}


do_I_want_this_player_in_my_guild(player)
{
/* No check if already member */
/* You could test if the player has solved the guild quest or anything... */
    return 1;
}

do_I_accept_the_guilds_this_player_has_joined(player)
{
/* No check if player is already member of a this guild type.*/
    return 1;
}

public int
sash(string str)
{
    if (TP->query_real_name() != "sorgum") 
	return 0;

    clone_object("/d/Terel/sorgum/gypsy/gypsy_sash")->move(TP);
    write ("You got it.\n");
    return 1;
}

public int
slide(string str)
{
    object room;
    
    if (TP->query_real_name() != "sorgum")
	return 0;

    if (str[0] != '/') {
	room = environment(find_player(str));
	TP->move_living("X", room);
    }
    else 
	TP->move_living("X", str);
    
    write("moved.\n");
    return 1;
}


/*
 * Function name: drink
 * Description:   A player may try and join the guild with this
 *                add_action
 * Arguments:     str - the string following the action verb
 * Returns:       1/0
 */
public int
drink(string str)
{
    object shadow;
    int result;

    if (!str) return 0;
    if (str == "liquid") {
	 TP->catch_msg("Drink liquid from where?\n");
	 return 1;
    }
     
    if(str == "liquid from hole"){
	 say(QCTNAME(TP) +" drinks some liquid from the hole in the earth.\n");
	 TP->catch_msg("You drink the liquid from the hole.\n");


	 /*
	  * Put in checks here
	  */
	 
	 notify_fail("You aren't fit to join this guild.\n");
	 if (!do_I_want_this_player_in_my_guild(this_player()))
	      return 0;

	 notify_fail("You have already joined a guild we cannot accept.\n");
	 if (!do_I_accept_the_guilds_this_player_has_joined(this_player()))
	      return 0;

	 notify_fail("For unknown reasons we couldn't help you join " +
		     "our guild.\n");
    
	 shadow = clone_object(GUILD_SHADOW);
	 if ((result = shadow->shadow_me(TP, GUILD_TYPE, GUILD_STYLE,
					 GUILD_NAME))!=1) {
	      "/secure/master"->do_debug("destroy", shadow);
	      return 0;
	 }

	 write("You are now a new member of this guild.\n");
	 return 1;	 
    }

    return 0;
}

/*
 * Function name: renounce
 * Description:   A player may use this add_action to leave the guild
 * Arguments:     str - the string following the action verb
 * Returns:       1/0
 */
public int
renounce()
{
    notify_fail("But you are no member of our guild.\n");
    if (this_player()->query_guild_name_occ() != GUILD_NAME)
	return 0;

    if (this_player()->remove_guild_occ())
	write("You left our beloved guild.\n");
    else
	write("There was a strange error, I'm afraid you are stuck " +
	      "with us.\n");

    return 1;
}

/*
 * Function name: list
 * Description:   Give player the result of list_major_guilds()
 * Returns:       1
 */
public int
list()
{
     string str;

     str = TP->list_mayor_guilds();
     if (str)
	  write("You are member of following guilds:\n" + str);
     else
	  write("You are not member of any guilds.\n");

     return 1;
}


