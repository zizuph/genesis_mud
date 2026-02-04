/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * chest.c
 *
 * A treasure chest
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit "/std/container";

public int do_open(string str);
public int do_close(string str);

int my_num;

/*
 * Function name: query_my_num
 * Description:   return number of this chest
 */
public int
query_my_num()
{
    return my_num;
}

/*
 * Function name: set_my_num
 * Description:   return number of this chest
 */
public void
set_my_num(int i)
{
    my_num = i;
}

/*
 * Function name: fill_er_up
 * Description:   Fill the chest
 */
public void
fill_er_up()
{
    string *objs;
    int i;

    FIX_EUID;

    add_prop(CONT_I_CLOSED, 0);
    objs = (CASTLE_DIR + "obj/treas_list")->query_chest_contents(my_num);
    for (i = 0; i < sizeof(objs); i++) {
	clone_object(objs[i])->move(TO);
    }
    add_prop(CONT_I_CLOSED, 1);    
}

/*
 * Function name: create_container
 * Description:   Default constructor
 */
public void
create_container()
{
    set_name("chest");
    set_long("This is a rather dull looking chest.  It is " +
	     "covered in old, faded wood, bound by rusted iron.  It is " +
	     "unlocked.\n");

    add_prop(CONT_I_MAX_WEIGHT, 2500000);
    add_prop(CONT_I_MAX_VOLUME, 2500000);
    add_prop(CONT_I_WEIGHT,     25000);
    add_prop(CONT_I_VOLUME,     30000);    
    add_prop(OBJ_I_NO_GET,      1);
    add_prop(CONT_I_CLOSED,     1);
    add_prop(CONT_I_LOCK,       0);
    add_prop(CONT_I_TRANSP,     0);
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
   ::init();
   add_action(do_open,  "open");
   add_action(do_close, "close");
}

/*
 * Function name: do_open
 * Description:   Handle the open action
 * Returns:       1/0
 */
public int
do_open(string str)
{
   if(!strlen(str) || str != "chest") {
       NF("Open what?\n");
       return 0;
   }

   if(!(TO->query_prop(CONT_I_CLOSED))) {
       write("The chest is already open!\n");
       return 1;
   }
   
   add_prop(CONT_I_CLOSED, 0);
   write("You open the chest.\n");
   return 1;
}

/*
 * Function name: do_close
 * Description:   Handle the close action
 * Returns:       1/0
 */
public int
do_close(string str)
{
    if(!strlen(str) || (str != "chest")) {
	NF("Close what?\n");
	return 0;
    }

    if(TO->query_prop(CONT_I_CLOSED)) {
	write("The chest is closed already!\n");
	return 1;
    }
    
    add_prop(CONT_I_CLOSED, 1);
    write("You close the chest.\n");
    return 1;
}

