/* an herb coded by Elizabeth Cook/Mouse, October 1996 */
inherit "/std/herb";
#include <herb.h>
#include "../mouse.h"

void create_herb()  {
    set_name("polypodium vulgare");
    add_name(({"wood licorice","fern","plant"}));
    set_herb_name("sweet fern");
    set_short("fern");   
    set_id_long("A woodland fern with a root that tastes remarkably "+
          "like licorice. Sweet fern is flowerless and its seeds can "+
          "be found on the backs of the leaves. You have discovered a "+
          "very rare form of fern that allows one to pass unnoticed.\n");
    set_unid_long("This plant looks like an ordinary fern. You suspect "+
          "there is something different about it, but you can't tell "+
          "what it is.\n");
    set_herb_value(1500);
    set_decay_time(3600);
    set_find_diff(7);
    set_id_diff(90);
    set_effect(HERB_SPECIAL,0,0);

  }
 
void special_effect()
{
  object invis;
  invis=clone_object(ROOT+"herbs/invis.c");
  invis->move(ENV(TO));  
}
