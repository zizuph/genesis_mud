inherit "/lib/guild_support";
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void 
create_room()
{
    set_short("A resting chamber");
    set_long("You are in a small chamber. The walls are cold, and "+
    "dark. A small torch burns on the north wall, casting shadows "+
    "across the room. On the ground, you see many kneeling mats.\n");    
    INSIDE;
    add_item("torch","It casts dim light over the room.\n");
    add_item("mats","They look comfortable. You feel like "+
    "meditating on them.\n");
    create_guild_support();
    add_exit("/d/Kalad/common/guilds/shadow_walkers/t12","east",0,-1,1);
}

void
init()
{
   ::init();
   init_guild_support();
}

void
gs_hook_start_meditate()
{
   write("You kneel on the mat and go into a trance.\n");
   say(QCTNAME(TP) +" kneels on the mat and goes into a trance.\n");
}

int
gs_hook_rise()
{
   write("As if ascending from a great depth, you rise to the surface\n" +
      "of your consciousness and rise from the mat.\n");
   say(QCTNAME(TP) + " rises from meditation and rises from the mat.\n");
}
