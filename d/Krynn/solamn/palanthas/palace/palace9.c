/* created by Vitwitch 08/08/21 */

#pragma strict_types

#include "../local.h"
#include CLOCKH
#include <ss_types.h>
#include <math.h>

inherit CITY_ROOMBASE;

#define JANITOR_ROOM "/d/Krynn/solamn/palanthas/palace/office4.c" 

#define QUEST_NAME "Flaw in the Jewel of Solamnia"
#define QUEST_DOMAIN "krynn"
#define QUEST_BITGROUP 4
#define QUEST_BIT 6
#define QUEST_XP 120

static int gAllowFixationEffects01 = 0;
static int gAllowFixationReward01 = 1;

public string lighting_str();
public string nward_descr();
public string sward_descr();
public string wward_descr();
public string eward_descr();
public string long_descr();

string
query_to_jail()
{
  return "down";
} 

void
tower_glimpse( object plyr )
{
    if ( !objectp(plyr) ) return;
    if ( !interactive(plyr) ) return;

    string str = "\nWalking the balcony, drinking in the magnificence of "
     + "the Jewel of Solamnia... from your vantage of privilege... you find "
     + "your attention drawn by a dark discordance to the south west. "
     + "The restless grove of gnarled oaks adjacent the Plaza is as a "
     + "dark stain upon marble, a distinctive flaw in this jewel of a city. "
     + "The dark tower crouching within the twisted grove "
     + "dares the bold viewer to <fixate> on it.\n\n";

    plyr->catch_msg(str);
    return;

}

public string
lighting_str()
{
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
        return "By the light of dawn, looking";
        break;
    case TOD_DAY:
        return "In broad daylight, looking ";
        break;
    case TOD_TWILIGHT:
        return "In pensive twilight, looking ";
        break;
    case TOD_NIGHT:
        return "In the dark of a moonlit night, looking ";
        break;
    default:
        break;
    }
    return "";
}

public string
nward_descr()
{
   string vista = "to the north, the waters of the Bay of Branchala "
        + "lap at the piers and shipping of the city's Dock District. "
        + "The Jewel of Solamnia hides well the largest part of its "
        + "great and growing wealth in the warehouses and trading "
        + "estates by the bay. "
        + "The silhouette of an airship can be seen dimly on the horizon.\n";

    string str = lighting_str() + vista + "\n";
    return str;
}

public string
sward_descr()
{
    string vista = "to the south, the interior of "
        + "Solamnia lays open beyond the "
        + "city walls. Within the walls, the proximity of the "
        + "Aesthetics Quarter with its marble places of learning invites "
        + "all those with any interest in letters to crack open a volume. "
	+ "Immediately south of the plaza, there is a three-story building "
        + "of translucent marble and aged green copper spires and roofing. "
	+ "Figures come and go at all hours from the Great Library of "
        + "Palanthas.\n";

    set_alarm( 3.0, 0.0, &tower_glimpse(this_player()) );
    string str = lighting_str() + vista + "\n";
    return str;
}

public string
eward_descr()
{
    string vista = "out, the Vingaard Mountains loom beyond the walls "
        + "to the east and southeast of the city. The Knights High Road "
        + "emerges from the walls, and progresses stoic southeast through "
        + "the cold high places of the land, providing communication "
        + "thenceward for armoured and un-armoured alike. Within the city "
        + "walls, the Noble Quarter reposes in the marble and gold of "
        + "fortunes long since made and now put on conspicuous display.\n";

    string str = lighting_str() + vista + "\n";
    return str;
}

public string
wward_descr()
{
    string vista = "to the west, flat lowlands extend immediately beyond the "
        + "walls of the city. Within the walls lie forest groves "
        + "and the Merchants Quarter. Within the nearest grove, "
        + "thickly wooded with healthy trees, a "
        + "broad field has been cleared. From its centre rises a squat, "
        + "square tower of great marble blocks. This Tower is as "
        + "muscular and martial in its aspect as the Palace is "
        + "elegant and considered.\n";

    set_alarm( 3.0, 0.0, &tower_glimpse(this_player()) );
    string str = lighting_str() + vista + "\n";
    return str;
}


public string
long_descr()
{
    string light;
    string spire = " The balcony spire, at the very peak of the Palace, "
    + "is the preserve of Lord Amothus Palanthus, his retinue and those "
    + "others he deems worthy. Being none of these, you draw in the "
    + "rarefied air of the place a little nervously.\n\n";

    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
    light = "The spire is illuminated within by yellowing torchlight. "
    + "Pale rays of the sun are peeking above the "
    + "mountains and streaming in through the openings to the surrounding "
    + "balcony. All Palanthas is laid out below in the light of dawn "
    + "for you to <examine>: northward, southward, eastward and westward.";   
    break;
    case TOD_DAY:
    light = "The spire is somewhat shady within while bright "
    + "sunlight illuminates the openings to the surrounding "
    + "balcony. All Palanthas is laid out below in the stark light of day "
    + "for you to <examine>: northward, southward, eastward and westward.";   
    break;
    case TOD_TWILIGHT:
    light = "The spire is somewhat darkened within, its torches as yet unlit, "
    + "while the last rays of the sun delicately "
    + "illuminate the openings to the surrounding "
    + "balcony. All Palanthas is laid out below in twilight and lamplight "
    + "for you to <examine>: northward, southward, eastward and westward.";   
    break;
    case TOD_NIGHT:
    light = "The spire is illuminated within by bright torchlight. "
    + "The moon and stars shed pale light across the translucent marble "
    + "of the surrounding balcony. All Palanthas is laid out below in "
    + "lamplight and glistening reflection for you "
    + "to <examine>: northward, southward, eastward and westward.";   
    break;
    default:
    break;
    }
    return spire + light + "\n\n";
}


