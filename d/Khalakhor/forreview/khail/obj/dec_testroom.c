#include "/d/Immortal/std/domain.h"

#define LIVE_I_APT_OWNER "_live_i_apartment_owner_"

inherit STDROOM;

string *wall_desc, *floor_desc, *ceiling_desc, *standing_desc;


void
create_room()
{
  set_short("an empty room");
  set_long("and empty room for testing decorations\n");
  add_item(({"testing one", "testing two"}),"A test description");
}

void
init()
{
  ::init();
  if(living(TP) && !TP->query_prop(LIVE_I_APT_OWNER))
    TP->add_prop(LIVE_I_APT_OWNER, 1);
}

mixed
add_decoration(string where, string *names, string desc)
{
   if(!wall_desc)
     wall_desc = ({});
   if(!floor_desc)
     floor_desc = ({});
   if(!ceiling_desc)
     ceiling_desc = ({});
   if(!standing_desc)
     standing_desc = ({});

   if(sizeof(query_item()) >= 10)
     return "You don't think you have enough space to add any more "+
       "decorations to this room.\n";

   switch(where)
     {
     case "wall":
        wall_desc += ({names[0]});
       break;
     case "floor":
       floor_desc += ({names[0]});
       break;
     case "ceiling":
       ceiling_desc += ({names[0]});
       break;
     case "standing":
       ceiling_desc += ({names[0]});
       break;
     }

  add_item(names, desc);
  return "You decorate the room with "+names[0]+"\n";
}

string
query_owner()
{ return "stexx"; }
