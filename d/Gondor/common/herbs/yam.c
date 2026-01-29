 /*
  *  /d/Gondor/common/herbs/yam.c
  *  An herb of south Gondor.
  *  Eating the yam increases strength slightly and adds some fatigue.
  *  Modified from /d/Gondor/common/herbs/dill.c by Olorin.
  * 
  *  June 19, 2001, Serif.
  */

#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("tuber");
    add_name(({"tuber"}));
    add_pname(({"tubers"}));
    set_adj(({"yellowish", "twisted"}));
    set_herb_name("yam");
    set_short("yellowish twisted tuber");
    set_pshort("yellowish twisted tubers");
    set_ingest_verb("eat");
    set_unid_long("This is a yellowish twisted tuber.\n");
    set_id_long("This is a wild yam tuber. Wild yams (Dioscorea "
        + "villosa) are the thickened roots of a twining herb of the "
        + "yam family. The plant prefers warm climates, its vines "
        + "twining a yard or two in height. Nutrients are stored in "
        + "the twisted yellowish roots.\n");

    set_effect(HERB_ENHANCING, "str", 10); 
    set_id_diff(38);
    set_find_diff(5);
    set_decay_time(10000);
    set_herb_value(432);
    add_prop(OBJ_I_WEIGHT, 60);
    add_prop(OBJ_I_VOLUME, 60);
    set_amount(60);
    set_dryable();
}
