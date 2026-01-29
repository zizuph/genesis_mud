
/* 
    Lavatory inherit file for Gelan.

    coder(s):   Merlin & Maniac

    history:  
       20/4/99   upgraded to use prevent_enter, tidied up, 
                 fixed bugs, corrected linkdeath handling         Maniac
        8/6/96   WIZ_CHECK used                                   Maniac
       29/4/96   changed graffiti desc                            Maniac
       11/4/96   call_out --> set_alarm                           Maniac
       10/11/95  lav_ob.c incorporated for paralysis              Maniac
        25.5.95  Separated as an inheritable file from room code  Maniac
       13.11.09  Added heal call for Avenir food poisoning quest  Petros
       
    Each element of the graffiti mapping takes the form:
             name : ({number, message})

    Where `name' is the lowercase name of the player, `number' is the 
    time the graffiti was written and `message' is a string, the 
    graffiti itself.
*/


#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include <std.h>
#include <macros.h>
#include <const.h>
#include "/config/sys/local.h"
#include "/d/Avenir/include/food_poison.h"
#include "/d/Calia/sys/lav.h"


public mapping graffiti = ([ ]);
public string *banned = ({ });

static int *times = ({ });
static int graffiti_size = 0;
static string lav_door;               /* path to door in the room */
static object door;                   /* door in the room */
static object occupant; 
static string lav_exit_room;          /* lavatory exit room */
static int just_doing;                /* what the player is doing now, see
                                         defs */
static int lav_gender;
static string graffiti_ob;  
static int def_alarm;
static int uri_alarm;
static int warn_alarm;

#define     NOTHING     0
#define     URINATING  1
#define     NOT_FLUSHED 2
#define     DEFECATING 3
#define     NOT_BRUSHED 4
#define     GRAFFITI_NUM_MAX 20
#define     GRAFFITI_SIZE_MAX 240

/*
 * Function name: query_occupied
 * Description:   query if occupied
 * Arguments:     none
 * Returns:       1 if cabin occupied, 0 if not
 */

int
query_occupied()
{
    if (!objectp(occupant))
        return 0; 

    if (!objectp(present(occupant, this_object()))) {
        occupant = 0; 
        return 0; 
    } 
    
    return 1; 
}

int
query_just_doing()
{
    return just_doing;
}

void
set_graffiti_ob(string go)
{
    graffiti_ob = go;
}

void
set_lav_gender(int g)
{
    if ((g == G_MALE) || 
        (g == G_FEMALE) ||
        (g == G_NEUTER))
        lav_gender = g;
    else
        lav_gender = G_MALE; 
}

void
set_lav_door(string ld)
{
    lav_door = ld;
}

void
set_lav_exit_room(string ler)
{
    lav_exit_room = ler;
}

string
query_lav_title()
{
    switch (lav_gender) {
        case G_MALE : return "men";
                      break;
        case G_FEMALE : return "women";
                        break;
        case G_NEUTER : return "neuter person";
                        break;
    }
}

string
my_short()
{
    return capitalize(query_lav_title() + "s lavatory");
}

string 
my_long()
{
      string str =      
         "You're in a small cabin. The floor and the walls are white "
       + "tiled and very clean. There are several closet-bowls of "
       + "various heights here. On the wall is a dispenser. In the "
       + "left corner is a W.C. brush. On the wall right in front of "
       + "you is a poster with instructions.";
  
      if (graffiti_size)
          str += " You notice some graffiti on the wall as well.\n";
      else   
          str += "\n";

      return str;
}

string
wall()
{
     if (graffiti_size)
         return "The back wall has a poster on it, and also some graffiti.\n";
     else
         return "The back wall is spotlessly clean and has a poster on it.\n";
}



/* Returns 1 if wizard has the right to rub graffiti from the
   wall, 0 if not.
*/
   
int
rub_rights(object tp)
{
    string nm = tp->query_real_name();
    int lev, t;

    if (!tp->query_wiz_level())
        return 0;

    if (SECURITY->query_wiz_dom(nm) == "Calia")
        return 1;

    t = WIZ_CHECK; 
    if ((t == WIZ_ARCH) || (t == WIZ_KEEPER))
        return 1;
    return 0;
}


