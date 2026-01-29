inherit "/d/Emerald/std/door";

void
create_emerald_door()
{
    object lock;

    set_name("gate");
    set_adj(({ "ornate", "gilded" }));
    set_long("A tall, ornate, gilded gate.  It bears the royal " +
        "coat of arms.\n");

    add_item(({ "coat", "coat of arms", "royal coat of arms" }),
        "The royal coat of arms portrays a winged unicorn rearing up over " +
        "the fallen body of an ogre.\n");

    set_open(0);

    lock = add_default_lock();
    lock->set_key("NONE");


}



