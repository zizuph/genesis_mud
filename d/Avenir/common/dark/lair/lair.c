//-*-C++-*-
// Part of the worm lair.
// Made by Boriska
// Here the master worm resets and clones all body parts.
// Worm healing rate and period is set in make_worm() function.
// Descriptions by Ilyian

inherit "/d/Avenir/common/dark/lair/lair_common";

#include "/d/Avenir/common/dark/dark.h"
#include "/d/Avenir/include/worm.h"

static object master_worm = 0;

void
reset_room()
{
    if (!objectp(master_worm))
        set_alarm (30.0, 0.0, "make_worm");
    // we're not hasty
}

void
create_room ()
{
    ::create_room();
    set_short ("in the worm lair");
    set_long ("The round tunnel seems to widen a bit here. The lava "+
        "at your feet glows yellow-red, sending stifling fumes into "+
        "the air. You can almost feel a gentle, rhythmic thumping in "+
        "the tunnel around you, as if the very heart of the world were "+
	"near.\n");
  
    set_tell_time (120);
    add_tell ("You hear a strange sound, like loud but distant sigh.\n");
    add_tell ("Part of stalactite above your head suddenly falls down, "+
	"narrowly missing you!\n");
    add_tell ("You hear low scraping sound, like rough paper against "+
        "rock.\n");
    add_tell ("The earth trembles slightly.\n");
    add_tell ("Your blood freezes as you hear a distant shriek of agony!\n");
    add_tell ("Suddenly a wave of hot air envelopes you!\n");
    reset_room();
}

private void
make_worm()
{
  string *locs = ({ LAIR + "lair",
		    LAIR + "l3",
		    LAIR + "l4" });
  
  string *parts = ({ MON + "worm_head",
		     MON + "worm_body",
		     MON + "worm_tail" });
  
  master_worm = clone_object (MON + "master_worm");
  
  if (!master_worm->move(this_object()) &&
      master_worm->create_worm( locs, parts ))
    {
      // all parts cloned and moved in their rooms OK
      // heal every 30 sec
      master_worm->set_heal_delay (30.0 );
      master_worm->set_heal_rate ( 6 );
    }
}

public object
query_master_worm () { return master_worm; }

