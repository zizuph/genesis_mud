/*                         
 * silk handkerchief
 *
 */

#include "/d/Shire/sys/defs.h" 
#include <cmdparse.h>
#include <composite.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/object";
inherit "/lib/keep";

create_object()
{
    seteuid(getuid());
    set_name("handkerchief");
    add_name("hanky");
    add_name("_shire_handkerchief_");
    set_pname("handkerchieves");

    set_short("small silk handkerchief");
    add_adj(({"small", "silk"}));

    set_long("This "+short()+" is square and white. It is soft and " +
        "smooth and used to wipe or dab your eyes, or to blow your nose.\n");

    add_prop(OBJ_I_WEIGHT, 15);
    add_prop(OBJ_I_VALUE,  50);
    add_prop(OBJ_I_VOLUME, 10);

}
void init() 
{
    ::init();
    add_action("blow_nose","blow");
//    add_action("wipe_eyes","wipe");
//    add_action("wipe_eyes","dab");


}

int blow_nose(string str)
{
    object target, armour;


    if(str !="nose") 
        return 0;

    if (this_player()->query_armour(TS_HEAD))
        say("You must remove your " +this_player()->query_armour(TS_HEAD) + 
        " before you can blow your nose.\n");

    say(QCTNAME(TP) + " blows " + HIS_HER(TP) + " nose with " + HIS_HER(TP) + " " + short() + ".\n"); 
    TP->catch_msg("You blow your nose with the " + short() + ".\n");
    return 1;
}                 

