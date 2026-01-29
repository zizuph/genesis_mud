// file name: d/Avenir/common/outpost/tower_privvy.c
// creator(s):  Lilith Apr 2022
// purpose:     A place to get rid of that poison from eating rotten rat meat.
// note:        Original 'quest' requires visiting the lavatories
//              in Gelan, so this is another option.     
//              /d/Avenir/common/dark/obj/fp.c is food poisoning obj.
//              Borrowing some functionality from the /d/Calia/std/lav.c for 
//              consistency of player experience.
//|   0    |   4     |  Rat Poison-Gelan toilet | Utterdark |    200        |
// revisions:    
// make no combat room

#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/include/food_poison.h"
#include "/sys/stdproperties.h"

inherit "/d/Avenir/inherit/room";

#define     NOTHING     0
#define     URINATING   1
#define     DEFECATING  2
#define     JUST_DOING  "_i_am_just_doing"

static int *times = ({ });  
static int def_alarm;
static int uri_alarm;
int occupied;

/* What the player is doing (urinating or defecating) */
void
set_doing(object p, int d)
{
    p->add_prop(JUST_DOING, d);
}

int
query_doing(object p)
{
    return p->query_prop(JUST_DOING);
}

string
poster()
{
    object tp = this_player();
    string str;

    str = 
    "Instructions for using this privvy:\n\n"
  + "   You have the following commands here:\n\n"
  + "      relieve   | urinate    get rid of your drinks\n"
  + "      eliminate | defecate   get rid of your food\n"
  + "      finish    | end        finish your business\n"
  + "      use paper | wipe       wipe yourself clean\n"
  + "\n\n";
    return str;
}

void
create_domain_room()
{
    set_short("Tower privvy");
    set_long("This is one of the privvies of Fort Sybarus. "+
      "It is the place where people relieve themselves of their food "+
      "and drink in a sanitary way that keeps filth and sickness at bay. "+
	  "There is a window here, through which the light of the flaming "+
      "pools outside the main gate can be seen. "+
	  "A poster with instructions hangs near the doorway. "+
	  "The floor is strewn with herbs, which, when crushed underfoot, "+
      "release a pleasant smell that almost conceals the other odors "+
      "associated with privvies. "+
      "There are a couple of large knee-high stone "+
      "blocks resting on the floor.\n");

    add_exit("tower_middle1", "northeast",0);

    IN_IN;
	LIGHT;
	/* Add some fun messages */
    add_prop(ROOM_I_HIDE, -1); // no peeping toms. 
// Apparently this isn't supported anymore?
//    add_prop(ROOM_M_NO_HIDE, "Hide where? You're too large to fit "+
//        "down the privvy hole.\n");	
	add_prop(ROOM_M_NO_SCRY, "Some things you really don't want to "+
        "see, like people relieving themselves -- or do you?\n");
    add_prop(ROOM_M_NO_TELEPORT_TO, "A privvy doesn't seem to be a "+
        "suitable place to teleport to.\n");
	add_prop(ROOM_M_NO_ATTACK, "You haven't sunk so low that you're "+
	    "going to attack someone while they're using the privvy.\n"); 
    add_prop(ROOM_M_NO_MAGIC_ATTACK, "The Gods of Sybarus brook no "+
       "such magick in this place.\n");

    add_item(({"funnel", "funnels", "stone block", "stone blocks", "toilet",
      "toilets", "throne", "thrones", "knee-high blocks", "blocks",
	  "block", "knee-high stone blocks", "hole", "privvy hole", "privvy"}),
      "There is a pair of knee-high stone blocks resting on the floor, "+
      "with funnel-shaped openings carved into them. "+
	  "Something that resembles lamp oil trickles through the funnel, "+
	  "taking most of the waste with it as it flows downward and "+
      "outside.\n");
    add_item(({"lamp oil", "oil", "fluid", "flammable liquid", "trickle"}),
      "This flammable liquid is used to clean the funnels of the privvy "+
      "by flushing the waste down toward the flaming pools outside. Having "+
      "discovered this, you feel some hesitancy about using the privvy, "+
      "as you can't help but wonder what prevents the flames from running "+
	  "up the funnel and causing burns on tender parts...\n");
    add_item(({"waste", "debris", "poop", "poo", "feces", "crap", "shit"}),
      "People produce waste, and lots of it. There is surprisingly little "+
      "remaining in the funnels, as it appears to be continuously emptied "+
	  "by the combination of gravity and a trickle of something that "+
      "resembles lamp oil.\n");	
    add_item(({"tower", "black tower"}),
       "The tower is made of the same black rock as much of the "+
       "fort.\n" );
    add_item(({"stone", "black stone"}),
      "The stone is very smooth and black. Little light reflects "+
      "from it.\n");
    add_item(({"door", "black stone door", "stone door"}),
      "What door? There is no door to this privvy. Sybarites must not have "+
      "much in the way of body modesty.\n" );
    add_item(({"floor", "herbs", "strewing herbs", "crushed herbs", 
      "fragrant herbs" , "fragrant strewing herbs"}),
      "Fragrant herbs like meadowsweet, mint, and hyssop have been "+
      "strewn on the floor. When walked upon, their fragrance is "+
      "is released, perfuming the air.\n");
    add_item(({"meadow sweet", "meadowsweet", "meadwort"}),
       "Also known as meadwort, this herb is strewn on floors to "+
       "give rooms a pleasant sweet aroma, reminiscent of almonds.\n");
    add_item(({"hyssop"}), "Amongst the herbs strewn upon the floor "+
       "you can see hyssop, which has a strong minty anise smell "+
       "that perfumes the room.\n");	   
    add_item(({"poster","note","sign"}), "@@poster");
    add_cmd_item(({"poster", "note", "sign"}), "read", "@@poster");
 
} 



