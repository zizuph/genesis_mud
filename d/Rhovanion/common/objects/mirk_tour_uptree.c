inherit "/d/Rhovanion/common/objects/uptree";

#include <macros.h>

#define WHERE_HAVE_BEEN "_where_have_been_"
#define TREE_TOUR       4
#define NUMBER_OF_TREES 8

void 
test_tour(object player)
{
  object note;
  string *where_have_been;

  if (note = present("Thranduil_Tour_Note", player))
  {
    if(note->query_tour_done() || (note->query_tour_no() != TREE_TOUR))
      return;
    if(!(where_have_been = player->query_prop(WHERE_HAVE_BEEN)))
    {
      player->add_prop(WHERE_HAVE_BEEN, ({ MASTER }));
      return;
    }
    if(member_array(MASTER, where_have_been) == -1)
      where_have_been += ({ MASTER });
    if(sizeof(where_have_been) == NUMBER_OF_TREES)
    {
      note->set_tour_done();
      player->remove_prop(WHERE_HAVE_BEEN);
      return;
    }
    player->add_prop(WHERE_HAVE_BEEN, where_have_been);
  }
  return;
}

void init()
{
  test_tour(this_player()); 
  ::init();
}
