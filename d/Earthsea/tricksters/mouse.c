inherit "/std/object";

#include "defs.h"

#include <macros.h>
#include <cmdparse.h>

void create_object()
{
 set_name("mouse");
 set_adj("big");
 add_adj("hairy");
 set_long("This is big hairy mouse. You can try to scare people "+
   "with it.\n");
}

void init()
{
 ::init();
 add_action("scare","scare");
}

int is_living(object ob)
{
 if(!living(ob) || ob==TP) return 0;
 return 1;
}

int scare(string who)
{
 object *obj,pl;

 NF("Scare who?\n");
 if(!who) return 0;

 obj=CMDPARSE_ONE_ITEM(who,"is_living","is_living");
 if(!sizeof(obj)) return 0;

 NF("You can scare only one person.\n");
 if(sizeof(obj)>1) return 0;

 pl=obj[0];
 if(pl->query_name()=="Ged")
  {
   write("You try to show "+short()+" to "+QtN(pl,TP)+" but "+PRO(pl)+
     " screams at you waving "+POS(pl)+" hands.\n");
   say(QCTNAME(TP)+" tries to show "+short()+" to "+QTNAME(pl)+" but "+
     QTNAME(pl)+" waves "+POS(pl)+" hands at "+OBJ(TP)+" screaming "+
     "loudly!\n");
   TP->command("jump stupid");
   TP->command("panic");
  }
 else
  {
   write("You show "+short()+" to "+pl->query_the_name(TP)+" and go "+
     "BOO!\n");
   say(QCTNAME(TP)+" shows "+short()+" to "+QTNAME(pl)+" and "+
     "goes BOO!\n",({TP,pl}));
   pl->catch_msg(QCTNAME(TP)+" shows "+short()+" to you and goes BOO!\n");
   pl->command("panic");
  }
 return 1;
}

