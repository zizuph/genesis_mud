/* 
 *  The preserved form of the Woad Woman - Danuine.
 *
 *  When she is initialised, she reads in the
 *  library path strings for use in determining
 *  if the players she encounters are librarians
 *
 *  if they are, she has a gift from Danu for them
 *
 *  Vitwitch 09/2020
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <math.h>

#define WWNAME "danuine"
#define PENDRAGON_PATH "/d/Khalakhor/se_speir/claryn/tabor/pendragon/"
#define PENDRAGON_LIBFILE "pendragon_librmap"
#define PENDRAGON_DEFAULT_NAME "vitwitch"

#define COLOUR_SEED 17

inherit "/std/monster";

/* do not change NAME nor ADJ */
#define PENDRAGON_NAME "pendragon"
#define PENDRAGON_ADJ "inky"

// library/librarian strings... each element is library path or librarian name
mapping librmap;


string
no_attack()
{
    if(this_player()->query_npc()) return 0;
    return "As you approach with hostile intent " +
       "you sense the loom of hawthorn trees unseen... " +
       "you stagger back, befuddled.\n";
}

string
keening_chitter()
{
    tell_room(environment(this_object()),
     "A keening chitter comes and goes on the winds hereabouts.\n");
    return "";
}

string
smell_of_hawthorn()
{
    tell_room(environment(this_object()),
     "The tainted smell of hawthorn blossoms lingers in the air.\n");
    return "";
}

string
flicker_movement()
{
    tell_room(environment(this_object()),
     "There are flickers of winged movement, more felt than seen,"+
     " about this place.\n");
    return "";
}

public void
get_library_data()
{
   seteuid(getuid());
   librmap = restore_map( PENDRAGON_PATH + PENDRAGON_LIBFILE );
   librmap[1] = PENDRAGON_DEFAULT_NAME;
   return;
}

