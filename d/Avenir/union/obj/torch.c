/* A torch for the Union. Cirion 042495 */
#pragma strict_types
#include "../defs.h"

inherit "/std/torch";
inherit "/lib/keep";

#include <macros.h>
#include <stdproperties.h>

#define TORCH_SUBLOC     "_Union_torch_subloc"


public void
create_torch()
{
    set_name("torch");
    set_short("torch");
    add_adj(({"thick", "tar", "tar-drenched", "hardwood"}));
    add_adj("union");
    set_long("It is a thick torch made from a tar-drenched "+
	"hardwood.@@lit_desc@@\n");

    set_time(1800); // 1/2 hour rl
    set_strength(2);
    set_value(130 + random(25));
    add_prop(OBJ_I_VOLUME, 580);
    add_prop(OBJ_I_WEIGHT, 400);
}

public string
lit_desc(void)
{
    if (!query_time())
	return " It is charred and burnt out.";
    else if (!query_prop(OBJ_I_HAS_FIRE))
	return " The wood seems dry and brittle.";
    else
	return " A large, rich orange flame rises from it, "+
	    "sending thick plumes of grey smoke into the air.";
}

/*
 * Function name: short, pshort, long
 * Description:   We change the short, plural short and long description of
 *		  the torch if it's lit, default settings.
 * Returns:	  The description.
 */
public varargs string
short(object for_obj)
{
    string desc;

    if (query_time(1) == query_max_time())
	desc = "new thick ";  // new torch, unlit
    else if (!query_lit(0) && query_time(1))
	desc = "thick ";      // unlit torch, still good
    else if (query_time(1) > 1100 && query_lit(0))
	desc = "brightly "; // lit torch, lots of time left
    else if (query_time(1) > 600 && query_lit(0))
	desc = "softly "; // lit torch, some time left
    else if (query_time(1) > 100 && query_lit(0))
	desc = "smoldering "; // lit torch, a little time left
    else if (query_time(1) && query_lit(0))
	desc = "charred "; // lit torch, very little time left
    else
	desc = "burnt-out "; // time's up!

    // double ::'s to get rid of the (lit) message
    return desc + ::short(for_obj);
}

public void
torch_tell(void)
{
    string str;
    object where;

    if (!query_lit(0))
	return;

    switch(random(5))
    {
    case 0:
	str = "emits some thick, black smoke into the air.";
	break;
    case 1:
	str = "flickers gently.";
	break;
    case 2:
	str = "crackles as it burns a dry splinter.";
	break;
    case 3:
	str = "flicker, making strange shadows dance all about.";
	break;
    default:
	str = "crackles gently.";
    }

    where = ENV(TO);
    if (!living(where))
    {
	tell_room(where, "The "+ QSHORT(TO) +" "+ str +"\n");
    }
    else
    {
	where->catch_msg("Your "+ QSHORT(TO) +" "+ str +"\n");
	tell_room(ENV(where), QCTPNAME(where) +" "+ QSHORT(TO) +
	    " "+ str +"\n", ({ where }));
    }

    set_alarm(itof(random(200) + 20), 0.0, torch_tell);
}

public int
light_me_after_delay(void)
{
    ::light_me_after_delay();
    set_alarm(itof(random(200) + 20), 0.0, torch_tell);
    return 1;
}
