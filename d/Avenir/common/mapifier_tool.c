#include <macros.h>
inherit "/std/object";
inherit "/lib/keep";
#define MAP_CENTRAL "/secure/map_central"
#define NEW_MAP 1
#define MAP_DATA 2
#define MAP_ART 3
#define TP this_player()
void
create_object ()
{
  ::create_object();
  set_short("Portable map controller");
  set_long("Tool that works with the map controller room, made by Tapakah.\n"+
      "Try <mapify>");
  set_name("mapifier");
}
void
do_mapify (string map_file, string dir)
{
  string line;
  int line_num = 1;
  int flag = NEW_MAP, x, y;
  int to_remove = 0;
  string file, file_c;
  string debug_command;
  string sea_type;
  object room;
  
  setuid();
  seteuid(getuid());
  write("Reading " + map_file + "\n");
  while ((line = read_file(map_file, line_num, 1)) && line_num < 1000) {
    line_num++;
    if (line == "::NEW_MAP::\n") {
      flag = NEW_MAP;
    }
    else if (line == "::MAPDATA::\n") {
      flag = flag == NEW_MAP ? MAP_DATA : MAP_ART;
    }
    else {
      if (flag != MAP_DATA)
        continue;
      if (! sscanf(line, "%s %d %d", file, x, y) == 3) {
        TP->catch_msg("Skipping badly formatted line " + (line_num-1) + ":" +
                      line);
        continue;
      }
      file = dir + "/" + file;
      file_c = file + ".c";
      if (room = find_object(file))
        room->init_map_update();
      if (file_size(file_c) < 1) {
        if (room)
          room->remove_object();
        sea_type = file[-1..-1];
        write_file(file_c,
                   sprintf("inherit \"/d/Khalakhor/ocean/sea-%s\";\n",
                           sea_type)
                   );
        TP->catch_msg("Wrote " + file_c + "\n");
        to_remove = 1;
      }
      else if (file_size(file_c) < 40) {
        if (room)
          room->remove_object();
        to_remove = 1;
      }
      if (LOAD_ERR(file_c)) {
        TP->catch_msg(sprintf("Stumbled over %s, aborting.\n", file_c));
        return;
      }
      debug_command = "Processed " + file_c;
      TP->catch_msg(debug_command + ";\n");
      MAP_CENTRAL->add_maplink(file, map_file);
      file->init_map_update();
      if (to_remove) {
        TP->catch_msg("Removing " + file_c + "\n");
        rm(file_c);
        to_remove = 0;
      }
    }
  }
}
int
mapify (string str)
{
  string map_file, dir;
  if (!str) {
    notify_fail("Usage: mapify MAP-FILE DIR\n");
    return 0;
  }
  if (sscanf(str, "%s %s", map_file, dir) != 2) {
    notify_fail("Usage: mapify MAP-FILE DIR\n");
    return 0;
  }
  if (file_size(map_file) <= 0) {
    notify_fail("File " + map_file + " is not a proper file.\n");
    return 0;
  }
  do_mapify(map_file, dir);
  return 1;
}
void
init ()
{
  ::init();
  add_action(mapify, "mapify");
}

