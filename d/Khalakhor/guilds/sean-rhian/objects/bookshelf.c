//
// A book shelf
//
// Zima  June 25, 98
//
#pragma strict_types
inherit "/std/container";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include "defs.h"
 
void add_book(string path)
{
   seteuid(getuid());
   (clone_object(path))->move(TO);
}
 
void add_books(string* path)
{
   int i;
   for (i=0; i<sizeof(path); i++)
      add_book(path[i]);
}
 
void create_container()
{
    set_name("bookshelf");
    add_name("shelf");
    set_adj(({"oak","tall"}));
    set_short("tall oak bookshelf");
    set_long("It is tall oak bookshelf ornately carved and stained "+
        "by excellent craftsmen. It is waxed and polished, the light "+
        "reflecting off its smooth surfaces.\n");
    add_cmd_item(({"books","titles"}),({"examine","read"}),"@@read_titles");
 
    add_prop(CONT_I_WEIGHT,     100000);
    add_prop(CONT_I_MAX_WEIGHT, 200000);
    add_prop(CONT_I_VOLUME,     200000);
    add_prop(CONT_I_MAX_VOLUME, 400000);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     1);
    add_prop(CONT_I_ATTACH,     1);
    add_prop(OBJ_M_NO_GET,     "The bookshelf is far to heavy and bulky " +
                               "for you to move.\n");
    add_prop(OBJ_I_VALUE, 1000);
}
 
string read_titles()
{
   object* ob = all_inventory(TO);
   string  d  = "The titles you can read are: \n", title;
   int     i, nt=0;
 
   for (i=0; i<sizeof(ob); i++)
      {
      title = (ob[i]->query_srbook_title());
      if (strlen(title)>2)
         {
         d += "   "+title+"\n";
         nt++;
         }
      }
   if (nt==0)
      return "There are no titled books on the "+short()+".\n";
   else
      return d;
}
