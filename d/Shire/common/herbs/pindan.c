inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"

create_herb()
{
    set_name("moss");
    set_short("handful of grey moss");
    set_pshort("handfuls of grey moss");
    set_herb_name("pindan");
    set_adj(({ "grey" }));
    set_id_long(
	"This is a handful of a very useful herb called Pindan. "+
	"It is used to brighten up one's mind, thereby gaining "+
	"a better sense of one's location. "+
	"You must inhale the scent of it to gain effect.\n");
    set_unid_long(
	"This is a handful of a grey moss.\n");
    set_ingest_verb("inhale");
    set_id_diff(22);
    set_find_diff(1);
    set_effect(HERB_SPECIAL);
    set_decay_time(4000);
    set_herb_value(3130);
}

string
query_recover() { return MASTER+":"+query_herb_recover(); }

void
init_recover(string arg) { init_herb_recover(arg); }

void
special_effect()
{
    object eff;

    setuid();
    seteuid(getuid());
    eff = clone_object("/d/Shire/common/herbs/pindanef");
    eff->move(this_player());
}
