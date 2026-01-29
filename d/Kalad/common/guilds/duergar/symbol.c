inherit "/std/object";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/duergar/default.h"
#define GROUPS ({"all","humans","elves","dwarves", \
      "gnomes","hobbits","goblins"})
#define REALLY_FOR ({"all","human","elf","dwarf" \
      "gnome","hobbit","goblin"})

create_object()
{
   ::create_object();
   set_name("_sniff_the_duergar");
   add_name("token");
   set_adj("golden");
   add_adj("metal");
   set_short("golden metal token");
   set_pshort("golden metal tokens");
   set_long("A stamped piece of golden metal that shows your connection "+
      "to the Duergar-clan of Underhome. You see some blood-red runes "+
      "circling the edge of the stamp.\n");
   add_item(({"runes","stamp"}),"The stamp has some runes that you dechiper to "+
      "mean this: Try 'dhelp' to learn more.\n");
   add_prop(OBJ_I_VALUE,400);
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,100);
   add_prop(OBJ_M_NO_DROP,"You cannot be rid of this unless you leave "+
      "the Duergar-Clan!\n");
   add_prop(OBJ_M_NO_SELL,1);
   message();
}
void
message()
{
   write("The world is yours to loot and ransack, mighty Duergar!\n");
   return;
}
void
enter_env(object to, object from)
{
   if(TO->query_race_name() != "dwarf")
      {
      TO->catch_msg("Your token suddenly melts in your hand! Only "+
         "dwarves may carry this, and you are not a dwarf!\n");
      TO->remove_guild_race();
      TO->clear_bit(4,6);
      TO->clear_guild_stat(SS_RACE);
      TO->update_hooks();
      remove_object();
   }
}

void
init()
{
   ::init();
   AA(dhelp,dhelp);
   AA(dlanguage,dlanguage);
   AA(dhistory,dhistory);
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

   ob->add_cmdsoul(DUERGAR_SOUL);

   for(i = 0; i < sizeof(souls); i++)
   if(souls[i] != DUERGAR_SOUL)
      ob->add_cmdsoul(souls[i]);
      ob->add_cmdsoul(souls[i]);
   ob->update_hooks();
}

int
dhelp()
{
   TP->more("/d/Kalad/open/GUILD/DUERGAR_INFO/dhelp",0,(int)TP->query_prop(PLAYER_I_MORE_LEN));
   return 1;
}

int
dlanguage()
{
   TP->more("/d/Kalad/open/GUILD/DUERGAR_INFO/dlanguage",0,(int)TP->query_prop(PLAYER_I_MORE_LEN));
   return 1;
}

int
dhistory()
{
   TP->more("/d/Kalad/open/GUILD/DUERGAR_INFO/dhistory",0,(int)TP->query_prop(PLAYER_I_MORE_LEN));
   return 1;
}
