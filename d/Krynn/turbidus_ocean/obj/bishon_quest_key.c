/*
*    Key for treasure chest in quest in Flotsam
*/
inherit "/std/key";

#define CHEST_KEY 7077

void
create_key() 
{
    ::create_key();

    set_name("key");
    add_name("_bishon_quest_key");
    set_short("rusty iron key");
    set_adj("rusty");
    add_adj("iron");
    set_long("This is a rusty iron key, corroded by exposure " +
        "to sea water.\n");

    set_key(CHEST_KEY);
    add_prop("_key_i_no_keyring", 1);
}
