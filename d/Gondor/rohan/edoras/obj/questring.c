inherit "/std/armour";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>

create_armour() 
{
  set_short("golden ring");
  set_pshort("golden rings");
  set_long("@@read_name");
  set_name("ring");
  add_name("golden ring");
  set_pname("rings");
  set_adj("golden");
  add_adj("gold");
  set_at(A_ANY_FINGER);
  set_ac(1);
  set_af(this_object());
  add_prop(OBJ_I_WEIGHT,50);
  add_prop(OBJ_I_VOLUME,50);
  add_prop(OBJ_I_VALUE,150);
  add_prop("_ring_from_edoras_well",1);
}

read_name(str) {
  int test;
  string beskr;
  beskr="The ring is made of gold, and is encarved with fine leaves. ";
  test=this_player()->query_skill(SS_LANGUAGE);
  if(test>10)
     beskr=beskr+"On the inside the name 'Funohed' is stamped. ";
  else if(test>=5)
     beskr=beskr+"On the inside you can see some letters stamped. But you can't figure out what they mean.";
  else
     beskr=beskr+"On the inside you can see some carvings.";
  beskr=beskr+"\n";
  return break_string(beskr,70);
}
     
query_recover()  { return MASTER; }
