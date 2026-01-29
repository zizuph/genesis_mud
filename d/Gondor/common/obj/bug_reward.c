/*
 * /d/Gondor/common/obj/bug_reward.c
 * 
 * This is a mechanical autoloading bug, given to deserving
 * mortals who enrich the Gondor domain.
 *
 * Originally coded by:
 * (C) Stern, April 23 2000
 *
 * Gwyneth : Altered the bug to be configurable and autoloadable
 *           with previous configuration on August 2, 2000.
 *          
 */

inherit "/std/object";
inherit "/lib/commands";

#include <cmdparse.h>
#include <composite.h>
#include <language.h>
#include <macros.h> 
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define BUG_NAME_LIST ({ "spider", "worm", "cockroach", "ladybug",    \
                         "louse", "bedbug",  "ant", "beetle",         \
                         "butterfly", "moth", "centipede",            \
                         "mosquito", "termite", "flea" })
#define BUG_PNAME_LIST ({ "spiders", "worms", "cockroaches", "ladybugs", \
                          "lice", "bedbugs",  "ants", "beetles",      \
                          "butterflies", "moths", "centipedes",       \
                          "mosquitos", "termites", "fleas"})
#define BUG_ADJ_LIST   ({ "crawly", "squirming", "creepy", "wriggly", \
                          "jumpy", "sluggish",  "jiggly", "wiggly",   \
                          "delicate", "fluttering", "speedy",         \
                          "biting", "winged", "jumping"})

/* Prototypes */
string bug_description();
string leg_description();
int wind(string str);
int release(string str);
void hop_bug();
int am_i_quitting();
object parse_bug(string str);

/*
 * Global variables.
 *
 * int bug_type  - one of 13 different bug types
 * int rotations - nr of rotations to wind the bug's spring
 */
int bug_type;
int rotations;

/*
 * Function name: bug_description
 * Description  : gives the bug's long_description
 */
string 
bug_description()
{
    string output = "This is a mechanical ";
    switch (bug_type)
    {
    case 0:
        output += "crawly spider of about two and a half inches long, " +
            "made of metal which is painted yellow. It has eight brown " +
            "legs and tiny black hairs are painted all over body and " +
            "legs. Four pairs of eyes cover its head. ";
        break;
    case 1:
        output += "squirming worm of about 3 inches long, made of " +
            "metal which is painted shiny greyish, giving the " +
            "illusion of a slimy surface. It is a rather featureless " +
            "tube shaped animal as worms tend to be. ";
        break;         
     case 2:
        output += "creepy cockroach of about 3 inches long, " +
            "made of metal which is painted golden brown. It has thin " +
            "brown legs, and two wobbly antennae on its forehead. ";
        break;
     case 3:
        output += "wriggly ladybug of approximately 2 inches long, " +
            "made of metal. The back of the bug is painted bright red " +
            "with shiny black dots. Its wings seem to flutter, and " +
            "it has thin black metal legs and a shiny black head. ";
        break;
     case 4:
        output += "jumpy louse of approximately 2 inches long, " +
            "made of metal, painted pinkish brown. It is a wingless bug, " +
            "and its shape is somewhat flattened. It has small beady " +
            "eyes, and short antennae protruding from its head. It has " +
            "well-developed claws and there seems to be a tiny " +
            "trace of blood (or paint?) on it's mouth part. ";
        break;
    case 5:
        output += "sluggish bedbug of approximately 2 inches long, " +
            "made of metal, painted reddish brown. It is a wingless bug " +
            "with long thin legs in the same color. It's head is " +
            "yellowish with blue eyes. There seems to be a tiny " +
            "trace of blood (or paint?) on it's little face. ";
        break;
    case 6:
        output += "jiggly ant, of approximately three and a half inches " +
            "long. It's painted glossy red and made of metal, " +
            "with a narrow stalk joining the abdomen and thorax. " +
            "It has two sharp wobbly antennae on it's round head, and " +
            "long thin metal legs. ";
        break;
    case 7:
        output += "wiggly beetle of approximately 2 inches long, " +
            "made of metal, painted shiny black. It is a wingless bug " +
            "with a round body, six hairy legs, and two antennae " +
            "sticking out of its small head. ";
        break;
    case 8:   
        output += "delicate butterfly of approximately three and " +
            "a half inches long, made of metal, painted in the colors " +
            "of the rainbow. Its large colorful wings are spread, and the " +
            "net structure of the metal wings highlights " +
            "their fragile nature. ";
        break;
    case 9:   
        output += "fluttering moth of approximately three and " +
            "a half inches, made of metal, painted in dull grey. " +
            "Its large wings are spread, and the " +
            "net structure of the metal wings highlights " +
            "their fragile nature. Its body is covered with tiny white " +
            "painted hair. ";
        break;
    case 10:   
        output += "speedy centipede of approximately four inches long. " +
            "made of metal, it's segmented body painted red-brown. " +
            "You count 35 tiny legs on each side, one pair per segment, " +
            "and a pair of claws near its mouth. ";
        break;
    case 11:   
        output += "biting mosquito of approximately 3 inches long, " +
            "made of metal, painted brown-yellow. It has thin wings " +
            "and very long thin legs.  There seems to be a tiny " +
            "trace of blood (or paint?) on it's little face. ";
        break;
    case 12:   
         output += "winged termite of approximately 3 inches long, " +
            "made of metal, painted glossy green. It has long wings " +
            "covering its back. Two short antennae protrude from its " +
            "round head. ";
        break;
    case 13:   
        output += "jumping flea of approximately 2 inches, " +
            "made of metal, painted light brown. It is a wingless bug, " +
            "its body flattened from side-to-side, with " +
            "claws on its feet, and powerful jumping hind legs. " +
            "It's eyes are beady and red. ";
        break;
    default:
         output += "bug. ";
     }
     output += "It looks cute in its own buggy way. A little red ribbon " +
        "is tied around its little neck. A ratchet protrudes from the " +
        "back of the mechanical bug.\n";
     return(output);
}

