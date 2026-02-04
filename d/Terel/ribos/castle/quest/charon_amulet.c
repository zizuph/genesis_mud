/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * charon_amulet.c
 *
 * Charon's amulet
 *
 * Vader
 * modified by Sorgum 950707
 */

#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;

public int rub(string str);

int am_used = 0;

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
    ::create_object();
    set_name("amulet of charon");
    add_name("amulet");
    set_adj("green");
    add_adj("striped");
    set_short("green striped amulet");
    set_long("This is an amulet, with green stripes covering its " +
	     "surface, which is decorated by ancient runes that you " +
	     "do not recognize.\n");
    
    add_prop(OBJ_I_VALUE,  10);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 30);

    am_used = 0;
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    add_action(rub, "rub");
}


/*
 * Function name: rub
 * Description:   Handle the rub action
 * Returns:       1/0
 */
public int
rub(string str)
{
    object dragon;
    
    if(!strlen(str) || (str != "amulet")) {
	NF("What?\n");
	return 0;
    }

    if (present("evil_thang", ETP)) {
	if (am_used == 0) {
	    if (dragon = find_living("thariderius")) {
		
		dragon->weaken();
		am_used = 1;
            }
	}
	else 
	    write("The amulet is all tuckered out.\n");
    }
    else  
	write ("Nothing happens.\n");
    
    return 1;
}
