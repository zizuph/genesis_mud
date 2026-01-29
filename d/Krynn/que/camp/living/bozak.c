/* Bozak draconian for the drac camp on the
 * Plains of Abanasinia.
 *
 *  ~Aridor, 08/97
 */

#include "/d/Krynn/common/defs.h"

inherit "/d/Krynn/std/bozak";

void
create_bozak()
{
    seteuid(getuid(TO));
    clone_object("/d/Krynn/que/plains/obj/tent")->move(TO,1);
    set_alarm(0.1,0.0,&command("drop tent"));
    set_alarm(0.2,0.0,&command("set up tent"));
    set_alarm(0.3,0.0,&command("enter tent"));
}
