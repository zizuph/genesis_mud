inherit "/std/herb";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#include <herb.h>

/* An herb that increases tracking skill by giving eater special */
/* senses. Strength is 40, Sarr */

void
create_herb()
{
    set_name("leaf");
    set_adj(({"yellow","bright"}));
    set_short("bright yellow leaf");
     
    set_id_long("This large leaf is called kuko. It can be recognized "+
    "easily by its bright yellow color. It is rare, and valuable, only "+
    "found in the depths of the wildest jungles and forests. When "+
    "chewed, it is said to give one a greater awareness.\n");

    set_unid_long("This is a large leaf that is bright yellow in "+
    "color. You have never seen anything like it before.\n");

    set_herb_name("kuko");
    set_amount(10);
    set_decay_time(2800);
    set_id_diff(30);
    set_find_diff(6);
    set_herb_value(1500);
    set_ingest_verb("chew");
    set_effect(HERB_SPECIAL,"",0);
}

void
special_effect()
{
    object ske;
    seteuid(getuid());
    ske = clone_object("/d/Kalad/common/herbs/kskill_enhance");
    ske->set_enhance_effect(SS_AWARENESS,"be aware",20);
    ske->move(TP);
}
