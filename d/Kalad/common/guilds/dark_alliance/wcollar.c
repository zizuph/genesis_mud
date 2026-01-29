inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* 
 * /d/Kalad/common/wild/pass/goblin/guild/riders/wcollar.c
 * Purpose    : collar for the warwolves
 * Located    : bought in Rider warstables
 * Created By : mhyrkhaan 2-20-97
 * Modified By: 
 */ 

string Gowner;
string Gtype;

void set_wolfname(string str)
{
    Gowner = str;
}
void set_type(string str)
{
    Gtype = str;
}

string query_wolfname()
{
    return Gowner;
}

string query_type()
{
    return Gtype;
}


void
create_armour()
{
   ::create_armour();
   set_name("collar");
   add_adj("leather");
   add_adj("black");
   set_short("black @@query_type@@ leather collar with a tag that "+
   "reads '@@query_wolfname@@'");
   set_long("This collar is made of black leather studded with studs.\n");
   set_at(A_NECK);
   set_ac(10);
   add_prop(OBJ_M_NO_SELL,1);
   add_prop(OBJ_I_WEIGHT,400);
   add_prop(OBJ_I_VOLUME,500);
   add_prop(OBJ_I_VALUE,0);
}
