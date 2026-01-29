#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
  set_name("leaf");
  set_adj(({"white", "broad"}));
  set_herb_name("culkas");
  set_short("broad white leaf");
  set_pshort("broad white leaves");
  set_pname(({"herbs", "leaves", }));
  set_ingest_verb("eat");
  set_unid_long("This is a broad white leaf of some sort.\n");
  set_id_long(BSN("This is a broad white leaf from the Culkas bush. "
    + "The bushes are mostly found in deserts and arid areas, and can "
    + "stand heat and dry weather very well. The leaves are known for "
    + "their fire-resisting virtue."));

  set_effect(HERB_ENHANCING,"fire",20);
  set_id_diff(56);
  set_find_diff(4);
  set_decay_time(4800);
  set_herb_value(864);
  set_dryable();
}

