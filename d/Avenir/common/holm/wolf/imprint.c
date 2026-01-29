// -*-C++-*-
// file name:	imprint.c	
// creator(s): 	Sirra march '98
// revisions:	Lilith March '98
// last update:	
// purpose:	container that holds the bones for the wolf quest
// note:	Lilith added the long and num_bones functions.
// bug(s):	
// to-do:	create wolf_bones file in /d/Avenir/log/quest/	
//		assign and check the bit and group number in
//                  /d/Avenir/private/BITS

inherit "/std/container";
inherit "/d/Avenir/inherit/quest";

#include "/d/Avenir/common/holm/wolf.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

int alarm_id, dump_id, magic_id, wolf_id;
int do_success(object player);
int do_breeze(object player);
int do_message(object player);
int do_wolf(object player);
int do_person(object player);
int magic_over_first(object player);
int magic_over_second(object player);

int do_sing(string str);
int do_drop();

void reward_wolf_quest(object player);

void
create_container()
{
    set_short("impression of fossilized bones");
    set_name("_Wolf_Quest_Imprints");
    add_name(({"imprints", "imprint", "impression", "impressions",
        "carving", "fossil", "fossils"}));
	
    set_long("Set deep in the black stone of the obsidian seawall "
	+ "are the imprints of many fossilized bones, the skeletal "
        + "remains of what was once a mighty animal.");
		
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_MAX_WEIGHT, 2900);	//the sum weight of the bones
    add_prop(CONT_I_MAX_VOLUME, 1000);  //the sum volume of the bones 

    set_no_show_composite(1);

    seteuid(getuid(this_object()));
}

/* Lets the player know how many bones are needed.
 * Makes long desc more interesting.
 */
string 
num_bones()
{
    int num; 
    string str; 

    num = sizeof(all_inventory(this_object()));
    switch(7 - num)
    {
        case 0: str = " All of the impressions are filled with bones, "+
                "seven of which appear to be loose.  "; break;
        case 1: str = " All but one of the impressions are full. "+
                "Six of the bones appear to be set more "+
                "loosely into their imprints than the others.  ";
                break;
        case 2: str =" Five of the bones appear to be looser than "+
                "the rest, and it looks like two have fallen "+
                "out.  "; break;
        case 3: str =" There are three empty impressions, and by the "+
                "looks of things, four more are ready to fall "+
                "out.  "; break;       
        case 4: str =" Three bones lie precariously in their imprints, "+                
                "while it appears that four others have fallen "+
                "out.  "; break;
        case 5: str =" There are two loose bones and five missing from "+
                "their impressions.  "; break;
        case 6: str =" A single bone lies loosly in its imprint, while "+
                "it appears that six have fallen out.  "; break;
        case 7: str =" There are seven hollowed-out imprints marking "+
                "the place where bones once were."; break;
        default: str ="It looks like there might be some missing bones.";
                break;
    }
    return str;
} 

/* Skip over /std/container's 'long' function, force our own */
public varargs string 
long(object obj)
{
    return ::long(obj) + " "+ num_bones() + "\n";
}

int
prevent_enter(object entering)
{
    if (!entering->id("WOLF_ID"))
    {
	write("The " + entering->short()+ " does not fit.\n");
	return 1;
    }

    //Either player is grossly guessing... or (s)he's cheating.
    if (this_player()->query_skill(SS_ANI_HANDL)< 20)
    {
        write("You try to fit the "+ entering->query_name() +
            " into the "+ short() +", but fail.\nIt is fairly "+
            "obvious that your knowledge of animals is too poor "+
            "for you to reconstruct the skeleton properly.\n");
        return 1;
    } 

    //Dont want more than one.
    if (entering->id("MANDIBLE_ID")
        &&present("MANDIBLE_ID", this_object()) )
    {
        write("There is already a "+ entering->short() +
            " in the "+ short() +".\n");
        return 1;
    }

    if (entering->id("VERTEBRA_ID")
        &&present("VERTEBRA_ID", this_object()) )
    {
        write("There is already a "+ entering->short() +
            " in the "+ short() +".\n");
        return 1;
    }

    if (entering->id("FEMUR_ID")
        &&present("FEMUR_ID", this_object()) )
    {
        write("There is already a "+ entering->short() +
            " in the "+ short() +".\n");
        return 1;
    }

    if (entering->id("PELVIC_ID")
        &&present("PELVIC_ID", this_object()) )
    {
        write("There is already a "+ entering->short() +
            " in the "+ short() +".\n");
        return 1;
    }

    if (entering->id("RIB_ID")
        &&present("RIB_ID", this_object()) )
    {
        write("There is already a "+ entering->short() +
            " in the "+ short() +".\n");
        return 1;
    }

    if (entering->id("TOE_ID")
        &&present("TOE_ID", this_object()) )
    {
        write("There is already a "+ entering->short() +
            " in the "+ short() +".\n");
        return 1;
    }

    if (entering->id("SKULL_ID")
        &&present("SKULL_ID", this_object()) )
    {
        write("There is already a "+ entering->short() +
            " in the "+ short() +".\n");
        return 1;
    }

}

