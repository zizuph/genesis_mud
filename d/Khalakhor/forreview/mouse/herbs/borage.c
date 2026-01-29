/* an herb coded by Elizabeth Cook/Mouse, December 1996 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("borago officinalis");
    add_name(({"flowers","plant"}));
    set_herb_name("borage");
    add_adj(({"blue","star-shaped"}));
    set_short("bunch of sky blue, star-shaped flowers");   
    set_id_long("The borage plant has dark green, toothless, and pointed "+
          "leaves. Both stem and leaves are covered with prickly white "+
          "hairs. Ingesting the light blue blossoms of this plant has long "+
          "been known to make one courageous in battle.\n");
    set_unid_long("A hairy plant with pretty sky blue blossoms. You do not "+
          "know for sure if it is useful.\n");
    set_herb_value(500);
    set_decay_time(2400);
    set_find_diff(4);
    set_id_diff(50);
    set_effect(HERB_ENHANCING,"dis",7);
  
  }
 
