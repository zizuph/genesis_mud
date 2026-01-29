/* an herb coded by Elizabeth Cook/Mouse, October 1996 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("achillea millefolium");
    add_name(({"milfoil","plant"}));
    set_herb_name("yarrow");
    set_short("plant with feathery leaves");   
    set_id_long("This plant is yarrow. It has small, white flowers "+
          "set in clusters atop long, thin stems. It has narrow, "+ 
          "feathery leaves endowed with mild healing properties.\n");
    set_unid_long("A plant with small, white flowers set in clusters "+
          "atop long, thin stems. Its leaves are narrow and feathery. "+
          "You aren't sure if it has any use.\n");
    set_herb_value(300);
    set_decay_time(3600);
    set_find_diff(3);
    set_id_diff(50);
    set_effect(HERB_HEALING,"hp",40);
    add_effect(HERB_HEALING,"fatigue",5);
  }
 
