/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * clue1.c
 *
 * A clue for the ribos crime quest
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
inherit "/std/container";                                                        
/*
 * Function name: create_container
 * Description:   Default constructor
 */
public void
create_container()
{
    set_name("bag");
    add_name("clue1_bag");
    set_short("leather bag");
    set_adj("leather");
    set_long("A small bag, large enough to carry a good sized melon.\n");
    add_prop(CONT_I_WEIGHT,     500);   
    add_prop(CONT_I_MAX_WEIGHT, 1000);  
    add_prop(CONT_I_VOLUME,     1000);  
    add_prop(CONT_I_MAX_VOLUME, 10000); 
    add_prop(CONT_I_RIGID,      0);
    add_prop(CONT_I_TRANSP,     1); 
    add_prop(OBJ_I_VALUE,       5);
}
