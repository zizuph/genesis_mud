#pragma strict_types

#include "defs.h"
inherit TBASE;

public void
tunnel_room(void)
{
    set_long("This is a dark passageway made from smooth granite. "+
	"The tunnel is fairly regular, indicating that it was not "+
	"made my natural means.@@ascending@@ The floor of the passage "+
	"is smooth and worn. A strong breeze is blowing down the "+
	"tunnel from the @@get_north@@. "+ LDESC +"\n");

    add_item(({"ground","floor"}), "It is smooth and worn.\n");

    southern("tunnel8");
    northern("tunnel10");
}
