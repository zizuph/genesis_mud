#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include "/d/Krynn/guilds/sohm/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

inherit FOREST_OUT;

int wraith_found = 0;
int hunter_found = 0;

object npc_wraith, hunter;

#include "/d/Krynn/common/herbsearch.h"

#define H1 KRHERB + "tangleshoot"
#define H2 KRHERB + "hazelnut"
#define H3 KRHERB + "bunchberry"
#define H4 KRHERB + "chantrelle"

void
reset_flotsam_room()
{
    set_searched(random(2));
    hunter = 0;
}

create_flotsam_room()
{
    set_short("Amongst ruins within a vast evergreen forest");
    set_long("@@long_descr");

    add_item("branches","The branches of great oaks sway " +
      "with the wind.\n");
    add_item(({"forest","evergreen forest","ancient forest","great oaks",
	"vast evergreen forest","vast forest",
	"ancient oaks","thick underbrush","shadows","trees"}),
      "Surroundings you is an ancient evergreen forest of great " +
      "oaks and thick underbrush. Sounds echoing from the shadows " +
      "give the forest a forboding aspect.\n");
    add_item(({"ruins","ancient stone ruins","stone ruins","tower"}),
      "Unmolested by the encroaching forest is what can only be " +
      "described as the ruins of some kind of tower. Made of some dark stone " +
      "with a blue hue, it looks like the upper part of " +
      "the tower was blasted away by some great force, leaving only " +
      "the ground floor and a circular wall that " +
      "stands about two feet off the ground.\n");
    add_item(({"dark stone","stone","circular wall","wall"}),
      "A broken circular wall standing about two feet high is all " +
      "that is left of what was once a grand tower. The " +
      "dark stone it is made of seems to hum with magical " +
      "energy, and seems to be keeping the forest from " +
      "molesting it.\n");
    add_item(({"ground floor","floor","grey stone","ground",
	"twigs","leaves"}),
      "The grey stone floor of the tower is littered with dead " +
      "twigs and leaves that must have been blown here by the wind. " +
      "There seems to be an area on the floor that has been scorched " +
      "by some great heat that not even the leaves and twigs " +
      "encroach on.\n");
    add_item(({"scorched area","area"}),"@@wraith_descr");

    add_item(({"intricate runes","runes","runes of magic","carved runes"}),
      "@@exa_runes");
    add_cmd_item(({"intricate runes","runes","runes of magic","carved runes"}),
      ({"read","study"}), "@@read_runes");


    add_invis_exit(FROOM + "nowhere","north","@@no_go");
    add_invis_exit(FROOM + "nowhere","south","@@no_go");
    add_invis_exit(FROOM + "forest16s","east",0,4);
    add_invis_exit(FROOM + "nowhere","west","@@no_go");

    set_tell_time(120);
    add_tell("You hear a deep growl from the underbrush nearby.\n");
    add_tell("The branches of great oaks sway as a silent wind " +
      "blows through the forest surrounding the ruins.\n");

    seteuid(getuid(TO));
    set_search_places(({"forest","underbrush","herbs"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(H1);
    add_herb_file(H2);
    add_herb_file(H3);
    add_herb_file(H4);

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand amongst some ancient ruins that surprisingly haven't " +
    "been overrun by the surrounding " +
    "evergreen forest." +
    season_descr() +
    " whistles through the branches of ancient oaks that surround " +
    "these ruins, and eerie " +
    "sounds echo from the shadows cast by the trees, as well as " +
    "from the underbrush, giving the surrounding forest a forboding " +
    "aspect." +
    "\n";
}

void
reset_wraith()
{
    wraith_found = 0;
}

void
reset_hunter()
{
    hunter_found = 0;
}

string
wraith_descr()
{
    if (!wraith_found)
    {
	write("As you look upon the scorched area of the floor, " +
	  "the shadows cast by the wall begin to swell, forming into " +
	  "an undead creature of your nightmares!\n");
        say("The shadows cast by the wall begin to swell, forming into " +
	  "an undead creature of your nightmares!\n");
	npc_wraith = clone_object(FNPC + "revenant");
	npc_wraith->arm_me();
	npc_wraith->move(TO);
	wraith_found = 1;
	set_alarm(3000.0,0.0,&reset_wraith());
	return "";
    }

    if((this_player()->query_guild_name_occ() != "School of High Magic") &&
       (this_player()->query_guild_name_occ() != "Wizards of High Sorcery")) 
    {
      write("A scorched area of floor, most likely caused by a very hot fire. " +
        "There is nothing really interesting with it.\n");
      return "";
    }
    else
    {
      write("A scorched area of floor, most likely caused by a very hot fire. " +
        "You notice intricate runes of magic carved in to the floor, heavily " +
        "weathered with time.\n");
      return "";
    }

}

string
exa_runes()
{
    if((this_player()->query_guild_name_occ() != "School of High Magic") &&
       (this_player()->query_guild_name_occ() != "Wizards of High Sorcery")) 
    {
      write("Examine what?\n");
      return "";
    }
    else
    {
      write("Runes of magic have been carved in to the floor. While heavily " +
        "weathered by time, you could still probably read them.\n");
      return "";
    }
}

string
read_runes()
{

    if((this_player()->query_guild_name_occ() != "School of High Magic") &&
       (this_player()->query_guild_name_occ() != "Wizards of High Sorcery")) 
    {
        write("Read what?\n");
        return "";
    } 

    if(this_player()->query_skill(SS_SPELLCRAFT) < 40)
    {
	write("Your spellcraft skills are too poor to " +
          "comprehend the weathered runes.\n");
	return "";
    }

    if(!this_player()->query_prop("_sohm_read_magic_active")) 
    {
        write("You are not mentally focused enough to decypher the " +
        "magical runes carved into the floor here. Perhaps try again after " +
        "preparing yourself to read magic?\n");
        return "";
    } 

    if(hunter_found || SOHM_MANAGER->query_scribed_spell(this_player(),"chikohk"))
    {
       write("You focus on the runes and read them out loud. As you do, you " +
          "realise they are inert with their magic recently released.\n");
       say(QCTNAME(TP) + " looks down at the floor and recites words of magic " +
          "out loud.\n");

       return "";
    }

        write("You focus on the runes and read them out loud. As you do, you " +
          "realise belatedly that these are activated runes of entrapment, and by " +
          "reading them you are unravelling them, releasing whatever had been " +
          "trapped by them!\n\nWith a moan that echoes throughout the ruins, " +
          "an ethereal mage hunter materialises before you.\n");
	say(QCTNAME(TP) + " looks down at the floor and recites words of magic " +
          "out loud.\nThe wind ominously ceases to blow through the trees, and " +
          " a moan of anguish echoes throughout the ruins!\n" +
          "An ethereal mage hunter materialises before you.\n");
	hunter = clone_object(FNPC + "istarian_wraith");
	hunter->arm_me();
	hunter->move(TO);
        hunter->command("emote wails: Unclean one! You have released me!");
	hunter_found = 1;
        return "";
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
	start_room_tells();
}

int
no_go()
{
    write("Thick underbrush impedes travel in that direction.\n");
    return 1;
}
