/*                         
 * elven lyre
 *
 */
 
#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
 
inherit "/std/object";
inherit "/lib/keep";
 
create_object()
{
    set_name("lyre");
    set_pname("lyres");
 
    set_short("lyre");
    add_adj(({"beautiful", "silver"}));
 
    set_long("This is an elven lyre. It is 'U' shaped and fans " +
        "out at the top. Two horizontal rods have been set into " +
        "the instrument. One is set into the neck where it " +
        "begins to fan out and at the base. Silver strings have " +
        "been strung between the two rods and are very taunt. " +
        "By strumming the strings the elves are able to play " +
        "beautiful music that warms the heart and soothes the " +
        "soul.\n");
 
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE,  500);
 
}

void init() 
{
        add_action("strum_lyre","strum");
}
 
int strum_lyre(string str)
{
    if(str !="lyre" && str !="strings") return 0;
 
    say(QCTNAME(TP) + " strums " + HIS_HER(TP) + short() + 
        ", filling the air with sweet music. You feel refreshed.\n"); 
    TP->catch_msg("You strum your " + short() + ", filling the " +
        "air with sweet music.\n");
    return 1;
}                 
