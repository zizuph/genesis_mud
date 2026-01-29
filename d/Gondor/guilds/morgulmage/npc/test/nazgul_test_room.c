inherit "/std/room";

void
create_room()
{
    set_long("Nazgul test room.\n");
    add_exit("/d/Gondor/guilds/morgulmage/npc/test/droproom", "south");

}

int
nazgul_cmd(string args)
{
    if (!this_player()->query_wiz_level()) return 0;
    write("Summoning nazgul.\n");

    setuid();
    seteuid(getuid());
    object nazgul = clone_object("/d/Gondor/guilds/morgulmage/npc/nazgul");
    nazgul->start_encounter(this_player());

    return 1;
}

void
init()
{
    ::init();
    add_action(nazgul_cmd, "nazgul");
}
