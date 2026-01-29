/*
 *  NCAMP_ROOM + "ipath1.c"
 *
 *  A woodland path. Only newbies and wizards should ever see this place.
 *
 *  Last modified by Alto, 27 September 2002
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include <math.h>
#include "/d/Gondor/defs.h"
#include "../ncamp_defs.h"

inherit NCAMP_LIB + "ncamp_funcs.c";

public void      	create_gondor();
public string    	long_desc();
public string		exa_bushes();
public string		exa_stems();
public int		check_entry();

public void
create_gondor()
{
    set_short("a narrow glade encircled with bushes");
    set_long(&long_desc());

    sky_add_items();
    woods_add_items();

    add_item(({"room", "area", "surroundings", "place", "glade",
        "landscape", "narrow glade", "woodland", "woods"}), long_desc);
    add_item(({"bushes", "bush"}), &exa_bushes());
    add_item(({"stems", "broken stems", "crushed leaves"}), &exa_bushes());
    add_item(({"path", "narrow path"}), "The path appears to end at the "
        + "dense bushes to the east of the glade.\n");
        
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(NCAMP_ROOM + "ipath1.c", "east", check_entry, 2, check_entry);
    add_exit("/d/Gondor/lebennin/sroad/sr2", "west", 0, 2);

    reset_room();
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
     sky_add_items();
}


string
long_desc()
{
    if (STAT_AVE < STAT_MAX)
    {
    return "A narrow glade has opened in the trees around you. The air is very "
        + "still and almost no sound drifts into the glade from the surrounding "
        + "woodland."
        + sky_desc() 
        + " The path leading in from the west comes to a sudden halt among dense "
        + "bushes on the east end of the glade. From your position in the "
        + "glade it is apparent someone has recently pushed through the bushes "
        + "further to the east.\n";
    }
    
    return "A narrow glade has opened in the trees around you. The air is very "
        + "still and almost no sound drifts into the glade from the surrounding "
        + "woodland."
        + sky_desc() 
        + " The path leading in from the west comes to a sudden halt among dense "
        + "bushes on the east end of the glade.\n";
}


string
exa_bushes()
{
    if (STAT_AVE < STAT_MAX)
    {
    return "From where you are standing in the glade, you can see broken stems "
        + "and crushed leaves on some of the bushes. It looks like someone has "
        + "been going and coming through them to the east.\n";
    }
    
    return "From where you are standing in the glade, the bushes appear to form "
        + "a seamless barrier to the east. The only way to leave this place appears "
        + "to be back the way you came, to the west.\n";
}


string
exa_stems()
{
    if (STAT_AVE < STAT_MAX)
    {
    return "The stems and leaves on some of the bushes are bent and broken, "
        + "suggesting that someone has been moving through them with some "
        + "regularity.\n";
    }
    
    return "The stems on the bushes support many broad-bladed leaves.\n";
}

public int
check_entry()
{

    if (STAT_AVE < STAT_MAX || WIZARD)
    {
        write ("You push aside the leaves and stems of some bushes and squeeze "
            + "through to the east.\n");
        return 0;
    }

    write("You cannot find a way through the dense bushes. It looks like the "
        + "only way out of the glade is back along the path to the west.\n");
        return 1;
}

