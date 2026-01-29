/*
 * /d/Gondor/guilds/militia/obj/guild_item.c
 *
 * This code is copyright (c) 2001 by Scott A. Hardy and Alyssa Hardy.
 * Genesis is a game currently run through Chalmers University.
 * Scott and Alyssa Hardy have seen the 1991 document of Genesis'
 * called 'legal', and they do not forfeit any of their intellectual
 * property rights as that document supposes they would.  They are the
 * sole and complete owners of this code, which as of April 2001 they are
 * loaning to Genesis.  Genesis does not own this code, or
 * have any right to transfer it to anyone.  By its ongoing
 * use and storage of their code, Genesis acknowledges and agrees
 * to all of the above.
 *
 * Guild item for the Militia
 *
 * Coded by Auberon and Gwyneth
 */
inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../militia.h"

string gName = "";

string
long_desc()
{
    string txt = "The soft and supple leather of the militia boots has been " +
        "lovingly stitched together by a citizen of Thornlin for the " +
        "brave men and women of the town militia. The coat of arms of the " +
        "Thornlin Militia has been embossed in the leather on one side";

    if (strlen(gName))
        txt += ", and on the other, the name '" + capitalize(gName) + "'.\n";
    else
        txt += ".\n";

    txt += "You see tiny words reading 'help militia' on the boots.\n";
    return txt;
}

void
create_armour()
{
    set_name(({"boots", MITEM_ID}));
    add_name("_ithilien_badge");
    set_pname("boots");
    set_adj(({ "soft", "pair", "of", "militia" }));
    set_short("pair of leather militia boots");
    set_pshort("pairs of leather militia boots");
    set_long(&long_desc());

    set_ac(5); /* I am very tired of these breaking, hope high AC helps */
    set_at(A_FEET);
    set_likely_break(1);
    
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 200);
}

/* Function name: set_militia_name
 * Description  : Keep track of the owner
 * Arguments    : string name - the name of the owner
 */
void
set_militia_name(string name)
{
    gName = name;

    name = environment()->query_real_name();

    /* Needs query_real_name() instead of query_name() */
    add_prop("_ithilien_leave_name", name);
    /* Let them into Ithilien. */
    environment()->add_prop("_ithilien_leave_by_hunthor", 1);
}

/* Function name: query_militia_name
 * Description  : Gives the name of the owner
 * Returns      : string gName - the name of the owner
 */
string
query_militia_name()
{
    return gName;
}

/* Function name: query_recover
 * Description  : It's autoloading already. If we let it recover, it
 *                might duplicate itself.
 */
string
query_recover()
{
    return 0;
}
void 
leave_env(object old, object dest)
{
    ::leave_env(old, dest);

    old->remove_prop("_ithilien_leave_by_hunthor");
}
