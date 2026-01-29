/*
 *
 *
 * Fake stamp for the stamp collecting event.
 *
 *  by Palmer
 * Date, Jan 2003
 */

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    ::create_object();

    set_name("stamp");
    set_pname("stamps");
    set_adj(({"green", "heart-shaped"}));
    set_short("green heart-shaped stamp");
    set_long("This postage stamp is shaped like a heart. " +
    "A picture of a laughing jackass adorns the front. " +
    "Judging from the poor print and paper quality, it is " +
    "obviously a forgery.\n");

}
