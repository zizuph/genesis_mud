/* Based on Blizzard's ash_bow.c in Qualinesti
 * 
 *
 * Blizzard, 12.05.2003
 */

#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include <formulas.h>

inherit "/std/bow";


public void
create_bow()
{
    set_adj(({"solamnian", "long"}));
    add_name("longbow");
    set_short("solamnian longbow");
    set_long("This is a well crafted Solamnian longbow.  It is feared for its "+
        "penetrating power, with accounts even of mounted warriors being pinned to "+
        "their horse by an arrow that passed through both armoured thighs " +
        "not being uncommon!\n"); 

    add_prop(OBJ_I_WEIGHT, 900);
    add_prop(OBJ_I_VOLUME, 3250);
    add_prop(OBJ_I_VALUE, 2000);
    set_wf(TO);

    set_hit(35);
    set_pen(40);
    
    seteuid(getuid(TO));
}