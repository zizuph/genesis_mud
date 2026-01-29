inherit "/d/Gondor/std/steed/steed";

void
create_steed()
{
    set_race_name("dogcow");
    set_adj(({"black and white", "spotted"}));

    set_long("It is a strange creature. It looks somewhat like a very small "+
      "or perhaps a very large terrier. It is long-haired, white with large "+
      "patches of carbon black, and has a pair of bone-yellow horns "+
      "and deep soulful eyes.\n");
}

public int
can_mount(object o)
{
    if (o->query_real_name() != "igneous")
	return 0;

    return 1;
}
