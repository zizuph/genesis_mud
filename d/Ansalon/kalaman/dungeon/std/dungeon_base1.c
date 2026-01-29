/*
 * This is the Dungeon base room that will hold
 * all the general descriptions and functions for
 * the dungeon.
 *
 * Might not always be the best of code but it works.
 *
 * 20080128 Lunatari : Created/Maybe
 * 20110927 Lunatari : Trying to move the Cell/CellCorridor 
 *                     functions into here.
 */
#include "../local.h"

inherit AR_FILE

void create_dungeon_room();
void reset_dungeon_room();

#define CREATE "create_dungeon_room"
#define RESET  "reset_dungeon_room"

/* 
 * Dungeon Type
 *
 * 0: Dungeon Corridor
 * 1: Dungeon Prison Cell 1
 * 2: Dungeon Prison Cell 2
 * 3: Dungeon Guard Room
 * 4: Dungeon Gate Room
 * 5: Cell Row type 1
 * 6: Cell Row type 2
 * 7: Tunnel type 1
 * 8: Tunnel type 2
 * 9: Inside well
 */
int gType, gDstream;
string gDextra;

/*
 * This function is called from the main Krynn room. It checks
 * weather or not the room should be reseted.
 * The function returns TRUE if there should be a reset.
 */
nomask public int 
query_reset()
{
  if (function_exists(RESET, TO))
  {
    return 1;
  }
  return 0;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void 
create_krynn_room()
{
  create_dungeon_room();
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void 
reset_krynn_room()
{
  reset_dungeon_room();
}

int 
set_dungeon_type(int value) 
{ 
  gType = value; 
  return value; 
}

int 
query_dungeon_type() 
{ 
  return gType; 
}

string 
get_short_desc()
{
  string text;

  switch (gType) 
  {
    case ROOM_MAIN:
      text = "A dark corridor";
      break;
    case ROOM_CELL1:
      text = "A prison cell";
      break;
    case ROOM_CELL2:
      text = "A small prison cell";
      break;
    case ROOM_GUARD1:
      text = "A small dark room";
      break;
    case ROOM_GUARD2:
      text = "A large gloomy room";
      break;
    case ROOM_CLROW1:
      text = "A corridor with cells";
      break;
    case ROOM_CLROW2:
      text = "An unfinished corridor";
      break;
    case ROOM_TUNNEL1:
      text = "A dark narrow tunnel";
      break;
    case ROOM_TUNNEL2:
      text = "A narrow tunnel";
      break;
    case ROOM_WELL:
      text = "Inside a well";
      break;
    default:
      text = "A default room";
  }

  return text;
}

void
add_extra_long(string text, int where)
{
  gDstream = where;
  gDextra  = text;
}

string
get_long_desc()
{
  string text;

  switch (gType) 
  {
    case ROOM_MAIN:
      text = "A damp, cold and dark dungeon. Water drips from the ceiling down " +
        "to the floor, creating small stinking pools. The floor is made out of "   +
        "rough stone bricks of various size, colour and shape. The walls "  + 
        "are basically made of the same stone as the floor and lean " +
        "inwards in an arch, become one with the ceiling.";
      break;
    case ROOM_CELL1:
      text = "A dirty, damp and dark cell within the dungeon. Like the rest of " +
        "of the rooms in this place, water is dripping down the walls but " +
        "since the cells have very little drainage the pools are much " +
        "larger and almost everything is wet or moist in here. On the left " +
        "side of the cell door a very primitive bed stands, made out of " +
        "steel with a crude wooden bottom and attached to the rock wall. " +
        "A massive wall of steel bars lets light in from the corridor.";
      break;
    case ROOM_CELL2:
      text = "A very small dirty, damp and dark prison cell. Like the rest of " +
        "of the rooms in this place, water is dripping down the walls but " +
        "since the cells have very little drainage the pools are much " +
        "larger and almost everything is wet or moist in here. This cell is " +
        "so small that there is no room for any kind of bed here, instead " +
        "of a bed some larger rocks have been place alongside eachother and " +
        "forms a very crude and uncomfortable resting spot.";
      break;
    case ROOM_GUARD1:
      text = "A small dusky room that seems to be a guardroom with the porpuse of " +
        "watching over the eastern corridor of cells. The room has a table a " +
        "couple of chairs and not much more. In here a wooden floor has been laid. "+
        "The floor has some rough carpets that gives some cover for the cold " +
        "and wet stone underneath the planks.";
      break;
    case ROOM_GUARD2:
      text = "A large room that based on its decoration and furniture must be the " +
        "main room of the dungeon guards, where they can relax and sleep after " +
        "they have done their hours in the guardrooms. The room has a few tables, " +
        "some chairs, several cupboards against the west wall and four rows of " +
        "bunks stand against the south wall. This room also has a wooden floor and " +
        "some carpets.";
      break;
    case ROOM_CLROW1:
      text = "A dark and narrow corridor with even darker and smaller prision cells " +
        "on each side. The ceiling is a bit lower here then in the other main " +
        "hall and the overall workmanship of this area is cruder and rougher.";
      break;
    case ROOM_CLROW2:
      text = "A small corridor with several of unfinished, halfbuilt, uncomfortable, " +
        "very small cells. Most of the cells dont even have the hinges ready on " +
        "their doorframes. The area is filled with work equipment and material.";
      break;
    case ROOM_TUNNEL1:
      return "A small narrow tunnel somewhere underneath the sewers of Kalaman. " +
        "It is rather hard to tell what is what here, floor, ceiling, walls, the " +
        "all seem to be covered with water and there is no way of telling what is " +
        "really what.";
      break;
    case ROOM_TUNNEL2:
      return "A damp and narrow tunnel underneath the sewers of Kalaman. Very dirty " +
        "almost black water drips down the walls from small cracks in the very " +
        "low, almost collapsing ceiling. The little space of floor that exists " +
        "here is all covered with muddy water.";
      break;
    default:
      text = "This is a very default room description. You should make a bug report.";
  }

  switch (gDstream)
  {
    case 1:
      text = gDextra + " " + text;
      break;
    case 2:
      text = text + " " + gDextra;
      break;
    default:
  }

  return text + "\n";
}

/* Function add_cell_window
 * Info:    A function to add exa window in door and then show the inside of the
 *          cell or room.
int
add_cell_window(mixed dir_room, object dest_room)
{
  return 1;
}
 */

/* Function: add_cell_door
 * Info:     A quick function to add a door!
 */
int
add_cell_door(string door_id, mixed door_cmd, mixed other_room, string door_dir, string door_key)
{
  object door;

  if (door = clone_object(DOBJ + "dungeon_celldoor")) 
  {
    door->set_door_id(door_id);
    door->set_other_room(other_room);
    door->set_pass_command(door_cmd);
    door->set_door_name(({"cell door leading " + door_dir, 
          "cell door", "door", "celldoor",
          door_dir + " door", door_dir + " cell door"}));
    door->set_key(door_key);
    door->set_locked(1);
    door->move(TO, 1);

    return 1;
  }

  return 0; 
}


string
add_cell_window(string room)
{
  if (LOAD_ERR(room))
  {
    return "You look through the bars and see nothing.\n";
  }

  object *item = all_inventory(find_object(room));
  string room_desc, living_desc;

  if (sizeof(item))
  {
    living_desc = COMPOSITE_LIVE(FILTER_LIVE(item));
  }

  room_desc = room->long();
  if ( living_desc != "nobody" )
  {
    return room_desc+living_desc+".\n";
  }

  return "You look through the bars and see: " + room_desc;
}

int
add_steel_door(string door_id, mixed door_cmd, mixed other_room, string door_dir, string door_key)
{
  object door;

  if (door = clone_object(DOBJ + "dungeon_celldoor")) 
  {
    door->set_door_id(door_id);
    door->set_other_room(other_room);
    door->set_pass_command(door_cmd);
    door->set_door_name(({"reinforced steel door leading " + door_dir, 
          "reinforced steel door", "door", "steel door",
          door_dir + " door", door_dir + " steel door"}));
    door->set_key(door_key);
    door->move(TO, 1);
    door->set_door_desc("This is a massive steel reinforced door.\n");
    door->set_lock_mess(({"locks the door.\n","You lock the door.\n"}));
    door->set_fail_lock(({"The door is already locked.\n","Lock an open door?\n"}));
    door->set_unlock_mess(({"unlocks the door.\n","You unlock " +
        "the door with a noisy 'click' of the lock.\n"}));
    door->set_pick(90);

    return 1;
  }

  return 0; 
}

/* Function: add_room_items
 * Info: Switch gType and add different items for all rooms
 */
void
add_room_items()
{ 
  /*
  add_item(({"ceiling","roof"}), get_ceiling_desc);
  */

  switch (gType) 
  {
    case ROOM_TUNNEL1:
      add_item(({"wall", "walls"}), 
        "It is hard to separate what is wall and what is ceiling here, the tunnel " +
        "is so narrow here and water dripping out from cracks almost everywhere make it " +
        "even harder to decide what is up and what is down.\n");
      add_item(({"rock","rocks"}),
        "The floor is covered with small rocks, most likely pieces of the ceiling or " +
        "the walls.\n");
      add_item(({"pool","pools"}),
        "Tiny pools of water cover the floor here.\n");
      add_item(({"floor", "ground"}),
        "The floor seems to merge into the ceiling and the ceiling is very " +
        "hard separate from the walls, it all seems to be the same. The floor " +
        "is of course easier to figure out since it is all covered with water, " +
        "not just small pools but completely covered with dirty muddy water. " +
        "There are also several rocks all over the floor.\n");
      add_item(({"water", "dripping", "drops"}), 
        "Water running down the walls and dripping from the ceiling form small pools " +
        "on the ground. The water looks completely undrinkable.\n");
    break;
    case ROOM_TUNNEL2:
      add_item(({"wall", "walls"}), 
        "There is no real way of telling if it is the floor or the wall " +
        "since the water seems to be dripping from everywhere.\n");
      add_item(({"rock","rocks"}),
        "The floor is covered with small rocks, most likely pieces of the ceiling or " +
        "the walls.\n");
      add_item(({"pool","pools"}),
        "There are small pools of foul smelling water all of the tunnel floor.\n");
      add_item(({"floor", "ground"}),
        "The floor seems to merge into the ceiling and the ceiling is very " +
        "hard separate from the walls, it all seems to be the same. The floor " +
        "is of course easier to figure out since it is all covered with water, " +
        "not just small pools but completely covered with dirty muddy water. " +
        "There are also several rocks all over the floor.\n");
      add_item(({"water", "dripping", "drops"}), 
        "Water running down the walls and dripping from the ceiling form small pools " +
        "on the ground. The water looks completely undrinkable.\n");
    break;
    case ROOM_MAIN:
      add_item(({"wall", "walls"}), 
        "The walls are cut out of the solid rock and crudely shaped into " +
        "looking like regular walls. Water is dripping down the walls here " +
        "and there through cracks in the ceiling; forming small cold pools on "+
        "dirty floor.\n");
      add_item(({"pool","pools"}),
        "Very dirty and putrid water has formed stinking pools all over " +
        "the floor.\n");
      add_item(({"torch", "torches", "light"}),
        "Attached to the walls with iron clamps are torches burning with "+
        "weak flickering flames, producing more smoke then light but still "+
        "enough just to make the area gloomy instead of pitch black.\n");
      add_item(({"water", "dripping", "drops"}), 
        "Water running down the walls and dripping from the ceiling form small pools " +
        "on the ground. The water looks completely undrinkable.\n");
    break;
    case ROOM_GUARD1:
      add_item(({"wall", "walls"}), 
        "The walls are covered with thick rugs to dampen the echoes and " +
        "give the guards some more hospitable living conditions down here.\n");
      add_item(({"torch", "torches", "light"}),
        "Attached to the walls with iron clamps are torches burning with "+
        "weak flickering flames, producing more smoke then light but still "+
        "enough just to make the area gloomy instead of pitch black.\n");
      add_item(({"floor", "ground"}),
        "This floor is basically covered with strong wooden planks. " +
        "The floor here seems much more cared for than in the corridors. " +
        "Someone must be freaquently cleaning in here. There are no stains, " +
        "no pools of water or anything else you could complain over. The floor " +
        "is partially covered with carpets of various quality.\n");
      add_item(({"carpet", "carpets"}),
        "These are regular carpets woven by the women of Kalaman. They are " +
        "covering the crude wooden planks that make up the floor.\n");
      add_item(({"planks", "plank"}),
        "Regular oak planks that suits well for its purpose to be a floor.\n");
    break;
    case ROOM_GUARD2:
      add_item(({"wall", "walls"}), 
        "The walls have been polished and covered halfway up with large " +
        "pieces of cloth in a dark red colour, to give the room a feeling " +
        "of warmth and to dampen the echoes from the weapons and voices.\n");
      add_item(({"torch", "torches", "light"}),
        "Attached to the walls with iron clamps are torches burning with "+
        "weak flickering flames, producing more smoke then light but still "+
        "enough just to make the area gloomy instead of pitch black.\n");
      add_item(({"floor", "ground"}),
        "This floor is basically covered with strong wooden planks. " +
        "The floor here seems much more cared for than in the corridors. " +
        "Someone must be freaquently cleaning in here. There are no stains, " +
        "no pools of water or anything else you could complain over. The floor " +
        "is partially covered with carpets of various quality.\n");
      add_item(({"carpet", "carpets"}),
        "These are regular carpets woven by the women of Kalaman. They are " +
        "covering the crude wooden planks that make up the floor.\n");
      add_item(({"planks", "plank"}),
        "Regular oak planks that suits well for its purpose to be a floor.\n");
      add_item(({"bunks", "bunk beds", "beds"}), 
        "These are regular bunk beds with a steel frame, wooden bottoms and " +
        "a mattress that seems well filled with hey. Each bed has a small pillow " +
        "and a big blanket on it. They look suprisingly quite comfortable " +
        "and nice to sleep in.\n");
    break;
    case ROOM_CELL1:
      add_item(({"wall", "walls"}), 
        "Cut out straight from the massive rock, they reate the most " +
        "perfect of prision walls, unpenetrateble, unmovable, totally " +
        "safe. The water that drips down them from the ceiling also " +
        "adds to the very unpleasent feeling of this cell. Attached to " +
        "the one of the walls are some rigid steel chains.\n");
      add_item(({"rock","rocks", "floor", "ground"}),
        "The floor is covered with small rocks, most likely pieces of the ceiling or " +
        "the walls.\n");
      add_item(({"cell", "cells"}),
        "Through the bars you see the other cell across the corridor.\n");
      add_item(({"pool","pools"}),
        "A small pool of extremly putrid water; filled with tiny remnants of " +
        "dead insects.\n");
      add_item(({"torch", "torches", "light"}),
        "Across the corridor you can see toches attached to the wall with some " +
        "type of clamps. The torches burning with weak flickering flames, " +
        "that barely produces enough light to make the cell gloomy instead " +
        "of pitch black.\n");
      add_item(({"water", "dripping", "drops"}), 
        "Water running down the walls and dripping from the ceiling form small pools " +
        "on the ground. The water looks completely undrinkable.\n");
      add_item("bed", "A steel framed bunkbed with wodden bottoms and a very thin " +
        "mattress stuffed with hey has been bolted firmly to the floor and wall.\n");
    break;
    case ROOM_CELL2:
      add_item(({"wall", "walls"}), 
        "These walls are not yet finished, only a little rock has been " +
        "cut off from the rock. Water drips down the walls all the time " +
        "making them cold to the touch.\n");
      add_item(({"rock","rocks", "floor", "ground"}),
        "The floor is covered with small rocks, most likely pieces of the ceiling or " +
        "the walls.\n");
      add_item(({"cell", "cells"}),
        "Across the corridor you see other unfinished cells.\n");
      add_item(({"pool","pools"}),
        "A small pool of extremly putrid water; filled with tiny remnants of " +
        "dead insects.\n");
      add_item(({"water", "dripping", "drops"}), 
        "Water running down the walls and dripping from the ceiling form small pools " +
        "on the ground. The water looks completely undrinkable.\n");
    break;
    case ROOM_CLROW1:
      add_item(({"cell", "cells"}),
        "The cells are basically three crude masssive, water soaked rock walls " +
        "and then strong steel bars have been forced into the sides closest to the " +
        "corridor, forming the fourth wall, giving access only through a massive " +
        "door.\n");
      add_item(({"pool","pools"}),
        "Very dirty and putrid water has formed stinking pools all over " +
        "the floor.\n");
      add_item(({"torch", "torches", "light"}),
        "Attached to the walls with iron clamps are torches burning with "+
        "weak flickering flames, producing more smoke then light but still "+
        "enough just to make the area gloomy instead of pitch black.\n");
      add_item(({"floor", "ground"}),
        "The floor is made out of rough stone bricks and dirt, stomped " +
        "down hard by the years of usage. Here and there are small pools " +
        "of dirty water that drips down from the ceiling and walls.\n");
      add_item(({"water", "dripping", "drops"}), 
        "Water running down the walls and dripping from the ceiling form small pools " +
        "on the ground. The water looks completely undrinkable.\n");
    break;
    case ROOM_CLROW2:
      add_item(({"cell", "cells"}),
        "The cells are not even half finished, most of the steel bars lay on the " +
        "stone floor and most of the doorframes stand against the corridor walls.\n");
      add_item(({"pool","pools"}),
        "Very dirty and putrid water has formed stinking pools all over " +
        "the floor.\n");
      add_item(({"floor", "ground"}),
        "The floor is only half-finished, crudely cut out blocks lay all " +
        "over the ground and several tools of craftmanship together with " +
        "the materials for the cells that are being built here.\n");
      add_item(({"block", "blocks" }),
        "These are massive stone blocks used to produce the inner walls, " +
        "they are usually stacked on top of eachother and then fixated.\n");
      add_item("tools", "These are just normal tools, hammers, chisel and so on.\n");
      add_item(({"water", "dripping", "drops"}), 
        "Water running down the walls and dripping from the ceiling form small pools " +
        "on the ground. The water looks completely undrinkable.\n");
    break;
    default:
  }
}

/* Function: create_dungeon_room
 * Info:     Basic function that starts up the room and sets the various
 *           default descs and such that we want.
 */
void create_dungeon_room()
{
  string long_desc;
  /* Set short and long desc for the room */

  set_short(get_short_desc);

  set_long(get_long_desc);

  add_room_items();

  if ( gType == ROOM_TUNNEL1 || gType == ROOM_TUNNEL1 || 
       gType == ROOM_WELL || gType == ROOM_CLROW2 || gType == ROOM_CELL2 )
  {
      /* ADD DARKNESS */
      DARK;
  }
  else
  {
      /* ADD LIGHT */
      LIGHT;
  }
}

void reset_dungeon_room()
{

}
