/* an herb coded by Elizabeth Cook/Mouse, April 1997 */
inherit "/std/herb";
#include <herb.h>
#include "../mouse.h"

void create_herb()  {
    set_name("bryony dioica");
    add_name(({"root","plant"}));
    set_herb_name("bryony");
    add_adj(({"large","fleshy"}));
    set_short("large, fleshy root");   
    set_id_long("Bryony is an ivy-like climbing plant with round, red "+
          "berries and a large, fleshy root. The root of this plant, "+
          "when eaten, causes illness and excessive vomiting.\n");
    set_unid_long("A viny plant with a large, fleshy root. You are not "+
          "aware of its uses.\n");
    set_herb_value(300);
    set_decay_time(2400);
    set_find_diff(4);
    set_id_diff(50);
    set_effect(HERB_SPECIAL,0,0);

  }
 
void special_effect()
{
    object ob;
    ob=clone_object(ROOT+"herbs/vomit.c");
    ob->move(ENV(TO));
    ob->start_poison();    
}
