After new rooms are loaded into the whatchamacalit so they are 
dynamically created:
Clone a ship, sail to the room, go out of the ship, and do something like this:
execr "/secure/map_central"->add_maplink("/d/Avenir/common/sea/room/sea-0-0-i", "/d/Avenir/open/MAP_FILES/sailing_rooms_sea.txt");
   where the add_maplink room is the path of the new room being added to the magic map.

And then afterwards you call:
Call here init_map_data
