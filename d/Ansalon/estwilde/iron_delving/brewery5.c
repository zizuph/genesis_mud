
/* 
 *  d/Ansalon/estwilde/iron_delving/brewery5.c
 *
 * A barrel-shaped hole between worlds, hidden
 * by way of a barrel-cot in the Iron Delving
 * Brewery (IDB) entrance vestibule.
 *
 * It is a means to view from Krynn
 * another world (ancient Sumer) where Ninkasi
 * goddess of fermentation brought beer and
 * brewing into existence. In Sumer, libations
 * are poured into funerary mounds so that the
 * dead of the Underworld (Kur) might have some
 * succour in the afterlife.
 *
 * The far end of the barrel-cot protrudes
 * into a cave which overlooks Kur, the domain
 * of Ereshkigal, whose palace of Ganzir can be
 * seen in the far distance across the shadowy
 * dusty plain.
 *
 * Any mortal of our Realms that enters bearing
 * the IDB Championship Grail as a libation to
 * Ninkasi is granted the ability to serve as
 * her Libator.
 *
 * Other mortals can visit this place and sample
 * the sacred brew which rains from above in Kur
 * by the intervention of Ninkasi, and fill crystal
 * vessels from a stream which runs at the cave
 * mouth.
 *
 * The brew of the IDB champion is a libation 
 * to Ninkasi which is falling from the 'sky'
 * in a rain-storm upon the plain of Kur.
 * The sound and smell of the storm are
 * overpowering. The magical power of fermentation
 * wrought by the goddess dominate this place.
 *  ... it is a free emote space; mortal magicks
 *    and combat actions lead to unconciousness;
 *     and many ordinary actions fail in an
 *      inebriated haze
 *
 * The crystal vessels from which the brew is
 * drunk are sacred items which must not be
 * removed. There is a quest to retrieve one
 * for a mortal questmaster in Krynn.
 *
 * free emote source code is copied from:
 * /d/Khalakhor/guilds/eilgalaith/room/emotes.c
 * (created by Damaris@Genesis 08/2006)
 *
 * Vitwitch 02/2021
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/estwilde/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <files.h>
#include <const.h>
#include <options.h>
#include <filter_funs.h>
#include <living_desc.h>
#include "/d/Ansalon/common/brewcraft/brewcraft.h"

#define BREWVESSL "/d/Ansalon/estwilde/obj/brewcraft_beervessel_full"
#define EMPTYVESL "/d/Ansalon/estwilde/obj/brewcraft_beervessel_empty"
#define BREWGRAIL "/d/Ansalon/estwilde/obj/brewcraft_beergrail"
#define BREWVESLNM "_brewcraft_beer_vessel_full"

#define STDPARALY "/std/paralyze.c"

#define PASSOUTRECOVER "_recovery_from_barrelhole_passout"
#define PASSEDOUTTIME 10.0

#define ALLOW_BREW_THIEVES 1
#define VESSEL_CATCH_PCT 50 
#define MAX_DRUNK_PCT 100

#define RARE_VESSEL_CHANCE_PCT 2

#define RAREVNUMTYPE 2
#define RAREVSTR "/d/Ansalon/estwilde/obj/brewcraft_beervessel_rare"

#define BARRELHOLE_I_LIBR_HERE "_barrelhole_i_libr_here"
#define BARRELHOLE_I_OPEN "_barrelhole_i_open"
#define BARRELHOLE_I_LIBATOR "_barrelhole_i_libator"
#define BARRELHOLE_I_LIBR_LEAVING "_barrelhole_i_libr_leaving"
#define BARRELHOLE_I_MORTAL_CAN_ENTER "_barrelhole_i_mortal_can_enter"
#define BARRELHOLE_I_GRAIL_CAN_ENTER "_barrelhole_i_grail_can_enter"

#define EJECTROOM "brewery6"

inherit DWARF_IN;

static int gAllowBrewThieves = ALLOW_BREW_THIEVES;
static object gLibator; 
static string gBarrelName = "";

static mapping banned_patrons;

/* PROTOTYPES */

void reset_banned_patron_map();
void reset_dwarf_room();
int drunk_action( string action, int difficulty );
int departure_check();
hook_smelled(string str);
string short_descr();
string long_descr();
void create_dwarf_room();
public int query_patron_banned( object patron );
void message_from_ninkasi(object player);
void come_to(object player);
int pass_out( string str );
int query_rarevessel_pct();
string rarevessel();
int has_no_fullvessel( object ob );
int deliver_drink(object patron);
int serve_it(string whostr);
int close_it();
int open_it();
int fill_bottle(string str);
int is_vessel( object ob );
int strip_vessel_bearer( object player );
int is_grail( object ob );
int strip_grail_bearer( object player );
int if_libator_arrives(object player);
void eject_patrons();
int if_libator_leaves(object player);
int if_patron_arrives(object player);
static nomask string cat_string(mixed org, string what, object pl, int up);
static nomask mixed mk_item(object ob);
static nomask void tell_them(object ob, mixed arg);
nomask int emote(string arg);
nomask void init_emotes();
void enter_inv(object ob, object from);
void leave_inv(object ob, object to);
public int catch_all(string str);
int read_it(string str);
int wish_it(string str);
int libator_here();
int libator_can_intone(object asker);
varargs int libator_intones(string message,object recipient);
int ask_it(string str);
void init();

/* FUNCTIONS */

void
reset_banned_patron_map()
{
    banned_patrons = ([]);
}

void
reset_dwarf_room()
{
    remove_prop(BARRELHOLE_I_OPEN);
    set_alarm(1.0, 3600.0, reset_banned_patron_map);
}

