inherit "/std/room";
inherit "/d/Gondor/open/HERBS/herbsearch";

#include "../garden.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include <wa_types.h>

#define DEBUG_WHO this_interactive()
#define DEBUG_ON
#include "/d/Emerald/sys/debug.h"

static mixed *exit_info  = ({ });
static int *plant_growth = ({ });
static int num_nasties  = 5;
static int random_herbs = 0;

varargs int add_garden_exit(int chance, string place, string cmd, 
                            mixed efunc, mixed tired)
{
    if (!place || !cmd)
    {
        return 0;
    }
  
    plant_growth += ({ 0 });
    exit_info += ({ ({ chance, place, cmd, efunc, tired }) });
}

mixed *query_exit_info() { return exit_info; }

void reset_garden_room() { }

void reset_room()
{
    int r;
    string *available_herbs, this_herb;

    /* reset the exits */
  
    plant_growth = allocate(sizeof(exit_info));
  
    if (sizeof(exit_info))
    {
        remove_prop(ROOM_I_NO_EXTRA_EXIT);
        for_each(exit_info, remove_exit @ &operator([])(, 2));
    
        /* yeah, this is going overboard, but one-liners are such fun ;) */
        for_each(filter(exit_info, not @ random @ &operator([])(,0)),
            &applyv(add_exit) @ &slice_array(, 1, 4));
        add_prop(ROOM_I_NO_EXTRA_EXIT, 1);
    }

    /* reset herbs */
  
    set_searched(3);
  
    setuid();
    seteuid(getuid());
  
    /* replace an herb */

    if (sizeof(herbs) && !random(10) &&
        (random_herbs > 1) &&
        sizeof(available_herbs = get_dir(POISON_GARDEN_RAND_HERB)))
    { 
        r = random(sizeof(herbs));
        herbs = exclude_array(herbs, r, r);
        set_up_herbs(POISON_GARDEN_RAND_HERB + 
            available_herbs[random(sizeof(available_herbs))]);
    }
     
    reset_garden_room();
}

void create_garden_room() { }

void create_room()
{
    string *available_herbs;
    int herbs_to_add;

    add_item("plants", "An amazing amount of plantlife fills every meter " +
        "of the surrounding area.  While many of the plants look slightly " +
        "familiar, they are all somehow strange...twisted and almost " +
        "ominous.\n");

    add_prop(ROOM_I_LIGHT, 2);
    add_prop("_room_i_sunlight", 25);

    create_garden_room();

    if (herbs_to_add = random(random_herbs) &&
        sizeof(available_herbs = get_dir(POISON_GARDEN_RAND_HERB)))
    {
        while (herbs_to_add--)
        {
            set_up_herbs(POISON_GARDEN_RAND_HERB + 
                available_herbs[random(sizeof(available_herbs))]);
        }
    }

    reset_room();
}

int
unq_no_move(string str)
{
    notify_fail("The plants have grown too thick in that direction; " +
	"you can't get past them.\n");
    return 0;
}

int cut(string str)
{
    string where, what, verb;
    int i;
    object *whatlist, *slash;
  
    if (!strlen(str))
    {
        return 0;
    }
  
    verb = capitalize(query_verb());
    if (sscanf(str, "%s with %s", where, what) != 2)
    {
        notify_fail(verb + " where with what?\n");
        return 0;
    }
  
    if (!parse_command(what, this_player(), "[the] %i", whatlist) ||
	!sizeof(whatlist = NORMAL_ACCESS(whatlist, 0, 0)))
    {
        notify_fail("You don't have one of those.\n");
        return 0;
    }
  
    if (!parse_command(where, ({ }), "[down] / [up] / [through] [the] " +
	"%w [plants] / [vines]", where))
    {
        notify_fail(verb + " what?\n");
        return 0;
    }
  
    if (!sizeof(slash = filter(whatlist, 
	&operator(&)(W_SLASH) @ &->query_dt())))
    {
        if (sizeof(whatlist) > 1)
        {
	  write("None of that would be very useful for cutting plants.\n");
  	  return 1;
        }
      
        write("That wouldn't be very useful for cutting plants.\n");
        return 1;
    }
  
    if (member_array(where, ({ "north", "south", "east", "west",
	"northeast", "northwest", "southeast", "southwest" })) < 0)
    {
        notify_fail(verb + " which plants?\n");
        return 0;
    }
  
    if (member_array(where, query_exit_cmds()) >= 0)
    {
    	write("You take a swipe at some plants to the " + where + ".\n");
    	say(QCTNAME(this_player()) + " takes a few swipes at some plants " +
	    " to the " + where + " with " + this_player()->query_possessive() +
	    slash[0]->short() + ".\n");
    	return 1;
    }
  
    write("You hack at the plants with your " + slash[0]->short() + ".\n");
    say(QCTNAME(this_player()) + " hacks at the plants with " + 
	this_player()->query_possessive() + slash[0]->short() + ".\n");
  
    slash[0]->set_dull(slash[0]->query_dull() + 1);    
  
    for (i = 0; i < sizeof(exit_info); i++)
    {
    	if (exit_info[i][2] == where)
    	{
	    if (slash[0]->query_prop(OBJ_I_BROKEN))
	    {
	        plant_growth[i] += random(slash[0]->query_pen() / 25 + 1);
	    }
	    else
	    {
	        plant_growth[i] += random(slash[0]->query_pen() / 10 + 1);
	    }
       
	    if (plant_growth[i] > 10)
	    {
	    	write("You manage to cut back enough of the plants to " +
		    "make your way " + where + ".\n");
	    	remove_prop(ROOM_I_NO_EXTRA_EXIT);
	    	applyv(add_exit, exit_info[i][1..]);
	    	add_prop(ROOM_I_NO_EXTRA_EXIT, 1);
	    	return 1;
	    }
      
	    return 1;
    	}
    }
    
    return 1;
}
  
void init_garden() { }

void init()
{
    ::init();
  
    add_action(cut, "hack");
    add_action(cut, "cut");
    add_action(cut, "chop");
  
    init_garden();
}

void set_monster_number(int n) { num_nasties = MAX(0, n); }

int query_monster_number() { return num_nasties; }

void set_random_herbs(int n) { random_herbs = n; }

int query_random_herbs() { return random_herbs; }

void enter_inv(object ob, object from)
{
    object picker_upper, *plants;
  
    ::enter_inv(ob, from);
  
    if (ob->query_no_show()) 
    {
        return;
    }
  
    if (sizeof(plants = filter(all_inventory(), &->query_plant_base())))
    {
        picker_upper = plants[random(sizeof(plants))];
        set_alarm(itof(random(3) + 1), 0.0, &picker_upper->pick_it_up(ob));
    }
}
