#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrains.h"
#include "defs.h"
#include <macros.h>
#include <language.h>
#include <stdproperties.h>

inherit "/d/Khalakhor/std/room";
inherit "/d/Khalakhor/igneous/herbsearch";

#define BEAMED        "_this_person_was_beamed_here"
#define EXIT_IS_BUSY  "_exit_is_busy_"
#define DOGGY         STAND_DIR + "dog"

//  Prototypes
void send_them_back(object player);

string gOwner = "igneous";
int Stage;
int Alarm_id;

void
create_khalakhor_room()
{
    set_short("Igneous' workroom");
    set_long(
      "This is by far the most unkempt room you have ever seen.  "
      + "Walls are plastered with weird designs and plans.   The floor "
      + "is covered with what appears to be dust.  Off in the corner "
      + "lies the only pieces of furniture that "+CAP(gOwner)+" owns;  his "  
      + "work desk and his bed.\n");

    add_item(({"design", "designs"}),
      "These designs appear to be of "+CAP(LANG_POSS(gOwner))+" ideas for some "
      + "queer invention.  After staring at them for a brief while, you get a "
      + "headache trying to find any logic behind them.\n");  
    add_item(({"plan", "plans"}),
      "Amazingly they are barely readable.  The only scribbles "
      + "you are able to understand are: The Plan and Things to do\n");
    add_item("desk",
      "A beautiful wooden desk made of the finest oak, never have you seen "
      + "such a desk.  The only thing wich stains it's beauty are the papers, "
      + "which have been piled high all the way to the ceiling!\n");
    add_item(({"paper", "papers"}),
      "When you examine them more closely they fall down in a "
      + "heap on the floor.\n");
    add_item("bed", "@@bed_func@@");
    add_item("spittoon","A small shiney spittoon.\n");
    add_item("dust", "@@dusty@@");

    add_cmd_item(({"The Plan","The plan","the plan","the Plan"}),"read",
      "         My plan to take over Genesis!\n"+
      " \n"+
      "1. Trick fools into letting me Wiz (check)\n"+
      "2. Annoy Wizards with MANY questions!!! (check)\n"+
      "3. Play tricks and pranks on all the wizards until they can\n"+
      "   bear me no longer and they quit(or I get deleted in which\n"+
      "   case I go back to step 1 and re-think plan).\n"+
      "4. Once Wizards are all gone repeat step 3 with the mortals.\n"+
      "5. With a completely empty MUD I have effectively taken over\n"+
      "   Genesis and now Rule it!!!\n");
    add_cmd_item(({"Things to do","things to do"}), "read",
      "         Things to do today.\n"+
      " \n"+
      "1.  Take over the world.\n"+
      "2.  Annoy Wizards with MANY questions!!\n"+
      "3.  Procrastinate so that things don't get done till Xmas\n"+
      "    of some year(tm).\n"+
      "4.  Play pranks on the general populous of Genesis.\n"+
      "5.  Do some coding *shrug*\n");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_PLAIN);

    add_std_herbs();
    add_exit(STAND_DIR + "is_afk", "afk", "@@check_if_wiz@@");
    add_exit("/d/Khalakhor/workroom", "Khalakhor", "@@check_if_wiz@@");
    add_exit("/d/Shire/workroom", "Shire", "@@check_if_wiz@@");
    add_exit(STAND_DIR + "workroom", "exit", "@@send_back@@");
}

void
init()
{
    if (TP->query_real_name() == gOwner)
    {
	add_action("beam","beam");
	add_action("doggy", "doggy");
    }
    ::init();
}

int
beam(string str)
{
    object person;

    person = find_living(str);

    if (person && interactive(person))
    {
	write("You are now beaming up "+capitalize(str)+".\n");
	tell_room(ENV(person),QCTNAME(person)+" is engulfed in a bright "+
	  "blue light and slowly dematerializes before your very eyes!\n",
	  person);
	person->catch_msg("You are surrounded by a bright blue light and "+
	  "your surroundings slowly fade away from your sight.\n");
	person->add_prop(BEAMED,1);
	person->move_living("M",TO);
	return 1;
    }
    notify_fail("Sorry could not find "+str+" anywhere.\n");
    return 0;
}

