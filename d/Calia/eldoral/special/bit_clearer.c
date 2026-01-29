inherit "/std/object";

public void
create_object()
{
    set_name("bitclearer");
    set_short("bitclearer");
    set_long("bitclearer");
}

public int
do_clear(string who)
{
    reset_euid();
    find_player("khailjr")->clear_bit(4,4);
    find_player("khail")->clear_bit(4,4);
}

init()
{
    ::init();
    add_action(do_clear, "clearbit");
}
