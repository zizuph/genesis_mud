/* A powder made of ground herbs;
**
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/25/98     Zima        Created
** 2/10/98     Zima        Added incense and saltpeter support
**
*/
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "powder.h"
int      special=0;           /* is this a special powder?      */
int      *ingwts=({});        /* list of weights of ingredients */
string   *inglist=({});       /* list of ingredients            */
string*  query_ingredients() { return inglist; }
int*     query_weights()     { return ingwts; }
int      query_special()     { return special; }
 
/*
** set_ingredients - initialize ingredient list
*/
int set_ingredients(string *ing, int *wts) {
   int wt=0, i;
   if (sizeof(ing) != sizeof(wts)) return 0;
   inglist=ing;
   ingwts=wts;
   for (i=0; i<sizeof(wt); i++) wt += wts[i];
   add_prop(OBJ_I_WEIGHT,wt);
   add_prop(OBJ_I_VOLUME,(wt/7));
   return 1;
}
 
/*
** set_powder - set descriptions and special value of powder
*/
void set_powder(int dnum) {
   switch (dnum) {
      case POWDER_INCENSE1:
         set_name("incense");
         add_name(TOUR_INCENSE);
         add_prop(POUNDABLE,1);
         set_short("handful of incense");
         set_pshort("handfuls of incense");
         set_long("It is a handful of sweet-smelling aromatic incense, "+
                  "with scents of flowers and evergreens.\n");
         set_ingredients(INC1_INGRED,INC1_AMT);
         break;
      case POWDER_INCENSE2:
         set_name("incense");
         add_name(({"ashes","ash"}));
         add_name(ASHEN_INCENSE);
         add_prop(POUNDABLE,1);
         set_short("handful of ashes");
         set_pshort("handfuls of ashes");
         set_long("It is a handful of sweet-smelling wood ashes.\n");
         set_ingredients(INC2_INGRED,INC2_AMT);
         break;
      case POWDER_SALTPETER:
         set_name("saltpeter");
         set_short("pinch of saltpeter");
         set_pshort("pinches of saltpeter");
         set_long("It is a pinch of a white salty crystalline powder that "+
                  "can burn.\n");
         set_ingredients(({"saltpeter"}),({10}));
         break;
      default:
         set_name("powder");
         set_long("It is a unidentifiable ground powder with an herbal "+
                  "aroma.\n");
         set_short("ground powder");
         set_pshort("ground powders");
         dnum=POWDER_NONDESC;
   }
   special=dnum;
}
 
 
/*
** create the object
*/
void create_object() {
   add_name(GROUNDED_POWDER);
   set_adj("ground");
   set_powder(POWDER_NONDESC);
 
   add_prop(OBJ_I_VALUE,   0);
   add_prop(OBJ_M_NO_SELL, 1);
   add_prop(OBJ_I_WEIGHT,  0);
   add_prop(OBJ_I_VOLUME,  0);
}
 
/*
** check_ingredients - check given ingredients against current
*/
int check_ingredients(string *ing, int *amt) {
   int i,ndx;
   if (sizeof(inglist) != sizeof(ing)) return 0;
   for (i=0; i<sizeof(inglist); i++) {
      ndx = member_array(inglist[i],ing);
      if (ndx<0) return 0;
      if (ingwts[i] != amt[ndx]) return 0;
   }
   return 1;
}
 
/*
** convert - ATTEMPT to convert powder to a special powder; return 1=ok,0=no
*/
int convert(int pnum) {
   switch(pnum) {
      case POWDER_INCENSE1:
         if (check_ingredients(INC1_INGRED, INC1_AMT)) {
            set_powder(POWDER_INCENSE1);
            return 1;
         }
         return 0;
      default:
         return 0;
   }
}
 
/*
** mix_powder() - adds another powder to this powder, making one
*/
void mix_powder(object other) {
   string* othering=(other->query_ingredients());
   int*    otherwts=(other->query_weights());
   int i,ndx;
 
   if (!(other->id(GROUNDED_POWDER))) return;
   if ((special)&&(!(other->query_special()))) {
      other->mix_powder(this_object());
      return;
   }
 
   /* merge ingredients of other powder with this one */
   for (i=0; i<sizeof(othering); i++) {
      ndx = member_array(othering[i],inglist);
      if (ndx<0)
         {
         inglist += ({(othering[i])});
         ingwts  += ({(otherwts[i])});
         }
      else
         {
         ingwts[ndx] += otherwts[i];
         }
   }
   add_prop(OBJ_I_WEIGHT,(query_prop(OBJ_I_WEIGHT) +
                         (other->query_prop(OBJ_I_WEIGHT)) ));
   add_prop(OBJ_I_VOLUME,(query_prop(OBJ_I_VOLUME) +
                         (other->query_prop(OBJ_I_VOLUME)) ));
   other->remove_object();
   if (special) set_powder(POWDER_NONDESC); /* not anymore! */
}
 
/*
** add_ingredient() - adds an herb to the powder - invoked by pestle.
*/
void add_ingredient(object herb) {
   int    wt,vol,ndx;
   string name;
 
   /* get the name, wt and vol of this ingredient. assumed grindable */
   if (!stringp((name = (herb->query_herb_name()))))
      name = herb->query_name();
   wt  = (herb->query_prop(OBJ_I_WEIGHT));
   vol = (herb->query_prop(OBJ_I_VOLUME));
 
   /* add weight and 70% of volume of herb to the powder */
   add_prop(OBJ_I_WEIGHT,(query_prop(OBJ_I_WEIGHT) + wt));
   add_prop(OBJ_I_VOLUME,(query_prop(OBJ_I_VOLUME) + ((vol*7)/10) ));
 
   /* update the ingredient list for this object */
   ndx = member_array(name,inglist);
   if (ndx<0)
      {
      inglist += ({name});
      ingwts  += ({wt});
      }
   else
      ingwts[ndx] += wt;
 
   if (special) set_powder(POWDER_NONDESC); /* not anymore! */
}

string query_recover()
{
   int i;
   string qs=MASTER + ":";
   qs += "#sp#" + special + "#numh#" + sizeof(inglist)+"#";
 
   for (i=0; i<sizeof(inglist); i++)
      qs += ("h" + i + "#" + inglist[i] + "=" + ingwts[i] + "#");
   return qs;
}
 
public void init_recover(string arg)
{
   string d1,d2,herb;
   int numh, wt, i;
   inglist = ({});
   ingwts  = ({});
 
   sscanf(arg, "%s#sp#%d#%s",   d1, special, d2);
   sscanf(arg, "%s#numh#%d#%s", d1, numh,    d2);
 
   for (i=0; i<numh; i++)
      {
      sscanf(arg, "%s#h" + i + "#%s=%d#%s", d1, herb, wt, d2);
      inglist += ({herb});
      ingwts  += ({wt});
      }
   set_ingredients(inglist, ingwts);
   set_powder(special);
}
