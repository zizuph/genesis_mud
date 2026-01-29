/*
    This item serves as replacement for hat.c, it will automatically
    give an owner of the hat new gc_item.c when the hat autoloads.
    Written by Valen, 20011110
 */

inherit "/std/object";

void
create_object(void)
{
    set_name("hat");
    set_short("special hat");
    set_long("This hat should replace itself with new version when a player " +
             "logs in.\n");
}

public int
move(mixed dest, mixed subloc)
{
    int rv;
    object ob;
        
    setuid();seteuid(getuid());

    rv = (ob = clone_object("/d/Raumdor/guilds/gc/gc_item"))->move(dest, subloc);

    ob->init_arg("dummy#it#0#");

    write_file("/d/Raumdor/guilds/gc/log/hat_changes",
        ctime(time()) + " " + capitalize(dest->query_real_name()) +
        " was given new guild item, result = " + rv + ".\n");

    remove_object();
}