int
drunk_action( string action, int difficulty )
{
    int intoxPCT;
    int unsuccessful;
    string intent, instead0, instead1, adverb;
    string sentence;

    intoxPCT = ( 100 * TP->query_intoxicated() ) 
             / TP->intoxicated_max();
    intoxPCT = min( intoxPCT, MAX_DRUNK_PCT );
    
    unsuccessful = ( random(100) > (100 - intoxPCT - max(0, difficulty) * 50) );

    if ( unsuccessful ) 
    {

        adverb = one_of_list( ({"confused","befuddled","bumfuzzled",
                                "in a haze","drunk","glassy-eyed"}) );
        switch (action)
        {
            case "depart":
            case "go":
                intent = "leave this place";
                instead0 = one_of_list( ({"wandered about","staggered about"}));
                instead1 = one_of_list( ({"bumping into things",
                              "peering at stuff","stopping at random"}));
                break;
            case "reveal":
            case "search":
                intent = action + " stuff";
                instead0 = one_of_list(({"examined the floor","peered about"}));
                instead1 = one_of_list( ({"pointing at things others cannot see",
                                     "starting at shadows"}) );
                break;
            case "hide":
            case "sneak":
                intent = action;
                instead0 = one_of_list(({"just crouched down","tripped over"}));
                instead1 = one_of_list( ({"while making a loud ssssshhhing noise",
                        "while burping loudly",
                        "in plain sight", "while looking out between parted fingers"}) );
                break;
            case "get":
                intent = action + " some thing or other";
                instead0 = one_of_list(({"grabbed at thin air","fumbled the grab"}));
                instead1 = one_of_list( ({"at the sight of a passing vessel",
                               "while shouting that it stop moving about",
                                "and was left looking at empty hands"}) );
                break;
            case "wear":
            case "remove":
                intent = action + " some thing or other";
                instead0 = one_of_list( ({"seemed to get caught-up",
                              "fruitlessly fumbled with fastenings"}) );
                instead1 = one_of_list( ({"for an age or more",
                                "while loudly protesting"}) );
                break;
            case "give":
            case "put":
                intent = action + " some thing or other";
                instead0 = one_of_list( ({"seemed to forget to let go",
                              "pocketed it with a nod"}) );
                instead1 = one_of_list( ({"while rubbernecking for more brew",
                                "while humming a tune"}) );
                break;
            case "send":
                intent = "write a message";
                instead0 = one_of_list( ({"forgot the purpose of it",
                              "lost their train of thought"}) );
                instead1 = one_of_list( ({
                        "and wondered aloud if chipmunks board ships",
                        "and sang a song about a lost pigeon",
                        "and complained that harrekkis are mean"}) );
                break;
            case "open":
            case "close":
            case "wield":
            case "unwield":
            case "extinguish":
            case "light":
                intent = action + " some thing or another";
                instead0 = one_of_list( ({"stopped to ponder the meaning of it all",
                                         "paused in thought... for some time"}) );
                instead1 = one_of_list( ({"while whistling tunelessly",
                                    "while staring at the ceiling",
                                "while letting out a long warbling fart"}) );
            default:
                intent = "do some thing or another";
                instead0 = one_of_list( ({"stopped to ponder the meaning of it all",
                                         "paused in thought... for some time"}) );
                instead1 = one_of_list( ({"while whistling tunelessly",
                                    "while staring at the ceiling",
                                "while letting out a long warbling fart"}) );
        }

        sentence = sprintf("to %s, but instead %s, %s, %s.\n",
                            intent,instead0,adverb,instead1);
        TP->catch_msg("You intended " + sentence);
        tell_room(TO,QCNAME(TP) + " seemed to try to " + sentence, TP);

    }

    return unsuccessful;
}


int
departure_check()
{             
    int n;
    string afterw0, afterw1;

    if ( TP->query_prop(BARRELHOLE_I_LIBATOR) )
    {
        if ( !TP->query_prop(BARRELHOLE_I_LIBR_LEAVING) )
        {
            TP->add_prop(BARRELHOLE_I_LIBR_LEAVING,1);
            write("Are you sure you want to leave? "+
             "There is no coming back without another grail. "+
             "Repeat the command to leave to be gone from this place.\n");
            return 1;
        }
        else
            TP->remove_prop(BARRELHOLE_I_LIBR_LEAVING);
            return 0;
    }

    if ( drunk_action("depart",0) ) return 1;

    if ( random(100) < VESSEL_CATCH_PCT )
    {
        n = strip_vessel_bearer(TP);
        if ( n > 0 )
        {
            afterw0 = "into a constellation"
                    + " of fragments under the gaze of ";
            afterw1 = ". As ethereal forces unseen sweep the glittering"
                    + " fragments outside through"
                    + " the cave-mouth, you feel a heavy censure settle upon"
                    + " you.\n";

            if ( n > 1 ) 
                write("On your way out, you drop " + val2str(n) + " crystal "
                    + " vessels on the shifting floor of the barrel. "
                    + "They shatter " + afterw0 
                    + gLibator->query_art_name(TP) + afterw1);
            else
                write("On your way out, you accidentally drop a crystal"
                    + " vessel on the shifting floor of the barrel. "
                    + "It shatters " + afterw0 
                    + gLibator->query_art_name(TP) + afterw1);
            if (!gAllowBrewThieves)
                banned_patrons[TP->query_real_name()] = val2str(time());
        }

        write("You stumble out of " + gBarrelName + " back to the "+
               "real world.\n\n");
        tell_room(E(TP),QCNAME(TP) + " stumbles out of "
                 + gBarrelName + " back to the real world.\n",TP);
        tell_room(IRON + "brewery1", QCNAME(TP) + " stumbles out of "
                 + "first barrel-cot.\n");
    }

    return 0; // can leave in any case
}


public void
hook_smelled(string str)
{
    write("The smell of fermentation overwhelms all "+
          "-- throbbing in the nose -- "+
          "as though the whole world is past ripe and everywhere changed. "+
          "Within this raw power there is the strong aroma of cedar, "+
          "as well as a faint trace of " + BREWCRAFT_SMELLG + ".\n");
}


string
short_descr()
{
    return "a curious barrel-shaped hole between worlds: " + gBarrelName;
}


