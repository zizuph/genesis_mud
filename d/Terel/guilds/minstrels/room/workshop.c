#pragma save_binary

inherit "/std/room";
inherit "/lib/trade";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <cmdparse.h>
#include <language.h>
#include "/d/Terel/common/terel_defs.h"
#include "../guild_defs.h"

#define MERCHANT "Kyrsis"
#define MERCHANT_OB GUILDNPC+"mc"

/*
* The Minstrel Guild Headquarters: Workshop
* Here the players get their instruments repaired, for instance, if a string
* breaks when the Minstrel attempts a song-spell beyond his or her powers.
* Cedric 1/93
*/

void fix_it(object instrument);

void
init()
{
    add_action("select", "select");
    add_action("abandon", "abandon");
    ::init();
}

void
reset_room()
{
    if(!present("kyrsis") || !present("man"))
        clone_object(MERCHANT_OB)->move(TO());
}

void
clean_up()
{
	object	*everything;
	int i;

	everything = all_inventory();
	for (i=0;i<sizeof(everything);i++)
		if (everything[i]->query_name() != MERCHANT)
			return;
	remove_object();
}
	
void
create_room()
{
   set_short("The Workshop of the Minstrels");
   set_long(BS("This small workshop fills your senses with the sweet smells "
         + "of rare oils and ancient wood.  Here the instruments of "
         + "the Minstrels breathe their first magic and whisper their "
         + "first songs.  Along the wall are among the rarest and most "
         + "beautiful instruments of Minstrels long dead, hung in a "
         + "solemn silence and reverence.  A small man, Kyrsis by name, "
         + "sits alone at a small table in the back of the room, "
         + "whispering a plea to the sweet Muses, begging them to aid "
         + "the tending of an instrument worn and frayed from a life "
         + "of lost glory.  The air seems to shimmer with music, "
         + "eons of ballads intertwined into one great symphony that "
         + "seems to hover just beyond understanding. "
         + "Your eye catches a small sign in the back of the room.\n"));

   add_exit(GUILD+"conservatoire", "north");
   add_exit(NEW_GUILD + "room/shop_storeroom", "store", 1, 1, 1); 
   add_item(({"instruments", "wall", "beautiful instruments"}),
	    ("Instruments of great age and power line the wall, each more "
	     + "beautiful than the others. Soft sounds flow from them all, "
	     + "and you can feel the power of the Muses within them all.\n"));
   
  add_item(({"kyrsis"}),
    ("An instrument maker whose talents are unsurpassed.  With the blessing "
     +"of the Muses he is able to bring life to even the most defiled "
     +"instrument.\n"));

     add_item(({"sign", "small sign"}),
      ("A small sign that reads:\n\n"
       + "I shall aid performers and true followers of the Muses.\n"
       + "And in return for a small donation, I shall help further their\n"
       + "influence in the deaf world around us.\n\n"
       + "I can <assess> the funds needed to fix an instrument and "
       + "<repair> it.  If you would like to buy a tuning fork I will happily "
       + "<list> what I have in stock.\n\nThere is further information " 
       + "about how to become a performer... would be worth reading it.\n"));

    add_cmd_item( ({"sign","small sign"}),"read","@@sign_read");
    reset_room();
} 

int
sign_read()
{
    TP()->catch_msg("The sign reads:\n"+"\n"+
        "I shall aid performers and true followers of the muses.\n"+
        "And in return for a small donation, I shall help further their\n"+
        "influence in the deaf world around us.\n"+"\n"+
        "I can <assess> the funds needed to fix an instrument and\n"+
        "      <repair> it.\n\n" +
        "For non-Minstrels, I can grant you the opportunity to be a\n" +
        "performer and craft you an instrument. You can <select> from:\n" +
        "    lute,\n" +
        "    recorder,\n" +
        "    dulcimer,\n" +
        "    harp,\n" +
        "    shawm,\n" +
        "    viol, or\n" +
        "    trumpet.\n" +
        "\n\nFor would-be-musician ogres, these instruments are too small\n" +
        "for your hands, however I can craft 'tuned' rocks for you to\n" +
        "perform percussion compositions.\n\n");
    return 1;
}

int
do_repair(string str) 
{
    int testflag,cost,damage; 
    object instrument;
    mixed result;

    if (query_verb()=="assess")
        testflag = 1;
    else
	testflag = 0;

    if (parse_command(str, TP(), "%o", instrument)
    && member_array("minstrel_instrument",instrument->query_names()) >= 0)
    {
        write("got an instrumenti: "+file_name(instrument)+"\n");
    	damage = instrument->query_damage();
	if (damage < 1)
	{
	    NF(BS("Kyrsis looks the "+instrument->query_name()+" over with the "
	    + "trained eye of an expert, and says, \"I see nothing wrong with "
	    + "your instrument, friend.\"\n"));
	    instrument->set_damage(0);
	    return 0;
	}
	cost = damage * damage * damage;
	result = pay(cost,TP(),"",testflag,0,"",0);
	if (intp(result))
	    switch (result)
	    {
		case 3: 
		    write("Kyrsis asks "+cost+" copper coins to repair your "
		    + "instrument.\n");
		    return 1;
		default:
		    write(BS("Kyrsis begins to take your money, then stops, "
		    + "confused. \"Odd!\" he exclaims. \"An error code "+result
		    + " kept me from taking your money. Better tell the "
		    + "guildmaster.\" Kyrsis shrugs and returns to his work.\n"));
		    return 1;
	    }
	if (testflag)
	{
	    write("Kyrsis asks "+text(result)+" to repair the "
	    + instrument->query_name()+".\n");
	    return 1;
	}
	else
	{
	    write(BS("You pay "+text(result)+" to Kyrsis, who carefully "
	    + "looks your "+instrument->query_name()+" over.\n"));
	    set_alarm(4.0, 0.0, &fix_it(instrument));
	    return 1;
	}
    }
    else
    {
        NF("Kyrsis snorts and glares, 'I am busy, fool.'\n");
        return 0;
    }
}

