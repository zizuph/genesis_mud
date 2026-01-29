inherit "/d/Gondor/elessar/lib/herb";
#include "/d/Gondor/elessar/lib/herb_types.h"

create_herb()
{
  set_name("leaf");
  set_adj("gray");
  set_adj("fuzzy");
  set_herb_name("frostheal");
  set_short("gray fuzzy leaf");
  set_pshort("gray fuzzy leaves");
  set_ingest_verb("eat");
  set_unid_long("This is a small, grayish fuzzy leaf from a diminutive creeping plant.\n"+
    "It's virtue is unknown.\n");
  set_id_long("This grayish fuzzy leaf comes from the Frostheal plant, a plant found at\n"+
    "higher elevations than any other plant, often growing at the very edge\n"+
    "of eversnow. It will make people who eat it more cold-resistant.\n");
  set_herb_value(760);
  set_id_diff(67);
  set_find_diff(6);
  set_effect(HERB_ENHANCING,"cold",20);
  set_decay_time(4600);
}