void
create_monster()
{
    if(!IS_CLONE)
	return;

    set_name( WWNAME );
    set_living_name( WWNAME );
    set_title("the Woman in Woad");
    set_race_name("human");
    add_name("woman");

    set_adj("supine");
    add_adj("shrouded in woad");

    set_gender(1);  // female

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_HEIGHT, 195);
    add_prop(CONT_I_WEIGHT, 25000);

    set_long("Before you, a woman lies upon an old stone" +
        " platform, exposed to the elements. At first glance she" +
        " appears shrouded in a shift of weathered indigo woad.\n");

    set_short("woman lying supine in woad");

    add_item(({"body","woman","shift","shroud","indigo","woad"}),
      "Upon closer inspection, the woman appears not to be clothed"+
      " at all. Instead, the entireity of her skin is covered in"+
      " a web of tattooed runes, inscribed in a peculiar cursive"+
      " form, and deeply stained indigo from woad. Though her skin"+
      " is perfectly preserved in woad, she is without flesh, having been"+
      " excarnated in this place; an offering in peace to the hunger"+
      " of all the small beasts of creation. There appears to be nothing"+
      " between her tattooed skin and her frame within, drawn taut"+
      " with the passage of time. Her eyes are closed, their colour"+
      " unknown. Her hair"+
      " of fiery red, streaked white and grey, lays spread across a"+
      " heavy scroll, burned and turned to stone, and set as a pillow"+
      " for her repose. Her hands bear a festoon of white mayflowers"+
      " across her hips, seemingly fresh despite the season. Her full lips"+
      " tattooed in woad are ever so slightly curled into an enigmatic"+
      " smile. The vivid woad tattoos upon her form capture the eye.\n");  

    add_item(({"platform","stone platform","stone","elements","place"}),
      "An old stone platform stands knee-high to the ground. It has been"+
      " worn smooth with the action of wind and rain and sun and ice over"+
      " a very long time. While it is edged in ancient lichen, its central"+
      " portion remains pristine about the figure lying upon it."+
      " Splotches of myriad colour have stained the fringing lichen as"+
      " though paint or ink has been spattered carelessly about."+
      " Worn runes are cut deep into the sides of the platform, but"+
      " they are beyond your ken. Though the wind from afar seems"+
      " strong, there is but a gentle breeze about the platform and"+
      " its occupant.\n");

    add_item(({"flowers","mayflowers","white flowers","white mayflowers"}),
      "The festoon consists of flowers of white, each of five small petals"+
      " with a spray of stamens and anther emergent from within. They"+
      " offer up the scent of flesh, and yet no creatures crawl upon them.\n");

    add_item(({"pillow","stone scroll","scroll","burned scroll"}),
      "The scroll beneath the head and hair of the woman is a curious"+
      " thing. It is as long as a the spread of an eagle's wings and"+
      " as thick as log, with tightly wound parchment"+
      " rent in many places and burned through in others, but all"+
      " rendered in sheets of glittering stone, so as to never"+
      " unfurl again.\n");

    add_item(({"tattoos","cursive","runes","cursive tattoos","cursive runes"}),
      "Cursive runes, large and small, are tattooed across every aspect of the"+
      " parchment skin of the Woman in Woad. Together they form an intricate"+
      " pattern of arcana, which escapes lay understanding. The"+
      " largest tattoos appear as titles in the common tongue above tracts"+
      " written densely in unfamiliar languages. One can only guess at the"+
      " secrets coded"+
      " under the titles of 'The Fae', 'Changelings', 'The Ways',"+
      " 'Familiars', 'Enchantment' and such. Clearly this woman is possessed"+
      " of a great body of knowledge; a peculiar portable library. The"+
      " tattoo upon her forehead, is arranged about an illumination of Danu,"+
      " Goddess of Wisdom. It seems to be legible in the common"+
      " tongue.\n");

    add_item(({"fae", "changelings", "ways", "familiars", "enchantment"}),
      "The vast body of knowledge in tattoed runes below this title are beyond"+
      " understanding.\n");

    add_item(({"tattoo","danu","forehead","common tongue","Danu","trove"}),
      "A tattoo on the woman's forehead is a common tongue"+
      " account named the Trove of Danu:\n\n"+
      "~~         Danu wrote about Seelie Sidhe...       ~~\n"+
      "~~        Danu wrote about Unseelie Sidhe...      ~~\n"+
      "~~     She gave of so much in mortal books,       ~~\n"+
      "~~    jealous Sidhe decided none should look;     ~~\n"+
      "~~   they cast them to stone and burned them too  ~~\n"+
      "~~    but ere the end -- in aid pendragons flew   ~~\n"+
      "~~      so to tattoo Her trove upon me true.      ~~\n\n");

    add_item(({"dragon","aid","pendragon","pendragons"}),
      "An illuminated tattoo of a dragon in a cloud is surrounded"+
      " by runes which can be interpreted in the common tongue"+
      " as 'a gift', or 'The Gift'. It is dedicated to all Keepers"+
      " of Written Words, from Danu, Goddess of Wisdom, so that they"+
      " might better discharge their sacred duty.\n");

    add_item(({"sidhe","Sidhe"}),
      "One tattoo warns the examiner that the Aon Sidhe,"+
      " the Trooping Fae, are not to"+
      " be slighted by mortals of even the greatest reknown"+
      " nor trifled with at all in this wide green land of Khalakhor."+
      " As best you can tell there are none hereabouts. Perhaps the"+
      " Goddess Danu has intervened to keep them from this place.\n");

    add_item(({"gift","the gift","The Gift","Gift"}),
      "Perhaps the time has come to ask about the gift.\n");

    add_ask(({"gift","the gift","The Gift","Gift","about the gift"}),
       VBFC_ME("dragon_ask"),1);

    set_default_answer(VBFC_ME("react_to_asking"),1);

    set_act_time(15);

    add_act("@@keening_chitter");
    add_act("@@flicker_movement");
    add_act("@@smell_of_hawthorn");

    add_act("emote 's parchment skin thrums with the gentle breeze; like" +
            " a drum, held taut over its frame.\n");

    trig_new("%w 'introduces' %s","react_to_intro");

    trig_new("%w 'says' %s","react_to_saying");
    trig_new("%w 'shouts' %s","react_to_saying");
    trig_new("%w 'grates' %s","react_to_saying");
    trig_new("%w 'mumbles' %s","react_to_saying");
    trig_new("%w 'hisses' %s","react_to_saying");
    trig_new("%w 'thunders' %s","react_to_saying");
    trig_new("%w 'sings' %s","react_to_saying");
    trig_new("%w 'whispers' %s","react_to_saying");
    trig_new("%w 'chirps' %s","react_to_saying");
    trig_new("%w 'bellows' %s","react_to_saying");

    set_stats(({90,160,400,400,400,200}));
    set_hp(query_max_hp());

    add_prop(OBJ_I_NO_ATTACK, "@@no_attack");
    add_prop(OBJ_I_NO_MAGIC, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_TELEPORT, 1);
    add_prop(OBJ_I_NO_BUY, 1);
    add_prop(OBJ_I_NO_SELL, 1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE,1);

    get_library_data();
}

void
react_to_asking()
{
    write("The indigo lips of the Woman in Woad are unmoved at your question." +
     " Perhaps the answer lies upon her body of knowledge.\n"); 
    return;
}

void
react_to_intro(string who,string garbage)
{
    set_alarm(3.0,0.0, 
              &tell_room(environment(this_object()),
              "As though from boughs of hawthorn trees "+
              "creaking in the wind, there comes the name of '" +
              capitalize(WWNAME) + "' as if in reply.\n\n"));
}

