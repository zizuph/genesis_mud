/* an herb coded by Elizabeth Cook/Mouse, October 1996 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("verbena officinalis");
    add_name(({"leaves","plant"}));
    set_herb_name("vervain");
    add_adj(({"delicate","lobed"}));
    set_short("plant with delicate, lobed leaves");   
    set_id_long("This plant is vervain. It has a long, thin stem and "+
          "delicate, lobed foliage. It is said to endow one with "+
          "courage and protect one from enchantments.\n");
    set_unid_long("A long stemmed plant with delicate, lobed leaves. "+
          "You do not know if it serves any useful purpose.\n");
    set_herb_value(500);
    set_decay_time(2400);
    set_find_diff(3);
    set_id_diff(40);
    set_effect(HERB_ENHANCING,"dis",2);
    add_effect(HERB_ENHANCING,"magic",10);
  }
 
