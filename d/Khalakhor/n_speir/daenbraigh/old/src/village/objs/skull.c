/*
 * Skull from Sa Morgan
 * TAPAKAH 10/2005
 */

#pragma strict_types

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <language.h>

#include "/d/Genesis/gems/gem.h"
#include "/d/Khalakhor/sys/defs.h"

#include "../../daenbraigh.h"
#include "../../village/village.h"

inherit "/d/Khalakhor/std/object";

#define SKULL_GEMS ({"beryl","opal","sapphire","topaz","lapis"})
#define JAW_SLOTS 32
#define SKULL_KNIFE_SKILL 50
#define SKULL_DAMAGE (-20)
#define ELVEN_SKULL_WHOLE "_elven_skull_whole"

string mouth_long();
int    pluck_tooth(string str);
void   place_gems();

void
create_khalakhor_object()
{
  if(! IS_CLONE)
    return;
  
  ::create_khalakhor_object();

  set_name(V_OBJID + "skull");
  add_name("skull");

  set_adj("thin-boned");
  set_short("thin-boned skull");
  set_long("This skull obviously belonged to an elf.\n");

  add_prop(OBJ_I_VOLUME,2000);
  add_prop(OBJ_I_WEIGHT,1000);
  add_prop(OBJ_I_VALUE, 400);

  setuid();
  seteuid(getuid());
  place_gems();
  set_long("@@mouth_long");
}

string
mouth_long()
{
  string desc, *gem_desc;
  object *myinv;
  int i,j,k,s,t,no_gem;

  gem_desc = ({});
  t = 0;
  s = 0;
  no_gem = 1;
  desc = "This skull obviously belonged to an elf. ";
  
  myinv = all_inventory(TO);
  j = sizeof(myinv);
  for(i=0;i<j;i++) {
    if(myinv[i]->query_gem()) {
      if(no_gem) {
	desc += "You see some sparkling gems set in between the teeth of the skull! ";
	desc += "You see ";
	no_gem = 0;
      }
      k = myinv[i]->num_heap();
      if(k == 1) 
	gem_desc += ({myinv[i]->short()});
      else
	gem_desc += ({LANG_WNUM(k) + " " +  myinv[i]->query_plural_short()});
      s += k;
    }
    else
      t += myinv[i]->num_heap();
  }
  if(sizeof(gem_desc) > 1) {
    gem_desc[sizeof(gem_desc)-1] = "and " + gem_desc[sizeof(gem_desc)-1];
  }
  desc += implode(gem_desc,", ");
  desc += ". ";
  if(t)
    if(t + s < JAW_SLOTS)
      desc += " There are some gaps between the teeth as well.\n";
    else
      desc += "There are no gaps at all between the teeth.\n";
  else
    desc += "For some obscure reason, there are no teeth in the jaws.\n";

  if(t + s == JAW_SLOTS)
    add_prop(ELVEN_SKULL_WHOLE,1);
  return desc;
}

void
place_gems()
{
  int i,gems;
  object gem,tooth;
  
  gems = random(3)+3;
  for(i=0;i<gems;i++) {
    gem = clone_object(GEM_OBJ_DIR+ONE_OF(SKULL_GEMS));
    gem->move(TO,1);
    add_item(({gem->query_name()}),gem->query_long());
  }
  for(i=gems;i<JAW_SLOTS;i++) {
    tooth = clone_object(V_TOOTH);
    tooth->move(TO,1);
  }
}

void
init()
{
  ::init();
  add_action(pluck_tooth,"pluck");
}

int
pluck_tooth(string str)
{
  object what,*weapon;
  int i,wps,moveres;

  if(! str) 
    NF0("Pluck what?\n");

  if(what = present(str,TO)) {
    weapon = TP->query_weapon(-1);
    wps = sizeof(weapon);
    for(i=0;i<wps;i++) {
      if(weapon[i]->query_wt(W_KNIFE))
	if(TP->query_skill(SS_WEP_KNIFE) > SKULL_KNIFE_SKILL) {
	  write("You wedge the knife blade between the jaws of the skull "+
		"and pluck the " + str + ".\n");
	  what->split_heap(1);
	  moveres = what->move(TP,1);
	  return 1;
	}
	else {
	  if(str == "tooth") {
	    write("You serrate the knife and break the tooth.\n");
	    what->split_heap(1);
	    what->remove_object();
	  }
	  else
	    write("You serrate the knife, but the gem remains in place.\n");
	  weapon[i]->set_dull(weapon[i]->query_dull()+1);
	  return 1;
	}
    }
    write("You reach with your fingers and the jaws of the skeleton snap "+
	  "on them, hurting you badly. Maybe you should wield a knife?\n");
    TP->heal_hp(SKULL_DAMAGE);
    return 1;
  }
  else
    NF0("Pluck what?\n");
  return 0;
}
