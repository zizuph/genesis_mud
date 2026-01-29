
#pragma save_binary
#pragma strict_types

inherit "/std/container";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define RACK_LOG    "/d/Shire/log/rack_log"
#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))

void
create_container()
{
    /* This compartment is suposed to be invisible and only accessable
     * under the propper circumstances.
     */

    object comp;

    add_prop(CONT_I_WEIGHT,     10000);     /* This is the entire container. */
    add_prop(CONT_I_VOLUME,       10000);   /* Max 50 dm^3 internal volume.  */
    add_prop(CONT_I_MAX_WEIGHT, 400000);   /* Can max hold  */
    add_prop(CONT_I_MAX_VOLUME,   400000);   /* Volume of box + content.  */
    add_prop(CONT_I_RIGID,            1);   /* This is a rigid container.*/
    add_prop(OBJ_I_NO_GET,            1);   /* Can't get it.*/
    add_prop(CONT_I_TRANSP,           1);   /* Transparent.*/
    set_no_show_composite(1);               /* Don't see it in room desc. */

    set_name("behind sign");

    set_long("This is behind the sign. Tall grasses grow " +
    "up the back of the sign, and some flowers twine up along the post.\n");

}

public void
enter_inv(object ob, object from)
{
	::enter_inv(ob, from);
	if (file_size(RACK_LOG) > 50000)
	{
	    rename(RACK_LOG, (RACK_LOG + ".old"));
	}

        write_file(RACK_LOG, (ctime(time()) + " "+  WRITE_NAME(from) + " Placed in rack: (a/an) " + ob->query_short() + ".\n"));
}

public void
leave_inv(object ob, object to)
{
	::leave_inv(ob, to);
	if (file_size(RACK_LOG) > 50000)
	{
	    rename(RACK_LOG, (RACK_LOG + ".old"));
	}

        write_file(RACK_LOG, (ctime(time()) + " "+  WRITE_NAME(to) + " Took from rack: (a/an) " + ob->query_short() + ".\n"));
}
