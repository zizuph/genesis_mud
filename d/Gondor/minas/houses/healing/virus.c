inherit "/std/object";

#include "/d/Earthsea/common/defs.h"
#include <macros.h>

#define TIDTID 1000
#define	GOT_NASTY_DISEASE	"Poor_TP_Got_A_Nasty_Disease"

int tid;

query_auto_load()
{
  string name;
  int i;
  sscanf(file_name(TO),"%s#%d",name,i);
  i = find_call_out("sjukdom");
  if(i<=0)
    i = TIDTID;

  return name+":"+tid+"#"+i;
}
init_arg(string s)
{
  int t;

  sscanf(s,"%d#%d",tid,t);
  remove_call_out("sjukdom");
  call_out("sjukdom",t);
}
create_object()
{
  set_no_show(1);
  set_name("virus");
  set_long("A nasty STD virus.\n");
  
  add_prop(OBJ_I_NO_DROP,"Thought it would be that simple, did you?\n");
  tid=0;
  call_out("sjukdom",TIDTID);
}
do_evil()
{
  object sh;

  E(TO)->catch_msg("You've been walking around too long with that awful crotch pain.\n"+
		   "Your dick falls off and is immediately carried away by some hungry ants.\n");

  seteuid(getuid());

  if(sh = clone_object(REDLIGHT+"obj/vshadow"))
    {
      ROKE_LOG("infected","neuterized "+E(TO)->query_real_name()+"\n");
      sh->shadow_me(E(TO)->query_real_name());
      E(TO)->add_autoshadow(REDLIGHT+"obj/vshadow:0");
    }

  E(TO)->remove_prop(GOT_NASTY_DISEASE);
  remove_object();
}
dra_stats(int i)
{
  int j;
  for(j=0;j<6;j++)
    E(TO)->add_tmp_stat(j,i*E(TO)->query_stat(j)/100,TIDTID+1);
  E(TO)->catch_msg("You feel a little weaker.\n");
}
sjukdom()
{
  tid++;
  call_out("sjukdom",TIDTID);
  if (!E(TO)) return; /* just in case */

  E(TO)->add_prop(GOT_NASTY_DISEASE,1);
  if(tid>20)
    do_evil();
  else
    {
      if(tid<5)
	E(TO)->catch_msg("You feel an uncomfortable itch in your crotch.\n");
      else if(tid<10)
	{
	  dra_stats(-3);
	  
	  E(TO)->catch_msg("The itch in your crotch is really annoying you.\n");
	}
      else if(tid<15)
	{
	  dra_stats(-8);
	E(TO)->catch_msg("You feel really bad from that awful crotch pain.\n");
	}
      else 
	{
	  dra_stats(-20);
	  E(TO)->catch_msg("The sudden pain from your crotch strikes you to the ground.\n");
	  tell_room(E(E(TO)),QCTNAME(E(TO))+" falls to the ground writhering in pain.\n");
	}
    }
}



