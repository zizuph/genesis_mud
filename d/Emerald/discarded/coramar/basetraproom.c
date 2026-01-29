#include "/d/Emerald/defs.h"
#include "dirheader.h"
#include "coramar.h"
#include <stdproperties.h>


#ifndef TO
#define TO this_object()
#endif

inherit BASEFOREST;

public void create_traproom();

object mytrap;


void
create_forest()
{
    set_short("A misty forest path");
    create_traproom();

    reset_euid();
    mytrap = clone_object(CORAMAR_OBJ+"trap");
    mytrap->move(TO,1);    
}

void
reset_room()
{
  object game;

  if ( !mytrap->query_game() ) 
  {
    game = clone_object(CORAMAR_NPC+"game");
    game->move(mytrap,1);
    tell_room(TO,"A painful, smothered cry echos against the mist as a small animal "+
	"falls victim to a pit trap.\n");
    mytrap->remove_prop(OBJ_I_HIDE);
    mytrap->set_game(game);
  }
}

void
create_traproom()
{
}