/*
 * Function name: leg_description
 * Description  : describes the bugs legs
 */
string 
leg_description()
{
     switch (bug_type)
     {
     case 0:
         return ("The legs of this crawly spider are eight in number. " +
            "They are brown with tiny black hairs painted all over them.\n");
     case 1:
         return ("Worms don't have legs!\n");
     case 2:
     case 3:
     case 6:
     case 7:
     case 8:
     case 9:
     case 11:  
     case 12:
         return ("They are long thin bug legs.\n");
     case 4:
         return ("What is there to say about lice legs...\n");
    case 5:
         return ("What is there to say about bedbug legs...\n");
     case 10:   
         return ("They are seventy identical legs attached to one " +
             "centipede.\n");
      case 13:   
          return ("The hind legs of this flea are specifically designed " +
             "for jumping.\n");
     default:
         return ("What legs?");
     }
}

/*
 * Function name: create_bug
 * Description  : Configures the bug. Note, it won't come out quite
 *                right if create_bug is called in an already
 *                configured bug. Clone a new unconfigured bug and
 *                configure it that way.
 * Arguments    : string type - the type of bug to set it to
 */
private int
create_bug(string type)
{
    bug_type = member_array(type, BUG_NAME_LIST);

    add_name(BUG_NAME_LIST[bug_type]);
    add_name("toy");
    set_pname(BUG_PNAME_LIST[bug_type]);
    add_pname("bugs");

    add_adj(BUG_ADJ_LIST[bug_type]);

    set_short(BUG_ADJ_LIST[bug_type] + " " + BUG_NAME_LIST[bug_type]);
    set_pshort(BUG_ADJ_LIST[bug_type] + " " + BUG_PNAME_LIST[bug_type]);

    set_long( bug_description() );

    add_item( ({ "ribbon", "red ribbon", "little red ribbon",
        "little ribbon", "neck" }), 
        "The ribbon is tied around the bug's neck. A small square card " +
        "is attached to the ribbon.\n");
    add_item( ({ "card", "small card", "square card", "small square card" }), 
        "On the card you read:\n" +
        "   /-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\\ \n" +
        "   |                                                   | \n" +
        "   |  A small token to express  our appreciation  of   | \n" +
        "   |  your extraordinary contributions to the Gondor   | \n" +
        "   |  Lands.                                           | \n" +
        "   |                                                   | \n" +
        "   |                              The Lord of Gondor   | \n" +
        "   \\-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-/ \n" +
        "Followed by some fine print.\n\n");
    add_item( ({ "print", "small print", "smallprint", "fine print", 
        "fineprint" }), 
        "You read: 'Please don't report this bug.\n" +
        "           Thank you for your cooperation.'\n");
    add_item( ({ "key", "knob", "ratchet", "back" }), 
        "The ratchet on the bug's back looks like a key or knob that can " +
        "be turned to wind the animal.\n");
    add_item( ({ "eye", "eyes" }), 
        "The little eyes of the bug seem to gleam with life.\n");
    add_item( ({ "nose" }), 
        "The nose of the little bug is tiny.\n");
    add_item( ({ "leg", "legs", "feet", "claw", "claws" }), 
        leg_description());
    add_item( ({ "hairs" }), 
        "What is there to say about bugs hair growth?\n");
    add_item( ({ "head" }), 
        "It looks like a small bugs head.\n");

    switch (bug_type)
    {
    case 8:
    case 9:
    case 12: 
        add_item( ({ "antenna", "antennae" }), 
            "The two antennae on the bug's head are long and wobbly.\n");
    case 11:
    case 3:
        add_item( ({ "wing", "wings" }), 
            bug_type == 3 ? "The wings look fragile.\n" :
            "The wings are made of metal strings woven together " +
            "to form a weblike mesh, creating a sense of delicacy.\n");
        break;
    case 2:
    case 4:
    case 5:
    case 6:
        add_item( ({ "antenna", "antennae" }), 
            bug_type == 4 ? 
            "The two antennae on the bug's head are short.\n" :
            "The two antennae on the bug's head are long and wobbly.\n");
        break;
    default:
        break;
    }    

    return 1;
}

