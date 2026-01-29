inherit "/std/room";   

public void
create_room()
{
    ::create_room();
   add_item(({"marble","marble flooring","flooring","floor"}),"The floor is "
   + "covered in beautiful marble tiles. It shines brightly and it appears "
   + "to be well kept and clean. It has carpet leading to every exit.\n");

   add_item(({"candle","candles"}),"These candles are long white candles "
   + "which dimly light the room.\n");

   add_item(({"holder","candle holder"}),"The candle holder is brass with "
   + "a swirling brass design which has been tacked to the wall.\n");

   add_item(({"holders","candle holders"}),"These candle holders are placed "
   + "stratigically across the room on each wall to illuminate the rooms "
   + "warm red colors which seem to make this a cozy but elliquent area.\n");

   add_item(({"chandeliers","brass chandeliers"}),"There is only one brass "
   + "chandelier in this room.\n");

   add_item(({"chandelier","brass chandelier"}),"Large and extravagant, this "
   + "fine piece of work has been polished and well kept. It hangs above from "
   + "the ceiling and looks like a lot of trouble to maintain.\n");

   add_item(({"picture","pictures"}),"The paintings seem to all portray some "
   + "far off place. Mostly, they are of gardens, lakes and rolling hill " 
   + "scenes\n");
}

