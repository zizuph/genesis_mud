/*
 * /doc/workroom.c
 * Written 920624 by Quis
 * 
 * This function serves two main purposes.  First, it is example coding
 * of a workroom.  Second, it gives the apprentice wizard an easy way to
 * get back to the wizard island.
 */

inherit "/std/workroom";

/* Inherit the room_tell functions */
inherit "/d/Krynn/open/room_tell";

#include "/sys/macros.h"                       /* macros like VBFC and QNAME */
#include "/sys/stdproperties.h"                /* self-explanatory */

int alarm_id;

string
my_long()
{
    if (this_player()->query_name() == "Lilith")
        return "Rather than create a lushly sybaritic room filled "+
           "with wondrous sensual delights, you have chosen to create "+
           "a boundless space that represents your imagination. "+
           "As such, it is stark, a clearing of sorts, but not empty. "+
           "Instead, it vibrates with possibility and potential.\n"+
           "What this space lacks in luxury appointments, "+
           "it makes up for with creative energy that fills the very "+
           "air, causing it to shimmer with mirage-forms in response to "+
           "your thoughts.\n"+
           "This is the space in your mind where all things are "+
           "possible, where your imagination and ingenuity can give "+
           "birth to more of the creations--both lauded and "+
           "infamous--for which you are known.\n";

    else
        return "As this is Lilith's workroom, you were probably expecting "+
           "something lush and sybaritic, a room of wondrous sensual "+
           "delights. Instead what you see is boundless space with "+
           "exits heading off toward distantly visible places. It is "+
           "stark, even unremittingly so, but not empty. "+
           "What this place lacks in luxury appointments, "+
           "it makes up for with a creative energy that fills the very "+
           "air, causing it to shimmer with mirage-forms in response to "+
           "her thoughts.\n"+
           "This is the space in Lilith's mind where all things "+
           "are possible, where her imagination and ingenuity have "+
           "given birth to the creations (both the lauded and the "+
           "infamous) for which she is known.\n";
}

/*
 * This function is called when the workroom is loaded.  It sets up the
 * description of the room, and its exits.
 */
void
create_workroom()
{
    /* Here is an example of VBFC in the long description.  The long
     * description will be the string returned by the function "long_desc"
     */
    set_long(my_long);
    set_short("Lilith's creating room and thinking tree");

    add_item(({"energy","creative energy", "air"}),
        "It shimmers and sparkles in response to thoughts.\nVery cool!\n");
    add_item(({"mirage-form", "mirage forms", "forms", "mirages"}),
        "The mirage-forms are born of Lilith's imagination. "+
        "Most of them ripple and fade away, ideas whose time has "+
        "yet to come, or perhaps never will.\n");

    LOAD_ERR("/d/Krynn/open/room_tell");
    set_tell_time(1000);

    add_tell("Sounds carry from the garth, sounds of "+
        "love and pleasure admixed with low murmuring voices.\n");
    add_tell("The chime of bells and the thrum of tympani can "+
        "be heard in the distance.\n");   
    add_tell("The faint undertone of reverent voices percolates "+
        "through the air.\n");
    add_tell("Eerie chanting rises and falls rythmically.\n");
    add_tell("Citrus and sandlewood scents swirl by.\n");
    add_tell("A puff of wind carries the scent of pungent "+
        "incense to your nose.\n");
    add_tell("A vision of lush hedgerows suddenly appears, "+
        "then wavers and fades.\n");
    add_tell("Voices murmur, ebbing and flowing, barely audible.\n");
    add_tell("A tidy little village manifests itself for an "+
        "eyeblink, and then is gone.\n");
    add_tell("A fierce female warrior appears, her eyes full "+
        "of challenge.\nHer fingers brush a tattoo over her "+
        "breast and then she fades to shimmering nothingness.\n");
    add_tell("A bathhouse shimmers into existance and slowly fades.\n");
    add_tell("A sudden insight:\n   "+
        "The meeting of impulse and intellect creates the "+
        "most extraordinary action.\n");
    add_tell("You feel the touch of warm fingers upon your nape, "+
        "and the echo of a kiss upon your cheek.\n");
    add_tell("The area is pervaded with a sense of sacredness.\n");
    add_tell("Your awareness floats and you find yourself "+
       "momentarily aswirl with the sparks of creative energy.\n");
    add_tell("A swirl of something appears near the tree, reaching "+
        "toward you.\nVoices wash through "+
        "your consciousness, all unified, all echoing a wordless "+
        "message of pride  affection  duty  longing  zeal  ecstacy "+
        " loyalty  perseverance  fervor  righteousness  fealty  passion...\n");
    add_tell("The very air seems to vibrate with possibility and "+
        "potential.\n");


    /* Finally we add an exit */
    add_exit("/d/Genesis/wiz/domain", "tor", 0, 0);
    add_exit("/d/Avenir/union/room/council", "council", 0, 0);
    add_exit("/d/Avenir/register/relate", "registry", 0, 0);
	add_exit("/d/Avenir/common/dark/submissions/a_vast_majestic_cave", "cave", 0, 0);

    clone_object("/w/mercade/obj/sequoia")->move(this_object(), 1);
}

int 
return_to_normal()
{
    
    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);    
    write("You get up from your seated position under the tree.\n");
    say(QCTNAME(this_player()) +" seems to prefer standing to sitting.\n");
    return 1;
}


int
do_sit()
{
    if (this_player()->query_name() == "Lilith")
    {
        write("You take a seat beneath your thinking tree "+
            "and lean comfortably against its shaggy trunk.\n");
        say(QCTNAME(this_player()) +" sits underneath the giant sequioa "+
            "and leans back against its shaggy trunk.\n");      
        this_player()->add_prop(LIVE_S_EXTRA_SHORT, 
            " is sitting under her thinking tree");        
        return 1;
    }
    write("You sit under the giant sequioa.\n");
    say(QCTNAME(this_player()) +" sits underneath the giant sequioa.\n");
    return 1;
}

void
do_seat_me(object ob)
{
    remove_alarm(alarm_id); 
    if (!present(ob, this_object()))
        return;    
    if (ob->query_name() == "Lilith")
    {
        write("You take a seat beneath your thinking tree "+
            "and lean comfortably against its shaggy trunk.\n");
        say(QCTNAME(ob) +" sits underneath the giant sequioa "+
            "and leans back against its shaggy trunk.\n");      
        ob->add_prop(LIVE_S_EXTRA_SHORT, " is sitting under her thinking tree");        
        return;
    }
    write("Lilith invites you to sit under the tree.\n");
    return;
}
    
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(ob))
        return;

    start_room_tells();
    alarm_id = set_alarm(3.0, 0.0, &do_seat_me(ob));
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!to || !ob || !interactive(ob))
        return;
    ob->remove_prop(LIVE_S_EXTRA_SHORT);
}
        
void
init()
{
    ::init();

    add_action(return_to_normal, "stand");
    add_action(return_to_normal, "stand up");
    add_action(return_to_normal, "rise");
    add_action(return_to_normal, "get up");
    add_action(do_sit, "sit");
    add_action(do_sit, "sit down");
    add_action(do_sit, "sit under tree");

}
    
