inherit "/d/Gondor/elessar/anduin/river";

create_room()
{
  ::create_room();
  rivertype = "river";
  landname = "Gondor";
  cur_str = 64;
  cur_dir = "south";
  up_dir = "north";
  shore = ({"west"});
  rivername = "Anduin";
  add_exit("/d/Gondor/elessar/anduin/testriver2","south",7,"@@do_swim@@");
  add_exit("/d/Gondor/elessar/workroom","west",0,"@@do_swim@@");
  add_exit("/d/Gondor/elessar/anduin/testriver6","north",10,"@@do_swim");
  make_the_room();
}
