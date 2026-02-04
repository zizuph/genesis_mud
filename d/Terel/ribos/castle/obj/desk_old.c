/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * desk.c
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit STDOBJECT;

public int steal(string str);

int keygotten = 0;

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
    ::create_object();
    set_name("desk");   
    set_long("This ornate wooden desk is large and elegant.  It has " +
	     "a drawer, but that is closed and locked using magic.  " +
	     "There is no way you can open it.\n");

    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(OBJ_I_VOLUME, 3000);
    keygotten = 0;
}

public void
reset_object()
{
    keygotten = 0;
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    /*
     * DO NOT add any more actions here, in particular DO NOT add
     * "steal" as an action.  Any questions, mail Sorgum.
     */
    add_action("steal", "remove");   
}

/*
 * Function name: steal
 * Description:   Handle the steal action
 * Returns:       1/0
 */
public int 
steal(string str)
{
    object key;
    
    if(!strlen(str) || (str != "key")) {
        NF(capitalize(query_verb()) + " what?\n");
	return 0;
    }
    
    if(TP->query_prop(PASS_HANDS) == 0) {
	NF ("How?\n");
	return 0;
    }
    
    if(keygotten == 0) {
	FIX_EUID;
	key = clone_object(CASTLE_DIR + "obj/treas_key");
	key->move(TP);
	key->set_key(TREASURE_KEY);
	write("Your hand slips through the wooden desk, easily removing the " +
	      "key from its hiding place.\n");
	keygotten = 1;	    
    }
    else 
	write("Your hand slips through the wooden desk, but finds " +
	      "nothing.\n");
	return 1;
}
