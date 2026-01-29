/*
 * Original Teleporting Wand
 *
 * This wand was the original wand that teleports to CROOM + "road15"
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
    return CROOM + "road15";
}
