inherit "/d/Emerald/std/obelisk";

public void
create_obelisk()
{
    add_name("stone");
    add_adj(({ "stone", "pointed", "dark" }));

    set_short("dark stone");

    set_long("A small, black obelisk, which is partially submerged in the " +
        "lake.  The edge of a small pedestal is visible among the rocks at " +
        "its base.  Ages ago, the obelisk was probably at the shore of the " +
        "lake, but a rise in the water level has hidden it.\n");

    add_item("pedestal", "The edge of a stone slab is visible through " +
        "the water.  It seems to form a pedestal for a small, black " +
        "obelisk.\n");

    set_destination("/d/Emerald/mist_tower/mist_isle01");
}
