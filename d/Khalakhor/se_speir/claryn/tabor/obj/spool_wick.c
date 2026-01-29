//
// A Spool of Wick Cord - spun with the spinning wheel; used by
//                        candlewraught to make candles
//
// Zima 5/22/98
//
// Added any W_KNIFE for cutting
// Tapakah 07/2021

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "obj.h"

inherit "/std/object";

 
#define  TPN  QCTNAME(TP)
#define  RM   ENV(TP)

string color;
int    numwicks;
 
string query_color ()        { return color;    }
int    query_numwicks ()     { return numwicks; }
void   set_num_wicks (int n) { numwicks=n;      }
void   do_remove_obj ()      { remove_object(); }
 
int
remove_wick ()
{
  numwicks--;
  add_prop(OBJ_I_WEIGHT,10*numwicks);
  add_prop(OBJ_I_VOLUME,15*numwicks);
  add_prop(OBJ_I_VALUE,(numwicks/2)+1);
  if (numwicks<=0)
    set_alarm(1.0,0.0,&do_remove_obj());
  return numwicks;
}
 
void
set_color (string c)
{
  if (stringp(color))
    remove_adj(color);
  color=c;
  set_short("spool of "+color+" wick cord");
  set_pshort("spools of "+color+" wick cord");
  set_long("It is a spool of "+color+" cord, used to make the wicks of "+
           "candles, homespun of fine wool. You could cut a wick from "+
           "the spool with a knife.\n");
  add_adj(color);
}
 
void
create_object ()
{
  set_name("wick");
  add_name(({"spool","spool of cord","spool of wick cord","cord"}));
  add_adj(({"wool","homespun"}));
  set_color("white");
  numwicks=13;
  remove_wick();
}
 
void
appraise_object (int num)
{
  ::appraise_object(num);
  write("There seems to be enough cord on the spool to make about "+
        numwicks+" wicks.\n");
}

int
do_cut (string cmd)
{
  object *inv=all_inventory(TP), knife, wick;
  string  ks,ss;
 
  notify_fail("Cut what? Wick from spool with what?\n");
  if (!stringp(cmd))
    return 0;
  if (!parse_command(cmd,inv,"'wick' 'from' 'spool' 'with' %o",knife))
    return 0;
 
  ks=knife->short();
  if (!stringp(ks))
    ks=(knife->query_name());
  ss=query_short();
 
  if (
      !knife->id("knife") && !knife->id("sword") &&
      !knife->query_wt(W_KNIFE) && !knife->query_wt(W_SWORD)
      ) {
    write("You can not cut the wick with the "+ks+".\n");
    return 1;
  }
 
  if (numwicks==1)
    write("You cut the last wick from the "+ss+" with the "+ks+".\n");
  else
    write("You cut a wick from the "+ss+" with the "+ks+".\n");
  tell_room(RM,TPN+" cuts a wick from a "+ss+" with "+HIS_HER(TP)+" "+
            ks+".\n",TP);
 
  seteuid(getuid());
  wick=clone_object(OBJ+"wick");
  wick->set_color(color);
  if (wick->move(TP)) {
    write("You drop the wick.\n");
    tell_room(ENV(TP),QCTNAME(TP)+" drops a wick.\n",TP);
    wick->move(RM);
  }
  remove_wick();
  return 1;
}
 
void init()
{
  ::init();
  add_action(&do_cut(),"cut");
}
