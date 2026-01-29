/*
 * This wand teleports the holder to Fermammons cottage
 */
 
inherit "/d/Ansalon/balifor/flotsam_forest/obj/wand_base";

#define CROOM "/d/Ansalon/balifor/flotsam_forest/coastline/"

public void
create_wand()
{
}

public string
query_teleport_destination()
{
    return CROOM + "cottage2";
}
