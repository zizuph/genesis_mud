/* an herb coded by Elizabeth Cook/Mouse, March 1997 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("urtica dioica");
    add_name("plant");
    set_herb_name("nettle");
    set_short("plant with stinging hairs");   
    set_id_long("Despite leaves and stems covered with stinging hairs, "+
          "nettle is a useful cure for all poisons. It has dark, large, "+
          "toothy leaves and square stems.\n");
    set_unid_long("This plant is covered with awful stinging hairs. It "+
          "hardly seems worth the effort to pick.\n");
    set_herb_value(500);
    set_decay_time(3600);
    set_find_diff(5);
    set_id_diff(60);
    set_effect(HERB_CURING,"all",70);
  }
 
