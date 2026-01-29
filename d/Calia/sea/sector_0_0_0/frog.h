
/* 
   Include file for resetting a frog.
   Room file is responsible for including water.h and 
   sea_defs.h too.
*/ 

object frog; 

void
reset_room()
{
     if (!objectp(frog)) { 
         frog = clone_object(SEA_CREATURES+"bluefrog"); 
         frog->move_living("into the sea", this_object()); 
     }
}

