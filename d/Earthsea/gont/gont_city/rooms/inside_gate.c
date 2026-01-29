#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Arch within city walls");
    set_long("The road passes through a wide arch in"+
        " the thick city walls here, perfectly rounded and"+
        " set in cut black stone. Inside the arch, the light is"+
        " very dim, provided by torches set into the walls"+
        " on both sides. Looking up, you can see the vaulted"+
        " stone roof high above you. The sound of your"+
        " footsteps echoes back from the walls as you walk. To the"+
        " south is the city, with many tall stone houses and"+
        " towers visible through the end of the tunnel.\n");
    add_item(({"arch","tunnel"}),"This tunnel is the only"+
        " entrance to the great Port of Gont from the landside,"+
        " leading through the thick, ancient city walls.\n");
    add_item("walls","You are inside the thick stone walls"+
        " surrounding the city. Torches are set into both sides"+
        " of the tunnel to provide a little light for travellers"+
        " entering.\n");
    add_item("torches","Several torches are set in iron rings"+
        " on both sides of the tunnel, providing a flickering"+
        " light.\n");
    add_item(({"city","houses","towers"}),"The city is south"+
        " of here at one end of the tunnel, with many tall stone"+
        " houses and towers.\n");
    add_item("stone","The city wall is built by cut black"+
        " stones, perfectly set together without almost any gaps"+
        " between them.\n");
    add_exit("landbridge", "north");
    add_exit("city_street/city_road1", "south");
}