/*
 * Function name : set_bug_name
 * Description   : initial checks before calling create_bug
 *                 when set manually to avoid receiving
 *                 messages upon recovery of item.
 */
private int
set_bug_name(string type)
{
    int num = member_array(type, BUG_NAME_LIST); 

    /* Only Gondorians or Lord+ may alter the bug. */
    if (WIZ_CHECK < WIZ_LORD &&
      SECURITY->query_wiz_dom(TP->query_real_name()) != "Gondor")
    {
        notify_fail("What?\n");
        return 0;
    }

    if (type == "random")
    {
        type = BUG_NAME_LIST[random(13)];
    }

    if (num == -1)
    {
        notify_fail("No such name available. Try:\n" +
        implode(BUG_NAME_LIST, "\n") + "\nrandom\n");
        
        return 0;
    }

    create_bug(type);

    write("You change the toy into a " + short() + ".\n");
    tell_room(environment(TP), QCTNAME(TP) + " changes a toy " +
        "into a " + short() + ".\n", TP);

    return 1;
}

/*
 * Function name: create_object
 * Description  : Creates an unconfigured bug. 
 */
void
create_object()
{
    set_name("bug");
    set_short("unconfigured bug");
    set_long("This bug is unconfigured. Use <bugtype type> to " +
        "configure it. Types of bugs available:\n" +
        implode(BUG_NAME_LIST, "\n") + "\nrandom\nNote: Only " +
        "configure an unconfigured bug, or the results will not " +
        "be as intended\n.");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME,  400);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_DROP, &am_i_quitting());

    rotations = 0;
}

/*
 * Function name: am_i_quitting
 * Description  : Determines whether player quits
 * Returns      : int - 0 when not quitting, 1 when quitting 
 */
int
am_i_quitting()
{
    return (query_verb() == "quit");
}

/*
 * Function name: wind
 * Description  : Deals with "wind bug" action
 * Returns      : int - 0 if fails, 1 if succeeds
 */