string
long_descr()
{
    return "This is a curious space. You sense it is a place apart from "+
           "Krynn, yet not quite a part of any other Realm either. "+
           "Inwardly it is has the form of a large ID Brewery barrel, "+
           "complete with the smell of brew. Age-stained wooden staves "+
           "make up the floor, walls and ceiling in an unbroken curve. "+
           "The barrel is wide "+
           "enough for three or four dwarves to stand one upon the other "+
           "and still have ample headroom. At one end, a wooden barrel "+
           "head is marked by some kind of graffito. You recognise "+
           "this head as the way by which you entered from Krynn. "+
           "In the opposite direction, the barrel runs "+
           "for a short dragonlength before it stops open-ended, flush "+
           "against a rocky cave-mouth. A stele is carved from rock; "+
           "framed by the cave-mouth against a dark storm outside. A warm "+
           "golden light suffuses the entire space; sufficient for you to "+
           "make out that the barrel is continuously turning on its axis "+
           "very slowly.\n";
}

void
create_dwarf_room()
{
    string grafadj, raceadj, raceplural;

    gBarrelName = capitalize(BREWCRAFT_NAMEG) + "'s Barrelhole";

    set_name(gBarrelName);

    set_short("@@short_descr");
    set_long("@@long_descr");

    add_prop(ROOM_I_LIGHT,1); // light of the Goddess Ninkasi
    add_prop(ROOM_M_NO_ATTACK, "@@pass_out|attack@@");
    add_prop(ROOM_M_NO_MAGIC, "@@pass_out|magic@@");
    add_prop(ROOM_M_NO_SCRY, 1);
    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_I_NO_STEAL, "@@pass_out|steal@@");
    add_prop(ROOM_M_NO_TELEPORT_FROM, "@@pass_out|teleport@@");

    if ( BREWCRAFT_ALIGNG > 100 )
       grafadj = "fine ";
    else
       grafadj = "cruel ";

    switch ( BREWCRAFT_RACEG )
    {
        case "goblin":
        case "human":
        case "gnome":
            raceadj = BREWCRAFT_RACEG;
            raceplural = BREWCRAFT_RACEG + "s";
            break;
        case "elf":
            raceadj = "elven";
            raceplural = "elves";
            break;
        case "dwarf":
            raceadj = "dwarven";
            raceplural = "dwarves";
            break;
        case "hobbit":
            raceadj = "halfling";
            raceplural = "halflings";
            break;
    }

    add_item(({"barrel","barrelcot","barrelhole"}), 
        "The barrel is four dwarfheights wide and runs for a short "+
        "dragonlength from end to end (not the "+
        "length of a drake fully outstretched; but the length of "+
        "one curled-up snug in its wyrmhole). " + 
        "It is warmly illuminated by golden light from the rocks "+
        "and stele at its open end. The barrel turns slowly on its axis, "+
        "causing you to "+
        "have to adjust your footing on its moving surface every once "+
        "in a while. The slow rotation of the barrel causes constellations "+
        "of pinpoints to flare and fade before your eyes -- reflecting "+
        "and refracting light as angles shift. The closed end of the "+
        "barrel bears a scratched grafitto. Beyond the message and the "+
        "wood of the closed end lies Krynn, beckoning you <krynnward> "+
        "to exit this odd place.\n");

    add_item(({"staves","wood","pinpoints","sparkles","constellations"}), 
        "Looking closely at the dark-stained staves of the barrel, you "+
        "can see countless tiny jagged fragments of crystal are embedded "+
        "in the wood. They catch the eye, sparkling in every hue, when "+
        "the viewing angles for each are just so.\n");

    add_item(({"closed end","krynnward end","barrel head"}), 
        "The closed barrel head bears a scratched grafitto. Beyond the "+
        "wood of this closed end lies Krynn and its dubious comforts, "+
        "calling you <krynnward> away from this gap between worlds.\n");

    add_item(({"graffito"}),
        "An expansive graffito is scratched deep in the "+
        "aged wood of the barrel. It is placed fartherest from the dark "+
        "unknown of the cave-like end of the barrel; instead it is on the "+
        "closed Krynnward end, closest to the familiarity of the known world. "+
        "The " + grafadj + raceadj + " lettering of the graffito spell out "+
        "words in the common tongue; easy enough to <read>.\n"); 

    add_item(({"stele"}), 
        "Standing at the height of a modest dwarf, the stele seems to have " +
        "been carved from the living rock of the cave, perhaps in the act " +
        "of creating the cave-mouth itself. Each side of this irregular "+
        "obelisque contains a tablet bearing line after line of intricate "+
        "wedge-shaped impressions. In studying the tablets, you "+
        "feel new knowledge pressing upon your mind and filling it. You feel "+
        "you can <read> these tablets.\n");

    add_item(({"tablets","tablet"}),
        "You are sure you can <read> the tablets on the stele.\n");
 
    add_item(({"rock","rocks","light","golden light","warm golden light"}), 
        "The rocks of the cave-mouth and the stele cast a warm golden "+
        "light over the entireity of the space. Though constant like "+
        "the sun, the light is cut by figures in the barrel; casting "+
        "shadows Krynn-ward. Shadows that move with every mortal movement. "+
        "Where the light falls on wood, myriad pinpoints sparkle.\n");

    add_item(({"cave","cave-mouth","open end"}),
        "Beyond the rocks and stele of the cave-mouth, at the open end "+
        "of the barrel, you can see there is a plain far below in the "+
        "darkness outside.\n");

    add_item(({"outside","plain","darkness","dark plain"}),
        "It is difficult to make out features "+
        "on the plain outside, especially since the whole vista lies "+
        "under a downpour of rain from a dark storm overhead. "+
        "Lightning cracks and flashes in the darkness from "+
        "time to time, providing a better glimpse of the plain. "+
        "Despite the downpour, it seems that clouds of dark dust "+
        "are being raised by the storm's winds. Among the streaks of "+
        "dust you see endless ranks of naked figures, "+
        "downcast and "+
        "immobile, standing dead in place. Far across the plain, the "+
        "high walls of a palace pierce the horizon.\n");

    add_item(({"walls","high walls","palace","palace walls","horizon"}),
        "Lightning flashes occasionally illuminate the high walls " +
        "of a palace on the horizon. They are largely shrouded in the "+
        "clouds of dust which pervade the plain. What can be seen of "+ 
        "them is built so high and sheer that in many places they have "+
        "tumbled down. Their tops and breaches are populated by "+
        "innumerable figures standing like statues.\n");

    add_item(({"storm","rain","downpour","downpour of rain","dark storm"}),
        "A steady downpour of rain falls in windblown sheets across the "+
        "plain outside; lightning flashes in the swollen storm clouds, "+
        "momentarily banishing the dark. The sound of the rain crashing "+
        "on the rocks outside rises and falls with passing gusts. A "+
        "stream runs off the rocks and flows into the cave-mouth. The "+
        "strong smell of the stream leaves no doubt in you mind... it is "+
        "raining beer!\n");

    set_tell_time(500);
    add_tell("Lightning illuminates " 
            + raceplural + " among the dead; their dusty mouths "
            + "upturned to receive the downpour of brew.\n");
    add_tell("Thunder rumbles outside across the plain in darkness.\n");
    add_tell("The rain beats a soothing cadence on the rocks outside"+
             " while a chuckling stream of brew flows into the cave-mouth.\n");
    add_tell("A gust of wind blows scent into the barrelhole from outside.\n");
    add_tell("You shift on aged wood as the barrelhole slowly turns.\n");

    add_exit(IRON + "brewery1","krynnward","@@departure_check",0);

    reset_dwarf_room();
}


