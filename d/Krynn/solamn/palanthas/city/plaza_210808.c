/* 
 * The center of the city of Palanthas.
 * This room contains a donation column (/d/Genesis/obj/donation/column)
 * Mortis 07.2005
 *
 * Added a disposal bin. Mortis 9.2014
 */

/* #pragma strict_types */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>

inherit CITY_BASE;

#define VIEWNE            (ROOM + "ecoffee")
#define VIEWNW            (ROOM + "mcoffee")

string
query_to_jail()
{
  return "north";
}

object column = 0;
object mapvendor, dbin;


/*nomask public string
get_time_plazasmell()
{
     string psmell;
     switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
    psmell = "Cool, misty air blowing south off the bay mingles here with "
    + "the rich smells of coffee and biscuits coming from the doorway of "
    + "the Dawnbringer, a cafe in the northwest of the plaza.  The streets "
    + "and sidewalks smell of the lily scented cleaning wash the "
    + "streetwashers use each morning";
    break;

    case TOD_DAY:
    psmell = "Cool air blowing south off the bay mingles here with the "
    + "rich smells of coffee and biscuits coming from the doorway of "
    + "the Dawnbringer, a cafe in the northwest of the plaza and with "
    + "the smells of a plaza busy with the human merchants and citizens "
    + "filling it";
    break;

    case TOD_TWILIGHT:
    psmell = "Warm air blowing south off the bay cools here mingling with "
    + "the rich smell of coffee from a northwest cafe, a hint of vanilla and "
    + "spices from the Light Hart Cafe in the northeast, and the scents of "
    + "perfume and cologne on the affluent, evening strollers";
    break;

    case TOD_NIGHT:
    psmell = "Cool air blowing south off the bay mingles here with the "
    + "rich smells of coffee and biscuits in the Dawnbringer, a cafe in "
    + "the northwest of the plaza, and coffee with a hint of vanilla "
    + "coming from the Light Hart Cafe in the northeast";
    break;

    default:
    break;
    }
    return psmell;
}*/

string plazasmell = "Misty air blowing south off the bay mingles here with the "
    + "rich smells of coffee and cooking coming from the doorways of a "
    + "cafe in the northwest of the plaza and one in the northeast along "
    + "with the smells of a plaza busy with the human merchants and citizens "
    + "frequenting it.  ";

nomask public string
get_time_desc()
{
    string desc = "";
    string plaza = "  To the north is the Palanthas palace, its great white "
    + "tower rising high above the plaza.  The city jail is to the south, "
    + "along with the post office.  Cafes and street vendors ring the plaza "
    + "between the administrative buildings.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
    desc += "The pristine marble of the streets and buildings of the Palatial "
    + "Plaza glows in pale purple hues as the sun peeks above the mountains.  "
    + "The air is rich with the smells of morning cooking and coffee borne "
    + "on a cool, misty breeze from the bay." + plaza;
    break;

    case TOD_DAY:
    desc += "The pristine marble of the streets and buildings of the Palatial "
    + "Plaza gleams in the midday sun as merchants, bureaucrats, "
    + "and shoppers crowd the plaza with the noisy murmurings of their "
    + "daily business." + plaza;
    break;

    case TOD_TWILIGHT:
    desc += "The translucent marble of the streets and buildings of the Palatial "
    + "Plaza catches the last rays of the sun appearing to glow of its own accord "
    + "as the evening crowd comes out to walk and dine mingling with the "
    + "remaining shoppers and merchants." + plaza;
    break;

    case TOD_NIGHT:
    desc += "The moon and stars shed pale light across the translucent marble "
    + "of the streets and buildings of the Palatial Plaza amplifying the "
    + "yellow glow of the street lamps.  Merchants and revelers still make "
    + "their way about at this hour." + plaza;
    break;

    default:
    break;
    }
    return desc;
}

void
reset_palan_room()
{
    if (!dbin)
    {
        dbin = clone_object(OBJ + "disposal_bin");
        dbin->move(TO);
    }

    if (!column)
    {
        column = clone_object("/d/Genesis/obj/donation/column");
        column->move(TO);
    }

    if(!objectp(mapvendor))
    {
        mapvendor = clone_object(LIV + "mapvendor");
        mapvendor->arm_me();
        mapvendor->move(TO);
    }
}

