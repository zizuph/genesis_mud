inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#include "/sys/filter_funs.h"
 
int charge;
 
void create_object()
{
   set_name("wand");
   add_name("stick");
   set_pname("wands");
   add_pname("sticks");
   set_short("strange wooden stick");
   set_pshort("strange wooden sticks");
   set_long("Very strange looking wooden stick..."+
            " Maybe it's magical?\n");
   add_prop(OBJ_I_WEIGHT,500);
   add_prop(OBJ_I_VOLUME,200);
   charge=10;
 
}
 
void init()
{
   add_action("do_disintegrate","disintegrate");
   add_action("do_point","point");
   add_action("do_point","zap");
}
 
static void
tell_watcher(string str, object me, object enemy)
{
    object *ob;
    int i;
 
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}
 
 
int do_disintegrate(string target)
{
   object *list;
   int i;
   mixed *what;
 
   notify_fail("Disintegrate what?\n");
   if (target==0) return 0;
 if ((target=="door")&&(charge>0)&&(ENV(ENV(TO))->allow_dest_door()==1))
     {
       ENV(ENV(TO))->dest_door();
       charge--;
       write("You point at door with your wand and powerful charge"+
           " completely disintegrated it!\n");
       say(QCTNAME(TP)+" points with "+TP->query_possessive()+
           " wand at the door and it's disintegrates with "+
           "a bright flash !\n");
       return 1;
     }
   if (charge==0)
     {
       write("Your wand says: Poof!\n");
       return 1;
     }
   if (ENV(TP)->item_id(target))
     {
       write("As you try to disintegrate "+target+", powerful charge "+
             "rejected by your target hits you!!!\n");
       say(QCTNAME(TP)+" tries to disintegrate "+target+", but only "+
           "got burned from blinding flash of fire!\n");
       TP->set_hp(TP->query_hp()-(TP->query_max_hp())/5);
       charge--;
       return 1;
     }
   list=FILTER_LIVE(all_inventory(ENV(TP)));
   if (!parse_command(target,list,"%l",what)) return 0;
   if ((what[0]==0)||(what[0]>1))
     {
       NF("You cannot zap wand at more then one living!\n");
       return 0;
     }
   TP->catch_msg("As you try to disintegrate "+QTNAME(what[1])+
         ", powerful charge "+
         "rejected by your target hits you!!!\n");
   tell_watcher(QCTNAME(TP)+" tries to disintegrate "+QTNAME(what[1])+
       ", but only "+
       "got burned from blinding flash of fire!\n",TP,what[1]);
   what[1]->catch_msg(QCTNAME(TP)+" tries to disintegrate YOU"+
       ", but only "+
       "got burned from blinding flash of fire!\n");
   TP->set_hp(TP->query_hp()-(TP->query_max_hp())/5);
   charge--;
   return 1;
 
}
 
int do_point(string target)
{
   object *list;
   int i;
   string *res;
   mixed *what;
   string trg;
 
   notify_fail("Zap what at what?\n");
   if (target==0) return 0;
   if ((target=="wand at door")&&(charge>0)&&(ENV(ENV(TO))->allow_dest_dr()==1))
     {
       ENV(ENV(TO))->dest_door();
       charge--;
       write("You point at door with your wand and powerful charge"+
           " completely disintegrated it!\n");
       say(QCTNAME(TP)+" points with "+TP->query_possessive()+
           " wand at the door and it's disintegrates with "+
           "a bright flash!\n");
       return 1;
     }
   if (charge==0)
     {
       write("Your wand says: Poof!\n");
       return 1;
     }
   res=explode(target," ");
   if (sizeof(res)<3) return 0;
   if (res[0]!="wand") return 0;
   if (res[1]!="at") return 0;
   if (res[2]=="") return 0;
   trg=res[2];
   for (i=3;i<sizeof(res);i++)
       trg=trg+" "+res[i];
   if (ENV(TP)->item_id(trg))
     {
       write("As you try to disintegrate "+trg+", powerful charge "+
             "rejected by your target hits you!!!\n");
       say(QCTNAME(TP)+" tries to disintegrate "+trg+", but only "+
           "got burned from blinding flash of fire!\n");
       TP->set_hp(TP->query_hp()-(TP->query_max_hp())/5);
       charge--;
       return 1;
     }
   list=FILTER_LIVE(all_inventory(ENV(TP)));
   if (!parse_command(target,list,"'wand' 'at' %l",what)) return 0;
   if ((what[0]==0)||(what[0]>1))
     {
       NF("You cannot zap wand at more then one living!\n");
       return 0;
     }
   TP->catch_msg("As you try to disintegrate "+QTNAME(what[1])+
         ", powerful charge "+
         "rejected by your target hits you!!!\n");
   tell_watcher(QCTNAME(TP)+" tries to disintegrate "+QTNAME(what[1])+
       ", but only "+
       "got burned from blinding flash of fire!\n",TP,what[1]);
   what[1]->catch_msg(QCTNAME(TP)+" tries to disintegrate YOU"+
       ", but only "+
       "got burned from blinding flash of fire!\n");
   TP->set_hp(TP->query_hp()-(TP->query_max_hp())/5);
   charge--;
   return 1;
 
}
