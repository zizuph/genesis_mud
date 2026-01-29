inherit "/std/shadow";

#include "../defs.h"

#define SW shadow_who

string *races;

string get_random_hex()
{
 int hex;

 hex=random(9);
 switch(hex)
  {
   case 0: return "has a sign on "+POS(SW)+" back saying, "+
             "\"KICK ME!!\"";
   case 1: return "has yellowish-green polka-dots in "+POS(SW)+
             " purple hair";
   case 2: return "has an upside-down nose on "+POS(SW)+" chin";
   case 3: return "has toilet paper stuck to "+POS(SW)+" shoe";
   case 4: return "is missing "+POS(SW)+" right eyebrow";
   case 5: return "looks more like a "+races[random(sizeof(races))]+
             " than a "+SW->query_race_name();
   case 6: return "is picking "+POS(SW)+" nose";
   case 7: return "is on "+POS(SW)+" knees worshipping Nob Nar";
   case 8: return "has a HUGE wart on the end of "+POS(SW)+
             " extremely looonnnggg nose";
   case 9: return "is walking on "+POS(SW)+" elbows";
  }
}

public varargs string short(object for_obj)
{
 return SW->short(for_obj)+" "+get_random_hex();
}

void unhex()
{
 remove_shadow();
}

void start_hex(object hexer)
{
 races=({"human","goblin","elf","dwarf","gnome","hobbit"})-
   ({SW->query_race()});
 set_alarm(itof(hexer->query_trickster_level()*30),0.0,&unhex());
}

int query_hexed() {return 1;}

