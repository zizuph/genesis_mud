/* A pestle; grinds herbs and other specific objects in a mortar into powder
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/25/98     Zima        Created
** 8/5/00      Rhyn        Changed description to keep people from whining
**                         since they can't get 'help pestle' without
**                         taking it from the workbench.
**
*/
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include "defs.h"
#include "powder.h"
#define  GRIND_SKILL        20
#define  DROP_MORTAR_SKILL  15
#define  DROP_ALL_SKILL     10
 
string my_extra_long() {
    if(environment() == this_player()) {
      return "You can learn more with 'help pestle'.\n";
    }
    return "Perhaps you should pick it up and examine it more carefully.\n";
}

void create_object() {
    set_name("pestle");
    set_adj(({"ceramic","white"}));
    set_short("ceramic pestle");
    set_long("It is a ceramic white pestle, a short smooth tool with a bulb on " +
        "the end, used to grind herbs and powders in a mortar. @@my_extra_long@@");
 
    add_prop(OBJ_I_VALUE,   320);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_WEIGHT,  1000);
    add_prop(OBJ_I_VOLUME,  260);
}
 
/*
** skilled - is player skilled enough? if not, is clumsy
*/
int skilled(object tp, object mortar, object *minv) {
   int    skill  = (tp->query_skill(SS_ALCHEMY)), i;
   object room   = ENV(tp);
   string mshort = (mortar->query_short()), pshort=(query_short()), adv;
 
   if (skill>=GRIND_SKILL) return 1;
 
   if (skill<=DROP_ALL_SKILL)         adv="ignorantly";
   else if (skill<=DROP_MORTAR_SKILL) adv="clumsily";
   else                               adv="ineptly";
 
   /* fumble and spill the contents */
   write("You "+adv+" attempt to grind with the "+mshort+" and the "+ pshort+
         "...\nYour fingers slip!\n"+
         "You spill the contents of the "+mshort+"!\n");
   tell_room(room,QCTNAME(tp)+" "+adv+" attempts to grind with a "+
         mshort+" and a "+pshort+"...\n"+
         QCTNAME(tp)+" spills the contents of the "+mshort+"!\n",tp);
   for (i=0; i<sizeof(minv); i++)
      (minv[i])->move(room,1);
 
   /* might drop the mortar */
   if ((skill<=DROP_MORTAR_SKILL)&&(skill>DROP_ALL_SKILL)) {
      mortar->move(room,1);
      write("You drop the "+mshort+" and it hits the ground with a clatter!\n");
      tell_room(room,QCTNAME(tp)+" drops the "+mshort+" and it hits the "+
         "ground with a clatter.\n!",tp);
   }
 
   /* might drop mortar and pestle! */
   else if (skill<=DROP_ALL_SKILL) {
      mortar->move(room,1);
      this_object()->move(room,1);
      write("You drop the "+mshort+" and the "+pshort+" and they hit the "+
         "ground with a clatter!\n");
      tell_room(room,QCTNAME(tp)+" drops the "+mshort+" and the "+pshort+
         "and they hit the ground with a clatter.\n!",tp);
   }
   return 0;
}
 
/*
** grindable() - is this object grindable?
*/
int grindable(object ob) {
   if (ob->query_herb_name()) return 1; /* all herbs are grindable */
   if (ob->query_prop(GRINDABLE)) return 1;
   return 0;
}
 
