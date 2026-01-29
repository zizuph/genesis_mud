// OBJECT: hot chili
    
    /*Calia Domain

    HISTORY

    [99-08-09] Created by Valkira
 
    PURPOSE

    To test a text editor and ftp, to practice writing code*/

// INCLUSIONS AND DEFINITIONS

inherit "/std/food";

#include <stdproperties.h>

// OBJECT DEFINITION

void
create_food()

{

    /*  DESCRIPTION  */


set_name("chili");
    set_adj("hot");
    set_short("hot chili");    

    set_long("This is chili the way mom never made it.\n");

    /*  PROPERTIES  */

    set_amount(500);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 400);

}






