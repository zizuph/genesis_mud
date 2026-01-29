/*
 * Hammerhands' rack
 * TAPAKAH 10/2005
 * Serves only for clubs
 */

inherit "/std/container.c";

#include <files.h>
#include <formulas.h>
#include <wa_types.h>

#include "/d/Khalakhor/sys/defs.h"

#include "../../daenbraigh.h"
#include "../../hhands/hhands.h"

#define RACK_MULTIPLIER 2

int value_object(object ob);
mapping rackmap;

void
create_container()
{
  set_name("rack");
  add_name(HH_OBJID + "_rack");
  set_adj("bludgeon"); 
  set_short("bludgeon rack"); 
  set_long("A large wooden rack with the emblem of crossed clubs.\n");
  
  add_prop(CONT_I_WEIGHT,500000);
  add_prop(CONT_I_MAX_WEIGHT,650000);
  add_prop(CONT_I_VOLUME,100000);
  add_prop(CONT_I_MAX_VOLUME,1000000);
  add_prop(CONT_I_RIGID,1);
  add_prop(CONT_I_CLOSED,0);
  add_prop(OBJ_I_NO_GET,1);
  
  setuid();
  seteuid(getuid());
}

void
enter_inv(object ob, object from)
{
  ::enter_inv(ob,from);
  rackmap = restore_map(HH_RACKMAP);
  if(rackmap[from->query_real_name()])
    rackmap[from->query_real_name()] += RACK_MULTIPLIER*value_object(ob);
  else
    rackmap += ([from->query_real_name():RACK_MULTIPLIER*value_object(ob)]);
  save_map(rackmap,HH_RACKMAP);
}

void
leave_inv(object ob, object to)
{

  ::leave_inv(ob,to);
  rackmap[to->query_real_name()] -= value_object(ob);
  save_map(rackmap,HH_RACKMAP);
}

int
prevent_leave(object ob)
{
  if(! TP->query_prop(HH_MEMBER)) {
    write("Only guild members may use this rack.\n");
    return 1;
  }
  rackmap = restore_map(HH_RACKMAP);
  if(rackmap[TP->query_real_name()] &&
     rackmap[TP->query_real_name()] > value_object(ob)) {
    return 0;
  }
  else 
    write("You do not dare to take anything from the rack yet.\n");
  return 1;
}

int
prevent_enter(object ob)
{
  if(!(IS_WEAPON_OBJECT(ob) &&
       (ob->query_dt() & W_BLUDGEON))) {
    write("Only bludgeons may be put into the rack.\n");
    return 1;
  }
  return 0;
}

int
value_object(object ob)
{
  return F_VALUE_WEAPON(ob->query_hit(), ob->query_pen()); 
}

void
init()
{
  ::init();
}
