inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/caravan/guild/default.h"
#define GROUPS ({"all","merchants","humans","elves","dwarves", \
      "gnomes","hobbits","goblins"})
#define REALLY_FOR ({"all","merchants","human","elf","dwarf" \
      "gnome","hobbit","goblin"})

create_armour()
{
   ::create_armour();
   set_name("_sniff_the_roses");
   add_name("necklace");
   set_adj("gold");
   add_adj("chain");
   set_short("gold chain necklace");
   set_pshort("gold chain necklaces");
   set_long("A long, beautifully-crafted gold chain necklace. It is a "+
      "symbol of your dedication to the Merchants Guild of Kabal and its "+
      "patron goddess, Ammercia, whose holy symbol this is that you carry.\n");
   set_ac(10);
   set_at(A_NECK);
   add_prop(OBJ_I_VALUE,1440);
   add_prop(OBJ_I_WEIGHT,500);
   add_prop(OBJ_I_VOLUME,500);
   add_prop(OBJ_M_NO_DROP,"You can't be rid of this unless you leave "+
      "the Merchants Guild of Kabal!\n");
}
void
enter_env(object to, object from)
{
   if(to->query_race_name() == "goblin")
      {
      to->catch_msg("Your gold chain necklace is taken away from you "+
         "because the Merchants Guild doesn't want stinking goblins in it!\n");
      remove_object();
   }
}

void
init()
{
   ::init();
   AA(mhelp1,mhelp1);
   AA(mhelp2,mhelp2);
   set_alarm(1.0,0.0,"get_me_soul",TP);
}

string
query_auto_load() { return MASTER + ":"; }

void
get_me_soul(object ob)
{
   int i;
   string *souls;
   
   seteuid(getuid());
   souls = ob->query_cmdsoul_list();
   for (i = 0; i < sizeof(souls); i++)
   ob->remove_cmdsoul(souls[i]);
   
   ob->add_cmdsoul(MERCHANT_SOUL);
   
   for(i = 0; i < sizeof(souls); i++)
   if(souls[i] != MERCHANT_SOUL)
      ob->add_cmdsoul(souls[i]);
   ob->update_hooks();
}


int
mhelp1()
{
   TP->more("/d/Kalad/common/caravan/guild/mhelp1",0,(int)TP->query_prop(PLAYER_I_MORE_LEN));
   return 1;
}
