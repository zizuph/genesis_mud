/* MClub - cabinet to hold the vestments of the club (7/25/95) */
/* Found in the sacristry (rooms/shconsac)                     */
inherit "/std/receptacle";
#include <macros.h>
#include "defs.h"
#include "/sys/stdproperties.h";
#define NUM_ROBES   7
#define NUM_MANTLES 2
#define NUM_INCENSE 5
#define NUM_ALBS    1
 
void load_cabinet_item(string PathName, int Num, object TObj) {
   int i;
   object *CObj=allocate(Num);
   for (i=0; i<Num; i++) {
      CObj[i]=clone_object(PathName);
      CObj[i]->move(TObj);
   }
}
 
void load_cabinet(object TObj) {
   TObj->add_prop(CONT_I_CLOSED,0); /* open cabinet to load */
   load_cabinet_item((ARMOUR_DIR+"robe"),  NUM_ROBES,  TObj);
   load_cabinet_item((ARMOUR_DIR+"mantle"),NUM_MANTLES,TObj);
   load_cabinet_item((ARMOUR_DIR+"alb"),   NUM_ALBS,   TObj);
   load_cabinet_item((OBJ_DIR+"initome"),  1,          TObj);
   load_cabinet_item((OBJ_DIR+"incense"),  NUM_INCENSE,TObj);
   TObj->add_prop(CONT_I_CLOSED,1); /* close after loaded */
}
 
void create_receptacle()
{
    set_name("cabinet");
    set_adj("antique");
    add_adj("rosewood");
    set_long(
       "It is a tall rosewood cabinet, its face bordered with the "+
       "images of winged spirits. It looks very old but recently "+
       "refinished.\n");
 
    add_prop(CONT_I_WEIGHT,      50000);
    add_prop(CONT_I_MAX_WEIGHT, 300000);
    add_prop(CONT_I_VOLUME,      40000);
    add_prop(CONT_I_MAX_VOLUME, 200000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_CLOSED, 0); /* leave open so can load items */
    add_prop(OBJ_I_NO_GET,1);
    set_alarmv(1.0,0.0,"load_cabinet",({(this_object())}));
}
 
