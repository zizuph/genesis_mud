/* an herb coded by Elizabeth Cook/Mouse, October 1996 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("polygonatum oficinale");
    add_name(({"root","plant","rhizome"}));
    set_herb_name("solomon's seal");
    add_adj("nodulous");
    set_short("nodulous plant rhizome");   
    set_id_long("A plant with yellowish-green, bell-shaped flowers "+
         "that hang beneath leaves set upon a drooping stem. The "+
         "rhizome, or root, has interesting nodules that bear a "+
         "resemblance to a seal on a letter. Thus you know you have "+
         "discovered Solomon's Seal, a plant with great healing "+
         "properties.\n");
    set_unid_long("A plant with yellowish-green, bell-shaped flowers "+
         "hanging from a drooping stem. It has a very strange looking "+
         "root. You can't imagine what to do with this strange plant.\n");
    set_herb_value(700);
    set_decay_time(3600);
    set_find_diff(6);
    set_id_diff(70);
    set_effect(HERB_CURING,"all",80);
    add_effect(HERB_HEALING,"hp",20);
  }
 