string
poster()
{
    object tp = this_player();
    string str;

    str = 
    "Instructions for using the public lavatory:\n\n"
  + "   You have the following commands here:\n\n"
  + "      urinate            get rid of your drinks\n"
  + "      defecate           get rid of your food\n"
  + "      stop               stop urinating or defecating\n"
  + "      flush              flush the toilet\n"
  + "      brush              brush the toilet\n"
  + "      use paper          use the toilet paper\n"
  + "      You can close, open and lock the door just as you want.\n"
  + "      To leave the cabin, just use `leave'.\n\n"
  + "You think to yourself: `Hmm, I wonder if I was to try " 
  + "<graffiti> I could write some graffiti on the wall. " 
  + "I'd better not write anything filthy though, or I'll " 
  + "get myself banned. Maybe I can <clean> any of my old graffiti " 
  + "off too if I want.'\n\n";

    if (rub_rights(tp))
        str += "Being a wizard of Calia or an Arch, you also think to " +
               "yourself `Hmm, if any of this graffiti is really " +
               "obscene I could <rub <number>> it off, which would also " +
               "ban the player who wrote it from writing any more.'\n"; 

    return str;
}


/* Arrange the order of the graffiti messages according to time */
void
arrange_order()
{
    int i;
    mixed v;

    if (graffiti_size < 1)
        return;
    times = ({ });
    v = m_values(graffiti);
    for (i = 0; i < sizeof(v); i++)
        times += ({v[i][0]});

    times = sort_array(times);
}


void
init_graffiti()
{
    int i;

    restore_object(graffiti_ob);
    graffiti_size = m_sizeof(graffiti);
    if (graffiti_size < 1)
        return;
    for (i = 0; i < sizeof(banned); i++)
        if (!SECURITY->exist_player(banned[i]))
            banned -= ({banned[i]});
    seteuid(getuid(this_object()));
    save_object(graffiti_ob);
    arrange_order();
}



string
exa_graffiti()
{
     if (graffiti_size < 1)
         return "You find no graffiti.\n";
     if (graffiti_size == 1)
         return "You see 1 item of graffiti on the wall, you can read " +
                "it by doing read 1.\n";
     return "You see " + graffiti_size + " items of graffiti on the wall " +
         "which you may read individually by doing <read 1-" + 
          graffiti_size + ">.\n";
}


void
make_the_room(string ler, string ld, string go, int lg)
{
    string dispenser;

    lav_exit_room = ler;
    lav_door = ld;
    graffiti_ob = go;
    lav_gender = lg; 

    just_doing = 0;

    /* descriptions */

    set_short(my_short());
    set_long(my_long);

    /* properties */

    add_prop(ROOM_I_INSIDE, 1);	
    add_prop(ROOM_I_IS, 1);

    /* items in the room */

    add_item(({"bowl", "closet"}), "The bowls are fixed in different "
          + "height for the different species.\n");

    switch (lav_gender) {
        case G_MALE : dispenser = "The dispenser contains blue coloured " +
                      "toilet paper with little swords on it.\n"; 
                      break;
        case G_FEMALE : dispenser = "The dispenser contains pink coloured " +
                        "toilet paper with little clouds on it.\n";
                        break;
        case G_NEUTER : dispenser = "The dispenser contains green coloured " +
                        "toilet paper with little question marks on it.\n";
                        break;
    }
    add_item("dispenser", dispenser);

    add_item("cabin","Well, you're in it.\n");

    add_item(({"floor","ground"}),
              "It is white tiled and very clean.\n");

    add_item(({"wall", "back wall"}), "@@wall");
    add_item("graffiti", "@@exa_graffiti");
    add_item("brush","It's clean W.C. brush, with a little note "
          + "`Do not use for brushing teeth!' on it.\n");

    add_item(({"poster","note","sign"}), "@@poster");
    add_cmd_item(({"poster", "note", "sign"}), "read", "@@poster");

    door = clone_object(lav_door);
    door->move(this_object());

    init_graffiti();

} /* make_the_room */



/* A player can clean his/her graffiti entry off the wall. */
int
clean_graffiti()
{
    object tp = this_player();
    string nm = tp->query_real_name();
    mixed el;

     if (!(el = graffiti[nm])) {
         notify_fail("There is none of your graffiti on the wall " +
                     "to clean off.\n");
         return 0;
     }

     graffiti = m_delete(graffiti, nm);
     graffiti_size--;
     seteuid(getuid(this_object()));
     save_object(graffiti_ob);
     
     arrange_order();
     
     tp->catch_msg("You clean your graffiti from the wall.\n");
     return 1;
}


/* A player can write some graffiti on the wall unless banned 
   or player already has some written on the wall. */