int
doggy(string str)
{
    object dog;

    if (TP->query_dog_follow_shadow())
	return 0;

    setuid(); seteuid(getuid());
    dog = clone_object(DOGGY);
    dog->set_master(TP);
    dog->move_living("void",TO);
    return 1;
}


//   When someone enters our workroom we welcome them 
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    if (!interactive(ob))
	return;
    if (ob->query_prop(BEAMED))
    {
	ob->remove_prop(BEAMED);
	ob->catch_msg("You slowly materialize in "+CAP(short())+"!\n");
	tell_room(TO,QCTNAME(ob)+" slowly materializes in the room.\n",ob);
    }
    if (ob->query_real_name()  == gOwner)
    {
	write("Hail "+CAP(gOwner)+"!!!\n");
	return;
    }
    say("Horns sound at the arrival of "+QTNAME(ob)+"!\n");
    write("Horns sound, welcoming you, as you enter "+
      CAP(query_short())+".\n");

}

//    To prevent mortals from entering certain areas
int
check_if_wiz()
{
    write("Before you can leave, an old man arrives at the door and stares " +
      "at you.\nHe looks you up and down, carefully studying your every " +
      "move, after awhile he finally says something.\n\n");

    if (TP->query_wiz_level() || TP->query_npc())
    {
	write("The old man says: Alright then, off you go.\n\n");
	return 0;
    }

    write("The old man says: I am sorry but you can not pass.\n\n");
    return 1;
}

int
send_back()
{   
    if (TO->query_prop(EXIT_IS_BUSY))
    {
	write("The old man says:  Wait your turn!!\n");
	return 1;
    }
    if ((TP->query_wiz_level()) && (TP->query_real_name() != gOwner))
    {  
	TP->move_living("exit", TP->query_prop(LIVE_O_LAST_ROOM));
	return 1;
    }
    TO->add_prop(EXIT_IS_BUSY, 1);
    write("An old man arrives at the exit and stops you, after a brief "+
      "silence he speaks up and starts to ask you some questions.\n\n");
    say("An old man arrives at the exit and starts to ask " +
      QCTNAME(TP) + " some questions.\n\n");
    Stage = 1;
    Alarm_id = set_alarm(itof(random(5)+1),itof(random(5)+1),
      &send_them_back(TP));
    return 1;
}

void
send_them_back(object player) 
{
    switch(Stage)
    {
    case 1:
	tell_room(TO, "The old man says: What is your name?\n");
	player->command("$say My name is "+player->query_name()+".");   
	break;
    case 2:
	tell_room(TO, "The old man says: What is your quest?\n");
	player->command("$say To return from where I came.");
	break;
    case 3:
	tell_room(TO, "The old man says: What is your favourite colour?\n");
	player->command("$say Blue.");
	break;
    case 4:
	player->command("$say No, ....");
	player->command("$scream");
	player->move_living("plumetting to earth",
	  player->query_prop(LIVE_O_LAST_ROOM));
	TO->remove_prop(EXIT_IS_BUSY);
	remove_alarm(Alarm_id);
	break;
    }
    Stage += 1;
}   

string
dusty()
{
    object itch;

    if (TP->query_real_name() == gOwner)
    {
	return("You suddenly remember that that dust is actually " +
	  "itching powder and quicky pull your hand away from it before "+
	  "you touch it and contract the annoying itch!\n");
    }
    setuid(); seteuid(getuid());
    itch = clone_object("/d/Shire/trickster/obj/itchy_scratchy");
    itch->move(TP);
    itch->start_itching(TP);
    return("Hmmmm...   You examine the dust carefully and discover " +
      "that the dust is a fine powder of some sort...   Unable to " +
      "discover the nature of the powder you shrug and put the strange " +
      "powder out of your mind.\n");

}

string
bed_func()
{

    say(QCTNAME(TP) +" stares at the bed and is slowly drawn to it. " +
      "All of a sudden " + HE_SHE(TP) + " runs up to the bed " +
      "and starts to jump up and down wildly upon it.\n");

    return("You see an extremely messy bed.  You wonder how it got so " +
      "messy.... All of a sudden you get an urge to jump on the bed, " +
      "you try to resist it but fail miserably. You run up to the " +
      "bed and start bouncing up and down on it like a child.\n");
}

void
remove_object()
{
    if (TI->query_real_name() != gOwner)
    {
	TI->remove_object();
	return;
    }
    ::remove_object();
}
