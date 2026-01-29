inherit "/d/Emerald/std/room";

public void
create_emerald_room()
{
    set_long("A room\n");
}

public int
check_persistent_object(object ob)
{
    return ob->query_furniture();
}
