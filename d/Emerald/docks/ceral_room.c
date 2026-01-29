inherit "/d/Emerald/std/room";

public void
create_ceral_room()
{
}

public nomask void
create_emerald_room()
{
    set_short("Ceral Island");

    add_item(({ "shore", "shores", "rocky shores" }), "The rocky shores " +
       "of the small island are marked by a large number of docks " +
       "extending out into the water.\n");

    add_item(({ "docks", "docking area" }),
       "Quite a number of docks extend out from the shore of the island, " +
       "all the way around.\n");

    add_item(({ "path", "pathway" }),
        "A circular pathway leads around the small island, " +
        "providing access to the many docks.\n");

    add_item("waves",
        "The swelling ocean waves crash loudly on the rocky shore.\n");

    add_item(({ "ships" }),
        "Ships of all types can be seen on the horizon and docked around " +
        "the island.\n");

    add_item(({ "seagull", "seagulls" }),
        "Seagulls can be seen and heard all about the island and in the " +
        "air above, screeching loudly as they search for bits of food " +
        "left behind by passengers.\n");


    add_item("pavilion", "The large structure resides at the center of " +
       "the small island.  It looks like a good place for travellers to " +
       "find information or shelter in inclement weather.  Unfortunately, " +
       "it seems to be closed at the moment.\n");


    create_ceral_room();
}

public void
hook_smelled(string arg)
{
    if (strlen(arg))
    {
        return;
    }

    write("The distinct smell of the ocean fills the air.\n");
}