void
enter_inv(object ob, object from)
{
    /* If someone put the bones in, then took one out and added
     * it again, we'd start running a new alarm, so lets make
     * sure that doesn't happen.
     */
    if (alarm_id)
        return;

    // Quest solution in progress already. One at a time.
    if (wolf_id)
        return;

    if (present("MANDIBLE_ID", this_object())
	&&present("RIB_ID", this_object())
	&&present("FEMUR_ID", this_object())
	&&present("TOE_ID", this_object())
	&&present("SKULL_ID", this_object())
	&&present("VERTEBRA_ID", this_object())
	&&present("PELVIC_ID", this_object()) )
    {
        // Been there, done that.
        if (from->test_bit("Avenir", WOLF_GROUP, WOLF_BIT))
        {

            from->catch_tell("You feel as if you have been here before.\n");
        		do_drop();
            return;
        }

        // set these alarms so that the messages will be
        // printed after the player get the "put" message.
        // Only run one alarm at a time. Make sure the
        // do_success knows who the questor is.
	alarm_id = set_alarm(1.0, 0.0, &do_success(from) );

        WRITE_THIS_LOG(QUEST_FILE, from->query_name()
	    + " put the last bone in.\n");
        return;
    }

}

int
do_success(object player)
{
    // Just to be safe, always remove the alarm before
    // starting the next one in the sequence.
    remove_alarm(alarm_id);
    alarm_id = 0;

    // This shouldn't happen, but lets be safe.
    if (wolf_id)
       return 0;


    // The quest is near the end. We don't want multiple people
    // getting credit from a full imprint, so we'll test for this.
    wolf_id = 1;

    // Lets make sure the questor is still here. If not,
    // s/he should not get these tells...s/he is out of luck.
    if (!present(player, environment(this_object())))
    {
    		magic_over_first(player);
        //dump_id = set_alarm(60.0, 0.0, "do_drop");
        return 0;
    }

    player->catch_tell("The fossilized wolf bones embedded in "
	+ "the obsidian glass wall begin to glitter with "
	+ "urgency ... and then subside, seeming to wait for "
        + "something.\n");

   alarm_id = set_alarm(7.0, 0.0, &do_breeze(player) );

     return 1;
}

int
do_breeze(object player)
{
    remove_alarm(alarm_id);
    alarm_id = 0;

    if (!wolf_id)
        return 0;

    if (!present(player, environment(this_object())))
    {
        magic_over_first(player);
        return 0;
    }

    if(!present("MANDIBLE_ID", this_object())
	||!present("RIB_ID", this_object())
	||!present("FEMUR_ID", this_object())
	||!present("TOE_ID", this_object())
	||!present("SKULL_ID", this_object())
	||!present("VERTEBRA_ID", this_object())
	||!present("PELVIC_ID", this_object()) )
   {
   	magic_over_first(player);
		return 0;
   }

    player->catch_tell("An oddly cold breeze wraps "
	+ "around your ankles and snakes up your body, "
        + "ruffling your hair.\n");

    alarm_id = set_alarm(10.0, 0.0, &do_message(player));


    return 1;
}

int
do_message(object player)
{
    remove_alarm(alarm_id);
    alarm_id = 0;

    if (!wolf_id)
      return 0;

    if (!present(player, environment(this_object())))
    {
        magic_over_first(player);
        return 0;
    }

    if (!present("MANDIBLE_ID", this_object())
	||!present("RIB_ID", this_object())
	||!present("FEMUR_ID", this_object())
	||!present("TOE_ID", this_object())
	||!present("SKULL_ID", this_object())
	||!present("VERTEBRA_ID", this_object())
	||!present("PELVIC_ID", this_object()) )
   {
   	magic_over_first(player);
		return 0;
   }

    if (player->query_gender()==G_MALE)
    {
	player->catch_tell("A warm baritone voice resonates "
	    + "softly in your ear, striking a timeless note so "
	    + "comforting in sound, you can only just make out the "
	    + "message: Sing ... over ... our ... bones ...\n");
    }

    else
    {
	player->catch_tell("A gentle voice like the tinkling "
       	    + "of chimes resonates softly in your ear, striking a "
	    + "timeless note so comforting in sound, you can "
	    + "only just make out the message: Sing ... over "
            + " ... our ... bones ...\n");
    }

    /* Lets give the player some time to sing over the bones
     * before deciding s/he hasn't solved the quest. Then dump
     * the contents of this container.
     */
    dump_id = set_alarm(300.0, 0.0, "do_drop");
    return 1;
}