int
wind(string str)
{
    object bug;

    bug = parse_bug(str);
    if (!objectp(bug))
    {
        return 0;
    }

    if (rotations < 3)
    {
        write("You turn the ratchet on the back of your " + short() +
            " with a rattling sound winding the bug.\n");
        say(QCTNAME(this_player()) + " turns the ratchet on the back of " + 
            this_player()->query_possessive() + " " + short() +
            " with a rattling sound to wind it.\n");
        rotations += 1;
    }
    else 
    {
        write("You try to turn the ratchet on the back of your " + short() +
            " but the knob is stuck as the spring is fully wound.\n");
        say(QCTNAME(this_player()) + " tries to turn the ratchet on the " +
           "back of " + this_player()->query_possessive() + " " + short() +
            " but the knob is stuck.\n");
    }
    return 1;
}

/*
 * Function name: release
 * Description  : Deals with "release bug" action
 * Returns      : int - 0 if fails, 1 if succeeds
 */
int
release(string str)
{
    object bug;

    bug = parse_bug(str);
    if (!objectp(bug))
    {
        return 0;
    }

    /* first put me on the floor */
    move(environment(this_player()), 1);
    write("You carefully put your " + short() + 
        " on the floor and release the ratchet on the back of your " + 
        "bug.\n");
    say(QCTNAME(this_player()) + " carefully puts " + 
        this_player()->query_possessive() + " " + short() +
        " on the floor and releases the ratchet on the back of the bug.\n");
    if (rotations > 0)
    {
        set_alarm(3.0, 0.0, &hop_bug());
    }
    return 1;
}

/*
 * Function name: hop_bug
 * Description  : Moves the bug one room
 */
void
hop_bug()
{
    mixed *exits;
    mixed exit;
    
    string *bug_movement_out =
          ({ "move all eight legs into a crawling " +
             "motion while producing a screeching sound and crawls ",
             "squirm spastically producing a shrill sound and slithers ", 
             "move rhythmically making a sharp screeching sound of " +
                 "metal against metal, and wobbles ",
             "flap its red and black wings frantically while producing " +
                 "a rasping sound and totters ",
             "shake violently while making a high pitched " +
                 "sound and hops ",
             "tremble and shake while making a scraping sound and staggers ", 
             "quiver with a grinding sound and moves its legs awkwardly " +
                 "staggering ",
             "sway unsteadily while making grinding sounds and wavers ",
             "flap its colorful wings making a chafing sound and waggles ",
             "vibrate intensely while making shrill grating sounds and " +
                 "flapping its wings and totters ",
             "stir all of its legs rhythmically with a rattling sound " +
                 "into a steady walk ",
             "buzzing vehemently, frantically vibrating its wings and " +
                 "suddenly waddles ",
             "quiver and shake with a loud chafing sound and jerkily walks ",
             "tremble forcefully while making a high pitched sound and " +
                 "quickly jumps "         });
    string *bug_movement_in =
         ({  " crawls in while producing a screeching sound of metal " +
                 "against metal.\n",
             " slithers in while producing a shrill sound.\n ", 
             " wobbles in while making a sharp screeching machanical sound.\n",
             " totters in flapping its red and black wings frantically.\n",
             " hops in shaking violently.\n",
             " staggers in while making a scraping sound.\n", 
             " staggers in with a grinding sound, moving its legs " +
                 "awkwardly.\n",
             " wavers in unsteadily while making grinding sounds.\n",
             " waggles in with colorful wings flapping.\n",
             " totters in with shrill grating noise and flapping wings.\n",
             " steadily walks in rhythmically moving all of its legs.\n",
             " waddles in,  frantically vibrating its wings.\n",
             " jerkily walks in accompanied by a loud chafing sound.\n",
             " jumps in while making a high pitched sound.\n "     });
    /* find possible exits */
    exits = environment()->query_exit();
    if (!sizeof(exits))
    {
        tell_room(environment(), "The " + short() + " quivers and " + 
            "shakes making a sharp screeching machanical sound.\n", 0);
    }

    else
    {
        /* pick a random exit */

        exit = random(sizeof(exits) / 3 );
    
        tell_room(environment(), "The " + short() + " starts to " +  
            bug_movement_out[bug_type] + exits[(exit * 3) + 1]   + ".\n", 0);
        move(exits[exit * 3], 1);
        tell_room(environment(), capitalize(LANG_ASHORT(this_object())) + 
            bug_movement_in[bug_type], 0);
    }

    rotations -= 1;
    if (rotations > 0)
    {
       set_alarm(4.0, 0.0, &hop_bug()); 
    }
}

