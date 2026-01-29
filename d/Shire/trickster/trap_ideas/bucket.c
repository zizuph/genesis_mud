#pragma strict_types

inherit "/std/object";

#include "/d/Shire/common/defs.h"
#include "/d/Shire/trickster/trickster.h"
#include <filter_funs.h>

#define TIME   300

//  Prototypes
void splash(object player);


string *open_commands = ({});
object door;
string stuff = "water";

void
create_object()
{
    set_name("splash");
    set_no_show();
    add_prop(OBJ_M_NO_GET,1);
}

void
set_up_trap(object door_obj,string *commands, string material)
{
    if (!commands || !door_obj)
    {
	remove_object();
	return;
    }
    door = door_obj;
    open_commands = commands;
    if (material)
	stuff = material;
}

void
init()
{
    int i;

    ::init();
    for (i = 0; i < sizeof(open_commands); i++)
	add_action("my_open",open_commands[i]);
    add_action("disarm","disarm");
    add_action("disarm","remove");
}


int
my_open()
{
    if (door->query_locked())
	return 0;
    write("As you open the "+door->short()+" a bucket of "+stuff+" "+
      "falls from it!\n");
    say("As "+QTNAME(TP)+" opens the "+door->short()+" a bucket "+
      "falls from it!\n");
    set_alarm(0.1,0.0,&splash(TP));
    notify_fail("Open what?\n");
    return 0;
}

void
splash(object player)
{
    object *team = player->query_team_others() + ({player});
    object shadow;
    int i;

    team = FILTER_PRESENT_LIVE(team);

    team->catch_msg("You get splashed with "+stuff+" as the bucket falls.\n");

    for ( i = 0; i < sizeof(team); i++)
    {
	shadow = clone_object(TRICKSTER_BUCKET_SHADOW);
	shadow->set_type(stuff);
	shadow->set_remove_time(TIME);
	shadow->shadow_me(team[i]);
    }
    remove_object();
}
