inherit "/d/Gondor/elessar/anduin/river";

create_room()
{
  rivertype = "river";
  landname = "Gondor";
  cur_str = 78;
  cur_dir = "west";
  up_dir = "northeast";
  rivername = "Anduin";
  add_exit("/d/Gondor/elessar/anduin/testriver5","west",10,"@@do_swim@@");
  add_exit("/d/Gondor/elessar/anduin/testriver1","south",7,"@@do_swim@@");
  make_the_room();
}

