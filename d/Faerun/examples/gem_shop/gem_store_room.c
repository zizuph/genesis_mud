/*
 * This is the store room where gems are stored that are sold to
 * the gemist. The room will also clone gems when the room resets 
 * so there is an inventory for mortals to choose from
 * -- Finwe, Sept 2016
*/

inherit "/std/room";

#define GEM_LIST ({"agate", "amber", "amethyst", "aquamarine", "beryl", \
    "bloodstone", "carnelian", "chalcedony", "chrysoprase", "coral", \
    "diamond_black", "garnet", "jade", "jasper", "lapis", "moonstone", \
    "onyx", "opal", "opal_fire", "pearl", "peridot", "pyrite", "quartz", \
    "sea_agate", "spinel", "spinel_blue", "spinel_red", "topaz", \
    "tourmaline", "turquoise"})

public void init_gem_store();
void
create_room()
{
    set_short("Gem shop store room");
    set_long("Gem shop store room. This room isn't open to mortals.\n");
}


public void
init_gem_store()
{
    int ran_num = random(17);
    int i;
    string store_gem = "";

    if(ran_num == 0)
    {
        ran_num = 7;
    }

    for(i=0; i<37; i++)
    {
        store_gem = one_of_list(GEM_LIST);
        room_add_object("/d/Genesis/gems/obj/" + store_gem, ran_num);
        ran_num = random(17);
    }
}

public void
init()
{
    ::init();
    init_gem_store();
}