int
write_graffiti(string str)
{
    object tp = this_player();
    string nm = tp->query_real_name();
    string *ind;
    mixed el;
    int i, t;

    if (!str) {
        notify_fail("Usage: graffiti <message> to leave the message " +
                    "written anonymously on the wall.\n");
        return 0;
    }
        
    if (member_array(nm, banned) > -1) {
        notify_fail("You have been banned from writing any graffiti " +
                    "in this cabin.\n");
        return 0;
    }

    if (graffiti[nm]) {
        notify_fail("You already have some graffiti on the wall, " +
                    "you'll have to remove it if you want to add " +
                    "something new.\n");
        return 0;
    }
     
    if (strlen(str) > GRAFFITI_SIZE_MAX) {
        notify_fail("That graffiti message was too long, please " +
             "keep it to less than " + GRAFFITI_SIZE_MAX + 
             " characters (" + (GRAFFITI_SIZE_MAX / 80) + " lines).\n");
        return 0;
    }

    ind = m_indexes(graffiti);

    /* take out oldest graffiti if num limit reached */
    if (graffiti_size == GRAFFITI_NUM_MAX) 
        for (i = 0; i < graffiti_size; i++) {
            el = graffiti[ind[i]]; 
            if (el[0] == times[0]) {
                graffiti = m_delete(graffiti, ind[i]);
                graffiti_size--; 
            }
        }
            
    graffiti += ([ nm : ({time(), str}) ]); 
    graffiti_size++;

    seteuid(getuid(this_object()));
    save_object(graffiti_ob);

    arrange_order();

    tp->catch_msg("You write some graffiti on the wall.\n");
    return 1;
}


/* A Calia wizard or arch can rub graffiti from the wall, which also 
   bans the player who wrote it from writing any again in this cabin. */
int
rub_graffiti(string str)
{
    object tp = this_player();
    string *ind, rub;
    mixed e;
    string nm = tp->query_real_name();
    int i, j, k;

    if (!rub_rights(tp)) 
        return 0;
    
    if (!str) { 
         notify_fail("Usage: rub <graffiti number>.\n");
         return 0;
    }

    if (sscanf(str, "%d", i) != 1) {
         notify_fail("Usage: rub <graffiti number>.\n");
         return 0;
    }
    
    if ((i > graffiti_size) || (i < 1)) {
        notify_fail("That number is outside the range of " +
                    "current graffiti messages on the wall.\n");
        return 0;
    }
    
    j = times[i-1];
    ind = m_indexes(graffiti);
    for (k = 0; k < sizeof(ind); k++) {
        e = graffiti[ind[k]]; 
        if (e)
            if (e[0] == j)
                rub = ind[k];
    }
    if (!rub) {
        notify_fail("Error, could not find that piece of graffiti.\n");
        return 0;
    }

    if (member_array(rub, banned) == -1)
        banned += ({rub});
    graffiti = m_delete(graffiti, rub);
    graffiti_size--;

    seteuid(getuid(this_object()));
    save_object(graffiti_ob); 
    arrange_order();
    tp->catch_msg("Ok, graffiti removed and player banned.\n");
    return 1;
}



int
read_graffiti(string str)
{
    object tp = this_player();
    string *ind, g;
    mixed e;
    string nm = tp->query_real_name();
    int i, j, k;

    if (!str) { 
         notify_fail("Usage: read <graffiti number>.\n");
         return 0;
    }

    if (sscanf(str, "%d", i) != 1) {
         notify_fail("Usage: read <graffiti number>.\n");
         return 0;
    }
    
    if ((i > graffiti_size) || (i < 1)) {
        notify_fail("That number is outside the range of " +
                    "current graffiti messages on the wall.\n");
        return 0;
    }
    
    j = times[i-1];
    ind = m_indexes(graffiti);
    for (k = 0; k < sizeof(ind); k++) {
        e = graffiti[ind[k]]; 
        if (e)
            if (e[0] == j)
                g = ind[k];
    }
    if (!g) {
        notify_fail("Error, could not find that piece of graffiti.\n");
        return 0;
    }

    tp->catch_msg("The graffiti reads:\n" + graffiti[g][1] + "\n");
    if(tp->query_wiz_level())
       tp->catch_msg("Wiz info, author of graffiti:\n" + g + "\n");

    return 1;
}





/* function to chide the player for using rude words */
int
rude_words()
{
  notify_fail("Oh how very coarse! Use less charged language " +
              "for that simple bodily function; have a look " +
              "at the poster for instructions.\n");
  return 0;
}


/* Allows the player to use toilet paper
   poster for instructions */

