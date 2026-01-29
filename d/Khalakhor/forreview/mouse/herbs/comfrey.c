/* an herb coded by Elizabeth Cook/Mouse, March 1997 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("symphytum officinale");
    add_name(({"knitbone","plant"}));
    set_herb_name("comfrey");
    add_adj("bristly");
    set_short("bristly plant");   
    set_id_long("Comfrey is a plant known for its healing properties. "+
          "Its leaves and stem are covered with rough, bristly hairs "+
          "and it bears clusters of drooping purple flowers.\n");
    set_unid_long("This plant is covered with rough, bristly hairs. You "+
          "doubt it is very useful.\n");
    set_herb_value(200);
    set_decay_time(3600);
    set_find_diff(3);
    set_id_diff(50);
    set_effect(HERB_HEALING,"hp",30);
  }
 
