inherit "/d/Emerald/std/obelisk";

public void
create_obelisk()
{
    add_name("stone");
    add_adj(({ "stone", "pointed", "dark" }));

    set_short("dark stone");

    set_long("A small, black obelisk, rests beside the path here.\n");

    set_destination("/d/Emerald/mist_tower/mist_isle01");
}

public void
touch_obelisk()
{
    if (!this_player()->query_vampire() && !this_player()->query_wiz_level())
    {
        return;
    }

    ::touch_obelisk();
}
