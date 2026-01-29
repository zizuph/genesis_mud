inherit "/std/object";
inherit "/cmd/std/command_driver";

#include <stdproperties.h>

#include "../defs.h"

int material;
static int intro_flag;

void create_object()
{
 set_name("kit");
 add_name("_trickster_kit_");
 set_adj("disguise");
 add_prop(OBJ_M_NO_DROP,1);
 set_long("@@exa_kit");
}

string exa_kit()
{
 string desc;

 desc="This is a disguise kit, used by Tricksters to disguise "+
   "themselves as someone else if they so choose.  Within this "+
   "wonderous kit there are various coloured hair which one could use "+
   "for wiggs, beards and mustaches as well as various items which one "+
   "could use for a fake nose, ears or other various parts used for "+
   "a proper disguise.\n";

 if(!material)  desc+=
   "You do not have any material to make disguises in your kit.\n";
 else desc+=sprintf("You have enough material to make %d disguises "+
   "in your kit.\n",material);

 return desc;
}

void init()
{
 add_action("intro","introduce");
 add_action("intro","present");
 ::init();
}

void outfit()
{
 material=ENV(TO)->query_max_kit(); 
}

int get_contents()
{
 return material;
}

int intro(string str)
{
 object *list;
 string who,to_who;
 int res;

 if(!ENV(TO)->query_prop_setting("_trick_i_disguise_adj1")) return 0;

 if(intro_flag)
  {
   intro_flag=0;
   return 0;
  }

 res=sscanf(str,"%s to %s",who,to_who);
 if(!res) who=str;
 if(who!="me" && who!="myself") return 0;

 if(to_who) list=parse_this(to_who,"[the] %l");
   else list=parse_this("all","[the] %l");
 intro_flag=1;
 if(sizeof(list))
  {
   me("You reveal your true identity to all those whom you just "+
      "introduced to.");
   target(" introduces "+OBJ(TP)+"self and reveals "+POS(TP)+" true "+
      "identity.",list);
  }
 if(TP->command(query_verb()+" "+str)) TP->add_intro(list);
 return 1;
}

void save_kit()
{
 (TRICK_SERVER)->save_kit(ENV(TO)->query_real_name(),get_contents());
}

void used_disguise()
{
 material--;
 save_kit(); 
}

void load_kit()
{
 material=(TRICK_SERVER)->query_kit_contents(ENV(TO)->query_real_name());
}

