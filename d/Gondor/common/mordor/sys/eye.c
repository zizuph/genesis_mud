#pragma strict_types
#pragma save_binary
#pragma no_inherit
#pragma no_clone

#include "../defs.h"

private static string *_areas;  // loaded outdoor, mordor area paths

private nomask void
log(string text) {
  write_file(MORDOR_LOG + "eye", ctime(time()) + " :: " + text + "\n");
}

private nomask object
locate_room(string path == "") {
  string *room_paths;
  int x, sz;
  if (!stringp(path) || !strlen(path)) {
    if (!(sz = sizeof(_areas)))
      return (0);
    path = _areas[random(sizeof(_areas))];
  }
  room_paths = get_dir(path);
  if (!(sz = sizeof(room_paths)))
    return (0);
}

// Method  : create
// Remarks : Constructor.

public nomask void
create() {
  setuid();
  seteuid(getuid());
}
