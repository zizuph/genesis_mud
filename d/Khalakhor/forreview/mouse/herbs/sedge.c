/* an herb coded by Elizabeth Cook/Mouse, October 1996 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("acorus calamus");
    add_name(({"sweetflag","plant","root"}));
    set_herb_name("sweet sedge");
    add_adj(({"sweetly","aromatic"}));
    set_short("sweetly aromatic root");   
    set_id_long("This plant is sweet sedge. It has reedlike, shiny "+
          "yellowish-green leaves and tiny yellowish flowers that "+
          "blossom along a spike protruding at an angle from the stem. "+
          "The leaves and root are highly aromatic. You believe the root "+
          "of this plant has some restorative properties.\n"); 
    set_unid_long("A plant with reedlike, shiny yellowish-green leaves "+
          "and a spike of yellow flowers protruding from its stem. The "+
          "spicy aroma of the leaves and root smells familiar, but you "+
          "don't recall why.\n");
    set_herb_value(300);
    set_decay_time(3600);
    set_find_diff(3);
    set_id_diff(50);
    set_effect(HERB_HEALING,"hp",40);
    add_effect(HERB_HEALING,"mana",20);
  }
 