public int
query_patron_banned( object patron )
{
    if ( !banned_patrons[patron->query_real_name()] ) return 0;
    return 1;
}


void
message_from_ninkasi(object player)
{
    if ( !libator_can_intone(player) ) return;

    if ( player->query_prop(BARRELHOLE_I_LIBATOR) )
    {

        // libation as flashback in past tense ... while unco

        player->catch_msg("" +
          "You recall images, sounds and smells:\n" +
          "the overpowering scent of ancient "+
                "fermentation...\n" +
          "the glory of the libation: the " +
                  capitalize(BREWCRAFT_STYLEG) + 
                " of the grail transcendent and in flood...\n" + 
          "the sudden crack of thunder and onset of rain crashing down outside in the dark...\n"+
          "the boundless legions of the Dead, lit by lightning on the dusty "+
              "plain, mouths upraised to the deluge...\n\n");

        libator_intones("\nYou are granted Dominion of this Hole Between Worlds "+
              "for as long as you choose to Remain. You are granted Power "+
              "to uphold my Laws and embody the Secret of Life among "+
              "mortals before legions of the Dead. <ask> for instruction, "+
              "should you desire it."
               ,player);

    }
    else
    {
        // message for normal patrons
        libator_intones("I bid You follow "+
          "My Laws and pursue the Secret of Life."
            ,player);

    }

    player->catch_msg("You feel yourself blessed; "+
                    "free from all bounds of emotion.\n\n");
    player->command("emote lets go in the presence of Ninkasi.");
}


void
come_to(object player)
{
    tell_object(player, "You regain your senses...\n\n");
    present(PASSOUTRECOVER, player)->remove_object();

    message_from_ninkasi(player);
}


int
pass_out( string str )
{
    float nsec = PASSEDOUTTIME;
    string context, str3rd;
    object obj;

    switch ( str )
    {
        case "arrive":
            context = "Arriving";
            str3rd = " stumbles.\n";
            break;
        case "attack":
            context = "Attempting an attack";
            str3rd = " threatens an attack.\n";
            break;
        case "magic":
            context = "Attempting magicks";
            str3rd = " plays at magicks as a mortal.\n";
            break;
        case "teleport":
            context = "Attempting teleportation";
            str3rd = " plays at magicks as a mortal.\n";
            break;
        case "steal":
            context = "Attempting to steal";
            str3rd = " attempts to steal.\n";
            break;
        default:
    }

    write(context + " in the confusion of this"
          + " barrelhole between worlds, you"
          + " feel the room around you"
          + " spin and spin and spin.\n\n"
          + "Divine laughter fills your mind.\n\n");
    tell_room(E(TP),QCNAME(TP) + str3rd, TP);

    if ( !present(PASSOUTRECOVER, TP) )
    {
        write("Your eyes flutter... you fall unconscious...\n\n");
        tell_room(E(TP),QCNAME(TP) + " collapses...\n",TP);

        set_alarm(nsec, 0.0, &come_to(TP));
        seteuid(getuid(this_object()));
        obj = clone_object(STDPARALY);
        obj->set_standard_paralyze(short(TP) + " passed out");
        obj->set_fail_message("You are unconscious.\n");
        obj->set_stop_message("You recover consciousness...\n");
        obj->set_name(PASSOUTRECOVER);
        obj->set_remove_time(ftoi(nsec) + 1);
        obj->move(TP, 1);
    }

    return 1;
}

int
query_rarevessel_pct()
{
    int pct = RARE_VESSEL_CHANCE_PCT;
    return pct;
}

string
rarevessel()
{
    int j, m, i, n, ns;
    int *selectf;

    m = RAREVNUMTYPE;
    if ( m < 1 ) return EMPTYVESL;

    selectf = ({});
    for ( j=0;j<m;j++ ) 
    {
        n = j * 3 + 1;
        for ( i=0;i<n;i++ )
            selectf += ({j});
    }
 
    ns = sizeof(selectf);
    if ( !ns ) return EMPTYVESL;
    
    return sprintf("%s%d",RAREVSTR,selectf[random(ns)]);
}


