/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/key";

public void
create_key()
{
    ::create_key();
    
    set_name("key");
    set_adj("arcane");
    add_adj("silver");
    set_long("An arcane silver key.\n");
    set_key(88800);
}

public void
self_destruct()
{
    object who = environment(this_object());

    if (who && living(who))
        who->catch_msg("The " + short() + " disappears.\n");
    remove_object();
}

public void
activate()
{
    set_alarm(itof(20 + random(5)), -1.0, self_destruct);
}
