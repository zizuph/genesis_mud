/* an herb coded by Elizabeth Cook/Mouse, February 1997 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("sempervivum tectorum");
    add_name(({"rosette","plant","hens and chickens"}));
    set_herb_name("houseleek");
    add_adj("succulent");
    set_short("succulent rosette");   
    set_id_long("A succulent plant with pointed leaves that form a "+
         "rosette. The leaves are fleshy and maroon at the tips. Houseleek "+
         "is known for its curative properties and protection against fire "+
         "and lightning.\n");
    set_unid_long("A plant with fleshy leaves arranged in a rosette. You "+
         "wonder if it has any use.\n");
    set_herb_value(500);
    set_decay_time(3600);
    set_find_diff(4);
    set_id_diff(50);
    set_effect(HERB_HEALING,"hp",20);;
    add_effect(HERB_ENHANCING,"fire",5);
    add_effect(HERB_ENHANCING,"electr",5);
    add_effect(HERB_CURING,"all",50);
  }
 
