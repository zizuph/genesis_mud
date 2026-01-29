/* Room of Gont City. Created by Porta 971014. */

#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

private object corporal, *patrol = allocate(3);

public void
reset_room()
{
    int i = sizeof(patrol);
    object to = this_object();

    setuid();
    seteuid(getuid());

    if(!objectp(corporal))
    {
        corporal = clone_object("/d/Earthsea/gont/gont_city/liv/corporal");
        corporal->move(to);
        corporal->command("emote marches in.");
    }

    while(i--)
    {
        if(!objectp(patrol[i]))
        {
            patrol[i] = clone_object("/d/Earthsea/gont/gont_city/liv/guard1");
            patrol[i]->move(to);
            patrol[i]->command("emote marches in.");
            corporal->team_join(patrol[i]);
        }
    }
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Narrow street in the living quarters");
    set_long("The narrow cobbled street continues,"+
        " winding between the tall houses and towers making up the"+
        " the living quarters of the city. Most of the"+
        " buildings here are at least two storys high, casting"+
        " large shadows over the road. There are lines full"+
        " of drying laundry hanging between the upper floors"+
        " of the houses. Everywhere around you can see people"+
        " passing by, on their way to different places."+
        " East the road continues within the living quarters"+
        " but to the southwest the buildings seem to become"+
        " even larger.\n");
    add_item(({"towers","houses","buildings"}),
        "Tall houses and towers"+
        " line the street on both sides, making it look dark"+
        " and gloomy. Most of the buildings seem to be living"+
        " quarters for the citizens.\n");
    add_item("street","The narrow cobbled street is very"+
        " dirty and dark, shadowed by the tall houses around.\n");
    add_item(({"lines","laundry"}),"Lines of drying laundry"+
        " are stretched between the upper storys of the houses"+
        " around.\n");
    add_item("people","Most are dark-skinned, showing that"+
        " they were born on the island of Gont, but you can also"+
        " see travellers from abroad dressed in exotic clothes.\n");
    add_exit("city_road2", "east");
    add_exit("city_road5", "southwest");
    reset_room();
}
