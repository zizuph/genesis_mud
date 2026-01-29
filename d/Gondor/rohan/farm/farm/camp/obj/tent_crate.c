/* 
 *  This is a crate that will contain items for a quest.
 *  More detail to be added after the quest is coded.
 *
 *  Raymundo, April 2020
 */

#pragma save_binary
#pragma strict_types

inherit "/std/container";
inherit "/d/Gondor/rohan/farm/farm/camp/lib/base_include_objects";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/farm/farm/camp/defs.h"


void
create_container()
{
    
    object comp;

    add_prop(CONT_I_WEIGHT,     10000);     /* This is the entire container. */
    add_prop(CONT_I_VOLUME,       10000);   /* Max 50 dm^3 internal volume.  */
    add_prop(CONT_I_MAX_WEIGHT, 400000);   /* Can max hold  */
    add_prop(CONT_I_MAX_VOLUME,   400000);   /* Volume of box + content.  */
    add_prop(CONT_I_RIGID,            1);   /* This is a rigid container.*/
    add_prop(OBJ_I_NO_GET,            1);   /* Can't get it.*/
    add_prop(CONT_I_TRANSP,           1);   /* Transparent.*/
    set_no_show_composite(1);               /* Don't see it in room desc. */

    set_name("crate");
    add_name("crates");
    add_name("_dunlending_crate");
    add_adj("wooden");
    add_adj("open");
    set_long("This is a medium-sized wooden crate. It's made from rough-"
        + "hewn wooden boards, nailed together to make a crate. It's "
        + "open on top, making it easy for the Dunlendings to store "
        + "items in it.\n");
    
    add_object(include_objects(), 1);
    enable_reset();
 //   reset_container();
    reset_object();

}

int
prevent_leave(object ob)
{
    if(objectp(ob = present("_dunlending_warrior_", environment(TO))))
    {
        write("The dunlending prevents you from grabbing anything from the crate.\n");
        return 1;
    }
    else
    {
        return 0;
    }
}
