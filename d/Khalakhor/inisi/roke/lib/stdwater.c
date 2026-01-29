/*
 * stdwater.c
 *
 * Standard water room
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

inherit "/std/room";

#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include <stdproperties.h>

/* The heal-rate when you are stuffed */
#define FHEALMAX (F_FATIGUE_FORMULA(1,1)*60/F_INTERVAL_BETWEEN_FATIGUE_HEALING)
/* The heal-rate when you are starved */
#define FHEALMIN (F_FATIGUE_FORMULA(0,1)*60/F_INTERVAL_BETWEEN_FATIGUE_HEALING)

/* The default swim-skill needed to swim without fatigue-loss */
#define SWIMEASILY 40
/* The max fatigue reduce i.e when swim_skill=0 */
#define MAXFLOSS (FHEALMAX*2)
/* The default max fatigue reduce when swimming from one room to another */
#define MAXFSWIM 15

/* The default ftobetired-level */
#define FTOBETIRED 40
/* The default ftodrown-level */
#define FTODROWN 3

/* How much to reduce fatigue per heartbeat, based on swim-skill */
#define FLOSS(swim) \
(((swim)<swimeasy ? MAXFLOSS*(swimeasy-(swim))/swimeasy : 0)*howhard/100/30)

/* How much to reduce fatigue when swimming from one room to another */
#define FSWIM(swim) \
((swim)<swimeasy ? swimbetween*(swimeasy-(swim))/swimeasy : 0)

int ftodrown; /* when fatigue is below this drown() is called */
int ftobetired; /* when fatigue is below this obj_is_tired() is called */
int howhard; /* how hard to swim on the spot, 100 is normal */
int swimeasy; /* swim-skill when you swim without f-loss */
int swimbetween; /* how much f to reduce when swimming between rooms */
mixed apa = ({});

void set_f_to_drown(int f);
void set_f_to_be_tired(int f);
void set_how_hard_to_swim(int f);
void set_swim_easy(int f);
void set_swim_between(int f);
void red_fati(object obj);
void obj_is_tired(object obj);
void drown(object obj);

/* Default Room */

void
create_waterroom()
{
    set_short("Water");
    set_long("You are swimming in some water.\n");
}

nomask void
create_room()
{
    set_f_to_drown(FTODROWN);
    set_f_to_be_tired(FTOBETIRED);
    set_how_hard_to_swim(100);
    set_swim_easy(SWIMEASILY);
    set_swim_between(MAXFSWIM);
  
    create_waterroom();
    
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(OBJ_I_CONTAIN_WATER, 1);
}

void
init()
{
    ::init();
    add_action("swim", "swim");
    add_action("dive", "dive");
}

/* Of course a swim function should be in a waterroom */

int
swim(string s)
{
    notify_fail("You swim around.\n");
    return 0;
}

/* And a dive function */

int
dive(string s)
{
    notify_fail("You make a quick dive below the surface.\n");
    return 0;
}

/*
 * Function name: set_f_to_drown
 * Description:   Sets the fatigue-level below which the drown
 *                function is called.
 * Arguments:     The fatigue-level
 */

void
set_f_to_drown(int f)
{
    ftodrown = f;
}

int query_f_to_drown() { return ftodrown;}

/*
 * Function name: set_f_to_be_tired
 * Description:   Sets the fatigue-level below which the obj_is_tired
 *                function is called.
 * Arguments:     The fatigue-level
 */

void
set_f_to_be_tired(int f)
{
    ftobetired = f;
}

int query_f_to_be_tired() { return ftobetired;}

/*
 * Function name: set_how_hard_to_swim
 * Description:   Sets how hard it is to swim in this room
 * Arguments:     The how_hard-factor, normal is 100
 */

void
set_how_hard_to_swim(int f)
{
    howhard = f;
}

int query_how_hard_to_swim() { return howhard;}

/*
 * Function name: set_swim_easy
 * Description:   Sets the skill-level where you swim without fatigue-loss
 * Arguments:     The skill-level
 */

void
set_swim_easy(int f)
{
    swimeasy = f;
}

int query_swim_easy() { return swimeasy;}

/*
 * Function name: set_swim_between
 * Description:   Sets the max fatigue reduced when you swim between rooms
 * Arguments:     The max-fatigue-reduce-value
 */

void
set_swim_between(int f)
{
    swimbetween = f;
}

int query_swim_between() { return swimbetween;}


/*
 * Check if the entering object came from another waterroom.
 * If so, reduce the fatigue 
 */

void
enter_inv(object who, object from)
{
    ::enter_inv(who, from);
    
    set_heart_beat(1);
    if (!from) return;
    if (!living(who)) return;

    if (from->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
        who->add_fatigue(-FSWIM(who->query_skill(SS_SWIM)));
}

/*
 * Reduce fatigue on all livings in the room based
 * on their swim-skill.
 */

void
heart_beat()
{
    object *objs;

    objs = all_inventory(this_object());
    objs = FILTER_LIVE(objs);
    if (!objs || !sizeof(objs)) {set_heart_beat(0); return;}
    
    map(objs, red_fati);
}

/* 
 * Reduce fatigue on an object and check
 * the ftodrown and ftobetired levels
 */

void
red_fati(object obj)
{
    int fatigue;
    int floss;
  
    floss = FLOSS(obj->query_skill(SS_SWIM));
    
    obj->add_fatigue(-floss);
    fatigue=obj->query_fatigue();

    apa += ({ obj, floss, fatigue });
    if (sizeof(apa) > 24)
    {
        apa = apa[0..23];
    }

    if (fatigue < ftodrown)
    {
        drown(obj);
    }
    else if (fatigue < ftobetired)
    {
        obj_is_tired(obj);
    }
}

/* 
 * Function name: obj_is_tired
 * Description:   Called when a living's fatigue is below the 
 *                ftobetired-level.
 * Arguments:     The object.
 */

void
obj_is_tired(object obj){}

/*
 * Function name: drown
 * Description:   Called when a living's fatigue is below the 
 *                ftodrown-level.
 * Arguments:     The object.
 */

void
drown(object obj)
{
    obj->catch_msg("Right now you should have drowned.\n"+
                   "But since I havent implemented that yet, you survive.\n");
}
