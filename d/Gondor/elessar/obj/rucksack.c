#include "defs.h"
#include <stdproperties.h>

inherit STD_DIR+"sack";

/*
 *  Description: Constructor.
 */
public void
create_sack() {
    set_name(({"sack","ruck-sack"}));
    set_pname(({"ruck-sacks","sacks"}));
    set_adj( ({ "polished", "finely", "ruck" }) );
    set_short("finely polished ruck-sack");
    set_pshort("sacks");
    set_long("This is a fine rucksack.\n");

    add_prop(CONT_I_WEIGHT,     1200);          /* 1.2 kg        */
    add_prop(CONT_I_VOLUME,     500);           /* Empty volume. */
    add_prop(CONT_I_MAX_VOLUME, 90*1000);       /* 60 l          */
    add_prop(CONT_I_MAX_WEIGHT, 400*1000);      /* 300 kg        */
    add_prop(CONT_I_CLOSED,     0);
    add_prop(CONT_I_RIGID,      0);
    add_prop(CONT_I_TRANSP,     0);
}
