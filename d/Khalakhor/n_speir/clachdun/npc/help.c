/* A lib file for guards and other npcs that
 * call for assistance.
 */

#include <stdproperties.h>
#include <macros.h>
#include "local.h"
#include "/d/Khalakhor/sys/defs.h"

// Protoypes
void go_away(object ob);
void go_home();


static int is_helper;
static mapping move_opposite = ([
  "north" : "south",
  "northeast" : "southwest",
  "east" : "west",
  "southeast": "northwest",
  "south" : "north",
  "southwest": "northeast",
  "west" : "east",
  "northwest" : "southeast",
  "in" : "out",
  "out": "in",
]);

void
go_and_help(object ob)
{
    int pos;

    if (this_object()->query_attack())
	return;
    if (!objectp(ob) || !environment(ob))
	return;

    if (environment(ob) == environment(this_object()))
    {
	this_object()->command("assist "+OB_NAME(ob));
	return;
    }
    pos = member_array(file_name(environment(ob)) ,
      environment(this_object())->query_exit_rooms());

    if (pos == -1)
	return;
    this_object()->command("shout "+ ONE_OF(({"Help is on the way!",
	  "Hold steadfast, I shall aid ye!", "Hold on help is coming.",
	  "Do not worry, I shall apprehend the blasted troublemaker!"})));
    this_object()->command(environment(this_object())->query_exit_cmds()[pos]);

    if (!ob->query_attack())
    {
	set_alarm(itof(random(3) + 1), 0.0, &go_away(ob));
	return;
    }
    
    this_object()->command("assist "+OB_NAME(ob));
    set_alarm(60.0, 0.0, go_home);
}

void
delayed_help(object ob)
{
    set_alarm(itof(random(3)), 0.0, &go_and_help(ob));
}

void
go_home()
{
    if (objectp(present(this_object()->query_attack(),
                        environment(this_object()))))
    {
        set_alarm(itof(random(20) + 25), 0.0, go_home);
        return;
    }
    this_object()->command(ONE_OF(({"grumble", "sigh", "snore"})));
    if (!random(7))
        this_object()->command("say Soooo bored.");
    if(!random(4))
        this_object()->command("say Well time to head back to "+
                               "me post.");
    this_object()->command(move_opposite[
	this_object()->query_prop(LIVE_S_LAST_MOVE)]);    
}

        
void
go_away(object ob)
{
    this_object()->command(ONE_OF(({"grumble", "sigh", "spit", "swear"})));
    this_object()->command("say " +ONE_OF(({"You dragged me from "+
	  "my post for this??",
	  "Do not cry wolf again "+ob->query_nonmet_name()+", or I may "+
	  "not come to protect ye.", "I should have called in sick, I "+
	  "had a feeling it would be one of these blasted days."})));
    this_object()->command(move_opposite[
	this_object()->query_prop(LIVE_S_LAST_MOVE)]);
}

void
get_assistance()
{
    object *rooms, *helpers;
    int i;

    if (!environment(this_object()))
	return;

    if (!sizeof(environment(this_object())->query_exit_rooms()))
	return;

    rooms = ({environment(this_object())});
    rooms += map(environment(this_object())->query_exit_rooms(), find_object);
    rooms = filter(rooms, objectp);

    if (!sizeof(rooms))
	return;

    i = -1;
    while(++i < sizeof(rooms))
    {
	helpers = filter(all_inventory(rooms[i]), &->query_helper());
	helpers->delayed_help(this_object());
    }
}

int
query_calchdun_guard()
{
    return 1;
}

int
query_helper()
{
    return is_helper;
}

void
set_helper() 
{
    is_helper = 1;
}

void
cry_for_assistance(object attacker, int agressive)
{
    if (!CAN_SEE_IN_ROOM(this_object()) || !CAN_SEE(this_object(), attacker))
    {
	if (!agressive)
	    this_object()->command("shout Help!! Guards!! I'm being attacked "+
	      "by someone.");
	set_alarm(itof(random(3) + 1), 0.0, get_assistance);
	return;
    }
    if (!agressive)
	this_object()->command("shout "+ ONE_OF(({"Help!! Help!! Guards!!!",
	      "Guards! Guards! I'm being attacked by a blasted "+
	      LANG_ADDART(attacker->query_nonmet_name()) +"!", 
	      "Invaders in Clach Dun!! Aid me!!"})));
    set_alarm(itof(random(3) + 1), 0.0, get_assistance);
}

int
query_not_attack_me(object who, int aid)
{
    object *helpers;

    if (random(7))
	return 0;
    helpers = filter(all_inventory(environment(this_object())),
      &->query_helper());
    helpers = filter(helpers, &->query_attack() @ &not());

    if (sizeof(helpers))
	helpers->go_and_help(this_object());

    return 0;
}
