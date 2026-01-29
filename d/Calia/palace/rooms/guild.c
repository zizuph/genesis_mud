
/*         the Calian sanctuary in the crystalline palace second floor

    coder(s):   Glykron
    history:
		5/27/99	Couches fixed				Glykron
               11/3/97  more wolfhelm types                      Maniac 
               18/8/96  exit south to library added              Maniac
                4/1/96  wolfhelms added                          Maniac
                27/10/95    better check for intruders           Maniac
                 19.4.95    check for acceptance/rec officer/council 
                            before admitting a player            Maniac
                 13.2.95    move player down if upstairs banned  Maniac
                21. 1.95    exit east to rack                    Glykron
                21. 1.95    sanctuary removed                    Glykron
                 2. 1.95    exit added to recruiter room         Malcontent
                15.11.94    anti-bug code put in enver_inv       Maniac
                10.17.94    move start location to here          Glykron
                21. 9.94    check to filter out occ-guild 
                            people from doing quest              Maniac
                 1. 5.92    quest added                          Glykron
                 5. 4.92    created                              Glykron
*/

#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <money.h>
#include "defs.h"
#include RANDOM_HEADER
#include CALIAN_HEADER
#include COUNCIL_HEADER
#include RECRUITER_HEADER
inherit GLYKRON_LIGHT_ROOMS + "couches_room";

string code, keyword;

string *wolfhelm_adj = 
      ({ "black", "blue", "bright", "blue-crystal", 
         "black-crystal", "claw-emblazoned", "crystal", 
         "dark", "dark-crystal", "fire-emblazoned", "flame-emblazoned", 
         "flower-emblazoned", "glimmering", "golden", 
         "grey", "golden-crystal", "green-crystal", 
         "moon-emblazoned", "rainbow", "rainbow-crystal", "red",  
         "red-crystal", "silver-crystal", "shimmering", 
         "sky-crystal",  "sting-emblazoned", 
         "star-emblazoned", "sky-blue", "silver", "steel", 
         "sun-emblazoned", "thorn-emblazoned", 
         "white", "white-crystal" });

string
query_keyword()
{
    return keyword;
}

string
query_picture_desc()
{
    log_file("picture", ctime(time()) + " (" + TP->query_name() + ")\n");
    return
        "The picture has 2 humanoid heads, ghostly hands reaching out from " +
        "within each.  The hands are clasping one another.  The word " +
        code + " is written at the " + "bottom of the picture.\n";
}

void
reset_room()
{
    code = RANDOM_WORD;
    keyword = RANDOM_WORD;
}

string
describe_couches()
{
    return
        "There are puffy looking couches of every color here." +
	::describe_couches();
}

status
down()
{
    object tp;
    if (can_leave() == 0)
	return 0;
    tp = TP;
    write
    (
	"You step into the white light, gently descend, and then step out.\n"
    );
    say(QCTNAME(tp) + " steps into the white light.\n");
    tell_room(ROOM("light_trainroom"),
        QCTNAME(tp) + " steps out of the white light.\n");
    tp->move_living("M", ROOM("light_trainroom"));
    return 1;
}

void
create_room()
{
    set_short("Calian Lounge");
    set_long(
        "This is a trapezoidal room whose east and north walls slant away " +
        "from you to the southwest.  " +
        "There are several comfortable looking couches here. " +
        "If you want to start in this room, type <start here>.  " +
        "A picture adorns the northeast wall.  " +
        "There is also a hole in the floor filled with white light.  " +
        "\n");
    add_item("picture", query_picture_desc);
    add_item("hole", "You can see nothing through the light in the hole.\n");
    add_prop(OBJ_S_WIZINFO, "This is a default start location.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(ROOM("light_boardroom"), "north", 0);
    add_exit(ROOM("light_rack"),"east", 0, 0);
    add_exit(ROOM("light_keyroom"), "southeast");  
    add_exit(GLYKRON_LIGHT_ROOMS + "private_library", "south"); 
    clone_object(GLYKRON_OBJECTS + "wolfhelm_sign")->move(this_object());
    ::create_room();
    reset_room();
}

int
start(string str)
{
    object tp;

    if (str != "here")
	return 0;

    tp = TP;
    tp->set_default_start_location(explode(ROOM("light_guild"), ".")[0]);
    write("Ok, you start here now.\n");
    return 1;
}


/* For people who are upstairs banned, kick them back downstairs,
   they may have done a "tell armageddon home" to here.
*/
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob)) 
        set_alarmv(0.2, 0.0, "down_check", ({ob})); 
}


