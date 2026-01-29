inherit "/std/receptacle";

#include <stdproperties.h>

/*
 * Revision Feb 2000 Stern: adapted to genesis gem system
 */

#include "/d/Gondor/defs.h"

#define GEM_DIR "/d/Genesis/gems/obj/"

void    reset_container();

void
create_receptacle()
{
    set_short("small desk");
    set_name("desk");
    set_adj("small");
    set_long(BSN("The  desk was probably crafted by the same skilled artisan "
      + "who made the table and the chairs. The legs are well-turned, and under "
      + "the wooden desk top there is a drawer which can be locked."));

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "Why would you want to take the small desk?\n");
    add_prop(CONT_I_VOLUME,      20000);
    add_prop(CONT_I_WEIGHT,      15000);
    add_prop(CONT_I_MAX_VOLUME,  25000);
    add_prop(CONT_I_MAX_WEIGHT,  20000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);

    set_key("baranor_desk_key");
    set_pick(75);

    reset_container();
}

void
reset_container()
{
    object  gem;

    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK,   1);
    if (present("scroll", TO))
        return;

    FIX_EUID
    clone_object(MORGUL_DIR + "quest/bsw/scroll")->move(TO, 1);

    if (!present("gem", TO))
    {
        gem = clone_object(GEM_DIR + "jade");
        gem->set_heap_size(2+random(4));
        gem->move(TO, 1);
    }
}

/*
 * Function name: short
 * Description  : Remove the status of the container.
 *                Use query_short().
 * Arguments    : object for_obj - the object that wants to know the short.
 * Returns      : string - the short description.
 */
public varargs string 
short(object for_obj)
{
    return obj_short;
}
