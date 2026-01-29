/*      This is a ghost that haunts people who kill a shopkeeper in 
        Gelan. Its description is set after whatever shopkeeper was killed.
        It haunts for a set duration (autoloads too). 
        See also haunt_code.c

    coder(s):  Maniac 
    history:
               2.9.94      Created                        Maniac

    purpose:   Make people think twice about killing shopkeepers! 

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>

#define GHOST_SUBLOC "_ghost_subloc"

string *appears = ({ "strange ghostly form",
                     "ghostly white apparition",
                     "shrouded phantom",
                     "frightening ghost" });
                     
string *reactions = ({ "Cold sweat forms on your forehead.",
                    "You shiver, horrified.",
                    "Icy fear takes hold of you.",
                    "You are paralysed with fear.",
                    "Horror strikes you to the core of your soul." });

string *actions = ({" leers horrifically at ",
                    " slowly rattles its chains at ",
                    " moans eerily at ", 
                    " hovers about for a while around ",
                    " groans frighteningly at " });
                     

int duration;      /* duration of haunting still to pass */
int haunt_alarm;    /* Id of alarm for haunting  */
object haunt_player;
string description;


/* set ghost description e.g. "short fat gnome"*/
void
set_ghost_des(string des)
{
  description = des; 
}


/* set the duration for the haunting */
void
set_duration(int dur)
{
  duration = dur;
}

/* start to haunt the player if possible */
void
start_haunt()
{
  if (living(environment(this_object()))) {
    haunt_alarm = set_alarm(15.0, 35.0, "haunt"); 
    haunt_player = environment(this_object());
    haunt_player->add_subloc(GHOST_SUBLOC, this_object());
    set_alarm(3.0, 0.0, "inform_haunt");
  }
  else remove_object();
}


void
inform_haunt()
{
  haunt_player->catch_msg("Suddenly an icy chill runs down your " +
            "spine.. a sixth sense tells you that you are being " +
            "haunted.\n");
}


/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *                me      - I
 *                for_obj - The looker
 * Returns:       The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    int myself;

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (subloc != GHOST_SUBLOC)
        return me->show_subloc(subloc, me, for_obj);

    myself = for_obj == me;
    return (myself ? "You are" : capitalize(me->query_pronoun()) + " is") +
        " being haunted!\n"; 
}




void
create_object()
{
    set_name("_a_ghost");
    set_short("a ghost");
    set_long(
        "A ghost haunting someone!\n"); 
    set_no_show();   /* Don't want people to be able to see in inventory */
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_I_VOLUME, 0);
}



/* Carry out one appearance of the apparition,
   finishing haunting if the duration has run out 
 */

void
haunt()
{
  string appear = appears[random(sizeof(appears))];
  string action = actions[random(sizeof(actions))];
  string reaction = reactions[random(sizeof(reactions))];
   
  if (haunt_player && (environment(this_object()) == haunt_player)) {
    tell_room(environment(haunt_player), "The " + 
              appear + 
              " of a " + description + " forms near " + 
              QTNAME(haunt_player) + " and" + action +
              haunt_player->query_objective() + 
              ", then slowly fades from view.\n", haunt_player);

    haunt_player->catch_msg("The " + appear +
                 " of a " + description + " forms near you and" +
                 action + "you. " + reaction + " The apparition " +
                 "then slowly fades from view.\n"); 

    /* Changed this from 1500; that's just an unrealistic value. */
    haunt_player->add_panic(100);
    duration = duration - 35;
    if (duration < 35)
      set_alarm(10.0, 0.0, "end_haunt");
  }
  else {
    if (haunt_alarm) remove_alarm(haunt_alarm);
    haunt_player->remove_subloc(GHOST_SUBLOC);
    remove_object();
  }
}


/* End the haunting */
void
end_haunt()
{
   if (haunt_alarm) remove_alarm(haunt_alarm);
   if (haunt_player && (environment(this_object()) == haunt_player)) {
     haunt_player->catch_msg("You feel a little less scared, perhaps " +
                  "the ghost has stopped haunting you now.\n");
     haunt_player->add_panic(-50);
     haunt_player->remove_subloc(GHOST_SUBLOC);
     remove_object();
   }
   else {
     haunt_player->remove_subloc(GHOST_SUBLOC);
     remove_object();
   }
  
}


/*
 * Function name: query_auto_load
 * Description:   Used to reload the ghost into the player if it hasn't
 *                left him yet when he quits.  
 */
public nomask string
query_auto_load()
{

    return MASTER + ":" +
	duration + "," +
	description;
}


/*
 * Function name: init_arg
 * Description  : Parses the data from the saved object.
 * Arguments    : arg - the arguments to init
 */
public nomask void
init_arg(string arg)
{
    int i, dur;
    string *arglist, des;

    /* recovery = 1; */

    arglist = explode(arg, ",");

    sscanf(arglist[0], "%d", dur);
    set_duration(dur);
   
    des = arglist[1];
    set_ghost_des(des);

    set_alarm(1.0, 0.0, "start_haunt"); 
}



/*
 * Function name: stat_object
 * Description  : Called when wizard stats the object
 * Returns      : A string describing the object.
 */
public string
stat_object()
{
    string str = ::stat_object();

    str += "Ghost description: " + description + "\n";
    str += "Haunt duration left: " + duration + "\n";

    return str;
}


