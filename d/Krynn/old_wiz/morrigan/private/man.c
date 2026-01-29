inherit "/std/creature";
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"

int soul_id;
void get_me_soul();
object query_mistress();
void set_mistress(object who);
void set_gen(string which);
int query_gender();
void configure();
object mistress;
int gender;

void
set_gen(string which)
{
   gender = (which == "female" ? 1 : 0);
   configure();
}

int
query_gender()
{
   return gender;
}

void
configure()
{
   
   if (query_gender() == 1)
      {
      switch(random(9))
      {
         case 0:
         set_name("lily");
         set_adj(({"charming", "mysterious"}));
         break;
         case 1:
         set_name("vivian");
         set_adj(({"slender", "dark-haired"}));
         break;
         case 2:
         set_name("olivia");
         set_adj(({"voluptuous", "green-eyed"}));
         break;
         case 3:
         set_name("carol");
         set_adj(({"dark-haired", "green-eyed"}));
         break;
         case 4:
         set_name("tiffany");
         set_adj(({"sexy", "green-eyed"}));
         break;
         case 5:
         set_name("sarah");
         set_adj(({"sensuous", "charming"}));
         break;
         case 6:
         set_name("melissa");
         set_adj(({"slender", "erotic"}));
         break;
         case 7:
         set_name("laura");
         set_adj(({"beautiful", "dark-haired"}));
         break;
         case 8:
         set_name("terry");
         set_adj(({"shy", "seductive"}));
         break;
         case 9:
         set_name("christine");
         set_name(({"playful", "sexy"}));
         break;
       }
   }
   
   if (query_gender() == 0)
      {
      switch(random(9))
      {
         case 0:
         set_name("dalizen");
         set_adj(({"charming", "mysterious"}));
         break;
         case 1:
         set_name("hans");
         set_adj(({"tall", "muscular"}));
         break;
         case 2:
         set_name("richard");
         set_adj(({"mysterious", "dark-haired"}));
         break;
         case 3:
         set_name("daniel");
         set_adj(({"sexy", "blue-eyed"}));
         break;
         case 4:
         set_name("kevin");
         set_adj(({"handsome", "dark-skinned"}));
         break;
         case 5:
         set_name("frederick");
         set_adj(({"smiling", "blue-eyed"}));
         break;
         case 6:
         set_name("tim");
         set_adj(({"charming", "handsome"}));
         break;
         case 7:
         set_name("steve");
         set_adj(({"dark-haired", "blue-eyed"}));
         break;
         case 8:
         set_name("jeff");
         set_adj(({"tall", "handsome"}));
         break;
         case 9:
         set_name("tom");
         set_adj(({"charming", "blue-eyed"}));
         break;
       }
   }
   
   set_title(query_gender() == 1 ? "the Love Slave of "+query_mistress()->query_name() :
      "the Manservant of "+query_mistress()->query_name());
   set_gender(query_gender());
   set_appearance(1500);
   if (query_gender() == 0)
      {
      set_long("This tall and muscular man draws the attention of everyone in "+
         "the room, men and women alike. His defined cheekbones and lush lips "+
         "provide him with a smile that makes your knees weak. His deep blue "+
         "eyes gleam in contrast to his dark skin and hair, which falls down "+
         "around his shoulders in shimmering dark locks. His chest is broad and "+
         "muscular, and quite exposed as all he is wearing is a small black "+
         "loincloth. His eyes see only his "+query_mistress()->query_name()+
         ", all others are of no concern to him whatsoever.\n");
   }
   else if (query_gender() == 1)
      {
      set_long("This slender woman moves with such sensuous grace that those "+
         "around her stop and stare with open mouths. Her long dark hair "+
         "flows in waves down her back, and playful emerald green eyes look "+
         "at you with a provocative mix of innocence and naughtiness. Scantily-"+
         "clad in emerald coloured lingerie, her curves are quite noticeable, "+
         "and certainly appreciated as she moves. Her affection is only for "+
         query_mistress()->query_name()+", others hold no interest to her.\n");
   }
}

void
set_mistress(object who)
{
   mistress = who;
   configure();
}

object
query_mistress()
{
   return mistress;
}

create_creature()
{
   soul_id = set_alarm(0.1, 0.0, &get_me_soul());
   configure();
}

void
get_me_soul()
{
   TO->add_cmdsoul("/d/Krynn/morrigan/private/servant_soul");
   TO->update_hooks();
   remove_alarm(soul_id);
}
void
intro()
{
   TO->command("introduce me");
   TO->command("say At your service, "+(query_mistress()->query_gender() == 0 ?
         "Master" : "Mistress")+" "+query_mistress()->query_name()+".");
   TO->command("emote kneels at the feet of "+query_mistress()->query_the_name(TP)+".");
}


int
please(object who)
{
   string name = query_mistress()->query_real_name();
   switch(random(13) + 1)
   {
      case 1:
      TO->command("e1 "+name);
      break;
      case 2:
      TO->command("e2 "+name);
      break;
      case 3:
      TO->command("e3 "+name);
      break;
      case 4:
      TO->command("e4 "+name);
      break;
      case 5:
      TO->command("e5 "+name);
      break;
      case 6:
      TO->command("e6 "+name);
      break;
      case 7:
      TO->command("e7 "+name);
      break;
      case 8:
      TO->command("e8 "+name);
      break;
      case 9:
      TO->command("e9 "+name);
      break;
      case 10:
      TO->command("e10 "+name);
      break;
      case 11:
      TO->command("e11 "+name);
      break;
      case 12:
      TO->command("e12 "+name);
      break;
      default:
      TO->command("e13 "+name);
      break;
   }
   
   return 1;
}
