/*
 * Random item for the Scavanger hunt
 * Coded by Finwe September 2003
 * Originally coded for the Shire, cleaned up in October 2015
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

void create_object()
{
    seteuid(getuid());
    set_name("cigar");
    add_name("_shire_cigar_");
    add_name("dark brown cigar");
    set_pshort("dark brown cigars");
    set_adj(({"dark", "brown"}));
    set_short("dark brown cigar");
    set_long("This is a "+short()+". It is made from pipe-weed that has " +
        "been aged for many months. The leaves have been wrapped together " +
        "tightly to form this " + short() + ".\n");
}