void
down_check(object ob) 
{
    if (!objectp(ob) || (environment(ob) != this_object()))
        return;

    seteuid(getuid());
    if (!COUNCIL_CODE->is_calian(ob) || 
        COUNCIL_CODE->is_upstairs_banned(ob)) 
    {
        ob->command("down");
    }
}



int
project_to(string str)
{
    string receiver_name, str1, str2;
    object tp, medallion, receiver;

    tp = TP;
    medallion = present("Calia_medallion", tp);
    if (!medallion)
        return 0;

    if (!str)
        return 0;
    if (sscanf(lower_case(str), "to %s %s" + code + "%s", receiver_name, str1,
        str2) != 3)
        return medallion->project_to(str);

    receiver = find_living(receiver_name);
    if (!receiver || receiver->query_guild_member(GUILD_NAME) ||
        receiver->query_guild_member(GUILD_TYPE) ||
        !(RECRUITER_CODE->is_recruiter(tp->query_name()) ||
          RECRUITER_CODE->is_accepted(receiver->query_name()) ||
          COUNCIL_CODE->is_council_member(tp->query_name())))
        return medallion->project_to(str);

/*
    if (!medallion->project_to("to " + receiver_name + " " + str1 + keyword +
        str2))
        return 0;
*/

    receiver->catch_msg("A word rings through your head: " + keyword + ".\n");
    tp->catch_msg("You feel the power of the word has reached " +
                   receiver_name + ".\n");
    OBJECT("calian_members_poster")->update_poster(capitalize(receiver_name) +
        " was aided by " + capitalize(tp->query_real_name()) +
        " to do the entrance quest.\n");

    if (tp->test_bit("Calia", 0, 1))
        return 1;

    write("You feel more experienced.\n");
    tp->add_exp(2000);
    tp->set_bit(0, 1);
    return 1;
}


int
wolfadj()
{
    object tp;

    tp = this_player();

    tp->catch_msg("Possible wolfhelm adjectives:\n" + 
                  COMPOSITE_WORDS(wolfhelm_adj) + ".\n");

    return 1;
}



/* Action to buy a wolfhelm */
int
wbuy(string str)
{
    object tp, wh;
    string s2;

    tp = this_player();

    if (!stringp(str)) {
        notify_fail("Syntax: buy <adjective>.\n");
        return 0;
    }

    if (sscanf(str, "%s wolfhelm", s2) != 1)  
        s2 = str;

    if (member_array(s2, wolfhelm_adj) == -1) {
        notify_fail("That was not one of the possible wolfhelm adjectives.\n");
        return 0;
    }

    if (!MONEY_ADD(tp, -1666)) {
        notify_fail("You didn't have enough money!\n");
        return 0;
    }

    wh = clone_object(GLYKRON_ARMOURS+"wolfhelm");
    wh->set_wolfhelm_a(s2);
    tp->catch_msg("You buy " + LANG_ADDART(wh->short()) + ".\n"); 
    say(QCTNAME(tp) + " buys " + LANG_ADDART(wh->short()) + ".\n");
    if (wh->move(tp)) {
        wh->move(this_object());
        tp->catch_msg("Ok, it's on the floor.\n");
    }
    return 1;
}

void
init()
{
    ::init();
    add_action(project_to, "project");
    add_action(start, "start");
    add_action(down, "down");
    add_action(wbuy, "buy");
    add_action(wolfadj, "wolfadj");
}