int
use_things(string str)
{
  if (!str) return 0;
   
  if (str == "paper")
  {
    tell_object(this_player(),"You wipe your bottom with some " +
                "of the sheets of lavatory paper.\n");
    return 1;
  }

  return 0;
}


/*
 * Function name: send_back
 * Description:   send the player back and print out why
 * Returns:       none
 */

void
send_back(object ob, string str)
{
    tell_object(ob, str);
    ob->move_living("the cabin",lav_exit_room);
}


/*
 * Function name: last_warning
 * Description:   take the player out of the cabin and tell him why
 * Arguments:     player object
 * Returns:       none
 */

void
last_warning(object player)
{

    int remdrink, remfood;
    int soaked, stuffed;

    tell_room(lav_exit_room, "Suddenly, the toilet attendant rises and "
          + "goes to the " + query_lav_title() + "s cabin.\n");
    if(door->query_locked())
    {
        tell_room(lav_exit_room, "The toilet attendant unlocks the door to "
          + "the " + query_lav_title() + "s cabin.\n");
        door->unlock_door("door");
    }
    if(!(door->query_open()))
    {
        tell_room(lav_exit_room, "The toilet attendant opens the door to "
          + "the " + query_lav_title() + "s cabin.\n");
        door->open_door("door");
    }
    tell_object(player, "Suddenly, the door is unlocked from the other side "
          + "and a second later it's opened. The toilet attendant looks in "
          + "and tells you that you have to leave now. In the same moment "
          + "she tears you out of the cabin.\n");

    tell_room(lav_exit_room, "The toilet attendant tells the player in the "
          + "cabin that " + player->query_pronoun() + " has to leave "
          + "now, and tears " + player->query_objective() + " out of the "
          + "cabin.\n");

    this_object()->forced_stop_using_lav(player);
    send_back(player,"Next time you'd better hurry up a bit.\n");
}


/*
 * Function name: first_warning
 * Description:   tell the player a first warning that he has soon to leave
 * Arguments:     player object
 * Returns:       none
 */

void
first_warning(object player)
{

    if(player->query_wiz_level())
        return;

    tell_object(player, "The toilet attendant knocks at your door and tells "
          + "you that you've already been in the cabin too long, and that "
          + "in a minute she will take you out.\n");

    tell_room(lav_exit_room, "Suddenly the toilet attendant rises from her "
          + "chair and goes to the door of the " + query_lav_title() + "s " 
          + "cabin. There she "
          + "knocks and tells the player in the box, that "  
          +  player->query_pronoun() + "'s already been "
          + "in the cabin too long and that she will take " 
          + player->query_objective() + " out in a " +
            "minute.\n");

    warn_alarm = set_alarm(60.0, 0.0, &last_warning(player));
}





/*
 * Function name: do_urinate
 * Description:   let the player get rid of all his drinks
 */

void
do_urinate(object player)
{
    int soaked;
    object ob;

    soaked = player->query_soaked() - 20;

    player->drink_soft( - soaked);
    just_doing = NOT_FLUSHED;
    tell_object(player, "Ahh, that was good. You really feel "
          + "relieved now.\n");
    ob = present(LAV_OB_NAME, player); 
    if (objectp(ob))
        ob->remove_object();
}


/*
 * Function name: urinate
 * Description:   let the player get rid of all his drinks
 * Arguments:     none
 * Returns:       1 if Ok, 0 if error
 */

int
urinate()
{
    int soaked;
    string s;
    object lo;

    if(door->query_open())
    {
        notify_fail("You'd better close the door first.\n");
        return 0;

    }

    soaked = this_player()->query_soaked() - 20;
    if (soaked < 20)
    {
        notify_fail("You don't feel that you have the need to " +
                    "urinate at the moment!\n");
        return 0;
    }

    just_doing = URINATING;

    if (lav_gender != G_MALE) 
        s = " sit down on the bowl and ";
    else 
        s = " ";
    tell_object(this_player(), "Ok, you" + s + "start urinating. That " +
           "will sure take a while.\n");

    lo = clone_object(LAV_OB);
    lo->set_doing("urinating");
    lo->move(this_player());

    uri_alarm = set_alarm(itof(soaked/20), 0.0, &do_urinate(this_player())); 

    return 1;
}



/*
 * Function name: do_defecate
 * Description:   let the player get rid of his food 
 */

