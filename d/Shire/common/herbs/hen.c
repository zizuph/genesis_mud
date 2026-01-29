inherit "/std/herb";
 
#include <herb.h>
#include <macros.h>
#include <ss_types.h>
 
#define EFFECT "/d/Shire/common/herbs/henef"
 
create_herb()
{
    set_name("flower");
    set_short("small yellow flower");
    set_pshort("small yellow flowers");
    set_herb_name("henblind");
    set_id_long("This is a field grass common in temperate areas. " +
        "It consists of a umbel of vivid small yellow buds with " +
        "sharp smell. Some say it has little effect but most " +
        "farmers avoid feeding their domestic animals this grass " +
        "as it makes the animals go blind.\n");
    set_unid_long("This is a simple looking small yellow flower.\n");
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
