#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit "/d/Krynn/std/room";

create_room()
{
    set_short("Near second floor landing");

    set_long(BS("A huge piece of machinery dominates this part of the " +
      	"tunnel.  The noise is awful.  The machine is pounding at the " +
      	"rock to the west, with water and rock dust spraying all over.  " +
     	 "A guardroom lies north.  You have reached the Krynnish " +
      	"gnomes' Expansion Guild lab.  It would have been put on the " +
      	"ground floor, but the rock here was more interesting.", 70));
    INSIDE;
    LIGHT;
    add_item(({"cave", "caves", "tunnel"}), "Hewn out of the solid rock, " +
	"this tunnel is one of the gnomish research labs. It extends a" +
	" long way from the main cavern.\n");
    add_item(({"machine", "machinery"}), "It's huge and noisy and you" +
	" haven't got the slightest clue to what it does.\n");
    add_exit(TDIR + "cavern23", "east", 0);
    add_exit(TDIR + "guard2", "north", 0);
}

reset_room()
{
    if (!present("emong", TO)) fillit(random(3) + 1);
    if (!present("gauntlets", TO))
	clone_object(OBJ + "gauntlets")->move(TO);
}

wayout() { return "east north"; }
tohelp() { return "north"; }
fromhelp() { return "east"; }
area() { return "Hereonthisfloor"; }

fillit(num)
{
    int i;
    for (i = 0; i < num; i++)
	clone_object(MON + "gnome")->move_living("xxx", TO);
}

