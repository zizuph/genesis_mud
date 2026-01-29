inherit "room/room";

reset(arg) {
    if (arg) return;

    set_light(1);
    short_desc = "The farm in the plain";
    no_castle_flag = 0;
    long_desc = 
       "You have entered the yard of a farm. The farm itself is\n"
     + "small and has a small round door and round windows. All\n"
     + "these signs indicate that a hobbit must live in this farm.\n"
     + "To the south is the main entrance of the farm. The smell\n"
     + "of manure comes out of a barn to the east. To the north\n"
     + "the fields gradually change into the surrounding plain.\n";
    dest_dir = 
      ({
       "players/Shire/common/hobbiton/heckenhoch3", "north",
       "players/Shire/common/hobbiton/farm1", "south",
       "players/Shire/common/hobbiton/farm2", "east",
      });
}

query_light() { return 1; }

query_room_maker() { return 101; }

/*
 make your additions below this comment, do NOT remove this comment
--END-ROOM-MAKER-CODE--
*/