/*
 * Function name: parse_bug
 * Description  : parses the bug commands and handles its errors
 * Returns      : object - bug 
 */
object 
parse_bug(string str)
{
   object bug;
   object *oblist;

   if (!strlen(str))
   {
       notify_fail(capitalize(query_verb()) + " what?\n"); 
       return 0;
   }
   str = lower_case(str);
   if (parse_command(str, ({ }), 
        "[the] 'key' / 'spring' / 'ratchet' / 'knob'"))
   {
       bug = this_object();
   }
   else
   {
       parse_command(str, this_player(), "[the] %i", oblist);
       oblist = NORMAL_ACCESS(oblist, 0, 0);
       if (!sizeof(oblist))
       {
           parse_command(str, environment(this_player()), "[the] %i", oblist);
           oblist = NORMAL_ACCESS(oblist, 0, 0);
       }  
       switch (sizeof(oblist))
       {
       case 0: 
           notify_fail(capitalize(query_verb()) + " what?\n"); 
           return 0; 
       case 1:
	 /* Check whether the object is this_object(). */
           if (this_object() != oblist[0])  /* if not bug */     
           {
               notify_fail(capitalize(query_verb()) + " what?\n"); 
               return 0;
           }     
           break;
       default:
           notify_fail("You can only " + query_verb() + 
              " one thing at the time.\n");
           return 0;     
       }
       bug = oblist[0];
    }     

    /* if we carry the bug */
    if (environment(bug) != this_player()) 
    {  
        notify_fail("Please pick up the bug before you " +
           (query_verb()) + " it.\n"); 
        return 0;                    
    }
    return bug;
}

/*
 * Function name: bug_lands
 * Description  : This function is called to handle a dropped bug that
 *                was wound.
 */
void
bug_lands()
{
    tell_room(environment(), "As the "  + short() + " lands on the floor " +
        "and its spring is released, the little bug starts to hum.\n");
    set_alarm(2.0, 0.0, &hop_bug()); 
}

/*
 * Function name: enter_env
 * Description  : This function is called whenever this object enters a new
 *                environment. Redefined.
 * Arguments    : object inv  - the environment this object is entering.
 *                object from - the possible place this object came from.
 */
void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    if (to->query_prop(ROOM_I_IS) && 
        interactive(from) &&
        rotations &&
        (query_verb() != "release"))
    {
        set_alarm(2.0, 0.0, bug_lands);
    }
}

/*
 * Function name: init
 * Description  : When someone 'comes close' to this object, the commands
 *                of this object are linked to the player. 
 */
void
init()
{
    ::init();

    add_action(wind, "wind"); 
    add_action(wind, "turn");
    add_action(release, "release");
    add_action(set_bug_name, "bugtype");
}

/* Function name : query_recover
 * Description   : mask query_recover() to prevent duplication of
 *                 autoloading items
 * Returns       : 0
 */
public string
query_recover()
{
    return 0;
}

/* Function name : query_auto_load
 * Description   : Make the item autoloading and preserve the type.
 * Returns       : The file and the name of the item.
 */
public string
query_auto_load()
{
    return MASTER + ":" + BUG_NAME_LIST[bug_type];
}

/* Function name : init_arg
 * Description   : Allow the item to recover its type and configure
 *                 accordingly.
 * Arguments     : string arg - the configured name of the bug.
 */
public void
init_arg(string arg)
{
    if (member_array(arg, BUG_NAME_LIST) == -1)
    {
        create_bug("random");
    }

    create_bug(arg);
}
