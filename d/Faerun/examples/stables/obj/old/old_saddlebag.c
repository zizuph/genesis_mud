/*
 * - saddlebag.c
 *
 * Saddlebag object for use with steeds.
 */
#pragma strict_types

#include "steed.h"
#include <macros.h>

inherit "/d/Genesis/std/pack";

static object   steed;
static int	pack_size;

public nomask int
query_steed_pack()	{ return 1; }

public nomask void
set_pack_size(int i)	{ pack_size = i; }

public nomask int
query_pack_size()	{ return pack_size; }

public void
create_saddlebag()
{
}

public nomask void
create_pack()
{
    set_name("saddlebag");
    set_long("A generic saddlebag, intended to be 'draped' over "+
	"the back of a horse or other type of steed.\n");

    add_prop(CONT_I_WEIGHT,	6000);
    add_prop(CONT_I_WEIGHT,	6000);
    add_prop(CONT_I_MAX_WEIGHT,	100000);
    add_prop(CONT_I_MAX_VOLUME,	100000);

    set_mass_storage(1);
    set_pack_size(STEED_NORMAL);

    create_saddlebag();
}

public int
drape_me_pack(string str)
{
    object pack, *tmp;

    if (!str)
    {
	notify_fail("Drape what?\n");
	return 0;
    }

    tmp = filter(all_inventory(this_player()), &->qeery_steed_pack());
    tmp += filter(all_inventory(environment(this_player())),
			&->query_valid_steed());

    
    if (!parse_command(str, tmp, "[the] %o [on] [the] %o", pack, steed))
    {   
	notify_fail("Drape what on what ?\n");
	return 0;
    }


    if (!pack->query_steed_pack())
    {
        notify_fail("That pack wasn't made for horses.\n");
        return 0;
    }

    
    if (!present(pack, this_player()))
    {
	notify_fail("You do not have any " + pack->short() + ".\n");
	return 0;
    }
    

    if (!steed->query_valid_steed())
    {
        notify_fail("That pack is for a different type of horse.\n");
        return 0;
    }
    if ((pack_size != STEED_ALL) && 
	(pack_size != steed->query_steed_size()))
    {
	write("The " + pack->short() + " was not designed to fit " +
	    "the " + steed->short() + ".\n");
	return 1;
    }

    if (pack->move(steed))
    {
	write("The " + pack->short() + " seems to be too heavy for the "+
	  steed->short()+" to carry.\n");
	return 1;
    }

    write("You drape the "+pack->short()+" over the "+
      steed->short()+"'s back.\n");

    say(QCTNAME(this_player())+" drapes a "+pack->short()+ 
	" over the back of the "+steed->short()+".\n");

    steed->set_steed_saddlebag(pack);
    return 1;
}

public void
remove_me_pack()
{
    if (move(this_player()))
    {
	write("You untie the straps of the "+short()+
	  " and it drops heavily to the ground.\n");

	say(QCTNAME(this_player())+" unties the straps of the " +
	   steed->short()+"'s "+short()+", and it falls heavily to"+
	  "the ground.\n");

	move(environment(steed));
    }
    else
    {
	write("You remove the "+short()+" from the "+
	  steed->short()+"'s back.\n");

	say(QCTNAME(this_player())+" removes a "+short()+ 
	  " from the back of the "+ steed->short()+".\n");
    }

    steed->set_steed_saddlebag(0);
    steed = 0;
}

public void
open_me_pack()
{
    if (!query_prop(CONT_I_CLOSED))
    {
	write("The "+short()+" is already open!\n");
	return;
    }

    remove_prop(CONT_I_CLOSED);

    write("You open the "+short()+" on the "+
      steed->short()+"'s back.\n");

    say(QCTNAME(this_player())+" opens the "+short()+" on the "+
      steed->short()+"'s back.\n");
}

public void
close_me_pack()
{
    if (query_prop(CONT_I_CLOSED))
    {
	write("The "+short()+" is already closed!\n");
	return;
    }

    add_prop(CONT_I_CLOSED, 1);

    write("You close the "+short()+" on the "+
      steed->short()+"'s back.\n");

    say(QCTNAME(this_player())+" closes the "+short()+" on the "+
      steed->short()+"'s back.\n");
}

public int
pack_fill_fail()
{
    if (!steed && (environment(this_object()) != this_player()))
    {
        write("You need to get the " + short() + " first.\n");    
        return 1;
    }
    
    if (query_prop(CONT_I_CLOSED))
    {
        write("The " + short() + " is closed.\n");
        return 1;
    }

    return 0;
}

public int
pack_empty_fail()
{
    if (!steed && (environment(this_object()) != this_player()))
    {
        write("You need to get the " + short() + " first.\n");    
        return 1;
    }
    
    if (query_prop(CONT_I_CLOSED))
    {
        write("The " + short() + " is closed.\n");
        return 1;
    }
  
    return 0;
}

public void
appraise_me_pack()
{
    appraise_object(0);
}

public void
init()
{
    ::init();
    add_action( drape_me_pack, "drape" );
}

