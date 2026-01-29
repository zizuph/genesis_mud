/*  Sheep Shears of Argos - used to get a bundle of wool from a sheep.
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/15/95  Created
** Maniac         10/7/97  fixed lost wool problem when couldn't carry stuff
** 
**/
inherit "std/weapon";
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include "defs.h"
#define  REQ_ANI_HANDL         10
#define  UNSHEARED_SHEEP_FOUND 0
#define  NO_UNSHEARED_SHEEP    1
#define  NO_SHEEP              2
 
void 
create_weapon() 
{
    set_name("shears");
    set_adj(({"brass","sheep"}));
    set_short("pair of brass sheep shears");
    set_pshort("pairs of brass sheep shears");
    set_long("It is a pair of brass sheep shears, two sharp blades "+
             "hinged together near one end with handles. The brasswork "+
             "on these is high quality, something any shepherd "+
             "would be proud to own.\n");
 
    set_hit(10);
    set_pen(5);
 
    set_hands(W_NONE);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);

    add_prop("mystic_weapon",1);
    add_prop(OBJ_I_WEIGHT,  800);
    add_prop(OBJ_I_VOLUME,  500);
}


/* Value must be lower than its sale price. 
   /std/weapon won't let one change the value 
   property in create_weapon() at the time of writing */ 
int
query_value()
{
    return 1;
}


 
int shear(string Parms) {
   object Tp=this_player();
   object Tr=environment(Tp);
   object To=this_object();
   object *TrInv;
   object sheep,wool;
   string *Parm;
   int    i,rc,InvSize;
 
   /* must wield shears to use them */
   if (!(To->query_wielded()))
      { write("You must first wield the shears to use them.\n"); return 1; }
 
   /* check syntax: shear sheep with shears */
   if (!(Parms)) { write("Shear what with what?\n"); return 1; }
   Parm=explode(Parms," ");
 
   if (Parm[0]!="sheep")
      { write("You may only shear sheep with the shears.\n"); return 1; }
 
   if (sizeof(Parm)<3) { write("Shear sheep with what?\n"); return 1;}
   if (!((Parm[1]=="with")&&(Parm[2]=="shears")))
      { write("Shear sheep with what?\n"); return 1; }

   /* see if any unsheared sheep around in this room */
   TrInv=all_inventory(Tr);
   InvSize=sizeof(TrInv);
   rc=NO_SHEEP; i=0;
   while ((i<InvSize)&&(rc!=UNSHEARED_SHEEP_FOUND)) {
      if (TrInv[i]->id("sheep")) {
         if (TrInv[i]->query_prop(SHEEP_SHEARED))
            rc=NO_UNSHEARED_SHEEP;
         else {
            rc=UNSHEARED_SHEEP_FOUND;
            sheep=TrInv[i];
         }
      }
      i++;
   }
 
   switch (rc) {
      case NO_SHEEP:
         write("But there are no sheep here!\n");
         return 1;
         break;
      case NO_UNSHEARED_SHEEP:
         write("All the sheep here have already been sheared.\n");
         return 1;
         break;
      case UNSHEARED_SHEEP_FOUND:
         if (!(objectp(sheep))) {
            write("The shears seem to be broken.\n");
            return 1;
         }
         break;
      default:
         break;
   }
 
   if ((Tp->query_skill(SS_ANI_HANDL)) < REQ_ANI_HANDL) {
      Tp->catch_msg("You try to get a hold on "+QTNAME(sheep)+
                    " but it slips away from you!\n");
      tell_room(Tr,QCTNAME(Tp)+" tries to catch "+QTNAME(sheep)+
                "but it slips away!\n",Tp);
      sheep->run_away();
      return 1;
   }

   Tp->catch_msg("You deftly shear "+QTNAME(sheep)+" with the shears, "+
                 "obtaining a bale of wool.\n");
   tell_room(Tr,QCTNAME(Tp)+" shears "+QTNAME(sheep)+" with a pair of "+
             "shears.\n",Tp);
    seteuid(getuid());
   wool=clone_object(OBJ_DIR+"wool_bale");
   if (wool->move(Tp)) 
       wool->move(environment(Tp)); 
   sheep->add_prop(SHEEP_SHEARED,1);
   return 1;
}

void init() {
   ::init();
   add_action("shear","shear");
}
