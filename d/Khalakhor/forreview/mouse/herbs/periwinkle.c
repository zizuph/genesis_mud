/* an herb coded by Elizabeth Cook/Mouse, February 1997 */
inherit "/std/herb";
#include <herb.h>
#include "../mouse.h"  

void create_herb()  {
    set_name("catharanthus roseus");
    add_name(({"plant","leaves"}));
    set_herb_name("rose periwinkle");
    add_adj("glossy");
    set_short("plant with glossy leaves");   
    set_id_long("Rose periwinkle is a vine-like plant with glossy "+
          "leaves and stems and bright pink, five petaled blossoms. "+
          "While very lovely, this plant causes hallucinations if eaten.\n");
    set_unid_long("A pretty plant with shiny leaves and bright pink "+
          "flowers. You have no idea of its uses.\n");
    set_herb_value(400);
    set_decay_time(2400);
    set_find_diff(5);
    set_id_diff(60);
    set_effect(HERB_SPECIAL,0,0); 
  
}
 
void special_effect()  
{
    object ob;
    ob=clone_object(ROOT+"herbs/euphoria.c");
    ob->move(ENV(TO));
    ob->start_poison();

}

