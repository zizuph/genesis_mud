inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#define TO   this_object()
#define TP   this_player()
#define ENV  environment
#define CAP  capitalize
#define PATH "/d/Terel/common/town/temple/"
    
object priest;



public void
reset_room()
{
    if (priest) return;
    
    seteuid(getuid());
    priest = clone_object(PATH + "priest");
    priest->move_living("M", TO);
    
}


public int
do_pray(string str)
{

    write("You pray.\n");
    write("You feel closer to the divine powers.\n");
    say(QCNAME(TP) + " prays.\n");
    

    if (TP->query_alignment() < 0 && priest && ENV(priest) == TO)
    {
        priest->command("say " + CAP(TP->query_race_name()) +
                        "! You better change your way of living.");
    }
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_pray, "pray");
}

public void
create_room()
{    
    set_short("Temple");
    set_long("This is a small temple sanctuary, it is made of dark " +
	           "granite, supported by white marble pillars. There is " +
	           "a marble archway that leads out to the north. A stand " +
	           "near the archway holds candles. In the center of the " +
             "sanctuary is a grand statue, it stands twenty feet " +
             "high. The walls are painted with colourful icons and " +
             "images, they depict heroes and heroines. The dome of " +
             "the temple has been coated with a sheen of gold. The " +
             "gold projects a golden glow upon the statue. " +
             "Triangular stained glass windows form a circle just " +
             "below the golden dome. Below each of the windows is " +
             "a large gold urn, out of the urns grow long hanging " +
             "primrose bushes.\n");
    
    add_exit("/d/Terel/common/town/paths/path_w06", "north", 0);
    
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
    
    add_item("statue",
             "The image of heroism, this figure is carved from " +
             "alabaster and seated upon a throne. A man of great " +
             "age, seen only in his eyes and long beard. His body " +
             "in perfect form, muscled and lithe. Upon his head a " +
             "crown-helm. Under his left arm is a harp, in his right " +
             "hand a broadsword.  The long robe he wears over his " +
             "shoulders is a mantle that hangs to the floor.\n");
    
    add_cmd_item("statue", "reverence", "@@rev_stat");
    
    add_item(({"dome", "gold"}), "The dome is brilliant and flawless.\n");
    add_item(({"primrose"}), "Beautiful blooming red flowers.\n");

    add_item(({"heroes","heroines","paintings","icons","images"}),
	     "These are the many holy people of the ages that have " +
             "made their vows before the divine powers.\n");
    reset_room();
}


public void
priest_react(object who)
{
    if (!priest || ENV(priest) != TO || who == priest) return;
    
    if (!who || ENV(who) != TO) {
        priest->command("shrug");
        return;
    }
    if (who->query_alignment() >= 95) {
        priest->command("whisper " + who->query_real_name() + 
                    " The result of defoliation may be found " +
                    "in a high place.");
    } else {
        priest->command("say " + CAP(who->query_race_name()) +
                    "! I will not reveal any secrets to you!");
    }     
}

public string
rev_stat()
{
    set_alarm(4.0, -1.0, &priest_react(TP));
    say(QCTNAME(TP) + " mumbles something while facing the statue.\n");
    return "You feel closer to the heroes and heroines of the world.\n";
}
