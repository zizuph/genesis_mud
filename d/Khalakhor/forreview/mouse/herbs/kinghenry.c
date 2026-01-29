/* an herb coded by Elizabeth Cook/Mouse, October 1996 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("chenopodium bonus-henricus");
    add_name(({"leaves","plant"}));
    add_adj(({"large","arrow-shaped"}));
    set_herb_name("good king henry");
    set_short("bunch of large, arrow-shaped leaves");   
    set_id_long("This plant has large, arrow-shaped green leaves. "+
          "Rather unremarkable tiny green flowers are found upon "+
          "spikes at the top of the plant. Good King Henry will "+
          "endow you with strength.\n");
    set_unid_long("A plant with large, arrow-shaped leaves and "+
          "unremarkable tiny green flowers. It just looks like an ugly "+
          "weed to you.\n");
    set_herb_value(300);
    set_decay_time(3600);
    set_find_diff(3);
    set_id_diff(50);
    set_effect(HERB_ENHANCING,"str",2);
    add_effect(HERB_HEALING,"fatigue",5);
  }
 
