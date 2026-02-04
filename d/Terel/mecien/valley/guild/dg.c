/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

create_room(){

set_short("Dark Grotto");
set_long(
"Shadowy, filled with swirling mists and drifting vapors, this ancient\n"
+"grotto captures some strange force, binds it to itself, forcing the way\n"
+"between worlds to be altogether nothing. The shadow of doom drifts here,\n"
+"likening itself to the perils of the abyss.\n"
);

add_prop("_can_summon_the_earth", 1);

add_exit("/d/Terel/mecien/valley/guild/lowt2", "south", 0);
}

