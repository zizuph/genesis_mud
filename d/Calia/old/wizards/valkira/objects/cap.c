// ARMOUR:  plumed military cap

    /* Calia Domain

    HISTORY

    [96-03-07] Created by Uhclem from [C:\CALIA\UHCLEM\OPEN\CAP.DOC].

    PURPOSE

    This is an armour written for coding practice.  Any Genesis wizard who
    wishes to copy it is welcome to do so.  It is designed to be worn with the
    uniform "/d/Calia/uhclem/open/uniform.c".*/

// INCLUSIONS AND DEFINITIONS

inherit "/std/armour";

#include </sys/wa_types.h>
#include </sys/stdproperties.h>
#include </sys/formulas.h>
#include </sys/macros.h>

// GLOBAL VARIABLES

string *colors1 = ({"indigo", "maroon", "black", "purple"});
string *colors2 = ({"white", "silvery", "golden"});
string capcolor = colors1[(random(sizeof(colors1)))];
string plucolor = colors2[(random(sizeof(colors2)))];

// ARMOUR DEFINITION

void
create_armour()

    {

    /* DESCRIPTION */

    set_name("cap");
    set_short(capcolor + " military cap with a tall " + plucolor + " plume");
    set_adj(({capcolor, "military","plumed"}));

    set_long("This cap is made of fine " + capcolor + " felt.  " +
        "The visor is shiny black leather, " +
        "and the headband is decorated with a gold braid.  " +
        "A tall " + plucolor + " plume stands straight up from the peak, " +
        "making the wearer easy to spot at a distance.  " +
        "Babes can't resist a guy wearing a cap like this!\n");

    /* PHYSICAL ATTRIBUTES */

    set_ac(1);                               /* type=helmet            */
    set_at(A_HEAD);                          /* worn on head           */
    add_prop(OBJ_I_WEIGHT, 200);             /* weight 200 grams       */
    add_prop(OBJ_I_VOLUME, 300);             /* volume 300 ml          */

    /* COMBAT ATTRIBUTES */

    set_am(({0,0,0}));                       /* none                   */

    }