int
deliver_drink(object patron)
{
    string str;
    object vessel;

    if ( !patron || !objectp(patron) ) return 0;

    str = "A crystal vessel enters the barrelhole, "+
        "having crossed the threshold between worlds.";

    if ( random(100) < RARE_VESSEL_CHANCE_PCT )
    {
        tell_room(TO,"\nA bolt of lightning strikes at the cave-mouth; "+
                    "thunder crashes all about.\n\n");
        patron->catch_msg(str + " You receive it empty... but charged with "+
                    "ethereal power.\n\n");
        tell_room(TO,QCTNAME(patron) + " receives an oddly charged vessel.\n",
                     patron);
        vessel = clone_object(rarevessel());
    }
    else
    {
        patron->catch_msg(str + " You receive it charged with brew.\n\n");
        tell_room(TO,QCTNAME(patron) + " receives a vessel of brew.\n", patron);
        vessel = clone_object(BREWVESSL);
    }

    return vessel->move(patron);
}


int
has_no_fullvessel( object ob )
{
   if ( sizeof(filter(deep_inventory(ob),is_vessel)) > 0 )
           return 0;

    return 1;
}


int
serve_it(string whostr)
{
    string str, str0, strps, str1, lwho;
    object pobj, *patrons, *recips, *inv;

    if ( !(TP->query_prop(BARRELHOLE_I_LIBATOR)) ) return 0;

    inv = all_inventory(TO);
    patrons = FILTER_PLAYERS(inv);
    inv -= patrons;

    // no one is served if there are full vessels on floor
    // noting that full vessels cannot be put in containers

    if ( sizeof(filter( inv, is_vessel )) > 0 )
    {
        write("\nFull vessels of " + BREWCRAFT_STYLEG + 
          " are unclaimed in the barrelhole... "+
          " an afront to Ninkasi... respect the Goddess..."+
          " tidy up and drink up!\n");
        return 1;
    }

    if ( whostr ) 
    {
        lwho = lower_case(whostr);

        switch (lwho)
        {
            case "me":
                patrons = ({ gLibator });
                break;
            case "team":
                patrons = FILTER_PRESENT(TP->query_team_others()) + ({TP});
                break;
            default:
                pobj = find_player(lwho);
                if (environment(pobj) == this_object())
                    patrons = ({pobj});
                break;
        }
    }

    recips = filter( patrons, has_no_fullvessel );

    switch (sizeof(recips))
    {
        case 0:
            write("\nAll who you would <serve> have a full "+
                    "vessel in their possession already.\n");
            return 1;
        case 1:
            strps = " a crystal vessel that fills";
            break;
        default:
            strps = " crystal vessels that fill";
            break;
    }

    str0 = "an arm towards the cave-mouth, summoning forth from Ganzir";
    str1 = " in the downpour crossing the plain of Kur.\n";

    str = str0 + strps + str1;

    write("\nYou extend " + str);
    tell_room(TO,"\n" + QCNAME(gLibator) + " extends " + str,TP);

    foreach(object recipient: recips)
       deliver_drink(recipient);

    return 1;
}


int
close_it()
{
    if ( !(TP->query_prop(BARRELHOLE_I_LIBATOR)) ) return 0;
    TO->remove_prop(BARRELHOLE_I_OPEN);

    write("You sense the divine hand of Ninkasi barring "+
           "the Krynnward entrance of this place to new arrivals.\n");

    return 1;
}


int
open_it()
{
    if ( !(TP->query_prop(BARRELHOLE_I_LIBATOR)) ) return 0;
    TO->add_prop(BARRELHOLE_I_OPEN,1);

    write("You sense the divine hand of Ninkasi opening "+
           "the Krynnward entrance of this place to new arrivals.\n");

    return 1;
}


int
fill_bottle(string str)
{
    if( wildmatch("*bottle*",lower_case(str)))
    {
        TP->catch_msg("Dazed and confused, you splash precious brew on your "+
                      "hands instead of in the bottle!\n");

        return 1;
    }
    return 0;
}


int
is_vessel( object ob )
{
    return ( wildmatch(sprintf("%s*",BREWVESSL),file_name(ob)) );
}

int
strip_vessel_bearer( object player )
{
    object *vessels;

    vessels = filter( all_inventory(player), is_vessel );

    foreach ( object vessel : vessels )
        vessel->remove_object();

    return sizeof(vessels);
}


int
is_grail( object ob )
{
    return ( wildmatch(sprintf("%s*",BREWGRAIL),file_name(ob)) );
}

int
strip_grail_bearer( object player )
{
    object *grails;

    grails = filter( all_inventory(player), is_grail );

    // only strip one grail if there are many
    if ( sizeof(grails) > 0 )  
    {
        grails[0]->remove_object();
        return 1;
    }
    else
        return 0;
}


int
if_libator_arrives(object player)
{
    if ( !objectp(player) ) return 0;

    if ( TO->query_prop(BARRELHOLE_I_LIBR_HERE) )
        return 0;

    if ( strip_grail_bearer(player) ) 
    {
        // add libator prop in place of grail
 
        notify_fail("There is a strangeness in the fabric of "
          + "space about grails and speakeasies!\n");

        player->add_prop(BARRELHOLE_I_LIBATOR,1);
       
        gLibator = player;

        TO->add_prop(BARRELHOLE_I_OPEN,1);
        TO->add_prop(BARRELHOLE_I_LIBR_HERE,1);

        pass_out("arrive");

        return 1;
    }

    return 0;
}