void
do_defecate(object player)
{
    int stuffed;
    object ob;

    stuffed = player->query_stuffed() - 20;

    player->eat_food(-stuffed);
    just_doing = NOT_BRUSHED;
    tell_object(player, "Ahh, that was good. You really feel "
          + "relieved now.\n");
    ob = present(LAV_OB_NAME, player); 
    if (objectp(ob))
        ob->remove_object();
}


/*
 * Function name: defecate
 * Description:   let the player get rid of his food
 * Arguments:     none
 * Returns:       1 if Ok, 0 if error
 */

int
defecate()
{
    int stuffed;
    object poison, lo;

    if (door->query_open())
    {
        notify_fail("You'd better close the door first.\n");
        return 0;

    }

    stuffed = this_player()->query_stuffed() - 20;

    if (stuffed < 10) 
    {
        notify_fail("You don't feel that you have the need " +
                    "to defecate at the moment, there's not " +
                    "enough food in you!\n");
        return 0;
    }

    just_doing = DEFECATING;

    tell_object(this_player(), "Ok, you sit down on the bowl and start " +
                 "defecating. That will sure take a while.\n");

    if (poison = present(AVENIR_FOOD_POISON_ID, this_player()))
    {
        write("You stomach feels much better as you defecate and rid "
            + "yourself of bad food.\n");
        poison->heal(); // Poison contained in /d/Avenir/common/dark/obj/fp.c
        poison->remove_object();
    }
    
    lo = clone_object(LAV_OB);
    lo->set_doing("defecating");
    lo->move(this_player());

    def_alarm = set_alarm(itof(stuffed/10), 0.0, &do_defecate(this_player())); 

    return 1;
}


int
prevent_enter(object ob)
{
    if (!living(ob))
        return 0; 

    if (file_name(environment(ob)) == OWN_STATUE) 
        return 0; 

    if(ob->query_wiz_level())
        return 0;

    if (query_occupied())
    {
        tell_object(ob, 
            "As you are about to enter, the toilet attendant follows you "
          + "and holds you back. She tells you that only one person is "
          + "allowed in the cabin and that you have to wait until the "
          + "other one is finished.\n");

        tell_room(lav_exit_room, QCTNAME(ob) + " tries to enter the "
          + query_lav_title() + "s "
          + "cabin, but the toilet attendant stops " + ob->query_objective()
          + " because there is already a person in the cabin.\n", ob);
        return 1;
    }
    else
    {
        if (!(lav_exit_room->query_paid(ob)))
        {
            tell_object(ob, 
               "As you try to enter, the toilet attendant follows you "
             + "and holds you back. She tells you that you have to pay the "
             + "fee before you can use the lavatory.\n");

            tell_room(lav_exit_room, QCTNAME(ob) + " tries to enter the "
              + query_lav_title() + "s "
              + "cabin, but the toilet attendant stops " 
              + ob->query_objective()
              + " because " + ob->query_pronoun() + " didn't pay "
              + "the fee.\n", ob);
            return 1;
        }
        else if (ob->query_gender() != lav_gender)
        {
            tell_object(ob, 
              "As you try to enter, the toilet attendant follows you "
            + "and holds you back. She tells you, that this cabin is "
            + "reserved for " + query_lav_title() + " and that you have to "
            + "use one of the other cabins.\n");

            tell_room(lav_exit_room, QCTNAME(ob)+" tries to enter the " 
              +  query_lav_title() + "s " 
              + "cabin, but the toilet attendant stops " 
              + ob->query_objective()
              + " because " + ob->query_pronoun() + " hasn't "
              + "chosen the right cabin.\n", ob);
            return 1;
        }
    } 
    return 0; 
}


/*
 * Function name: enter_inv
 * Description:   called when player enters room
 * Arguments:     object who enters, object where it came from
 * Returns:       none
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(!(living(ob)))
        return;

    if (file_name(from) == OWN_STATUE) {
        ob->move_living("to the lavatory", lav_exit_room->get_this_object()); 
        return;  
    }

    occupant = ob; 
    warn_alarm = set_alarm(300.0, 0.0, &first_warning(ob)); 
    lav_exit_room->remove_paid(ob);
}



/*
 * Function name: leave_inv
 * Description:   called when an object leaves the rooms
 * Arguments:     which object, where it leaves
 * Returns:       none
 */
void
leave_inv(object ob, object to)
{
    ::leave_inv(ob,to);

    if (!(living(ob)))
        return;

    if (door->query_locked())
        door->unlock_door("door");

    if (ob == occupant) {
        this_object()->forced_stop_using_lav(ob); 
        occupant = 0; 
    } 

    if (!query_occupied())
    {
        remove_alarm(warn_alarm);
        warn_alarm = 0; 
        just_doing = NOTHING;
    }

    
}


