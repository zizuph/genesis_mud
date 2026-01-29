// ARMOUR:  military cape

    /* Calia Domain

    HISTORY

    [96-03-13] Created by Uhclem from [C:\CALIA\UHCLEM\OPEN\CAPE.DOC].

    PURPOSE

    This is an armour written for coding practice.  Any Genesis wizard who
    wishes to copy it is welcome to do so. It is designed to be worn with the
    uniform "/d/Calia/uhclem/open/uniform.c".*/

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

    set_name("cape");
    set_adj("black");
    add_adj("full-length");

    set_short("full-length black cape with a sable collar" +
        " and gold satin lining");

    set_long("This cape is made of finest black lambs' wool and covers" +
        " the wearer from the neck down to the ankles.  Despite its" +
        " light weight, it can keep you comfortably warm even" +
        " in the harshest weather, and the flamboyant but" +
        " tasteful contrast of jet black and bright gold" +
        " makes this garment suitable for even the" +
        " most elegant occasions.\n");

    /* PHYSICAL ATTRIBUTES */

    set_ac(1);                               /* type=clothing          */
    set_at(A_ROBE);                          /* covers whole body      */
    add_prop(OBJ_I_WEIGHT, 200);             /* weight 200 grams       */
    add_prop(OBJ_I_VOLUME, 300);             /* volume 300 ml          */
    add_prop(OBJ_I_VALUE, 0);

    /* COMBAT ATTRIBUTES */

    set_am(({0,0,0}));                       /* none                   */

    }
