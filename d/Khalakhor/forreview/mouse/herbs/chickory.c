/* an herb coded by Elizabeth Cook/Mouse, December 1996 */
inherit "/std/herb";
#include <herb.h>

void create_herb()  {
    set_name("cichorium intybus");
    add_name(({"succory","plant","flowers"}));
    set_herb_name("chicory");
    add_adj(({"pale","blue"}));
    set_short("bunch of pale blue flowers");   
    set_id_long("A plant with clusters of pale blue flowers set along "+
          "thin, hairy stems. The stems are bare of foliage over most "+
          "of their lengths. The flowers of this plant are sometimes "+
          "effective in cleansing poisons from the body.\n");
    set_unid_long("A plant with clusters of pale blue flowers.\n");
    set_herb_value(400);
    set_decay_time(3600);
    set_find_diff(4);
    set_id_diff(60);
    set_effect(HERB_CURING,"all",60);
  }
 