void
eject_patrons()
{
    int n;
    string afterw, ejectlocn;
    object *patrons;

    ejectlocn = IRON + EJECTROOM;

    patrons = FILTER_PLAYERS(all_inventory(TO));

    foreach (object patron: patrons)
    {
        patron->catch_msg("In the sudden confusion"
          + " of this hole between worlds, you"
          + " feel the barrel-shaped room around you"
          + " spin and spin and spin some more.\n\n");

        if ( random(100) < VESSEL_CATCH_PCT )
        {
            n = strip_vessel_bearer(patron);
            if ( n > 0 )
            {
                afterw = "into a constellation of fragments, "+
                 "awash in a " + BREWCRAFT_COLOURG + " spill of " +
                   BREWCRAFT_STYLEG + ", that are swept away "+
                    "by forces unseen.\n";

                if ( n > 1 ) 
                    patron->catch_msg("You drop " 
                        + val2str(n) + " crystal "
                        + " vessels. "
                        + "They shatter " + afterw); 
                else
                    patron->catch_msg("You drop a crystal"
                        + " vessel. "
                        + "It shatters " + afterw); 
            }
        }

        patron->move_living("M", ejectlocn, 1, 0);

        patron->catch_msg("\nThe world stops spinning and you "+
                            "regain your senses.\n");
    }

    return;
}


int
if_libator_leaves(object player)
{
    if ( !player || !interactive(player) ) return 0;

    if ( player->query_prop(BARRELHOLE_I_LIBATOR) )
    {
        player->remove_prop(BARRELHOLE_I_LIBATOR);
        TO->remove_prop(BARRELHOLE_I_LIBR_HERE);
        TO->remove_prop(BARRELHOLE_I_OPEN);

        tell_room(TO, "As " + QNAME(player) + 
          ", the Libator of Ninkasi, makes " + 
           LD_POSSESSIVE_MAP[player->query_gender()] + " apologies and leaves,"+
          "the rainstorm of brew upon the plain suddenly abates... "+
          "a sigh of anguish arises from the dead outside...\n"+
          "Divine dismissal sweeps through the barrel... "+
          "the party is over.\n\n");

        eject_patrons();
        return 1;
    }
}


int
if_patron_arrives(object player)
{
    if ( !objectp(player) ) return 0;
    if ( player->query_prop(BARRELHOLE_I_LIBATOR) ) return 0;
    pass_out("arrive");
    return 1;
}


/**************************************************
 * START:                                       - *
 * emotes                                       - *
 * - Created by Damaris@Genesis 08/2006         - *
 **************************************************/

static nomask string
cat_string(mixed org, string what, object pl, int up)
{
    if (objectp(pl))
        org[1] += (pl == org[0] ? (up == 1 ? "You" : "you") :
            (up == 1 ? QCTNAME(pl) : QTNAME(pl)));
    else
        org[1] += what;
    
    return org;
}

static nomask mixed
mk_item(object ob)
{
    return ({ ob, "" });
}

static nomask void
tell_them(object ob, mixed arg)
{
    arg[0]->catch_msg(QCTNAME(ob) + arg[1] + "\n");
}

