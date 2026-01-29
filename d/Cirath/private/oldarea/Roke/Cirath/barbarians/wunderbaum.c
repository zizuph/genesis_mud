inherit "/std/spells";

#include <macros.h>
#include "/d/Roke/teradeth/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include "/std/combat/combat.h"
#include "/d/Roke/common/defs.h"
#include <cmdparse.h>

query_auto_load() {
  string name;
  int i;
  sscanf(file_name(this_object()),"%s#%d", name, i);
  
  return name;
}

create_spells()
{

  set_short("sweet smelling Wunderbaum");
  set_name("wunderbaum");
  add_name("barb_baum");
  set_adj("smelling");
  set_long("This is a sweet-smelling Wunderbaum, it has an awful stench "+
           "to cover the smell from a true barbarian.\n"+
           "use 'help barbarian to get the information.\n");

}

init()
{
  /* string souls;
  * string = TP->query_cmdsoul_list()
  *  @ Olorin: put query_cmdsoul_list() into an array, remove the cmdsouls, load
  *  your guild soul, load the cmdsouls from the array
  */ 
 ::init();
  this_player()->remove_cmdsoul("/cmd/live/state");
  this_player()->add_cmdsoul("/d/Roke/Cirath/barbarians/barb_soul");
  this_player()->add_cmdsoul("/cmd/live/state");
  this_player()->update_hooks();

}

