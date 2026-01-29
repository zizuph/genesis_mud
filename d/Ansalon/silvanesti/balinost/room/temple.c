
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include "/d/Ansalon/silvanesti/balinost/local.h"
#include <macros.h>

inherit BALINOST_IN;
inherit "/lib/guild_support";

reset_balinost_room()
{
    return;
}


create_balinost_room()
{
    set_short("Temple of E'li");
    set_long("This temple was built in honour of E'li, more commonly "+
      "known as Paladine.  Though the temple hasn't been used much "+
      "since the Cataclysm, a few devout followers have kept it in "+
      "use for the past 350 years.  Rumors of the gods returning to "+
      "Krynn had the temple busier than usual up until the "+
      "Dragonarmies attacked.  It is barely used now since the "+
      "population now resides elsewhere.\nAn altar stands at the "+
      "front of the temple, and there are still a few cushions around "+
      "upon which you can meditate.\n");

    add_exit(BROOM + "street14","west",0);
    add_prop(ROOM_M_NO_ATTACK,"E'li keeps peace in his temple.\n");
}

void
init()
{
    ::init();
    init_guild_support();
    add_action("gs_meditate","meditate");

}

void
gs_hook_start_meditating()
{
    write("You choose one of the cushions nearby and sit comfortably "+
      "upon it.  Letting yourself relax, you tap into your deepest "+
      "self.  You breathe in deeply, hold your breath for a short "+
      "moment, then release the air slowly from your lungs.  You "+
      "think the true gods may be closer than the world knows.\n");
    say(QCTNAME(TP)+" sits down on a cushion and begins to meditate.\n");
}

void
gc_hook_rise()
{
    write("You breath in deeply once more, but this time let the air "+
      "rush out.  You open your eyes and examine your surroundings.  "+
      "You stand from the cushion and stretch.  You feel the true "+
      "gods of Krynn are with you.\n");
    say(QCTNAME(TP)+" stands up looking more confident than before.\n");
}
