/*
 * Generic Armour
 * 
 * This is a generic armour that can be made into a number
 * of different types of armour in the Sparkle Smithy
 *
 * Created by Petros, June 2009
 */
 
#pragma strict_types

#include <macros.h>
#include <wa_types.h>

inherit "/std/armour.c";
inherit "/lib/keep"; 


public void
create_armour()
{
    set_name(({"armour"}));
    set_adj(({"generic"}));
    set_short("generic armour");
    set_long("A generic armour that has not be customized.\n");
}


/* 
 * Function:    query_recover
 * Description: Recovery function for the generic armour. Sets up
 *              the armour with the same parameters as before.
 */
public string
query_recover()
{
    string rec;
    rec = MASTER + ":";
    rec += query_arm_recover();
    rec += query_keep_recover(); 
    return rec;
}


/* 
 * Function:    init_recover
 * Description: Recovers and initializes the variables in the armour
 */
public void
init_recover(string arg)
{
//    string foobar;
    
//    sscanf(arg, "%s#a#%s#m#%s#c#%s#myend%s", 
//                foobar, armtype, metal, const, foobar);
    init_arm_recover(arg);
    
//    if(!make_the_armour())
//    {
//        log_file("armour_recover", ctime(time()) + ":" + " " +
//               armtype + " " + metal + " " + const + "\n" );
//        remove_object();
//    }
    
    init_keep_recover(arg); 
}
