inherit "/d/Gondor/elessar/anduin/river";

create_room()
{
  rivertype = "river";
  landname = "Gondor";
  cur_str = 85;
  cur_dir = "southwest";
  up_dir = "north";
  rivername = "Anduin";
  add_exit("/d/Gondor/elessar/anduin/testriver1","north",10,"@@do_swim@@");
  add_exit("/d/Gondor/elessar/anduin/testriver3","southwest",7,"@@do_swim@@");
  make_the_room();
}