void create_palan_room()
{
    SHORT("The Palatial Plaza of Palanthas");
    LONG("@@get_time_desc@@");

    ITEM("palace", "The palace of the Palanthas family dominates the entire "
    + "north side of the plaza, its balconied windows gazing down upon the "
    + "plaza from the many city offices it houses. Great white-enameled "
    + "iron doors grant access to those who have waited in line for an "
    + "audience.  Formidably plated knights guard the entrance, their "
    + "oiled and polished halberds held crossed barring intruders and line "
    + "jumpers.\n");

    ITEM(({"line", "queue"}), "The line of citizens waiting for an audience "
    + "at the doors to the palace is long at any hour and seems to be moving "
    + "steadily forward at an unhurried pace.\n");

    ITEM(({"vendor", "vendors", "merchant", "merchants", "salesman", "salesmen"}),
        "Street vendors and merchants wander the plaza looking for business "
    + "as well as ring the plaza catering to the fancies of the officials, "
    + "nobles, and citizens of the city regardless of hour.\n");

    ITEM(({"hue", "hues", "purple hues", "sunrise"}), "@@get_dawn_hue@@" + "\n");
    ITEM(({"smells", "cooking", "coffee", "breeze"}), 
        "You would get more from that if you used your nose.\n");
    ITEM(({"crowd", "crowds", "people", "shoppers", "citizens"}),
        "@@get_day_crowd@@" + "\n");
    ITEM(({"reveler", "revelers", "reveller", "revellers"}),
        "@@get_night_revel@@" + "\n");
    ITEM(({"streetwasher", "streetwashers", "washer", "washers"}),
        "@@get_morn_streetwashers@@" + "\n");
    ITEM(({"cafe", "cafes"}), "Which cafe?  There are so many in the "
    + "palatial plaza.\n");
    ITEM(({"northwest cafe", "nw cafe", "dawnbringer"}), "This is a cafe "
    + "in the northwest of the plaza with a great, green-shaded window.  "
    + "Written in white calligraphic letters across a blackboard sign "
    + "outside is `The Dawnbringer'.  Its door is open inviting customers "
    + "to enter.  You can peer through its window with <view northwest "
    + "cafe>.\n");
    ITEM(({"northeast cafe", "ne cafe", "light hart cafe"}), "This is a "
    + "cafe in the northeast of the plaza.  Across its long, high window "
    + "is written `The Light Hart Cafe' with its logo of an antlered deer "
    + "head before thin clouds in between the words Hart and Cafe.  Its "
    + "door is open inviting customers to enter.  You can peer through "
    + "its window with <view northeast cafe>.\n");
    ITEM("jail", "A tall, three-story building of translucent marble in "
    + "the southwest of the plaza, its band of reliefs interrupted above "
    + "the double-doored entryway by the words `City Jail' chiseled "
    + "in the old style.\n");
    ITEM("old style", "The old style is angular and stiff and very "
    + "official looking.\n");
    ITEM(({"post", "po", "post office"}), "The post office of the city "
    + "of palanthas is south of you in the southeast portion of the "
    + "Palatial plaza.  Of all the old buildings of translucent marble "
    + "in the inner city, this is the most modestly sized of the great "
    + "buildings.  It is two stories in height and runs for at least "
    + "half a block to the south.\n");

    EXIT(PALACE + "palace1", "north", "@@palace_closed", 0);
    EXIT(ROOM + "nwr1", "northwest", 0, 0);
    EXIT(ROOM + "ner1", "northeast", 0, 0);
    EXIT(ROOM + "er1", "east", 0, 0);
    EXIT(ROOM + "ser1", "southeast", 0, 0);
    EXIT(ROOM + "sr1", "south", 0, 0);
    EXIT(ROOM + "swr1", "southwest", 0, 0);
    EXIT(ROOM + "wr1", "west", 0, 0);
    EXIT(ROOM + "jailfoyer", "jail", "@@place_closed", 0);
    EXIT(ROOM + "po", "post", 0, 0);
    
    CMD(({"line","in"}),({"stand","wait"}),"@@wait_forever");
    
    CMD(({"northwest cafe","dawnbringer","the dawnbringer", "nw cafe"}),
                 ({"enter","go","walk"}),
                 "@@mcof_portal");
    CMD(({"northeast cafe", "light hart", "light hart cafe", "ne cafe"}),
        ({"enter","go","walk"}), "@@ecof_portal");
    CMD(({"northeast cafe", "ne cafe", "light hart cafe"}), "view",
          "@@view_necafe");
    CMD(({"northwest cafe", "nw cafe", "dawnbringer"}), "view",
          "@@view_nwcafe");

    set_tell_time(180);

    add_tell("@@get_tell_time@@" + "\n");

    add_smell("vampire", plazasmell + "Your heightened sense of smell "
    + "picks up the scent of coffee, biscuits, and fruit coming from the "
    + "northwest cafe and from the northeast the scent of vanilla, coffee, "
    + "turkey, and spices all subdued by the scent of human blood insipidly "
    + "underlying it all.");
    add_smell("morgul", plazasmell + "Through the strong presence of "
    + "human odours in this plaza you detect something you seek... no, it's "
    + "just hobbit.  You smell food and coffee being served in the cafes "
    + "to the northwest and northeast.");
    
    add_smell("human", plazasmell + "The smell of human food, wine, "
    + "coffee, and people at their business in the city is familiar.");
    add_smell("elf", plazasmell + "The scents of food and drink on the "
    + "air are distinctly human.  Though simple to your elven palate, the "
    + "hint of spices from the northeast cafe is intriguing.");
    add_smell("goblin", plazasmell + "The scent of human flesh and offings "
    + "is strong here with a hint of food and alcohol.");
    add_smell("dwarf", plazasmell + "The air though strong with human smells "
    + "is clean enough to breathe.  Your dwarven nose picks up the smell of "
    + "wine coming from the northeast cafe.");
    add_smell("hobbit", plazasmell + "There is a pleasant smelling mix of "
    + "coffee and biscuits and lemon and tart fruits coming from the "
    + "doorway of the northwest cafe and the hints of vanilla, spices, "
    + "turkey, and wine from the northeast cafe.");
    add_smell("gnome", plazasmell + "The air is good enough to breathe at "
    + "the moment and strong with many inviting human smells from the "
    + "surrounding cafes and buildings.");
    add_smell("minotaur", plazasmell + "The smell of human flesh floods "
    + "your senses in this great human plaza beneath which is the scent of "
    + "cooked meat and wine coming from the northeast cafe.");
    add_smell("halfhuman", plazasmell + "The smell of human food, wine, "
    + "coffee, and people at their business in the city is not "
    + "unfamiliar.");
    add_smell("halfelf", plazasmell + "The scents of the plaza are not "
    + "unfamiliar to your senses nor the smell of coffee and cooking in "
    + "the nearby cafes unpleasant.");
    add_smell("orc", plazasmell + "The smell of manflesh is strong here in "
    + "the center of their large city along with, what's that... a hint of "
    + "hobbit?  The scents of food and drink come to your nose from the "
    + "northwest and northeast cafes.");
    add_smell("hobgoblin", plazasmell + "The scents of human flesh, offings, "
    + "and all the smells of a fortified human city abound here.");
    add_smell("kender", plazasmell + "Oh my!  You are almost overwhelmed "
    + "by the multitude of amazing people and things to smell!  Human "
    + "cities must be very rich with things to discover and places to "
    + "explore.");
    add_smell("drow", plazasmell + "Jiv'elgg!  All your composure is "
    + "needed to keep from retching at the overwhelming stink of humans "
    + "and overdwellers in this crowded plaza.  Still you can pick out the "
    + "scents of food and drink, reminiscent of the strongest drow poisons, "
    + "coming from a cafe in the northwest and less offensive scents from "
    + "the cafe in the northeast.");
    add_smell("noldor", plazasmell + "The scent of humans is strong in the "
    + "air along with the smells that accompany so many of their dwellings.");

    reset_palan_room();
}

