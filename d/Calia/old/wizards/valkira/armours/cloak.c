// ARMOUR:  cloak

    /* Calia Domain

    HISTORY

    Created by Valkira, 8/16/99

    PURPOSE

    This is cloak may be worn with a pocketed lining.*/

// INCLUSIONS AND DEFINITIONS

inherit "/std/armour";

#include </sys/wa_types.h>
#include </sys/stdproperties.h>
#include </sys/formulas.h>
#include </sys/macros.h>

// ARMOUR DEFINITION

void
create_armour()

    {

    /* DESCRIPTION */

    set_name("cloak");
    add_name("traveller's cloak");

    // set_adj();
    
    set_short("traveller's cloak");

    set_long("This traveller's cloak is woven of multi color threads," +
        " some the dark green of the forest, the lighter green of" +
        " prairies, the color of sands and the blue grey of mountains." +
        " When worn, the traveller has a better chance of blending" +
        " into the surroundings.  It is thick and may deflect some" +
        " slashes. It also may be worn with a lining.\n");

    /* PHYSICAL ATTRIBUTES */

    set_ac(1);                               /* type=clothing          */
    set_at(A_ROBE);                          /* covers whole body      */
    add_prop(OBJ_I_WEIGHT, 200);             /* weight 200 grams       */
    add_prop(OBJ_I_VOLUME, 300);             /* volume 300 ml          */
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_NO_DROP, "This is your only cloak, so you keep it");


    /* COMBAT ATTRIBUTES */

    set_am(({0,0,0}));                       /* change this */

// need to add hide to this object             

    }
