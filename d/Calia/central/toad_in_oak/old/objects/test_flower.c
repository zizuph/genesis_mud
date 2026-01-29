 /*
 * /d/calia/kcirderf/test_flower.c
 *
 * This is a test object to see if it's possible to make a wearable 
 * food item. 
 *  
 * HISTORY: [99-05-15] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

inherit "/d/Calia/std/hair_ornament.c"; 

void 
create_hair_ornament()
{
    set_name("rose");
    add_name("flower"); 
    set_adj(({"red", "thorny", "rose"})); 

    set_short("thorny red rose");
    set_long("This is a ordinary looking red rose, it's stem covered with " + 
        "with thorns. You could try wearing it on your head.\n"); 

}


    
    
   