/*
 * Function name: clean_up
 * Description:   called for clean up
 * Arguments:     none
 * Returns:       none
 */

void
clean_up()
{
    door->remove_door_info(this_object());
    door->remove_object();

    ::clean_up();
}


/*
 * Function name: exa_lock
 * Description:   description of lock
 * Arguments:     none
 * Returns:       string with desc
 */

string
exa_lock()
{
    return door->exa_lock();
}




/*
 * Function name: stop_using_lav
 * Description:   sorts out what happens when player stops using the lav.
 */
void
stop_using_lav(object player)
{
    object ob;
    int soaked, stuffed;
    int remdrink, remfood;
    mixed al;

   if (just_doing == URINATING)
   {
        tell_object(player,"You stop urinating, although "
                         + "you're not really finished.\n");

        soaked = player->query_soaked() - 20;
        al = get_alarm(uri_alarm); 
        if (sizeof(al))  
            remdrink = soaked - ftoi(al[2]) * 20;
        else
            remdrink = 0; 

        if (remdrink < 0)
            remdrink = 0;

        remove_alarm(uri_alarm); 
        uri_alarm = 0;

        player->drink_soft( - remdrink);

        just_doing = NOT_FLUSHED;
        return;
    }
    else if (just_doing == DEFECATING)
    {
        tell_object(player, "You stop defecating and "
            + "stand up, although you're not really finished.\n");

        stuffed = player->query_stuffed() - 20;
        al = get_alarm(def_alarm); 
        if (sizeof(al))  
            remfood = stuffed - ftoi(al[2]) * 10;
        else
            remfood = 0; 

        if (remfood < 0)
            remfood = 0;

        remove_alarm(def_alarm); 
        def_alarm = 0;

        player->eat_food( - remfood);

        just_doing = NOT_BRUSHED;
        return;
    }
}


/* Player is forced to stop using the lavatory because of being dragged
   out by the attendant. */
void
forced_stop_using_lav(object player)
{
    object ob;

    stop_using_lav(player);
    ob = present(LAV_OB_NAME, player); 
    if (objectp(ob))
        ob->remove_object();
    just_doing = NOTHING;
}


/*
 * Function name: flush_toilet
 * Description:   flush the toilet
 * Arguments:     none
 * Returns:       1 if OK, 0 if not
 */

int
flush_toilet()
{

    tell_room(lav_exit_room, "You hear the sound of a flushing toilet.\n");
    tell_object(this_player(), "FLOOOSSSH.\n");
    if (just_doing == NOT_FLUSHED)
        just_doing = NOTHING;

    return 1;
}


/*
 * Function name: brush_toilet
 * Description:   brush the toilet
 * Arguments:     none
 * Returns:       1 if OK, 0 if not
 */

int
brush_toilet()
{

    tell_room(lav_exit_room, "You hear the sound of a flushing toilet.\n");
    tell_object(this_player(), "You take the brush and while flushing "
          + "you clean the toilet bowl. Now it's as clean as before.\n");
    just_doing = NOTHING;

    return 1;
}


/*
 * Function name: pass_door
 * Description:   called when door passed
 * Arguments:     string with arguments
 * Returns:       0 for passed, 1 for not passing
 */

int
pass_door(string arg)
{
    if (just_doing == NOT_FLUSHED)
    {
        tell_object(this_player(), "Just as you try to leave, the "
          + "toilet attendant reminds you not to forget to flush the "
          + "toilet before you leave. You had better do what she wants.\n");

        return 1;
    }

    if (just_doing == NOT_BRUSHED)
    {
        tell_object(this_player(), "Just as you try to leave, the "
          + "toilet attendant reminds you not to forget to brush the "
          + "toilet before you leave. You had better do what she wants.\n");
     
        return 1;
    }

    return 0;  
}


/*
 * Function name: init
 * Description:   add commands to the player
 * Arguments:     none
 * Returns:       none
 */
void
init()
{
    ::init();
    add_action(urinate, "urinate");
    add_action(flush_toilet, "flush");
    add_action(defecate, "defecate");
    add_action(brush_toilet, "brush");
    add_action(rude_words, "piss");
    add_action(rude_words, "shit");
    add_action(use_things, "use");
    add_action(rub_graffiti, "rub");
    add_action(write_graffiti, "graffiti");
    add_action(clean_graffiti, "clean");
    add_action(read_graffiti, "read");
}
