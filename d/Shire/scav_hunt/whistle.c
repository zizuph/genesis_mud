/*                         
 * duck whistle
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
    set_name("whistle");
    add_name("_shire_duckwhistle_");
    set_pname("whistles");

    set_short("round wooden duck whistle");
    add_adj(({"round", "wooden"}));

    set_long("This "+short()+" is carved of wood. The mouthpiece is " +
        "smooth and flat which flares out to a small bell shape.\n");
    add_item(({"mouthpiece"}),
        "The mouthpiece is a finger's length and flat. A slit is carved " +
        "into the top where you can blow into it. At the end is a " +
        "square hole with rectangular groove for escaping air.\n");  

    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VALUE,  50);
    add_prop(OBJ_I_VOLUME, 10);

}
void init() 
{
    ::init();
    add_action("blow_whistle","blow");
}

int blow_whistle(string str)
{
    object target;

    if((str !="whistle") && (str !="duck whistle") && 
       (str !="round duck whistle") && (str !="round wooden duck whistle") && 
       (str !="wooden duck whistle")&& (str !="wooden whistle")) return 0;


    say(QCTNAME(TP) + " blows " + HIS_HER(TP) + " duck whistle. " +
        "It goes: 'Quaaack! Quaaack!!'\n"); 
    TP->catch_msg("You blow the " + short() + ". It goes: " +
        "'Quaaack! Quaaack!!'\n");
    return 1;
}                 

