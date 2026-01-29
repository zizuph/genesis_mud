/* an herb coded by Elizabeth Cook/Mouse, October 1996 */
inherit "/std/herb";
#include "../mouse.h"
#include <herb.h>

void create_herb()  {
    set_name("eranthis hyemalis");
    add_name(({"leaves","plant"}));
    set_herb_name("aconite");
    add_adj(({"narrow","toothless"}));
    set_short("bunch of narrow, toothless leaves");   
    set_id_long("This is a rather dangerous member of the aconite "+
          "family. It has narrow, toothless leaves arranged atop the "+
          "stem, giving the plant the appearance of a miniature palm tree. "+
          "It has a tuberous root and in the winter, it bears yellow "+
          "blossoms. This herb should not be eaten. It is toxic and causes "+
          "blindness.\n");
    set_unid_long("This plant has narrow,toothless leaves and resembles a "+
          "miniature palm tree. You are not knowledgeable enough to "+
          "discover its uses.\n");
    set_herb_value(500);
    set_decay_time(3600);
    set_find_diff(5);
    set_id_diff(70);
    set_effect(HERB_SPECIAL,0,0);

  }
 
void special_effect()
{
  object blind;
  blind=clone_object(ROOT+"herbs/blind.c");
  blind->move(ENV(TO));
  blind->start_poison();
}