/* 
 * The following two functions are used for <enter>ing the two plaza
 * cafes
 */

ecof_portal() 
{ 
  write("You enter the northeast cafe The Light Hart Cafe.\n"); 
  this_player()->move_living("entering a cafe in the northeast of the plaza",
      ROOM + "ecoffee", 1, 0);
  return ""; 
}

mcof_portal()
{ 
  write("You enter the northwest cafe The Dawnbringer.\n");
  this_player()->move_living("entering a cafe in the northwest of the plaza",
      ROOM + "mcoffee", 1, 0); 
  return ""; 
}

/* 
 * The following large strings are the room emotes that vary depending
 * on what time of day you're in the plaza. 
 */

string
get_tell_time()
{
    string ttell = "";
    
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
    ttell += one_of_list(({"The aroma of strong, fresh-brewed coffee wafts "
    + "on a cool morning breeze under your nose from somewhere in the plaza.",
      "A pair of aesthetics in quiet discussion munch on biscuits as they "
    + "make their way south across the plaza.",
      "The plaza streetwashers put the finishing touches on the plaza as "
    + "they sweep and scrub efficiently.",
      "A gathering of merchants walks past you arguing the details "
    + "of a shipment.",
      "A flock of pigeons flutters into the air from atop a nearby "
    + "building.",
      "A cool morning breeze off the bay ruffles banners and sways signs.",
      "A page walks hurriedly past you."}));

    break;

    case TOD_DAY:
    ttell += one_of_list(({"A path clears before a merchant leading his draft "
    + "horses and wagon west out of the plaza in the midday sun.",
      "A knight, his squire marching behind him carrying several packs, makes "
    + "his way through the crowd on foot to the noble quarter in the east.",
      "A trio of aesthetics in vigorous discussion make their way south "
    + "across the plaza.",
      "A cloud passes across the sun for a moment.",
      "The clouds drift gently across the sky spreading their bulbous "
    + "shadows across the plaza.",
      "A page walks hurriedly past you.",
      "A messenger jogs swiftly past you."}));

    break;

    case TOD_TWILIGHT:
    ttell += one_of_list(({"An official walks past you, his elegantly dressed "
    + "lady at his arm.  She nods at you as she fans herself with a small "
    + "foldout fan.",
      "A grey cloaked female human bumps into your side and then is gone, just "
    + "another face in the crowd.",
      "The aroma of coffee with a hint of vanilla wafts on a breeze under "
    + "your nose from somewhere in the plaza.",
      "A squire of Solamnia clips along slowly across the plaza atop his "
    + "steed.",
      "A cloaked noble accompanied by a pair of knights and a "
    + "retinue of courtesans push past the line to the palace and are "
    + "ushered within by the guards.",
      "A cool breeze off the bay ruffles banners and sways signs.",
      "A page walks hurriedly past you.",
      "A messenger jogs swiftly past you."}));

    break;

    case TOD_NIGHT:
    ttell += one_of_list(({"A grey cloaked male human bumps into your side "
    + "and then is gone, just another face in the plaza under the stars.",
      "A constable looks you over slowly before nodding his head and continuing "
    + "on across the lamp-lit plaza.",
      "A reveler sings a tavern ditty about a girl, too much sweets, lost her "
    + "teeth, and something you can't clearly make out as his voice trails off "
    + "into the night.",
      "A young woman helps a reveler leaning on her shoulder cut a crooked path "
    + "across the plaza steering clear of constables.",
      "A squire of Solamnia clips along slowly across the plaza atop his "
    + "steed, a skin of wine in his hand.",
      "A bearded merchant and a sailor walk through the plaza sharing a "
    + "bottle of wine stopping briefly beneath a lit lamp post.",
      "Clouds pass briefly across the night sky overhead leaving only yellow "
    + "lamp light on the translucent white streets.",
      "A shadow passes over the roof of a nearby building.",
      "A messenger jogs swiftly past you.",
      "The lamp atop a tall, grey lamp post nearby flickers briefly in the chill "
    + "night breeze."}));

    break;

    default:
    break;
    }
    return ttell;
}

