
/* 
   Include file for resetting a boat with fishermen.
   Room file is responsible for including water.h and sea_defs.h
   too.
*/ 

object boat, fisherman; 

void
reset_room()
{
     object f, boat_in;

     if (!objectp(boat)) { 
          boat = clone_object(SEA_OBJECTS+"rower"); 
          boat->move(this_object()); 
     }

     if (!objectp(boat_in = boat->query_boat_in())) { 
         boat->config_boat_inside(); 
         boat_in = boat->query_boat_in(); 
     }

     if (!objectp(fisherman)) { 
         fisherman = clone_object(SEA_CREATURES+"fisherman"); 
         fisherman->arm_me(); 
         fisherman->move_living("into his boat", boat_in); 
         f = clone_object(SEA_OBJECTS+"little_fish"); 
         f->set_heap_size(10 + random(25)); 
         f->set_owner(fisherman); 
         f->move(boat_in); 
         boat_in->set_owner(fisherman); 
     }
}

