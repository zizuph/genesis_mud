inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"

create_room()
{
   set_short("A dim bedroom in a cottage.");
    set_long("In this dim bedroom, you cannot make out many details, "+
   "though you can see a large bed placed carefully in the corner. "+
   "Towels are spread around the bed, a bowl rests on the floor beside them. "+
   "The main room of the cottage is back east.\n");

   add_item(({"bedroom","bed","corner","towels","bowl","floor"}),
   "This bedroom is obviously for a very ill person. The towels are soaked in some "+
   "sort of medicinal concoction, but now the bowl is empty. "+
   "In the corner, you think you see an old sick man, apparently on his deathbed.\n");

   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_LIGHT,0);

   add_exit("/d/Shire/common/hobbiton/in_house","east",0,1);
}

/*
void
reset_room()
{
    add_stuff();
}

void
add_stuff()
{
   object man;

   if(!present("man"))
   man = clone_object("/d/Shire/common/hobbiton/npc/dyingman");
   man->move(TO);

}
*/
