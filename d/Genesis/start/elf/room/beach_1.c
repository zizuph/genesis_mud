#include "../stddefs.h"
#include "/sys/stdproperties.h"

#pragma save_binary

inherit ELFROOM;

#define NORTH    ROOMDIR + "begin"

#define SHORT  "On the shore of a small lake"

#define NAT_LONG \
  "You are standing on the shore of the small Lake of the Lady. "+\
  "The still surface has the cloudy, slate-gray colour that very deep lakes "+\
  "have, and it is never warmed even by the hottest sun. Its water is " +\
  "clear and fresh, but with a tang of otherworldliness in its taste, " +\
  "and it sparkles with a blue light when drawn from the lake.\n" + \
  "Over the cold lake shreds of fog slowly form, drifting towards the " +\
  "shore where you are standing, thickening as they approach.\n" +\
  "Among the waterpolished pebbles of the beach there are a few pieces of " +\
  "drying driftwood.\n"
#define FOR_LONG \
  "You are standing on the shore of a small lake. "+\
  "The still surface has the cloudy, slate-gray colour that very deep lakes "+\
  "have, and the water seem to be very clear. " +\
  "Over the cold lake shreds of fog slowly form, drifting towards the " +\
  "shore where you are standing, thickening as they approach.\n" +\
  "Among the waterpolished pebbles of the beach there are a few pieces of " +\
  "drying driftwood.\n"
  
#define WIZINFO \
  "There is a hidden torch here, found when you examine the driftwood. "+\
  "It is only findable once per reset\n"


#define WATER_ITEM  ({"water", "waters"})
#define WATER_FDESC \
  "When you taste the water, you find it clear, cold, and with a strange, "+\
  "tart, but not unpleasant, taste. It tickles your tongue and the inside "+\
  "of your mouth slightly.\n"
#define WATER_NDESC \
  "When you taste the water, you find it clear, cold, and with a strange, "+\
  "tart, but not unpleasant, taste. It emits blue sparkles when taken from "+\
  "the lake, and tickles your tongue and the inside of your mouth slightly.\n"

#define FOG_ITEM ({"fog", "mist", "shred", "shreds"})
#define FOG_DESC \
  "The fog seem to be forming when the warmer air around the lake meets "+\
  "the cold water. What makes them drift this way, however, is hard to say, "+\
  "as there is not much wind to speak about.\n"

#define SURFACE_ITEM ({"surface", "lake", "wave", "waves"})
#define SURFACE_DESC \
  "The surface of the lake is still, with just a few low, lazy waves "+\
  "rolling towards the shore.\n"

#define SHORE_ITEM ({"shore", "beach"})
#define SHORE_DESC \
  "The shore is quite long, and you cannot see all of it from here.\n"

#define PEBBLE_ITEM ({"pebble", "pebbles", "stone", "stones"})
#define PEBBLE_DESC \
  "The stones are polished smooth and round by the water. They are "+\
  "multicoloured in muted brown, red, and gray nuances, and very, very " +\
  "ordinary.\n"

#define DRIFTWOOD_ITEM ({"driftwood"})
#define DW_WITH_TORCH \
  "Among the pathetic, broken twigs you actually see a perfectly good torch.\n"
#define DW_WITHOUT_TORCH \
  "You only see a few pathetic, broken twigs, good for nothing.\n"

#define TORCH_ITEM ({"torch"})
#define TORCH_ID     "torch"
#define TORCH_DESC \
  "It is a knaggy stick of wood, wrapped with tar-drenched rags at one end.\n"
#define NO_TORCH_DESC \
  "Torch? What torch? There is none here...\n"
#define TORCH_GOTTEN \
  "You take a torch from among the driftwood.\n"
#define TORCH_NOT_GOTTEN \
  "There is no wood fit for a torch here.\n"

#define DONT_SWIM \
  "The lake is by far too cold for that. You would not last long enough to "+\
  "get anywhere.\n"


status got_a_torch;
  
create_room()
{
  set_short(SHORT);
  set_long(N_KNOW(WRAP(NAT_LONG), WRAP(FOR_LONG)));
  
  add_item(    WATER_ITEM, N_KNOW(WRAP(WATER_NDESC), WRAP(WATER_FDESC)));
  add_item(      FOG_ITEM, WRAP(    FOG_DESC));
  add_item(   PEBBLE_ITEM, WRAP( PEBBLE_DESC));
  add_item(  SURFACE_ITEM, WRAP(SURFACE_DESC));
  add_item(    SHORE_ITEM, WRAP(  SHORE_DESC));
  add_item(DRIFTWOOD_ITEM, H_ITEM(TORCH_ID, 
				  WRAP(DW_WITH_TORCH), WRAP(DW_WITHOUT_TORCH)));
//   add_item(    TORCH_ITEM, H_ITEM(TORCH_ID, 
// 				  WRAP(TORCH_DESC), WRAP(NO_TORCH_DESC)));

  add_cmd_item(TORCH_ITEM, "take", GET_H_ITEM(TORCH_ID, TORCH_GOTTEN, TORCH_NOT_GOTTEN));
  add_cmd_item(TORCH_ITEM,  "get", GET_H_ITEM(TORCH_ID, TORCH_GOTTEN, TORCH_NOT_GOTTEN));
  add_cmd_item(WATER_ITEM, "drink", N_KNOW(WRAP(WATER_NDESC), 
					   WRAP(WATER_FDESC)));

  STD_WIZINFO;

  add_exit(NORTH, "north", 0);

  stock();
}

reset_room()
{
  stock();
}


stock()
{
  restock_hidden_item(OBJDIR + "torch", 1, TORCH_ID);
}

init()
{
  ::init();
  add_action("do_swim", "swim");
  add_action("do_swim", "bathe");
}


wizinfo()
{
  return WRAP(WIZINFO);
}


int do_swim(string arg)
{
  if (!arg ||
      arg == "out" ||
      arg == "lake" ||
      arg == "across" ||
      arg == "across lake" ||
      arg == "in lake") {
    write(WRAP(DONT_SWIM));
    return 1;
  }
}
  