string
get_dawn_hue()
{
    string dhue = "";
 
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
    dhue += one_of_list(({"The sun rising above the eastern peaks spreads soft "
    + "hues of purple fading to orange in the long, wispy clouds sailing slowly "
    + "across the morning sky.", "The sun rising above the eastern peaks "
    + "spreads tendrils of pink and orange fading to purple in the long, wispy "
    + "clouds sailing slowly across the morning sky."}));
    break;

    case TOD_DAY:
    dhue += "Sunrise has passed.  You will have to wait another day.";
    break;

    case TOD_TWILIGHT:
    dhue += "Sunrise has passed.  You will have to wait another day.";
    break;

    case TOD_NIGHT:
    dhue += "You'll have to wait a little while longer for the sunrise.";
    break;
    default:
    break;
    }
    return dhue;
}

string
get_day_crowd()
{
    string dcrowd = "";
    string dline = "Among them to the north is a slow moving line of people "
    + "at the entrance to the palace.";
 
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
    dcrowd += "The crowds have not yet filled the plaza though the early "
    + "shoppers, deliverers, and messengers are already going about their "
    + "business.  " + dline;
    break;

    case TOD_DAY:
    dcrowd += "Crowds of people throng the plaza in the midday sun eating, "
    + "drinking, looking for the best deals to be found in the various quarters "
    + "and districts.  " + dline;
    break;

    case TOD_TWILIGHT:
    dcrowd += "The crowds of people milling about the plaza have thinned since "
    + "afternoon leaving it easier to make your way across the plaza.  The "
    + "strolling, relaxed evening crowd now mixes with the hustling, bustling "
    + "afternoon shoppers.  " + dline;
    break;

    case TOD_NIGHT:
    dcrowd += "Though most people have retired for the night, constables, "
    + "merchants selling wares, and revelers heading for the next tavern "
    + "still make their way through the plaza.  " + dline;
    break;
    default:
    break;
    }
    return dcrowd;
}