void
create_palan_room()
{
    set_short("Balcony Spire of the Palace");
    set_long("@@long_descr");

    add_item(({"northward","north","n"}),"@@nward_descr");
    add_item(({"southward","south","s"}),"@@sward_descr");
    add_item(({"eastward","east","e"}),"@@eward_descr");
    add_item(({"westward","west","w"}),"@@wward_descr");

    EXIT(PALACE + "palace5","down",0,1);

    JANITOR_ROOM->load_me(); 
}

void
fixate_stat_effects(object ob)
{
    // - to discipline, + to wisdom

    if ( !gAllowFixationEffects01 ) return;

    int ieff;
    int maxieff;  // max. allowed effect (/std/living/stats.c)

    // in equivalent HP HEALING INTERVALS
    int duration = min( 30, (6 * (5 + random(3))) );

    maxieff = 9 + ( 11 * ob->query_base_stat(SS_WIS) ) 
            / 10 - ob->query_stat(SS_WIS);

    ieff = random(5) * maxieff / 5;
    ob->add_tmp_stat(SS_WIS, ieff, duration);

    ieff = -1 * ieff;
    ob->add_tmp_stat(SS_DIS, ieff, duration);

    return;
}


void
fixate_tour_failure(object who)
{
    if ( who->test_bit(QUEST_DOMAIN,QUEST_BITGROUP,QUEST_BIT) ) return;

    who->catch_msg("\nYou feel you are missing something. "
                  + "Perhaps if you were to "
                  + "see the tower in a different light...?\n\n");
    return;
}


void
fixate_tour_reward(object who)
{
    // exploration QXP awarded

    if ( !interactive(who) ) return;
    if ( !gAllowFixationReward01 ) return;
    if ( who->test_bit(QUEST_DOMAIN,QUEST_BITGROUP,QUEST_BIT) ) return;
    
    setuid();
    seteuid(getuid());

    K_QUEST_LOG("quest",QUEST_NAME, who, QUEST_XP);
    who->set_bit(QUEST_BITGROUP,QUEST_BIT);
    who->add_exp_quest(QUEST_XP);

    write("You feel slightly more experienced!\n");

    return;
}


int
fixate_it( string str )
{
    if ( !strlen(str) ) return 0;

    string lstr = lower_case(str);

    if ( wildmatch("* dark tower*",lstr) )
    {
        string mesg = "Fixating on the Dark Tower; it fills your field of "
      + "view and fills your mind.  All breath rushes from your lungs in "
      + "a long wordless sigh, accompanying the flight of all thought "
      + "from your head. Black shapeless things take the place of thoughts "
      + "while you stand locked in asphyxia. At your wits end, you "
      + "divine a dark robed cadaver fluttering in the winds of eternity, "
      + "impaled before the tower, "
      + "sealing terrible prophecy in place with a life's blood spilt.\n\n";

        int eff = 0;
        switch(GET_TIMEOFDAY)
        {
        case TOD_DAWN:
        case TOD_DAY:
            if ( this_player()->query_alignment() > 0 ) eff++;
            break;
        case TOD_TWILIGHT:
        case TOD_NIGHT:
            if ( this_player()->query_alignment() < 0 ) eff--;
            break;
        default:
            break;
        }
 
        mesg += "Regaining your mind and breath,";

        string str0 = " you feel you have gained an understanding "
      + "of the dark truth "
      + "of the world... but are unnerved by the power of evil that ";
        string str1 = " you in this Realm. "
      + "You know it will still be quite some time before you feel "
      + "like your old self again.\n\n";

        switch( eff ) 
        {
        case 1:
            mesg = mesg + " by the light of day," + str0 + "confronts" + str1;
            fixate_stat_effects(this_player());
            set_alarm( 3.0, 0.0, &fixate_tour_reward(this_player()) );
            break;
        case -1:
            mesg = mesg + " by the dark of night," + str0 + "rivals" + str1;
            fixate_stat_effects(this_player());
            set_alarm( 3.0, 0.0, &fixate_tour_reward(this_player()) );
            break;
        default:
            mesg += 
       " you feel quite like your old self again.\n\n";
            set_alarm( 3.0, 0.0, &fixate_tour_failure(this_player()) );
            break;
        }

        this_player()->catch_msg(mesg);

        return 1;
    }
    else
    {
        this_player()->catch_msg("Fixate on what exactly?\n");
        return 1;
    } 

    return 0;
}

void
init()
{
    ::init();
    add_action("fixate_it","fixate");
}
