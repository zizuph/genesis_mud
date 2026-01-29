/* An Elven plate - another classic from Daneel's Armoury inc. */
/* coded 26/4/93 */

#pragma save_binary

inherit "/std/armour";           /* I've looked through lots of examples. */
inherit "/lib/keep";
#include "/sys/stdproperties.h"  /* It seems all armour start with these  */
#include "/sys/wa_types.h"       /* so why should mine be different?      */
   
void
create_armour()
{
   /* Set name, short description and long description */
   set_name("brigadine");
   set_short("elven brigadine");
   set_long(break_string("On closer inspection you notice that "
         + "it is probably of elven origin, it's "
         + "made of steel. \n",70));
   
   /* Better add an adjective or two */
   set_adj("elven");
   set_adj("elf");
   
   /* Set armour class */
   set_ac(26); /* elven and steel, 23+3 */
   
   set_am(({ 3, -1, -2 }));
   set_at(A_BODY);
   
   /* Set physical attributes */
   add_prop(OBJ_I_WEIGHT, 19000);
   add_prop(OBJ_I_VOLUME,  3000);
}

string
query_recover()
{
   return "/d/Rhovanion/common/armours/plate.c"+":"+
   query_arm_recover();
}

void
init_recover(string arg)
{
   init_arm_recover(arg);
}
