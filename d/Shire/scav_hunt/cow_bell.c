/*                         
 * cow bell
 *
 */

#include "/d/Shire/sys/defs.h" 
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <cmdparse.h>

inherit "/std/object";
inherit "/lib/keep";

create_object()
{
    seteuid(getuid());
    set_name("bell");
    add_name("_shire_cowbell_");
    add_name("cow bell");
    set_pname("bells");
    add_pname("cow bells");

    set_short("copper cow bell");
    add_adj(({"copper"}));

    set_long("This is a "+short()+". It is worn by cows so their " +
        " owner can locate the animal. It rectangular shaped and " +
        "flares out at the bottom. On top is a ring that a piece of " +
        "leather or rope can be strung through to tie around the " +
        "cow's neck\n");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VALUE,  125);
    add_prop(OBJ_I_VOLUME, 100);

}
void init() 
{
    ::init();
    add_action("ring_bell","ring");
}

int ring_bell(string str)
{
    object   target;

    if((str !="bell") && (str !="cow bell")) return 0;


    say(QCTNAME(TP) + " shakes " + HIS_HER(TP) + " "+short() + 
        " wildly, making the bell ring raucously.\n"); 
    TP->catch_msg("You shake your " + short() + ", making it ring raucously.\n");
    return 1;
}                 

