#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/guilds/sohm/defs.h"
#include <ss_types.h>

inherit CITY_OUT;

void
reset_kalaman_room()
{
    return;
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Cobbled street before a squat tower");

    add_item(({"entrance","tower","squat tower"}),
      "@@tower_desc");
    add_item(({"runes","runes of magic","magic runes","entrance"}),
      "@@runes_desc");
    add_cmd_item(({"runes","runes of magic"}), "read","@@read_runes");

    add_item_city();

    add_item(({"citys walls","walls","wall"}),
      "The cobbled street you stand on is fairly close to the city walls.\n");

    add_exit(CITY + "mt1","southeast","@@no_go");
    add_exit(CITY + "r3","northwest",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand at the end of a cobbled street before the entrance to a " +
    "squat tower at the base of the wall surrounding the city. " +tod_descr1()+ season_road()+
    "\n";
}

string
tower_desc()
{
    if(this_player()->query_guild_name_occ() == GUILD_NAME ||
       this_player()->query_guild_name_occ() == "Wizards of High Sorcery") 
    {
        return "To the southeast is the entrance to a tower of strange black stone. " +
        "It strongly resembles the shape of a squat mushroom. Over the entrance you " +
        "notice runes of magic have been carved.\n";
    } 

    return "To the southeast is the entrance to a tower of strange black stone. " +
    "It strongly resembles the shape of a squat mushroom.\n";
}

string
runes_desc()
{
    if(this_player()->query_guild_name_occ() == GUILD_NAME ||
       this_player()->query_guild_name_occ() == "Wizards of High Sorcery") 
    {
        return "Runes of magic have been scribed over the entrance of the tower " +
        "to your southeast. By looks, they are runes of summoning.\n";
    } 

    return "Examine what?\n";
}

int
no_go()
{
    write("A spectral minion appears before you, stopping you " +
      "from entering.\n" +
      "The spectral minion says: No one may enter the tower until the Master of " + 
      "Past and Pre...\n" +
      "The spectral minion looks a little confused.\n" +
      "The spectral minion says: Ahem, what I mean is the hedge wizard " +
      "is out of the city at the moment, talking to dwarves. You may " +
      "not enter until he returns.\n" +
      "The spectral minion fades away.\n");
    say("A spectral minion appears in front of " +QTNAME(TP) + 
      " stopping " +HIM(TP)+ " from entering the tower.\n" +
      "The spectral minion says something to " +QTNAME(TP)+ ", " +
      "and then fades away.\n");
    return 1;
}

string
read_runes()
{
    if(this_player()->query_guild_name_occ() != GUILD_NAME &&
       this_player()->query_guild_name_occ() != "Wizards of High Sorcery") 
    {
        write("What?\n");
        return "";
    } 

    if(this_player()->query_skill(SS_FORM_CONJURATION) < 40)
    {
	write("Your conjuration skills are too poor to even begin " +
          "comprehending the magical runes over " +
          "the entrance of the tower.\n");
	return "";
    }

    if(!this_player()->query_prop("_sohm_read_magic_active")) 
    {
        write("You are not mentally focused enough to decypher the " +
        "magical runes over the entrance. Perhaps try again after " +
        "preparing yourself to read magic?\n");
        return "";
    } 

    write("You chant loudly the runes of magic carved over the entrance " +
          "of the tower. As you do, you feel yourself being teleported " +
          "elsewhere!\n");
    say(QCTNAME(this_player()) + " chants loudly words of magic, and suddenly " +
          "vanishes!\n");

    tell_room(CITY + "tower01", QCTNAME(this_player()) +
          " suddenly appears in a blinding flash of light!\n");
    this_player()->move_living("X", CITY + "tower01", 1, 0);

    return "";
}
