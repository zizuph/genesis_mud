/* an herb coded by Elizabeth Cook/Mouse, October 1996. */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("angelica archangelica");
    add_name("plant");
    set_herb_name("angelica");
    set_short("stalky-stemmed plant");
    set_id_long("Angelica is an aromatic plant with a stalky, dark stem "+
          "and large fronds of bright green leaves with jagged edges. "+
          "It improves upon one's mental power and resistance to magical "+
          "forces.\n");
    set_unid_long("An aromatic plant with a stalky, hollow and dark stem "+
          "and large fronds of of bright green leaves with jagged edges. "+
          "Although you have no idea of the uses for this plant, you "+
          "somehow sense you should treat it with respect.\n");  
    set_herb_value(1000);
    set_decay_time(2400);
    set_find_diff(6);
    set_id_diff(70);
    set_effect(HERB_ENHANCING,"int",2);
    add_effect(HERB_ENHANCING,"magic",40);

  }
 
