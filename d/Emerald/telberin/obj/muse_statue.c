/* Bas code for the statues of the Lost Muses - Arman 2019     */


inherit "/std/object";

#include "/d/Terel/guilds/minstrels/guild_defs.h"

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>

#define EUTERPE     "euterpe"
#define TERPSICHORE "terpsichore"
#define ERATO       "erato"
#define POLYHYMNIA  "polyhymnia"
#define URANIA      "urania"

#define P_COUNT     "_muse_performance_count"

string muse_type, power_song;

public void
set_power_song()
{
   switch(muse_type)
   {
       case EUTERPE:
           power_song = "animato";
           break;
       case TERPSICHORE:
           power_song = "accelerando";
           break;
       case ERATO:
           power_song = "concerto";
           break;
       case POLYHYMNIA:
           power_song = "bellicoso";
           break;
       case URANIA:
           power_song = "lento";
           break;
       default:
   }
}

public void
set_muse_type(string str)
{
    muse_type = str;
    set_power_song();
}

public string
query_muse_type()
{
    return muse_type;
}

public string
query_power_song()
{
    return power_song;
}

string
long_desc()
{
   switch(muse_type)
   {
       case EUTERPE:
           return "one of the lost Five Muses. She stands before you " +
               "in the act of playing a double-flute, a figure of " +
               "inspiration and beauty.";
           break;
       case TERPSICHORE:
           return "one of the lost Five Muses. She is depicted here " +
               "sitting down holding a lyre, accompanying dancing " +
               "nymphs with her music.";
           break;
       case ERATO:
           return "one of the lost Five Muses. Crowned in a wreath of " +
               "myrtle and roses, this maiden of incredible beauty " +
               "stares into the distance with a wistful look, a " +
               "small kithara nestled in her hands.";
           break;
       case POLYHYMNIA:
           return "one of the lost Five Muses. She is depicted dressed " +
               "in a long cloak and veil, with a serious meditative " +
               "look on her face.";
           break;
       case URANIA:
           return "one of the lost Five Muses. She is depicted dressed " +
               "in a cloak embroidered with stars, and her attention " +
               "focused upwards to the heavens.";
           break;
       default:
           return "of an unknown Muse.";
   }
}

public void
create_object()
{
    set_name("statue");
    add_name("muse");
    add_name("_lost_muse_statue");
    set_short("white marble statue");
    set_adj(({"white","statuary", "marble", "lost"}));
    set_long("A white marble statue stands before you of " +
        "@@long_desc@@ Carved on the base is an inscription in " +
        "an ancient elven dialect.\n");

    add_item(({"inscription", "base", "carving"}),
        "Upon the base of the statue is an inscription in " +
        "ancient elven. You may be able to read it.\n");

    add_cmd_item(({"inscription", "carving"}), "read",
        "@@read_inscription");

    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_WEIGHT, 200200);
    add_prop(OBJ_I_VALUE, 500500);
    add_prop(OBJ_M_NO_GET, "The white marble statue is too heavy.\n");
    add_prop(OBJ_M_NO_STEAL, 1);
}

string
read_inscription()
{
   if(this_player()->query_skill(SS_LANGUAGE) < 60)
       return "This ancient dialect is too difficult for you " +
           "to translate.\n";

   switch(muse_type)
   {
       case EUTERPE:
           return "The inscription reads: 'Euterpe, Lost Muse " +
               "of Lyric Poetry'.\n";
           break;
       case TERPSICHORE:
           return "The inscription reads: 'Terpsichore, Lost Muse " +
               "of Dance'.\n";
           break;
       case ERATO:
           return "The inscription reads: 'Erato, Lost Muse " +
               "of Love Poetry'.\n";
           break;
       case POLYHYMNIA:
           return "The inscription reads: 'Polyhymnia, Lost Muse " +
               "of Hymns and Sacred Poetry'.\n";
           break;
       case URANIA:
           return "The inscription reads: 'Urania, Lost Muse " +
               "of Imagination and Foretelling'.\n";
           break;
       default:
           return "The inscription reads: 'The Unknown Muse'.\n";
   }
}

int 
perform(string str)
{
    string muse;
    string instrument = this_player()->query_instrument_name();  

    if (!str)
    {
        notify_fail("Perform for who?\n"); 
        return 0;
    }

    if (!parse_command(str, ({}), "[for] / [to] %s", muse))
    {
        notify_fail("Perform for <who>?\n");
        return 0;
    }

    muse = lower_case(muse);

    if(!instrument)
    {
        if(present("minstrel_instrument", this_player()))
            instrument = present("minstrel_instrument", 
            this_player())->short();  
        {
            notify_fail("You have no instrument to perform with.\n");
            return 0;
        }
    }

    if(muse == "statue")
    {
        write("You perform a wordless tune on your " +
            instrument+ " for the statue.\n");
        say(QCTNAME(this_player())+ " performs a wordless tune on " +
            this_player()->query_possessive()+ " " +instrument+ 
            " for the marble statue of the lost muse.\n");
        return 1;
    }

    if(muse == query_muse_type())
    {
        string performance_prop = "_performed_for_" +muse;
        int performance_num = this_player()->query_prop(P_COUNT);

        if(this_player()->query_prop(performance_prop))
        {
            write("You have already dedicated a performance " +
                "to " +capitalize(muse)+ ".\n");
            return 1;
        }

        this_player()->add_prop(performance_prop, 1);

        write("You dedicate a wordless tune on your " +
            instrument+ " to the Lost Muse " +capitalize(muse)+
            ".\n");
        say(QCTNAME(this_player())+ " performs a wordless tune on " +
            this_player()->query_possessive()+ " " +instrument+ 
            " for the marble statue of the lost muse.\n");

        if(MEMBER(this_player()))
        {
            performance_num++;
            this_player()->add_prop(P_COUNT, performance_num);

            string * song_list = SONGBOOK_MANAGER->query_power_songs(this_player());
            object song_book = present("minstrel_song_book", this_player());

            if(!IN_ARRAY(power_song, song_list))
            {
                if(!song_book->add_power(power_song))
                {
                    write("You have been inspired by the lost muse " +
                    capitalize(muse)+ "! However with no space in " +
                    "your songbook to copy the inspiration down, " +
                    "it fades swiftly from memory.\n");
                }
                else
                {
                    write("You have been inspired by the lost muse " +
                        capitalize(muse)+ ", and have learnt the " +
                        "long lost Song of Power, " +capitalize(power_song) + 
                        "!\n");
                    say(QCTNAME(this_player())+ " seems to have been " +
                        "inspired!\n");
                    song_book->add_power(power_song);
                 }
            }
        }

        return 1;
    }

    notify_fail("Perform what?\n");
    return 0;
}

void
init()
{
   ::init();
   add_action(perform, "perform");
}
