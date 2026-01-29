inherit "/std/object";
#include "/d/Shire/common/defs.h" 
#include <stdproperties.h>
#include <ss_types.h>

void urges();
int defeat_me(object player);

int alarm_id;

#define MININT 40 + random(40)
#define MINWIS 50 + random(50)
#define MINDIS 35 + random(35)

void
create_object()
{
  set_name("jewel");
   add_name("_annuminas_jewel_");
  set_short("blue-black jewel");
  set_adj("blue");
  add_adj("black");
  add_adj("blue-black");
  set_long("@@my_long@@");

  add_prop(OBJ_I_WEIGHT,3500-random(501));
  add_prop(OBJ_I_VOLUME,1500-random(251));
  add_prop(OBJ_I_VALUE,1500+random(93));
}

string
my_long()
{

   write("This blue-black jewel is dark and sinister-looking.  A shimmer "+
   "of blue light crosses over its surface from time to time, almost like a "+
   "lightning strike.\n");

   alarm_id = set_alarm(1.0,60.0,"urges",TP);

   TP->catch_msg("As you look at the blue-black jewel, it looks into you as well.\n");

   return "";