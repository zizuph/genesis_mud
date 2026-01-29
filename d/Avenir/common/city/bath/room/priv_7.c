#pragma strict_types
/*
 * ~/priv_7.c
 *
 * Private room in Melchior's Bath.
 *
 * Revisions:
 *   Grace,  Feb 1994: Created.
 *   Lilith, Apr 2002: ?
 *   Lucius, Oct 2008: Cleanup.
 *   Lucius, Aug 2016: Recoded baths.
 *
 */
#include "../priv.h"
inherit BATH_PRIV;

static void
create_priv_bath(void)
{
    set_short("Northeast private bath");
    set_long("This place invites contemplation and renewal. Hot "+
	"mineral water bubbles up in a deep pool which is cooled "+
	"by a small open aqueduct carrying icy water. The floor "+
	"and walls are made of a textured, rippling travertine "+
	"formed by the spring itself. To aid in meditation, an "+
	"ornate mandala has been cut into the south wall, its "+
	"geometric design seeming to flow with a motion that "+
	"enthralls you. Clouds of steam glow whitely in the "+
	"gentle light provided by hanging lanterns. The air "+
	"is slightly chilly and quite humid scent. "+
	"There is a sign on the door.\n");

    add_item(({"steam", "clouds"}),
	"White and rather dense, the obscuring moisture billows "+
	"up from the surface of the pool.\n");
    add_item(({"wall", "walls", "floor", "travertine"}),
	"This rippled texture, so irregular and yet pleasing to the "+
	"eye, is eternally renewed by the contact of water and "+
	"air. It is smooth and light-coloured.\n");
    add_item(({"aqueduct", "aquaduct", "icy water"}),
	"An artificial channel carved into the floor and wall that "+
	"acts as a conduit for very cold water obtained from a "+
	"cold spring, and is used to cool the extremely hot mineral "+
	"water.\n");
    add_item(({"mandala", "ornate mandala", "south wall"}),
	"The south wall is adorned with a large mandala. It is a "+
	"geometric mosaic of polished opaque stones and gold-leaf "+
	"which catches the light and draws your attention into "+
	"meditative contemplation.\n");
    add_item(({"lantern", "lanterns", "light"}),
	"Suspended from the ceiling on thin wires, the lanterns sway "+
	"slightly, casting vague shadows in the mist.\n");

    add_cmd_item(({"wall","walls"}), ({"feel","touch"}),
	"The walls feel smooth and cool to the touch.\n");

    bath_door("seven", "arc_ne", "sw");
}

public void
hook_smelled(string str)
{
    write("The air has a faint pine scent to it.\n");
}
