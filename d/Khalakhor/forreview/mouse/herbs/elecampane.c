/* an herb coded by Elizabeth Cook/Mouse, October 1996 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("inula helenium");
    add_name(({"root","plant"}));
    set_herb_name("elecampane");
    add_adj(({"fleshy","tuberous"}));
    set_short("plant with a fleshy, tuberous root");   
    set_id_long("A plant with long, pointed leaves and yellow flowers "+
          "that look like scraggly daisies. The large, fleshy root of "+
          "the elecampane is supposed to be a useful antidote to "+
          "venomous snake bites.\n");
    set_unid_long("A plant with long, pointed leaves and yellow flowers "+
          "that look like scraggly daisies. It has a tuberous root. You "+
          "have no idea of its use.\n");
    set_herb_value(800);
    set_decay_time(3600);
    set_find_diff(5);
    set_id_diff(60);
    set_effect(HERB_CURING,"snake",100);
  }
 