nomask int
emote(string arg)
{
    object      pl, *pls;
    string      *args, *nms, oarg;
    int         i, sz, up;
    mapping     emap;

    pls = FILTER_LIVE(all_inventory(TO)) - ({TP});
    emap = mkmapping(pls, map(pls, mk_item));

    if (!stringp(arg))
    {
        notify_fail("Usage: : <emote string>, emote string can contain " +
            "names of present people enclosed in '|' characters, which " +
            "then will be identified by their met/nonmet names to observers. " +
            "e.g. ': smile fondly at |mrpr|.'\n");
        return 0;
    }

    /* Allows "emote 's head ..." -> "Mrpr's head ..." and yes the ''' does
     * look funny, but that's the syntax for getting the integer value of a
     * single quote.
     */
    if (arg[0] != ''')
    {
        arg = " " + arg;
    }

    // add in tell-tale adverb at start
    arg = " drunkenly" + arg;

    oarg = arg;
    args = explode(arg, "|");

    emap = map(emap, &cat_string(, args[0], 0, 0));
    if ((sz = sizeof(args)) > 1)
    {
        for (i = 1 ; i < sz ; i ++)
        {
            nms = explode(args[i], " ");
            up = nms[0] == lower_case(nms[0]) ? 0 : 1;
            nms[0] = lower_case(nms[0]);
            if (objectp((pl = present(nms[0], environment(this_player())))))
            {
                emap = map(emap, &cat_string(, "", pl, up));
                if (sizeof(nms) > 1)
                {
                    arg = implode(nms[1..], " ");
                    emap = map(emap, &cat_string(, arg, 0, up));
                }
            }
            else if (i % 2)
                return notify_fail("You cannot see " + nms[0] + " here.\n");
            else
                emap = map(emap, &cat_string(, args[i], 0, up));
        }
    }

    map(emap, &tell_them(this_player(), ));

    if (this_player()->query_option(OPT_ECHO))
        write("You emote: |" + capitalize(this_player()->query_real_name()) +
            "|" + oarg + "\n");
    else
        write("Ok.\n");
    return 1;
}


nomask void
init_emotes()
{
	if (this_player()->query_wiz_level())
	return;
	
	add_action(emote, "emote");
	add_action(emote, ":", 2);
}

/**************************************************
 * END:                                         - *
 * emotes                                       - *
 * - Created by Damaris@Genesis 08/2006         - *
 **************************************************/


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    set_long("@@long_descr");
    if (interactive(ob))
    {
        set_alarm(1.0, 0.0, &if_libator_arrives(ob));
        set_alarm(2.0, 0.0, &if_patron_arrives(ob));
        start_room_tells();
        ob->remove_prop(BARRELHOLE_I_MORTAL_CAN_ENTER);
        ob->remove_prop(BARRELHOLE_I_GRAIL_CAN_ENTER);
    }
}

void leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    if(!objectp(to) || !objectp(ob))
         return;
    if_libator_leaves(ob);
}


public int
catch_all(string str)
{
    string verb;

    if ( this_player()->query_wiz_level() ||
        this_player()->query_prop(BARRELHOLE_I_LIBATOR) )
        return 0;

    verb = query_verb();

    switch (verb)
    {
        case "give":
        case "put":
        case "get":
        case "open":
        case "close":
        case "wield":
        case "unwield":
        case "wear":
        case "remove":
        case "fill":
        case "extinguish":
        case "light":
        case "go":
        case "send":
            if ( drunk_action(verb,0) ) return 1;
            break;
        case "search":
        case "reveal":
        case "hide":
        case "sneak":
            if ( drunk_action(verb,1) ) return 1;
            break;
        case "home":
        case "backstab":
        case "block":
            return 1;
        default:
    }
    return 0;
}


int
read_it(string str)
{
    string lstr;

    if (!str)
    {
        return 0;
    }

    if (!strlen(str))
    {
        write("Read what?\n");
        return 1;
    }

    lstr = lower_case(str);

    if (lstr == "the tablets" || lstr == "tablets" || lstr == "tablet")
    {
        // on the stele
        write("Read which tablet? The Krynnward or Kurward tablet?\n");
        return 1;
    } 

    if (lstr == "the kurward tablet" || lstr == "kurward tablet")
    {
        // on the stele
        write("Let it Be Known to NETI, honoured Gatekeeper, that "+
            "this Concession is hereby made to NINKASI, Blessed of "+
            "the Fresh Waters, so that She may bring Succour from "+
            "far away and time to time to the dusty plain of Kur "+
            "where the Dead ever stand in Want. This Protected "+
            "Compact is made "+
            "at Ganzir by the grace of ERESHKIGAL, Queen of the Great "+
            "Earth.\n\n");
        return 1;
    } 

    if (lstr == "the krynnward tablet" || lstr == "krynnward tablet")
    {
        // on the stele
        write("Lunitari, the Veiled Maiden, has joined this place "+
         "with Krynn. All may find cheer, "+
         "in the way of their own choosing, through the gift of "+
         "Ninkasi which satisfies desire and sates the heart. "+ 
         gLibator->query_name() + " has the power to grant the "+
         "gift, all one need do is <ask>.\n\n");
        return 1;
    } 

    if (lstr == "graffito")
    {
        write(" \n" +
         upper_case(gBarrelName) +
         "\n\n");
        return 1;
    } 
}


int
wish_it(string str)
{
    int naughty;
    string lstr;
    object *patrons;
    string *badwords = ({"kill","attack","hit","poison","vessel","unconscious",
                       "stab","dies","arrives","leaves","magic","grail"});

    if ( !this_player()->query_prop(BARRELHOLE_I_LIBATOR) ) return 0;

    if (!str)
    {
        return 0;
    }

    if (!strlen(str))
    {
        write("Wish what? Wish a ripple of laughter passes "+ 
                 "through this place? For instance?\n");
        return 1;
    }

    naughty = 0;
    lstr = lower_case(str);

    foreach ( string badword : badwords ) 
        naughty += wildmatch(sprintf("*%s*",badword),lstr);

    if ( !naughty )
    {
        tell_room(environment(TP),capitalize(str)+"\n");
        return 1;
    } 
    else
       write("Your wish is not granted.\n");

    return 0;
}


int
libator_here()
{
    if ( !gLibator || !objectp(gLibator) ) return 0;
    if ( !present(gLibator) ) return 0;
    return 1;
}

int
libator_can_intone(object asker)
{
    if ( gLibator->query_real_name() == asker->query_real_name() ) return 1;

    if ( libator_here() )
    {
        if ( CAN_SEE(gLibator, asker) )
            return 1;
        else
            asker->catch_msg("You are unseen -- an affront to Ninkasi.\n");
    }
    return 0;
}


varargs int
libator_intones(string message,object recipient)
{
    string str0, str1, name;
    string str80 = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"+
                   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

    if ( !message || !strlen(message) ) return 0;

    if ( !recipient || !interactive(recipient) )
    {
        // no designated recipient
        str0 = "\nAn ethereal voice emanates from ";
        str1 = 
         sprintf(". You hear it intone:~~~~~~~~~~\n%s\n%s\n\n",message,str80);

        gLibator->catch_msg(str0 + "your mouth" + str1);

        tell_room(TO, str0 + "the mouth of " 
            + QNAME(gLibator) + str1,gLibator);
    }
    else
    {  
        // designated recipient
        name = recipient->query_name();

        if ( gLibator->query_name() == name )
        {
            str0 = "\nAn ethereal voice "+
                   "resonates in your mind:~~~~~~~~~~\n";
            str1 = sprintf("Libator %s, %s\n%s\n\n",name,message,str80);

            gLibator->catch_msg(str0+str1);
        }
        else
        {
            str0 = "\nAn ethereal voice emanates from ";
            str1 = 
             sprintf(". You hear it intone:~~~~~~~~~~\nSupplicant %s, %s\n%s\n\n",
                      name,message,str80);

            gLibator->catch_msg(str0 + "your mouth" + str1);

            tell_room(TO, str0 + "the mouth of " 
                + QNAME(gLibator) + str1,gLibator);
        }

    }

    return 1;
}


int
ask_it(string str)
{
    string lstr, istr;
    string answer;

    if (!str || !strlen(str) )
    {
        write("Ask what?\n");
        return 1;
    }

    if ( !libator_can_intone(TP) )
        return 1;

    tell_room(environment(TP),
         QCNAME(TP) + " asks something of someone unseen.\n",TP);

    lstr = lower_case(str);

    switch (lstr)
    {
        case "laws":
        case "law":
               answer= "\nThou wilt not Kill, nor seek to Harm nor "+
                "Harrass.\n" +
                "Thou wilt not Covet mortal Goods nor Practice mortal "+
                "Magicks.\n"+
                "To Attempt these Things is to Fail in My Sight.";
            break;
        case "help":
        case "instructions":
        case "instruction":
        case "for instruction":
           if ( TP->query_prop(BARRELHOLE_I_LIBATOR) )
               answer= "\nYou are granted Powers in this place while you choose "+
                   "to Remain. You may <serve> any mortal, without a drink in hand, "+
                   "be they alone or " +
                   "of your team or yourself, so that they be given "+
                   "Vessels from which to sup on the " + BREWCRAFT_STYLEG + 
                   " of the Libation. You are granted also the Power to <wish>. " +
                   "For example, you might <wish> 'a wave of light passes "+
                   "through the barrel'. "+
                   "You may <openup> or <closeup> the Krynnward entrance " +
                   "to further visitors from that Realm. " +
                   "Should You leave <krynnward>, "+
                   "all Others will be compelled to leave also. And "+
                   "the Blessing upon the plain of Kur will be at an End.";
           else
               answer= "\nMy Libator has the Power to grant that all sup on " +
                    BREWCRAFT_STYLEG + " borne forth in Vessels of crystal "+
                     "from where it falls from darkened skies Outside. "+
                    "May " + LD_PRONOUN_MAP[gLibator->query_gender()] +
                  " give unto you succour from a dry throat and weary soul!";
           break;
        case "who":
        case "who are you":
        case "who you":
        case "ninkasi":
            istr = "I Am the One who ";
            answer = "\n\n" +
             "I Am borne of the fresh flowing water, "+
             "tenderly cared for by Ninhursag;\n"+ 
             "I Am of Enki, Lord Nidimmud, and "+
             "Ninti, Queen of the Sacred Lake;\n\n"+
             istr + "hands the dough with the big shovel;\n"+
             istr + "bakes the bappir in the big oven;\n"+
             istr + "puts in order the piles of hulled grains;\n"+
             istr + "waters the malt set on the ground;\n"+
             istr + "soaks the malt in the jar;\n"+
             istr + "spreads the cooked mash on large reed mats;\n"+
             istr + "holds with both hands the great sweet wort;\n"+
             istr + "filters the brew, making pleasant sounds;\n"+
             istr + "holds the brew appropriately in the vat;\n"+
             istr + "lets pour out the brew from the vat;\n\n"+
             "It is as the wild onrush of the Tigris and Euphrates;\n\n"+
             "All drink in My Name,\n\n"+
             "NINKASI\n";
            break;
        case "outside":
        case "plain":
        case "kur":
            answer = "\nLook beyond this threshold into the World.\n"+
                     "Look upon this place where All come in Time.\n"+
                     "Behold Kur! The Underworld of Ereshkigal.\n"+
                     "Ponder Your coming to Darkness and Dust.\n"+
                     "Thence seek Wisdom, The Secret of Life!";
            break;
        case "dead":
        case "the dead":
            answer = "\nPity the Dead gathered before your mortal sight.\n"+
                     "Kur the desert feeds nought but Dust to All.\n"+
                     "None but the Living can grant Them succour.\n"+
                     "As the faithful child pours beer into the grave,\n"+
                     "So the libation to Ninkasi brings sweet rain to Kur.";
            break;
        case "dwarf":
        case "dwarf who knows my blessing":
            answer = "We shall not speak of Her.";
            break;
        case "other place":
        case "the other place":
            answer = "\nThe Other Place lies beyond the closed end. It is the "+
                      "dominion of the Dwarf who Knows My Blessing.";
            break;
        case "libation":
        case "libation to ninkasi":
            answer = "\nThe Libation to Ninkasi is made from " 
                     + BREWCRAFT_SHORTG + " of the "+
                     "Grail brought here from the other place.";
            break;
        case "walls":
        case "palace":
        case "ganzir":
            answer = "Ganzir is the palacial Seat of Ereshkigal over all Kur.";
            break;
        case "neti":
        case "gatekeeper":
            answer = "\nNeti, is chief Gatekeeper of the Underwold.\n"+
                     "He opens and closes the Seven Gates of Kur.\n"+
                     "He serves at the pleasure of Ereshkigal.";
            break;
        case "ereshkigal":
            answer = "\nEreshkigal, Queen of the Great Earth rules all Kur.\n"+
                     "Daughter of Nanna and Ningal; she is the Law Giver.\n"+
                     "She grants that this Concession might exist in Kur.";
            break;
        case "quest":
        case "task":
            answer = "\nYour Quest, Your Task, O Mortal child... "+
                     "is to embody the Secret of Life.";
            break;
        case "vessel":
        case "vessels":
        case "crystal vessels":
        case "crystal vessels":
            answer = "\nBlessed are the Vessels that travel betwixt "+
               "Worlds bearing the Libation of Ninkasi. They are granted "+
               "under the Concession, and are of the consummation of Neti "+
               "and Ninkasi -- thus charmed and charged with power.";
            break;
        case "concession":
        case "this concession":
            answer = "\nThis Concession is made to Ninkasi, of the Fresh Waters "+
             "of Sumer, so that She may bring Succour from time to time "+
             "and faraway to the dusty plain of Kur where the Dead "+
             "ever stand in Want. This Cross-Over between Worlds is Here "+
             "wrought by the Grace of Lunitari -- Veiled Maiden, "+
             "and Ereshkigal -- Queen of the Great Earth.";
            break;
        case "wisdom":
        case "secret":
        case "secret of life":
            answer = "\nDRINK, LOVE and BE MERRY; for TOMORROW YOU DIE!";
            break;
        case "gift":
        case "the gift":
        case "grant the gift":
            answer = "\nThe Gift from the Libation of Ninkasi is given so that "+
                "Mortals may slake their thirst and satisfy their hearts. If you "+
                "are known well to my Libator, " 
                  + LD_PRONOUN_MAP[gLibator->query_gender()] +
                " may grant It to You.";
            break;
        default:
            answer = "";
            break;
    }

    if ( answer != "" ) libator_intones(answer,TP);

    return 1;
}


void
init()
{
    ::init();
    init_emotes();
    add_action(catch_all, "", 1);                  // available to all 
    add_action(read_it, "read");                   // available to all 
    add_action(ask_it,"ask");                      // available to all 
    add_action(open_it, "openup");                 //  "  "     to libator
    add_action(wish_it, "wish");                   //  "  "     to libator 
    add_action(serve_it, "serve");                 //  "  "     to libator 
    add_action(close_it, "closeup");               //  "  "     to libator
    add_action(fill_bottle,"fill");                // prevent filling of takeaway bottles
}