void
react_to_saying(string who,string garbage)
{

    set_alarm(3.0,0.0, 
              &tell_room(environment(this_object()),
              "The sound of the wind abruptly rises, drowning "+
              "out mortal statements in this place set aside for "+
              "examination and asking.\n\n"));
}

void
dragon_call()
{

    object pendrg;
    object plibrary, librarian;
    
    int iobj;
    object *ownerobj;

    int iagree, nlbr, ilbr;
    int inkidx, nink;
    mixed ind, val; 
    string lname, pname;
    string inks = "alizarin amaranth amber amethyst aquamarine azure black" +
                  " blue bronze cerulean chartreuse cinnabar cobalt copper" +
                  " crimson cyan emerald gold green harlequin jade magenta" +
                  " maroon olivine purple red ruby sapphire scarlet sepia" +
                  " silver turquoise ultramarine vermilion violet viridian";
    string *ink;

    ind = m_indices(librmap);
    val = m_values(librmap);

    nlbr = (sizeof(ind));

    pname = this_player()->query_real_name();

    // loop through librmap, interpreting data as library or librarian
    // and making appropriate comparisons with this player

    for (iagree=0,ilbr=0;ilbr<nlbr;ilbr++) 
    {
        lname = val[ilbr];

        librarian = find_living(lname);

        if (!librarian)
        { 
           plibrary = find_object(lname);
           if (!plibrary)
           {
              continue;  // non-object garbage
           }
           else // *is* potential library
           {
               if (!function_exists("query_librarian",plibrary))
               {
                   continue;  // non-library object
               } 
               else  // *is* actual library
               {
                  iagree = plibrary->query_librarian(this_player());
                  if (iagree) break;
               }
           }
        }
        else // *is* a librarian
        {
             if (lname == pname) 
             {
                 iagree = 1;
                 break;
             }
        }

    } // for loop nlbr


    if (iagree) 
    {

        ownerobj = all_inventory(this_player());

        for (iobj=0;iobj<sizeof(ownerobj);iobj++)
        {
            if ( lower_case(ownerobj[iobj]->query_name()) == PENDRAGON_NAME )
            {

               if ( lower_case(ownerobj[iobj]->query_adj(0)) == PENDRAGON_ADJ )
               {
                   write("Your pendragon waves a wing-tip before you," +
                   " thinking that you had forgotten she was there," +
                   " and that one pendragon is enough for anyone.\n");

                   say("A pendragon gestures anxiously to "
                      + QTNAME(this_player()) +".\n");

                   return;
               }

           }
        }

        ink = explode(inks, " ");
        nink = sizeof(ink);

        inkidx = NAME_TO_RANDOM( pname, COLOUR_SEED, nink );

        write("A flapping shape appears abruptly" +
           " in mid-air above the form of the Woman in Woad amidst" +
           " a swirling cloud of " + ink[inkidx] + " ink drops.\n\n" +    
           " After examining you carefully, the" +
           " tiny dragon impulsively wings its way to land"+
           " on your shoulder and wrap her tail tightly about your neck.\n\n" +
           " This pendragon is imprinted on you, " +
             capitalize(pname) +
           ", in your duty as a Keeper of Written Words.\n\n" +
           " She is at your command to <dragon_tattoo your words...> of wisdom"+
           " upon your flesh."+
           " You may keep or <scour> these tattoos as you wish."+
           " By way of these tattoos you may also summon her to your shoulder"+
           " when you wake.\n\n"+
           " Where once your body was a but temple, it is now become"+
           " a library also.\n\n");

        say("A tiny dragon appears to " + QCTNAME(this_player()) +".\n");

        setuid();
        seteuid(getuid());
        pendrg = clone_object(PENDRAGON_PATH + "pendragon");
        pendrg->move(this_player(),1);

        pendrg->assign_librarian_name( pname );
        pendrg->assign_ink_colour( ink[inkidx] );

        return;
    }
    else 
    {
        write("Your claim to the Gift as a Keeper of Written Words" +
           " goes unrecognised by the powers that be here and now.\n\n");
        tell_room(environment(this_object()),
          "A tear escapes the closed left eye of the Woman in Woad.\n\n"); 

        return;
    }


}


int
read(string str)
{
    if( (str == "tattoo") || (str == "tattoos") )
    {
        write("Tattooed runes are not for reading." +
               " They are for examining.\n");
        return 1;
    }
    if( (str == "gift") || (str == "Gift") )
    {
        write("Tattooed runes are not for reading." +
               " They are for examining.\n");
        return 1;
    }
    if( (str == "pendragon") || (str == "dragon") )
    {
        write("Tattooed runes are not for reading." +
               " They are for examining.\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

void
dragon_ask()
{
    tell_room(environment(this_object()),
        "The indigo lips of the Woman in Woad part in a momentary grin.\n\n"); 

    set_alarm(3.0,0.0,&dragon_call()); 
}

