/*                         
 * elven harp
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
    set_name("harp");
    add_name("_shire_harp_");
    set_pname("harps");

    set_short("beautiful wooden harp");
    add_adj(({"beautiful", "wooden"}));

    set_long("This is a " + short() + ". It is 'U' shaped and fans " +
        "out at the top. Two horizontal rods have been set into " +
        "the instrument. One is set into the neck where it " +
        "begins to fan out and at the base. Eight silver strings have " +
        "been strung between the two rods and are very taunt. " +
        "By strumming the strings the player is able to play " +
        "beautiful music that warms the heart and soothes the " +
        "soul.\n");
    add_item(({"strings", "silver strings"}),
        "The strings are made from spun silver. They are smooth and " +
        "stretched between the rods.\n");
    add_item(({"rods", "horizontal rods"}),
        "These rods are round and smooth. Stretched taunt between " +
        "them are eight silver strings.\n");

    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VALUE,  500);
    add_prop(OBJ_I_VOLUME, 100);

}
void init() 
{
    ::init();
    add_action("strum_harp","strum");
    add_action("strum_harp","play");
}

int strum_harp(string str)
{
    if((str !="harp") && (str !="strings") && (str !="silver strings")) return 0;

    say(QCTNAME(TP) + " strums " + HIS_HER(TP) + short() + 
        ", filling the air with sweet music. You feel refreshed.\n"); 
    TP->catch_msg("You strum your " + short() + ", filling the " +
        "air with sweet music.\n");
    return 1;
}                 

