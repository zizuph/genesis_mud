#pragma save_binary

inherit "/std/key";
#include <stdproperties.h>
#include <macros.h>

void test_council_member(object player);

create_key()
{
    ::create_key();
    add_name("_Captain_Key");
    set_adj("silver");
    set_pshort("gold keys");
    set_long("This is the key to the Chamber of Officers.\n"+
      "Only the officers of the North Rangers are allowed to carry this key.\n");
    set_key("Captain_Key");
    add_prop(OBJ_I_NO_DROP,"@@who_gives");
    add_prop(OBJ_I_VOLUME,10);
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VALUE,0);
}

init()
{
    set_alarm(10.0, 0.0, &test_council_member(this_player()));
}

void
test_council_member(object player)
{
    if (player != environment(this_object())) return;
    if (!player) remove_object();
    if (player->query_wiz_level()) return;
    seteuid(getuid(this_object()));
    if (!player->query_officer())
    {
        write("You are not allowed to have this key!\n");
        write("The key melts out of your hand.\n");
        remove_object();
        return;
    }
    return;
}

query_auto_load()
{
    return MASTER + ":";
}

who_gives()
{
    if (this_player()->query_real_name()=="elessar") return 0;
    return 1;
}

string query_recover() { return 0; }
