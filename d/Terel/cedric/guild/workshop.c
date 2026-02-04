#pragma save_binary

inherit "/std/room";
inherit "/lib/trade";
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include "/d/Terel/cedric/guild/guild_defs.h"
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
   
   
   set_noshow_obvious(1);
   add_exit(GUILD+"conservatoire", "north");
   add_exit(GUILD+"shop_storeroom", "store"); 
   add_item(({"instruments", "wall", "beautiful instruments"}),
	    ("Instruments of great age and power line the wall, each more "
	     + "beautiful than the others.  Soft sounds flow from them all, "
	     + "and you can feel the power of the Muses within them all.\n"));
   
  add_item(({"kyrsis"}),
    ("A instrument maker whose talents are unsurpassed.  With the blessing\n"
     +"of the Muses he is able to bring life to even the most defiled\n"
     +"instrument.\n"));

     add_item(({"sign", "small sign"}),
      ("A small sign that reads:\n\n"
       + "I shall aid only those who are true followers of the Muses.\n"
       + "And in return for a small donation, I shall help further their.\n"
       + "influence in the deaf world around us.\n\n"
       + "I can <assess> the funds needed to fix an instrument and "
       + "<repair> it.  If you would like to buy a tuning fork I will happily "
       + "<list> what I have in stock.\n"));
    add_cmd_item( ({"sign","small sign"}),"read","@@sign_read");
    reset_room();
} 

int
sign_read()
{
    TP()->catch_msg("The sign reads:\n"+"\n"+
    "I shall aid only those who are true followers of the muses.\n"+
    "And in return for a small donation, I shall help further their\n"+
    "influence in the deaf world around us.\n"+"\n"+
    "I can <assess> the funds needed to fix an instrument and\n"+
    "      <repair> it.\n");
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