void fix_it(object instrument)
{
    switch (instrument->query_damage())
    {
	case 1..4: 
	    write(BS("Kyrsis remarks: Why, it's only out of tune! Don't you know "
	    + "how to tune your own "+instrument->query_name()+"?\"\n")+BS("He "
	    + "quickly tunes the instrument and hands it back to you.\n"));
	    break;
	case 5:
	    write(BS("Kyrsis seems amused. \"They don't get much more out of "
	    + "tune than this, do they?\" he laughs. He quickly tunes the "
	    + instrument->query_name()+" and hands it back to you."));
	    break;
	case 6..10:
	    write(BS("Kyrsis takes the damaged instrument gingerly and "
	    + "places it on his workbench. Working quickly, but with great "
	    + "love and care, his deft fingers fly over the instrument. When "
	    + "he hands it back to you, the "+instrument->query_name()
	    + " looks as fine as the day "+environment(instrument)->
	    query_muse_name() + " first handed it into your care.\n"));
	    break;
    }
    instrument->set_damage(0);
}

string
eligible_instruments(string str)
{
    switch(str)
    {
        case "lute":
            return "lute";
            break;
        case "recorder":
            return "recorder";
            break;
        case "dulcimer":
            return "dulcimer";
            break;
        case "harp":
            return "harp";
            break;
        case "shawm":
            return "shawm";
            break;
        case "viol":
            return "viol";
            break;
        case "trumpet":
            return "trumpet";
            break;
    }

    return 0;
}

int
select(string str)
{
    setuid();
    seteuid(getuid());

    object club_obj = clone_object(NEW_GUILDOBJ + "instrument_club");
    object book = clone_object(NEW_GUILDOBJ + "club_songbook");
    string instrument;

    NF("Select which instrument?\n");
    if (!str)
	return 0;

    instrument = lower_case(str);

    NF("As a Minstrel, you are already a performer and don't " +
        "need another instrument!\n");
    if(MEMBER(this_player()))
        return 0;

    if(this_player()->query_race_name() == "ogre")
    {    
        NF(capitalize(str)+ " isn't an eligible instrument " +
            "to select for an ogre. You are capable of performing " +
            "with traditional ogre tuned rocks only.\n");
        if(str != "rock" && str != "tuned rock")
	    return 0;

        instrument = "rock";
    }

    if(this_player()->query_race_name() != "ogre")
    {
        if(str == "rock" || str == "tuned rock")
        {
            NF(capitalize(str)+ " is an eligible instrument " +
                "for ogres only!\n");
	        return 0;
        }
        NF("That isn't an eligible instrument to select.\n");
        if(!eligible_instruments(instrument))
	    return 0;
    }

    NF("You are already a performer!\n");
    if(IS_PERFORMER(this_player()))
        return 0;
    
    PERFORM_MANAGER->add_member(this_player());
    PERFORM_MANAGER->set_reputation_level(this_player(), 0);

    club_obj->move(this_player(), 1);
    club_obj->set_name(instrument);

    say(QCTNAME(this_player()) + " has selected an " +
        "instrument and taken up the role of performer of Genesis!\n", 
        this_player());
    write("You have selected an instrument and are now a " +
        "performer of Genesis!\n");

    if (!present("minstrel_song_book", this_player()))
    {
        book->move(this_player(), 1);
        book->set_owner(this_player());
	write("You also take a songbook to pen your songs in!\n");	    
    }

    return 1;

}

public int
abandon(string str)
{
    NF("Abandon what? Being a performer?\n");
    if (!str || str != "being a performer")
	return 0;

    NF("You are not a performer, so can't abandon being one!\n");
    if(!IS_PERFORMER(this_player()))
        return 0;

    NF("As a Minstrel, you can't not be a performer!\n");
    if(MEMBER(this_player()))
        return 0;

    tell_object(this_player(),"As with many before you who thought " +
        "fame and fortune awaited them through music, " +
        "realisation has hit that this is not a path for you. " +
        "You abandon being a performer.\n");

    PERFORM_MANAGER->remove_member(this_player());

    if(present("minstrel_instrument", this_player()))
        present("minstrel_instrument", this_player())->do_things();

    if(present("minstrel_song_book", this_player()))
        present("minstrel_song_book", this_player())->remove_object();

    return 1;
}

