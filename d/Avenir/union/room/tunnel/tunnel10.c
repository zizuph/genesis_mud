#pragma strict_types

#include "defs.h"
inherit TBASE;

public void
tunnel_room(void)
{
    set_short("end of tunnel");
    set_long("The tunnel ends to the north at a natural arch, "+
	"leading out onto a dimly lit ledge, from where a strong "+
	"current of air is blowing.\n");

    remove_prop(OBJ_I_LIGHT);

    southern("tunnel9");
    add_exit(OUTPOST + "seawall", "north");
}
