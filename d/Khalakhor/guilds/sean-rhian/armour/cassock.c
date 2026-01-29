/* A black cassock, vestment of a Searmanagh
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           6/22/98  Created
** Damaris        02/01    Updated the description
**/
inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
 
void create_armour()
{
    set_name("cassock");
    set_adj("black");
    set_short("black cassock");
    set_long("It is a long black cassock. I is a snug fitting full length "+
      "robe that buttons down the front with medium sized black buttions. "+
      "It is full length and the sleaves are snug fitting as well.\n");
    set_ac(5);
    set_at(TS_ROBE);
}
