/*                         
 * feather duster
 *
 */

#include "/d/Shire/sys/defs.h" 
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <cmdparse.h>

inherit "/std/object";
inherit "/lib/keep";
inherit "/cmd/std/command_driver";

create_object()
{
    set_name("duster");
    add_name("_shire_duster_");
    set_pname("dusters");

    add_adj(({"fluffy"}));
    set_short("feather duster");

    set_long("This "+short()+" is made from many large feathers. They " +
        "are bunched together around a wooden handle. The ends fan out " +
        "slightly and look well used.\n");
    add_item(({"feathers", "large feathers"}),
        "They are large and brown. It appears to be the feathers of " +
        "a duck or goose.\n");
    add_item(({"handle", "wooden handle"}),
        "The wooden handle is round and smoooth from constant use. " +
        "Attached to the end are many large feathers.\n");

    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VALUE,  50);
    add_prop(OBJ_I_VOLUME, 10);

}
void init() 
{
    ::init();
    add_action("do_dust","dust");
}


int
do_dust(string str)
{
    object *oblist;
    if(!strlen(str)) /* no string supplied */
    {
	write("You begin dusting the area with your " + short() + 
        ". After a few minutes, everything looks neat and clean.\n");
	all(" begins dusting the area with " + HIS_HER(TP) + " " + short() + 
        ". After a few minutes, everything looks neat and clean.\n");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Dust what?\n");
	return 1;
    }

    actor("You wave your "+short()+" in front of the face of", oblist); 
    target(" waves " + HIS_HER(TP) + " "+short()+" in front of your face.", oblist);
    all2act(" waves " +HIS_HER(TP) + " "+short()+" in front of",oblist,
         "'s face.");
    return 1;
}
