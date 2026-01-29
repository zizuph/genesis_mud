inherit "/std/room";
 
#include "/d/Emerald/defs.h";
 
object eagle;
 
void reset_room();
int do_climb(string str);
 
void
create_room()
{
   object ob;
 
   set_short("Shelf in eastern wall");
   set_long("You are standing on a ledge just down from "+
         "the top of Mount Black. The shelf is covered with boulders and "+
         "rocks that have fallen. Atop one boulder is a "+
         "large nest. You can see the skies quite easily here as "+
         "the fog seems to have dispersed.\n");
 
   add_exit(MBLACK_DIR + "east_edge", "up", 0);
 
   add_item("nest", ("The nest is sitting on top of a smooth "+
         "grey boulder. It seems to belong to an eagle.\n"));
   add_item(({"rock", "boulder"}), ("This large boulder has "+
         "a nest atop it.\n"));
    add_item(({"sky", "skies"}), ("@@my_sky"));
   add_item(({"rocks", "boulders"}), ("The rocks are strewn "+
         "along the ledge. Fortunately it looks like they "+
         "can help you get back up to the top of the mountain.\n"));
   add_item("nest", "The nest is sitting atop a rock.\n");
   reset_room();
}
 
string
my_sky()
{
    if(eagle)
     return "The eagles are flying around and watching you carefully.\n";
    else
    return "The skies are empty and blue.\n";
}
 
void
init()
{
   ::init();
   add_action(do_climb, "climb");
}
 
int
do_climb(string str)
{
    notify_fail("Climb what?\n");
    if (!str)
        return 0;
    if (str == "rocks" || str == "boulders")
    {
        write("Which one? If you want to go up just do that.\n");
        return 1;
    }
    if (str == "rock" || str == "boulder")
    {
        write("If you are trying to climb into the nest just say so.\n");
        return 1;
    }
    if (str == "into nest" || str == "nest")
    {
        write("You climb up into the nest.\n");
        TP->move_living(" into the nest.", MBLACK_DIR + "nest", 1);
        return 1;
    }
    return 0;
}
 
 
void
update_large_eagle()
{
   object eagle;
   int i;
 
   /* Changed path from ~Emerald/halgor/ to this. Hope i did right
         thing. SN */
   eagle=clone_object(MBLACK_DIR + "npc/large_eagle");
   eagle->move_living("into a room",this_object());
   /* They were in halgor dir... and where are these babies now? SN
   for (i=0 ; i<2 ; i++)
   {
      eagle=clone_object(MBLACK_DIR + "npc/babyeagle");
      eagle->move_living("into a room",this_object());
   }
  */
}
 
void
reset_room()
{
   if (!eagle)
      update_large_eagle();
   if (eagle)
      return;
   eagle=clone_object(MBLACK_DIR + "npc/mother_eagle");
   eagle->move_living("into a room",this_object());
}