int
do_sing(string str)
{
    object player = this_player();

    // If no string, do default cmdsoul sing.
    if (!str)
       return 0;

    // Player is still in an earlier part of the sequence.
    // No run-throughs. The last alarm_id is removed in the
    // do_message, above, which tells the player to sing.
    if (alarm_id)
        return 0;

    // do_success wasn't initiated, or the quest failed somehow.
    if (!wolf_id)
        return 0;

    // Been there, done that.
    if (player->test_bit("Avenir", WOLF_GROUP, WOLF_BIT))
        return 0;


    if (str=="over our bones" || str== "over the bones" ||
        str=="over bones")
    {
        if (present("MANDIBLE_ID", this_object())
            &&present("RIB_ID", this_object())
            &&present("FEMUR_ID", this_object())
            &&present("TOE_ID", this_object())
            &&present("SKULL_ID", this_object())
            &&present("VERTEBRA_ID", this_object())
            &&present("PELVIC_ID", this_object()) )
        {
            //This message is printed second to the player
            //The first message print to the player in this
            //function is below, in the else()
            if (this_player()->query_prop("_player_i_sings") == 1)
            {
                this_player()->catch_tell("Your voice reaches a "
                    + "howl of perfect pitch and harmony with all "
                    + "that is primal. The shore, the forest, the "
                    + "the air... all resonate with the beauty "
                    + "and power of a song so ancient and pure.\n\n"
                    + "Before your eyes, muscles knit upon the "
                    + "fossilized wolf bones, followed by skin "
                    + "and a luscious, silky pelt!\n"
                    + "The voice grows with intensity, humming: "
                    + "Sing!\n");

                tell_room(environment(this_object()),QCTNAME(this_player())
                    + " howls magnificently! The hair on your skin "
                    + "stands tall.\n", this_player());

                /* Remove earlier alarm */
                remove_alarm(magic_id);

                /* Give them a minute -- for slow links */
                magic_id = set_alarm(60.0, 0.0, &magic_over_second(player));

                WRITE_THIS_LOG(QUEST_FILE, player->query_name()
                    + " sings the second time.\n");
                this_player()->add_prop("_player_i_sings", 2);
                return 1;
            }

            //This message is the last message printed to the
     	      //player in this function.
            if (this_player()->query_prop("_player_i_sings")==2)
	    {
                remove_alarm(magic_id);
                this_player()->remove_prop("_player_i_sings");

                /* Lets get rid of the bones now. They've supposedly
                 * come to life and run off :)
                 */
                all_inventory(this_object())->remove_object();

                /* Lets make sure the dump alarm is removed */
                if (dump_id)
                {
                    remove_alarm(dump_id);
                    dump_id = 0;
                }

		this_player()->catch_tell("Your howl trails off, "
                + "absorbed by and one with the world around it.\n"
		    + "The wolf comes alive, jumping down to the sand "
		    + "beside you in one easy glittering stride!\n");

		tell_room(environment(this_object()),QCTNAME(this_player())
		    + "'s howl trails off into the distance.\n",
		    this_player());

                WRITE_THIS_LOG(QUEST_FILE, this_player()->query_name()
                    + " sings the final time.\n");

		set_alarm(10.0, 0.0, &do_wolf(player));

		return 1;
            }

	    //This is the message printed first to the player
	    //The next message printed is above where
	    //if (this_player()->query_prop("_player_i_sings")==1)
       else
	    {
			write("You begin singing over the bones, "
          + "your voice ascending the scale reaching "
		    + "toward a magnificant howl.\n"
		    + "Flesh begins forming around the bones on the "
		    + "wall.\n"
		    + "The voice breathes around you: Sing. Sing!\n");

			tell_room(environment(this_object()),QCTNAME(this_player())
			+ " begins singing.\n", this_player());

         this_player()->add_prop("_player_i_sings", 1);

         WRITE_THIS_LOG(QUEST_FILE, this_player()->query_name()
         + " sings for the first time.\n");

                /* Give them a minute -- for slow links */
         magic_id = set_alarm(60.0, 0.0, &magic_over_first(player));

         return 1;
         }
        }
        // All bones aren't present.
        else
		{


           	remove_alarm(magic_id);
	    		this_player()->remove_prop("_player_i_sings");

            WRITE_THIS_LOG(QUEST_FILE, this_player()->query_name()
                +" sings over imprint with bones still missing.\n");

            write("You sing over the bones.\n"
                + "Nothing happens.\n");

            magic_over_first(player);

            return 1;
	}
        //if the str is not the one desired,
        //do the normal sing cmd.
        return 0;
    }
    // Shouldn't get this far, but just in case.
    return 0;
}

