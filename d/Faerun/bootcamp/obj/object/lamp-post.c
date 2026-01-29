inherit "/std/object.c";
inherit "/cmd/std/command_driver";
inherit "/std/act/action";
 
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <const.h>
#include <filter_funs.h>
#include <language.h>
#include <living_desc.h>

#define TP        this_player()
#define TO        this_object()
#define QPO       query_possessive()
#define QPR       query_pronoun()
#define QBJ       query_objective()
#define QCTP      QCTNAME(this_player())

int light_post(string str);
int extinguish_post(string str);

void
create_object()
{
    set_name("lamp-post");
	
	add_cmd_item(({ "lamp-post" }), ({ "touch lamp-post" }), ({ "You touch the lamp-post.\n" }));

set_long("This is a tall, black lamp-post. " +
    "Six small wicks are set inside the casing.\n");
	set_adj("light-post");
}			
public int
do_enter(string str)
{
    if(!strlen(str))
    {
        notify_fail("What did you wish to enter?\n");
        return 0;
    }

    if (!parse_command(str, ({}),
        " [in] [enter] [the] [solid]"
      + " [black] 'lamp-post'"))
    {
        notify_fail("Enter what? The lamp-post?\n");
        return 0;
    }

    write("The lamp-post swivels to the right and reveals an entrance set " +
         "into the earth.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " arrives\n");
    tell_room(PATH, QCTNAME(this_player()) + " arrives\n");
    this_player()->move_living("M", PATH, 1, 0);
    return 1;
}