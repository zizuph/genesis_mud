/* 	this is the workroom for Calia
 *
 *   coder(s):   Merlin
 *
 *   history:    20.09.93    created                         Merlin
 *               18.1.96     update                          Maniac
 *               27/5/96     update                          Maniac
 *               31/3/98     added domain board              Jaacar
 *
 *   purpose:    workroom for Calia, board	
 *   exits:      post, church, each area of Calia
 *
 *   objects:    domain_board ( )
 *   npcs:       none
 * 
 *    quests:     none
 *   special:    none
 *
 *   to do:      include exits for all the areas
 *   bug:        none known
 */


inherit "/std/workroom";

#include "domain.h"
#pragma save_binary

void load_board();

create_workroom()
{

  set_short("Centre Point Calia");
  set_long("This is Centre Point Calia. From here wizards can go " +
           "directly to many parts of the domain, and a few other " +
           "useful places.\n");

  add_exit("/d/Calia/common/domain_entr", "south", 0);
  add_exit("/d/Calia/argos/metro/rooms/visitctr", "argos", 0);
  add_exit("/d/Calia/mountain/croad/croad12", "croad", 0);
  add_exit("/d/Calia/argos/dephtemp/rooms/foyer", "deph", 0);
  add_exit("/d/Calia/mountain/road/road21", "docks", 0);
  add_exit("/d/Calia/mountain/foothill/fh85", "foothill", 0);
  add_exit("/d/Calia/gelan/rooms/boardroom", "gelan", 0);
  add_exit("/d/Calia/mountain/road/m13", "moor", 0);
  add_exit("/d/Genesis/wiz/entrance", "news", 0);
    add_exit("/d/Calia/palace/rooms/light/trainroom","palace",0);
  add_exit("/d/Genesis/wiz/post", "post", 0);
  add_exit("/d/Calia/palace_raid_room", "raid", 0);

    load_board();
}

void
load_board()
{
    object bb;
    seteuid(getuid(this_object()));
    bb = clone_object("/d/Calia/domain_board");
    bb->move(this_object());
}

int
query_prevent_snoop()
{
    return 1;
}
