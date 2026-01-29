inherit "/d/Emerald/ctower/room/ctower_base";
 
#include "/d/Emerald/defs.h"
#include <stdproperties.h>
#include "../../ctower.h"
 
void
create_ctower_room()
{
    set_short("Reflection canyon");
   
    set_long("You stand in a crystal canyon, bedazzled by the "+
	"brilliant display of colors\nbefore you.  The rocky ground must "+
	"contain thousands of crystals of every\nshape, size and color "+
	"imaginable.  Rainbows seem to dance and shimmer in the\nvery air "+
	"you breathe, and the ground thrums with power.\n");
   
    add_item(({"crystal", "crystals", "ground"}), "The crystal doesn't "+
	"seem to be individual pieces but rather facets of a larger whole."+
	"\n" );
   
    add_exit(PATH_DIR + "entrance", "back", "@@back@@");
   
    add_prop(ROOM_I_LIGHT, 8);
}
 
int
back()
{
    write( "You return, following the path that "+
        "lead you here.\n" );
    return 0;
}
 
void fade(object who)
{
    say(QCTNAME(this_player()) + " slumps " +
	"to the ground, sparkles and fades out of sight!\n");
   
    this_player()->move_living("M", CTOWER_ROOM_ENTRY + "pointnight", 1);

    tell_room(CTOWER_ROOM + "pointnight", QCTNAME(this_player()) +
        " fades into view.\n", this_player());
}
 
int
sleep(string arg)
{
    if (strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
     
    if (!CTOWER_MANAGER->register_quester(this_player()))
    {
        write("You doze off for a moment, but awaken shortly.\n");
        this_player()->command("$snore");
        return 1;
    }

    write("You doze off and when you awaken you find "+
	     "yourself in a different--yet strangely similar--place.\n" );
   
    fade(this_player());
   
    return 1;
}
 
void pass_out(object who)
{
    if (!present(who))
    {
        return;
    }
 
    if (!CTOWER_MANAGER->check_ctower_entrance(who))
    {
        set_alarm(600.0, 0.0, &pass_out(who));
        return;
    }

    write("Suddenly you become very lightheaded....\n\nWhen you awake, " +
        "you find yourself in a different, yet strangely familiar place.\n\n");
 
    fade(who);
}
 
void
init()
{
  ::init();
 
  set_alarm(300.0, 0.0, &pass_out(this_player()));
 
  add_action(sleep, "sleep");
  add_action(sleep, "wait");
}

int
query_inside_ctower()
{
    return 0;
}
