inherit "/std/workroom";

create_workroom()
{
  set_short("Janus's workroom");
  set_long("Janus is now finished with a grandiose description \n"
    + "that takes your breath away. \n GASP \n");
  add_exit("/d/Genesis/wiz/entrance", "news", 0);
  add_exit("/d/Genesis/wiz/post", "post", 0);
  add_exit("/d/Terel/workroom", "meet", 0);
  add_exit("/d/Terel/common/town/t_hall", "hall", 0);
  add_exit("/d/Terel/common/town/mansion/grd/ogrd1","oldgarden",0);
  add_exit("/d/Terel/janus/garden/garden2", "garden", 0);
  add_exit("/d/Terel/mecien/valley/guild/post","mpost",0);
  add_exit("/d/Terel/mecien/valley/guild/chancery", "mboard", 0);
  add_exit("/d/Terel/cedric/guild/entrance", "minstrel", 0);
   add_exit("/d/Terel/common/road/cornerstone", "cornerstone", 0);
}
