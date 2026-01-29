/*	Created by: 	??? (probably Anthanaros)
 *	Purpose:	Thanar guild item
 *	Modified by:	Toby, 971007 (corrected tranks) 
 */


inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include <thanardefs.h>

#define GROUPS ({"all","thanarians","humans","elves","dwarves", \
      "gnomes","hobbits","goblins"})
#define REALLY_FOR ({"all","thanarians","human","elf","dwarf" \
      "gnome","hobbit","goblin"})

query_auto_load()
{
   return MASTER;
}

query_recover()
{
    return 0;
}

void
create_armour()
{
   ::create_armour();
   set_name("_sniff_my_licker");
   add_name("necklace");
   set_adj("platinum");
   add_adj("chain");
   set_short("platinum chain necklace");
   set_pshort("platinum chain necklaces");
   set_long("A long, beautifully-crafted platinum chain necklace. It is a "+
      "symbol of your servitude to the beliefs and purpose of the Thanarians "+
      "and the patron god of humanity, Thanar.\n"+
      "A symbol of a dark sun hangs from its end.\n"+
      "Engraved on the symbol are the following words:\n"+
      "Type 'tinfo' to see what commands are available to you.\n");
   set_at(A_NECK);
   set_ac(1);
   add_prop(OBJ_I_VALUE,5000);
   add_prop(OBJ_I_WEIGHT,500);
   add_prop(OBJ_I_VOLUME,500);
   add_prop(OBJ_M_NO_DROP,"You can't be rid of this unless you leave "+
      "the Thanarians!\n");
}

#define MOVE_LOG_FILE "/d/Kalad/common/guilds/thanar/move_log"
#define MOVE_LOG(x) write_file(MOVE_LOG_FILE, ctime(time()) + " " + (x))

void
enter_env(object to, object from)
{
    string race = to->query_race_name();

    // added by Valen as part of guild moving code
    if(member_array("/d/Kalad/common/guilds/thanar/thanar_shadow:0",
       to->query_autoshadow_list()) == -1)
    {
      // the player is no longer member of old Kalad guild
      setuid();
      seteuid(getuid());
      
      MOVE_LOG("Old guild object removed from " +
          capitalize(to->query_real_name()) + "\n");
      remove_object();
    }

    if(race != "human" && race != "god" && !to->query_wiz_rank())
      {
      to->catch_msg("Your platinum chain necklace is taken away from you "+
         "because the Thanarians don't allow savage demihumans in it!\n");
      to->remove_guild_race();
      to->clear_bit(4,4);
      to->clear_guild_stat(SS_RACE);
      to->update_hooks();
      remove_object();
   }
   set_alarm(2.0,0.0,"wearneck",to);
}

void
wearneck(object ob)
{
    ob->command("wear necklace");
}    

void
init()
{
   ::init();
   AA(tinfo,tinfo);
   AA(tranks,tranks);
   set_alarm(1.0,0.0,"get_me_soul",TP);
}
void
get_me_soul(object ob)
{
   int i;
   string *souls;
   
   seteuid(getuid());
   souls = ob->query_cmdsoul_list();
   for (i = 0; i < sizeof(souls); i++)
   ob->remove_cmdsoul(souls[i]);
   
   ob->add_cmdsoul(THANAR_SOUL);
   
   for(i = 0; i < sizeof(souls); i++)
   if(souls[i] != THANAR_SOUL)
      ob->add_cmdsoul(souls[i]);
   ob->update_hooks();
}

int
tinfo()
{
   TP->more("/d/Kalad/open/THANAR_INFO/tinfo",1,(int)TP->query_prop(PLAYER_I_MORE_LEN));
   return 1;
}

int
tranks()
{
   TP->more("/d/Kalad/open/THANAR_INFO/page5",1,(int)TP->query_prop(PLAYER_I_MORE_LEN));
   return 1;
}
