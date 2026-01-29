#pragma no_clone
#pragma no_inherit
#pragma strict_types

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"

void
create_object()
{
  set_name("_mirkwood_clearer_");
  set_no_show();
  add_prop(OBJ_I_INVIS, 100);
  add_prop(OBJ_S_WIZINFO,
	"You can clear mirkwood directory " +
	"from the unnecessary files. If you want to do this you should do:\n"+
        "   cd /d/Rhovanion/common/mirkwood\n"+
        "   Call mirkwood_clearer clear_mirkwood_directory\n"+
        "Note that this removes max 200 files in one go so you may need "+
        "to call this function more than once\n");
}

void
clear_mirkwood_directory()
{
  string  *files, *subdirs, tmp;
  int     i, s;

  setuid();
  seteuid(geteuid());

  files = get_dir(MIRK_DIR+"*");
  if(!sizeof(files)) return;
  files = files - ({ ".", ".." });
  if(!sizeof(files)) return;

  subdirs = ({ });
  for (i = 0 ; i < sizeof(files) ; i++)
    if(file_size(MIRK_DIR + files[i]) == -2)
      subdirs += ({ files[i] });
  if(sizeof(subdirs)) files = files - subdirs; 
  if(!sizeof(files)) return;

  for (i = 0 ; i < MIN(200, sizeof(files)) ; i++)
  {
    tmp = read_file(MIRK_DIR + files[i], 1, 3);
    if(sizeof(explode(tmp, "\n")) == 1)
    {
      rm(MIRK_DIR + files[i]);
    }
  }
  set_alarm(0.0, 0.0, "remove_object");
} 
