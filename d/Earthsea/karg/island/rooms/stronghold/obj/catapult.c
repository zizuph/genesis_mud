inherit "/std/object";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

#include "defs.h"
#include "/d/Earthsea/quest_handler/quest_handler.h"

int cat_id;

void create_object()
{
 set_name("catapult");
 set_adj("large");
 add_adj("war");
 set_long("This is an experimental model of karg catapult. It is "+
   "designed to throw large stones towards target , crushing it "+
   "into pieces.\n");

 add_prop(OBJ_I_WEIGHT,500000);
 add_prop(OBJ_I_VOLUME,500000);
}

void init()
{
 ::init();

 add_action("destroy","destroy");
}

void put_pile()
{
 setuid();
 seteuid(getuid());

 clone_object(STRHOLD_OBJ+"pile")->move(ENV(TO));
 remove_object();
}

int destroy(string what)
{
 object *weapons,*d_wep=({});
 int i;
 string d_wep_string;
 int prop;

 NF("Destroy what??\n");
 if(!what) return 0;
 if(what!="catapult") return 0;

 NF("No no no! Kargs will get mad and kill you!!\n");
 if(QH_QUERY_QUEST_COMPLETED(TP,"karg_catapult")) return 0;
 if(!TP->query_prop("_asked_vorn_for_quest")) return 0;
 prop=TP->query_prop("_catapults_destroyed");
 if((prop|cat_id)==prop) return 0;

 NF("You don't have any weapon wielded to do that.\n");
 weapons=TP->query_weapon(-1);
 if(!sizeof(weapons)) return 0;

 NF("Destroy a catapult with a knife??? You gotta be kidding!\n");
 for(i=0;i<sizeof(weapons);i++)
   if(weapons[i]->query_wt()!=W_KNIFE) d_wep+=({weapons[i]});
 if(!sizeof(d_wep)) return 0;

 d_wep_string=d_wep[0]->short();
 if(sizeof(d_wep)>1) d_wep_string+=" and "+d_wep[1]->short();
 
 write("You start crushing "+TO->short()+" with your "+d_wep_string+
   " and in a seconds only pile of wood left on the ground.\n");
 say(QCTNAME(TP)+" starts crushing "+TO->short()+" with "+POS(TP)+" "+
   d_wep_string+" and in a seconds only pile of wood left on the "+
   "ground.\n");

 TP->add_prop("_catapults_destroyed",prop|cat_id);
 set_alarm(0.5,0.0,&put_pile()); 

 return 1;
}

void set_cat_id(int idd) {cat_id=idd;}
int query_cat_id() {return cat_id;}

