#include <stdproperties.h>

#include "../defs.h"

static string *dis_adj=
  ({
    "white-haired","gray-haired","black-haired","blond-haired",
    "brown-haired","red-haired","green-haired","blue-haired",
    "orange-haired","purple-haired","dark-haired","light-haired",
    "chestnut-haired","long haired","blond-bearded","red-bearded",
    "green-bearded","blue-bearded","orange-bearded","purple-bearded",
    "thinly-bearded","fork-bearded","long bearded","gray-bearded",
    "black-bearded","white-bearded","brown-bearded","mustachioed",
    "hook-nosed","Roman-nosed","red-nosed","big-nosed","pug-nosed",
    "potato-nosed","knob-nosed","pointy-eared","furry-eared",
    "jug-eared"
  });

mapping query_trick_disguise()
{
 return 
   ([
     "disguise":"disguise"
   ]);
}

int disguise(string how)
{
 int res;
 string adj1,adj2;
 string *allow_adj;
 object *al,sh;
 object kit;

 if(how=="remove")
  {
   TP->remove_prop("_trick_i_disguise_adj1");
   TP->remove_prop("_trick_i_disguise_adj2");
   TP->remove_prop(LIVE_I_NEVERKNOWN);
   TP->remove_dis_shadow();
   me("You remove your disguise.");
   all(" removes "+POS(TP)+" disguise.");
   return 1;
  }

 NF("But you don't have the kit!\nYou'd better run and recover it!\n");
 kit=present(KIT_DESC,TP);
 if(!kit) return 0;

 NF("You already wearing disguise!\n");
 if(TP->query_prop_setting("_trick_i_disguise_adj1")) return 0;

 NF("You need to be a tad more descriptive to disguise yourself.\n");
 if(!how) return 0;

 NF("You do not have enough material here to make a disguise!\n");
 if(!kit->get_contents()) return 0;

 res=sscanf(how,"%s %s",adj1,adj2);
 NF("That is an invalid adjective!\n");
 if(res!=2) return 0;

 allow_adj=dis_adj+TP->query_adj(1);
 if(member_array(adj1,allow_adj)==-1) return 0;
 if(member_array(adj2,allow_adj)==-1) return 0;

 NF("You must use different adjectives!\n");
 if(adj1==adj2) return 0;

 al=parse_this("all","%l");
 NF("You can't disguise yourself in room with people!\n");
 if(sizeof(al)) return 0;

 me("You carefully disguise yourself as a "+adj1+" "+adj2+" "+
   TP->query_gender_string()+" "+TP->query_race_name()+".");
 
 TP->add_prop("_trick_i_disguise_adj1",adj1);
 TP->add_prop("_trick_i_disguise_adj2",adj2);
 TP->add_prop(LIVE_I_NEVERKNOWN,"@@never_test");

 setuid();
 seteuid(getuid());

 sh=clone_object(TRICKSTERS+"obj/dis_shadow");
 if(sh->shadow_me(TP)!=1)
  {
   NF("Failed! Please inform your guildmaster about this bug!\n");
   TP->remove_dis_shadow();
   return 0;
  }
 TP->clear_intro();
 TP->add_subloc("disguise_subloc",sh);
 kit->used_disguise();

 return 1;
}