string
get_morn_streetwashers()
{
    string swasher = "";
 
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
    swasher = "Dressed in long, white tunics and stocking caps, the "
    + "streetwashers of Palanthas are a well paid, industrious crew.  At "
    + "present they are vigorously sweeping and scrubbing the streets and "
    + "sidewalks, polishing and refilling the lamp posts, and picking up "
    + "litter from the night's revelries.";
    break;

    default:
    swasher = "The streetwashers are only out at daybreak.";
    break;
    }
    return swasher;
}

string
get_night_revel()
{
    string drevel = "";
 
    switch(GET_TIMEOFDAY)
    {
    case TOD_TWILIGHT:
    drevel += "There won't be anymore revelers out this early";
    break;

    case TOD_NIGHT:
    drevel += "Having drinks and socializing is a common pasttime in the "
    + "palatial plaza, and nobles, merchants, officials, and common citizens "
    + "alike are all passing through the plaza on their way to various inns "
    + "and taverns as well as stopping for a drink at the cafes here.";
    break;
    
    default:
    drevel += "There aren't any revelers left.";
    break;
    }
    return drevel;
}

/*
 * This function is what sets the room_tells a-workin.
 */

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

/* 
 * This keeps people from going north into the palace without waiting
 * in line unless they are a wizard. 
 */

int
palace_closed()
{
    if ((present("iletter", TP)) || (TP->query_wiz_level()))
      {   
      write("The palace guards step out of your way and say:  "
        + "It is a great honour to have you here.\n"
        + "The guards bow deeply before you and beckon you to enter.\n");
      return 0;
      }
    write("The palace guards bar your way with crossed halberds saying:  The Lord " +
      "of Palanthas has auditions today, so please wait in line " +
      "until it is your turn.\n\n");
    return 1;
}

/* 
 * This is called when people do the room command "wait in line". 
 * (It actually sends people to a mirror room of plaza.c!  Funny :)
 */

int
wait_forever()
{
    write("You stand in line. It seems this might take a while.\n");
    say(QCTNAME(TP) + " stands in line.\n");
    TP->move_living(0,ROOM + "line");
    return 1;
}

int
place_closed()
{
    write("You don't want to go to jail now.\n");
    return 1;
}

view_necafe()
{
    /* This function returns an equivalent of 'look' from ecoffee
     * most importantly without any supporting code from the
     * target room.
     */

    object *inv, *obs, *ppl, target;
    string vdesc;

    write(VIEWNE->long());
    target = find_object(VIEWNE);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    write("Through the green-tinted window of the northwest cafe, you can "
    + "make out " + vdesc + " on the floor.\n");

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    write("Inside the northwest cafe you see " + vdesc + ".\n");

    say(QCTNAME(TP) + " peers into the green-tinted window of a cafe "
    + "in the northwest of the plaza.\n");
 
    return 1;
}

view_nwcafe()
{
    /* This function returns an equivalent of 'look' from mcoffee
     * most importantly without any supporting code from the
     * target room.
     */

    object *inv, *obs, *ppl, target;
    string vdesc;

    write(VIEWNW->long());
    target = find_object(VIEWNW);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    write("Through the window of the northeast cafe, you can make out "
    + vdesc + " on the floor.\n");

    if (strlen(vdesc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    write("Inside the northeast cafe you see " + vdesc + ".\n");

    say(QCTNAME(TP) + " peers into the window of a cafe in the northeast "
    + "of the plaza.\n");
 
    return 1;
}
