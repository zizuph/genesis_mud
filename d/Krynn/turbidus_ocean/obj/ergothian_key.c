/*
*    Key for treasure chest in quest in Flotsam
*/
inherit "/std/key";

#define CHEST_KEY 7007

void
create_key() 
{
    ::create_key();

    set_name("key");
    add_name("_ergothian_captain_key");
    set_short("heavy iron key");
    set_adj("heavy");
    add_adj("iron");
    set_long("This is a heavy iron key, stamped with the " +
        "mark of the Blue Phoenix.\n");

    set_key(CHEST_KEY);
    add_prop("_key_i_no_keyring", 1);
}