/* function to chide the player for using rude words */
int
rude_words()
{
    notify_fail("Oh how very coarse! Please use respectful " +
        "verbs for such simple bodily functions. Read the " +
        "the poster for instructions.\n");
    return 0;
}


/* Allows the player to use toilet paper
   poster for instructions */
int
use_things(string str)
{
 
    tell_object(this_player(), "You wipe your bottom with some " +
        "of the sheets of privvy paper and drop them into the "+
		"privvy for disposal.\n");
 
    return 1;
}

/*
 * Function name: do_urinate
 * Description:   let the player get rid of all his drinks
 *                at half the rate of lavatories in Gelan
 */

void
do_urinate(object player)
{
    int soaked;

    soaked = player->query_soaked() - 50;

    player->drink_soft( - soaked);
 
    tell_object(player, "Ahh, that was good. Your bladder "
          + "feels a bit more relieved now.\n");
	
    occupied--;	
	
    set_doing(player, NOTHING); 	  
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
	
    soaked = this_player()->query_soaked() - 150;
    if (soaked < 150)
    {
        notify_fail("You don't feel that you have the need to " +
                    "relieve yourself at the moment!\n");
        return 0;
    }

    if (query_doing(this_player()) > 0)
    {
        write("You're already busy at that. You'd better slow down "+
            "or you'll hurt yourself!\n");
        return 1;			
    }

    if (occupied >= 2)
    {
        notify_fail("There doesn't seem to be a privvy block "+
            "available for you to use.\n");
        return 0;
    }		

    occupied++;
	
    set_doing(this_player(), URINATING);

    tell_object(this_player(), "Ok, you start relieving your bladder "+
        "into the funnel-shaped opening in the stone block.\n"+
        "That will surely take a while.\n");

    uri_alarm = set_alarm(itof(soaked/150), 0.0, &do_urinate(this_player())); 
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

    stuffed = player->query_stuffed() - 50;

    player->eat_food(-stuffed);
    tell_object(player, "Ahh, that felt good. You really feel "
          + "lighter now.\n");
		  
    occupied--;	
	
    set_doing(player, NOTHING);
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
    object poison;

    stuffed = this_player()->query_stuffed() - 50;

    if (stuffed < 50) 
    {
        notify_fail("You don't feel that you have the need " +
                    "to defecate at the moment, there's not " +
                    "enough food in you!\n");
        return 0;
    }

    if (query_doing(this_player()) > 0)
    {
        write("You're already busy at that. You'd better slow down "+
            "or you'll hurt yourself!\n");
        return 0;			
    }

    if (occupied >= 2)
    {
        notify_fail("There doesn't seem to be a privvy block "+
            "available for you to use. Please wait for someone "+
            "to finish.\n");
        return 0;
    }		

    occupied++;

    set_doing(this_player(), DEFECATING);

    tell_object(this_player(), "Ok, you sit down on the stone block and " +
        "start eliminating food from your bowels.\n"+
        "This will surely take a while.\n");

    if (poison = present(AVENIR_FOOD_POISON_ID, this_player()))
    {
        write("Your stomach feels much better as you defecate and rid "
            + "yourself of bad food.\n");
        poison->heal(); // Poison contained in /d/Avenir/common/dark/obj/fp.c
        poison->remove_object();
    }

    def_alarm = set_alarm(itof(stuffed/50), 0.0, &do_defecate(this_player())); 

    return 1;
} // defecate

void
reset_domain_room()
{
    occupied = 0;
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

   if (query_doing(player) == URINATING)
   {
        tell_object(player,"You stop urinating, although "
                         + "your bladder isn't empty yet.\n");

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

        set_doing(player, NOTHING);
		occupied--;
        return;
    }
    else if (query_doing(player) == DEFECATING)
    {
        tell_object(player, "Even though your bowels aren't empty "+
            "You stop defecating and stand up.\n");

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

        occupied--;
        set_doing(player, NOTHING);
        return;
    }
} //  stop_using_lav


/*
 * Function name: finish_up
 * Description:   finish using the privvy
 * Arguments:     none
 * Returns:       1 if OK, 0 if not
 */

int
finish_up()
{
    if (query_doing(this_player()) > NOTHING)
      stop_using_lav(this_player());        
    
	write("You finish up doing your business and prepare to exit the "+
        "privvy.\n");
    return 1;
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

    if (query_doing(ob) > 0) 
    {
        stop_using_lav(ob); 
    } 
	
	/* Control the occupancy */
	if (occupied < 0)
		occupied = 0;    
	if (occupied > 2)
		occupied = 2;
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
    add_action(urinate,    "urinate");
    add_action(urinate,    "relieve");	
    add_action(defecate,   "defecate");
    add_action(defecate,   "eliminate");	
    add_action(rude_words, "piss");
    add_action(rude_words, "shit");
    add_action(rude_words, "crap");
    add_action(rude_words, "pee");
    add_action(rude_words, "poop");
    add_action(use_things, "use");
	add_action(use_things, "wipe");
	add_action(finish_up,  "finish");
}