int
do_wolf(object player)
{

    player->catch_tell("The wolf takes off running down the beach, "
        + "its heavy paws thumping along the shore, kicking "
        + "up sand in its wake. Its coat gleams silver in "
        + "the light of the Source.\n");

    tell_room(environment(this_object()),
        "A silvery streak brushes past you and disappears.\n", player);

    set_alarm(15.0, 0.0, &do_person(player));

    return 1;
}

int
do_person(object player)
{

    if (player->query_gender()==G_MALE)
	player->catch_tell("Just before disappearing over the "
	+ "horizon, the gleaming wolf-figure turns into a "
      + "laughing man, running freely along the surf.\n"
	+ "He turns and calls back to you: Thank you, "
      + (capitalize(player->query_name()))
	+ ".\n");

    else
	player->catch_tell("Just before disappearing over the "
  	+ "horizon, the gleaming wolf-figure turns into a "
      + "laughing woman, running freely along the surf. \n"
	+ "She turns and calls back to you: Thank you, "
      + (capitalize(player->query_name()))
	+ ".\n");

	reward_wolf_quest(player);
}

int
do_drop()
{

    /* The quest has been done...or it has taken too long,
    * the bones are lost forever.
    */
    if (dump_id)
    {
        remove_alarm(dump_id);
        dump_id = 0;
    }

    // Reset the quest.
    if (wolf_id)
        wolf_id = 0;

    if (!present("MANDIBLE_ID", this_object())
	||!present("RIB_ID", this_object())
	||!present("FEMUR_ID", this_object())
	||!present("TOE_ID", this_object())
	||!present("SKULL_ID", this_object())
	||!present("VERTEBRA_ID", this_object())
	||!present("PELVIC_ID", this_object()) )
	return 1;

    all_inventory(this_object())->remove_object();

    return 1;
}

//Called from do_sing() when the player has successfully sung over
//the bones once, and the prop("_player_i_sings") has been set to one.
//If after 60.0 secs., the player still hasnt sung again (which would
//change the prop to equal 2, the if statement below checks true, and
//the magic is over.
int
magic_over_first(object player)
{
    if (player->query_prop("_player_i_sings") < 2)
	player->remove_prop("_player_i_sings");

    if (dump_id)
    {
        remove_alarm(dump_id);
        dump_id = 0;
    }

    // Reset the quest.
    if (wolf_id)
        wolf_id = 0;

    WRITE_THIS_LOG(QUEST_FILE, player->query_name()
       + " failed to sing in time or removed a bone.\n");

    tell_room(environment(this_object()),
        "The bones fall to the ground and the moment of magic is lost.\n");

    all_inventory(this_object())->move(environment(this_object()) );

    return 1;
}

//See magic_over_first()
//If property equals 2, then player hasnt sung for third time.
int
magic_over_second(object player)
{
    if (player->query_prop("_player_i_sings") == 2)
	player->remove_prop("_player_i_sings");

    if (dump_id)
    {
        remove_alarm(dump_id);
        dump_id = 0;
    }

    // Reset the quest.
    if (wolf_id)
        wolf_id = 0;

    WRITE_THIS_LOG(QUEST_FILE, player->query_name()
       + " failed to sing in time.\n");

    tell_room(environment(this_object()),
        "The bones fall to the ground and the moment of magic is lost.\n");

    all_inventory(this_object())->move(environment(this_object())); 

    return 1;
}

void
reward_wolf_quest(object player)
{

    /* The quest has been done...or it has taken too long,
    * the bones are lost forever.
    */
    if (dump_id)
    {
        remove_alarm(dump_id);
        dump_id = 0;
    }

    // Reset the quest.
    if (wolf_id)
        wolf_id = 0;


    if (player->test_bit("Avenir", WOLF_GROUP, WOLF_BIT))
        return;

    seteuid(getuid(this_object()));

    reward_quest("Wolf-song", player, WOLF_GROUP, WOLF_BIT, WOLF_EXP);

    WRITE_THIS_LOG(QUEST_FILE, player->query_name()
      + " sang over all the bones and "
	+ "was rewarded "+WOLF_EXP+" exp.\n" );

    return;
}

//Player must sing over the bones to bring wolf alive.
void
init()
{
    ::init();
    add_action(do_sing, "sing");
}
