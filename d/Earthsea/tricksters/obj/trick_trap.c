inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>

#include "../defs.h"

string trap_exit; // Exit that trap was set to
int trap_level;   // Trickster level of trap setter
object *aware;    // Array of objects who aware of the trap
string *cmd;      // Commands to move in trapped direction

void create_object()
{
 set_long("@@long_desc");
 set_name("trap");
 add_name("_trickster_trap_");
 add_adj("blocking");
 add_prop(OBJ_M_NO_GET,"How would you want to pick up a trap??\n");
 cmd=({});
 aware=({});
}

void init()
{
 ::init();
 add_action("block","",1);
}

void set_trap_exit(string exit)
{
 trap_exit=exit;
 cmd=({exit});

 set_adj(exit);

 switch(exit)
  {
   case "east": cmd+=({"e"}); break;
   case "west": cmd+=({"w"}); break;
   case "north": cmd+=({"n"}); break;
   case "south": cmd+=({"s"}); break;
   case "northeast": cmd+=({"ne"}); break;
   case "southeast": cmd+=({"se"}); break;
   case "northwest": cmd+=({"nw"}); break;
   case "southwest": cmd+=({"sw"}); break;
   case "up": cmd+=({"u"}); break;
   case "down": cmd+=({"d"}); break;
  }
}

string query_trap_exit()
{
 return trap_exit;
}

void set_trap_level(int lv)
{
 trap_level=lv;
}

int query_trap_level()
{
 return trap_level;
}

void add_aware(object ob)
{
 if(member_array(ob,aware)==-1) aware+=({ob});
}

int is_aware(object ob)
{
 return (member_array(ob,aware)==-1 ? 0 : 1);
}

int do_disarm(string what)
{
 object *trap,*obj;
 int i;

 obj=FIND_STR_IN_OBJECT(what,ENV(TP));
 if(!sizeof(obj)) return 0;

 for(i=0;i<sizeof(obj);i++)
   if(member_array("_trickster_trap_",obj[i]->query_names())==-1)
     return 0;
 trap=({});
 for(i=0;i<sizeof(obj);i++)
   if(obj[i]->is_aware(TP)) trap+=({obj[i]});
 if(!sizeof(trap)) return 0;

 NF("Disarming traps must be done gently! How do you expect to "+
   "disarm all of traps simultaneously?\n");
 if(sizeof(trap)>1) return 0;    

 if(!TP->query_trickster_level())
  {
   if(TP->query_skill(SS_FR_TRAP)<trap[0]->query_trap_level()*3/2)
    {
     me("You can't remove this trap. Apparently you don't know a jack "+
       "about traps...");
     say(QCTNAME(TP)+" tried to remove "+trap[0]->short()+
       ", but failed.\n");
     return 1;
    }
   me("You disarm "+trap[0]->short()+" and remove the string.");
   say(QCTNAME(TP)+" succesfully removes "+trap[0]->short()+".\n");
   trap[0]->remove_object();
   return 1;
  }

 if(TP->query_trickster_level()<trap[0]->query_trap_level())
  {
   me("You study the trap and decide not to touch it , since it has "+
     "been set by more expirienced Trickster.\n");
   return 1;
  }
 me("You disarm "+trap[0]->short()+" and remove the string.\n"+
    "Ohh good! Now you ruined all the fun to one who set it!");
 say(QCTNAME(TP)+" succesfully removes "+trap[0]->short()+".\n");
 trap[0]->remove_object();
 return 1;
}

int do_cut(string str)
{
 object *trap,*weapon,*obj;
 int i,res;
 string what,with;

 if(!str) return 0;

 res=sscanf(str,"string on %s with %s",what,with);
 if(res!=2) return 0;

 obj=FIND_STR_IN_OBJECT(what,ENV(TP));
 if(!sizeof(obj)) return 0;

 for(i=0;i<sizeof(obj);i++)
   if(member_array("_trickster_trap_",obj[i]->query_names())==-1)
     return 0;
 trap=({});
 for(i=0;i<sizeof(obj);i++)
   if(obj[i]->is_aware(TP)) trap+=({obj[i]});
 if(!sizeof(trap)) return 0;

 NF("Disarming traps must be done gently! How do you expect to "+
   "disarm all of traps simultaneously?\n");
 if(sizeof(trap)>1) return 0;    

 weapon=FIND_STR_IN_OBJECT(with,TP);
 NF("Cut string on "+trap[0]->short()+" with what?\n");
 if(!sizeof(weapon)) return 0;
 NF("Choose one weapon to cut with!\n");
 if(sizeof(weapon)>1) return 0;
 NF("It's not sharp! How do you expect to cut with it?\n");
 if(!(weapon[0]->query_dt() & W_SLASH)) return 0;

 me("You cut a string on "+trap[0]->short()+" with "+weapon[0]->short()+
   " removing the trap.");
 if(TP->query_trickster_level())
   me("Ohh good! Now you ruined all the fun to one who set it!");
 say(QCTNAME(TP)+" cuts a string on "+trap[0]->short()+" with "+
   weapon[0]->short()+".\n");
 trap[0]->remove_object();
 
 return 1;
}

int block(string str)
{
 string verb;

 verb=query_verb();

 if(verb=="disarm") return do_disarm(str);
 if(verb=="cut") return do_cut(str);

 if(member_array(verb,cmd)==-1) return 0;

 if(is_aware(TP))
  {
   write("Since you aware of trap , you simple step over it.\n");
   return 0;
  }
 me("As you try to go "+trap_exit+" you suddenly stumble over "+
   "something and fall down!\n"+"You look down and discover very "+
   "simple trap: string stretched at the "+trap_exit+" exit.");
 say(QCTNAME(TP)+" suddenly stumbles over something and falls down!\n");
 add_aware(TP);

 return 1;
}

int query_no_show()
{
 return (is_aware(TP) ? 0 : 1);
}

int query_no_show_composite()
{
 return (is_aware(TP) ? 0 : 1);
}

string long_desc()
{
 string info;
  
 if(TP->query_trickster_level())
  {
   if(TP->query_trickster_level()<trap_level)
     info="You study the trap and realize that someone more "+
          "experienced then you set it.\n";
   if(TP->query_trickster_level()==trap_level)
     info="You study the trap and realize that someone as "+
          "experienced as you set it.\n";
   if(TP->query_trickster_level()>trap_level)
     info="You study the trap and realize that someone less "+
          "experienced then you set it.\n";
  } 
 else info="";

 return "This is simple trap: string stretched to block "+trap_exit+
   " exit from the room. To remove the trap you may try to disarm trap"+
   " or cut string on trap with something sharp.\n"+info;
}