/*
** grind() - allows player to grind things with the mortar and pestle
*/
int grind(string cmd) {
   object obj, powder, powder2;
   object mortar=present("mortar",TP);
   object *minv;
   int    newpowder=0, OK=0, i;
   string objshort,mshort,mart;
 
   /* did the player give any args to the command? */
   if (!stringp(cmd)) {
      write("Grind what into powder with pestle?\n");
      return 1;
   }
 
   /* does the player have a mortar? */
   if (!objectp(mortar)) {
      write("You do not have a mortar.\n");
      return 1;
   }
 
   /* is this "mortar" a container? ensure I can call subinventory() */
   if (!(mortar->query_prop(CONT_I_WEIGHT))) {
      write("You do not have a proper mortar.\n");
      return 1;
   }
   minv   = (mortar->subinventory());
   mshort = (mortar->query_short());
 
   /* check syntax for "grind <herb> into powder", for <herb> in mortar */
   OK=parse_command(cmd,minv,"%o 'into' [the] 'powder' 'with' 'pestle'", obj);
   if (OK) {
      if (!skilled(TP,mortar,minv)) return 1;
 
      /* check if object specified is grindable */
      objshort = (obj->query_short());
      if (!grindable(obj)) {
         write("The "+objshort+" can not be ground into powder.\n");
         return 1;
      }
 
      /* make sure powder object is here */
      powder=present(GROUNDED_POWDER,mortar);
      if (!objectp(powder))
         {
         /* clone the powder object into the mortar */
         reset_euid();
         powder=clone_object(SR_OBJ+"powder");
         powder->move(mortar,1);
         mart="the ";
         }
      else
         mart="";
 
      /* add the ingredient to the powder and inform all of what happened */
      powder->add_ingredient(obj);
      obj->remove_object();
      write("You grind the "+objshort+" into "+mart+"powder with the "+
            "pestle.\n");
      tell_room(environment(TP),QCTNAME(TP)+" grinds something into powder "+
                   "with a mortar and pestle.\n",TP);
      return 1;
   } /* end if "grind <herb> into powder with pestle" */
 
   /* check syntax for "grind powders together" */
   OK=
   parse_command(cmd,minv,"'powders' / 'powder' 'together' 'with' 'pestle'");
   if (OK) {
      if (!skilled(TP,mortar,minv)) return 1;
 
      /* find two powders */
      i=0;
      while ((i<sizeof(minv))&&(!objectp(powder2))) {
         if ((minv[i])->id(GROUNDED_POWDER)) {
            if (objectp(powder))
               powder2 = minv[i];
            else
               powder = minv[i];
         }
         i++;
      }
      if (!objectp(powder2)) {
         write("There must be two powders in the mortar!\n");
         return 1;
      }
 
      /* mix the powder into powder2 and report what happened */
      powder2->mix_powder(powder);
      write("You grind the two powders together with the pestle.\n");
      tell_room(environment(TP),QCTNAME(TP)+" grinds something into powder "+
                "with a mortar and pestle.\n",TP);
      return 1;
   }
 
   /* otherwise, there must by a syntax error in the command */
   write("Grind what into powder with pestle?\n");
   return 1;
}
 
/*
** pound() - allows player to pound some powders into a cake
*/
int pound(string cmd)
{
   object obj, cake, mortar=present("mortar",TP);
   object *minv;
   string objshort,mshort;
 
   /* check out the mortar for later use */
   if (objectp(mortar))
      {
      mshort=(mortar->query_short());
      if (mortar->query_prop(CONT_I_WEIGHT))
         minv=(mortar->subinventory());
      }
 
   /* check that a correct command was entered */
   if ((!stringp(cmd))||(!parse_command(cmd,minv,"%o 'into' [a] 'cake' "+
      "'with' [the] 'pestle'",obj)))
      {
      notify_fail("Pound what into a cake with pestle?\n");
      return 0;
      }
   objshort=(obj->query_short());
   if (!stringp(objshort)) objshort=(obj->query_name());
 
   if (!objectp(mortar))
      write("You do not have a mortar.\n");
   else if (sizeof(minv)==0)
      write("There is nothing in the "+mshort+".\n");
   else if (sizeof(minv)!=1)
      write("There should only be one powder in the "+mshort+".\n");
   else if (!(obj->id(GROUNDED_POWDER)))
      write("The "+objshort+" is not a ground powder.\n");
   else if (!(obj->query_prop(POUNDABLE)))
      write("The "+objshort+" is not a powder that can be pounded into a "+
            "cake.\n");
   else
      {
      seteuid(getuid());
      switch((obj->query_special()))
         {
         case POWDER_INCENSE1:
            cake=clone_object(SR_OBJ+"cake_incense");
            cake->set_type(SR_INC_TOUR);
            break;
         case POWDER_INCENSE2:
            cake=clone_object(SR_OBJ+"cake_incense"); 
            cake->set_type(SR_INC_ASHEN);
            break;
         default:
            write("There is a bug in pestle::pound switch special!\n");
            return 1;
         }
      obj->remove_object();
      cake->move(mortar);
      write("You pound the "+objshort+" in the "+mshort+" into a cake "+
            "with the pestle.\n");
      tell_room(ENV(TP),"Pounds something in "+LANG_ART(mortar)+" "+mshort+
               "into a cake with a pestle.\n",TP);
      }
   return 1;
}

/*
** help on pestle
*/
int help(string cmd)
{
   if (!stringp(cmd)) return 0;
   if ((cmd!="pestle")&&(cmd!="grind")&&(cmd!="pound")) return 0;
   write(
      "Help on using the pestle: \n"+
      "  'grind <herb> into powder with pestle' \n"+
      "    - grinds a single herb into a powder \n"+
      "    - herb added to any powder already present in mortar \n"+
      "  'grind powders together with pestle'   \n"+
      "    - combines ingredients of 2 powders into one         \n"+
      "  'pound powder into cake with pestle'   \n"+
      "    - pounds some powders into a cake    \n"+
      "Note: all herbs/powders must be in a mortar to grind/pound\n");
   return 1;
}

public void init() {
   ::init();
   add_action(&grind(),"grind");
   add_action(&pound(),"pound");
   add_action(&help(),"help");
}
