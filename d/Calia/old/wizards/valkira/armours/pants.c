// ARMOUR:  pants

    /* Calia Domain

    HISTORY

    [99-08-09] Reconstruction by Valkira of cape.c created by Uhclem from [C:\CALIA\UHCLEM\OPEN\CAPE.DOC].

    PURPOSE

    This is an armour written for coding practice.*/

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

    set_name("pants");
    set_adj("green");
    
    set_short("a pair of green pants");

    set_long("These pants are loose in the hips, then taper" +
        " to fit snuggly at the calves.\n");

    /* PHYSICAL ATTRIBUTES */

    set_ac(1);                               /* type=clothing          */
    set_at(A_LEGS);                          /* covers legs            */
    add_prop(OBJ_I_WEIGHT, 200);             /* weight 200 grams       */
    add_prop(OBJ_I_VOLUME, 300);             /* volume 300 ml          */
    add_prop(OBJ_I_VALUE, 0);

    /* COMBAT ATTRIBUTES */

    set_am(({0,0,0}));                       /* none                   */

    }

