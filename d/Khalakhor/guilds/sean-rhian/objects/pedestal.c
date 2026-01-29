/* Marble pedestal fround in kirks
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 3/7/98      Zima        Created
**
*/
inherit "/std/container";
#include <stdproperties.h>
#include "defs.h"
 
void ped_config(string* parm) {
   //parms = ({material,adj,object_is_beneath,which_wall,how_formed,solsheyder}) 
   // ex:     ({"wood","wooden","window","south","carved",SR_MAIGHAL})
   if (sizeof(parm)==6) add_name(parm[5]+SR_PEDESTAL);   
   add_adj(({"ornate",parm[1]}));
   set_short("ornate "+parm[1]+" pedestal");
   add_adj(parm[3]);
   set_long(
      "It is an ornate "+parm[1]+" pedestal, about waist high to a human, "+
      "standing beneath the "+parm[2]+" along the "+parm[3]+" wall. It is "+
      "made of a cylinder of "+parm[0]+" "+parm[4]+" with deep vertical "+
      "grooves with a square top and foot. The top is "+parm[4]+" with "+
      "three interlocked circles.\n");
}
 
void create_container() {
    set_name("pedestal");
    add_name(SR_PEDESTAL);
    set_short("pedestal");
    set_long(
       "It is a simple pedestal. You can put things on it.\n");
 
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_MAX_WEIGHT, 10000);
    add_prop(CONT_I_MAX_VOLUME, 100000);
    add_prop(OBJ_I_VOLUME,10000);
    add_prop(OBJ_I_WEIGHT,15000);
}
