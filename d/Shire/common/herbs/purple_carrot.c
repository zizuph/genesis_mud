inherit "/std/herb";
 
#include <herb.h>
#include <macros.h>
#include <ss_types.h>
 
#define EFFECT "/d/Shire/common/herbs/purple_carrotef"
 
create_herb()
{
    set_name("carrot");
    set_short("purple carrot");
    set_pshort("purple carrots");
    set_herb_name("grapels");
    set_id_long("This is a purple carrot.\n");
    set_unid_long("This is a purple carrot.\n");
    set_ingest_verb("eat");
    set_id_diff(25);
    set_find_diff(2);
    set_effect(HERB_SPECIAL);
    set_decay_time(3500);
    set_herb_value(0);
}
 
string
query_recover() { return MASTER+":"+query_herb_recover(); }
 
void
init_recover(string arg) { init_herb_recover(arg); }
 
void
special_effect()
{
    object eff;
    eff = clone_object(EFFECT);
    eff->move(this_player());
}
