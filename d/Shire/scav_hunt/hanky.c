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
inherit "/cmd/std/command_driver";


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
        "smooth, and used to wipe or dab your eyes, or to blow your nose. " +
        "You may also offer your handkerchief to someone with <offer " +
        "'name'>.\n");

    add_prop(OBJ_I_WEIGHT, 15);
    add_prop(OBJ_I_VALUE,  50);
    add_prop(OBJ_I_VOLUME, 10);

}
void init() 
{
    ::init();
    add_action("blow_nose","blow");
    add_action("wipe_eyes","wipe");
    add_action("wipe_eyes","dab");
    add_action("offer_hanky","offer");
    add_action("offer_hanky","proffer");


}

int blow_nose(string str)
{
    object target, armour;


    if(str !="nose") 
        return 0;

    say(QCTNAME(TP) + " blows " + HIS_HER(TP) + " nose with " + HIS_HER(TP) + 
        " " + short() + ".\n"); 
    TP->catch_msg("You blow your nose with the " + short() + ".\n");
    return 1;
}                 

int wipe_eyes(string str)
{
    object target;

    if(str !="eyes") 
        return 0;

    say(QCTNAME(TP) + " " + query_verb() +"s " + HIS_HER(TP) + " eyes with " + HIS_HER(TP) + 
        " " + short() + ".\n"); 
    TP->catch_msg("You " + query_verb() + " your eyes with your " + short() + ".\n");
    return 1;
}                 

int wave_hanky(string str)
{
    object *oblist;
    if(!strlen(str) || str=="hanky" || str=="handkerchief") /* no string supplied */
    {
    write("You wave farewell to everyone with your " + short() + ".\n");
    all(" waves farewell to everyone with " + HIS_HER(TP) + " " + 
        short() + ".\n");
    return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
    write("Wave your handkerchief to who?\n");
    return 1;
    }

    actor("You wave your " + short() + " to",oblist,".");
    target(" offers " + HIS_HER(TP) + " " + short() + " to you.", oblist);
    all2act(" offers " + HIS_HER(TP) + " " + short() + " to ", oblist,".");
    return 1;
}                 
int offer_hanky(string str)
{
    object *oblist;
    if(!strlen(str) || str=="hanky" || str=="handkerchief") /* no string supplied */
    {
    write("You offer your " + short() + " to anyone who needs it.\n");
    all(" offers " + HIS_HER(TP) + " " + short() + " to anyone who needs it.\n");
    return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
    write("Offer your handkerchief to who?\n");
    return 1;
    }

    actor("You offer your " + short() + " to",oblist,".");
    target(" offers " + HIS_HER(TP) + " " + short() + " to you.", oblist);
    all2act(" offers " + HIS_HER(TP) + " " + short() + " to ", oblist,".");
    return 1;
}                 
