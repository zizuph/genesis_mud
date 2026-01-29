
/* 
   Include file for resetting a angel fish.
   Room file is responsible for including water.h and 
   sea_defs.h too.
*/ 

object fish; 
object fish2;
object fish3;

void
reset_room()
{
    if (!objectp(fish))
    {
         fish = clone_object(SEA_CREATURES+"fish"); 
         fish->move_living("into the sea", this_object()); 
    }
    if (!objectp(fish2))
    {
        fish2 = clone_object(SEA_CREATURES+"fish");
        fish2->move_living("into the sea", this_object());
    }
    if (!objectp(fish3))
    {
        fish3 = clone_object(SEA_CREATURES+"fish");
        fish3->move_living("into the sea", this_object());
    }
}

