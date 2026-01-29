/* Nippur, the gift box maker of Kendermore, Gwyneth, May-June 1999 */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/sys/money.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE

int make_box_id = 0;
void
create_krynn_monster()
{
    set_name("nippur");
    set_title("Shadowpoker of Kendermore");
    set_race_name("kender");
    set_living_name("nippur");
    set_gender(1);
    set_introduce(1);
    set_adj("curious");
    add_adj("blond-haired");
    set_long("This kender has her hair tied up in a topknot like " + 
        "most kender, but has pretty paper bows tied in her hair. " + 
        "She is neatly wrapping a box with purple and yellow striped " +
        "wrapping paper. Perhaps you could get a nice box like that " + 
        "if you asked nicely.\n");
    set_stats(({60,75,60,70,70,90}));
    add_prop(NPC_M_NO_ACCEPT_GIVE, " looks it over intently and hands it " +
        "back, saying 'See, sometimes I do remember to return things!'\n");

    set_alarm(1.0,0.0,"arm_me");
}

/* Function name : Arm me
 * Description : Clones, wears and wields armours and weapons.
 * Returns : Null
*/

void
arm_me()
{
    setuid();
    seteuid(getuid(TO));
    clone_object(KOBJ + "std_knife")->move(TO);
    clone_object(KOBJ + "hoopak")->move(TO);
    clone_object(KOBJ + "leggings")->move(TO);
    clone_object(KOBJ + "boots")->move(TO);
    clone_object(KOBJ + "cloak")->move(TO);
    clone_object(KOBJ + "blouse")->move(TO);

    command("wear all");
    command("wield all");
}

/* Function name : Reset id
 * Description : Resets the make_box_id to 0 so a player can buy a box
 *     when Nippur is done with the previous box.
 * Returns : Null
*/

void
reset_id()
{
    make_box_id = 0;
}

/* Function name : Make box
 * Description : Shows the box making routine, and calls the function that
 *     loads the box with the right colour/pattern at the end.
 * Returns : Null
*/

void
make_box(string str)
{
    object buyer = TP;

    {
        set_alarm(1.0,0.0, &command("emote chatters: " + 
            "Oh, " + str + ", what a nice choice!"));
        set_alarm(2.0,0.0, &command("emote takes out a large gift box."));
        set_alarm(3.0,0.0, &command("emote takes out a piece " + 
            "of " + str + " wrapping paper."));
        set_alarm(4.0,0.0, &command("emote places the " + str + " paper " +
            "on top of the box."));
        set_alarm(5.0,0.0, &command("emote pushes the paper neatly into " + 
            "the box."));
        set_alarm(6.0,0.0, &command("emote pulls the corners of the " + 
            "wrapping paper over the edges of the box."));
        set_alarm(7.0,0.0, &command("emote pastes the paper at the bottom " + 
            "of the box and smiles."));
        set_alarm(8.0,0.0, &command("emote places the finished gift box " + 
            "in the display window for you to buy when ready."));
        set_alarm(8.1,0.0, "load_box",str);
        return;
    }
}

/* Function name : Load box
 * Description : Clones a box with the desired pattern/colour paper,
 *     and moves it to the storeroom to be bought.
 * Returns : Null
*/

void
load_box(string str)
{
    object box;
    box = clone_object(KOBJ + "gift_box");
    box->set_colour(str);
    box->move(KROOM + "gift_shop2");
    reset_id();
    return; 
}

/* Function name : Check id
 * Description : Prevents Nippur from making more than one box at a time.
 * Returns : Null
*/

void
check_id(string str)
{
    object buyer = TP;
    object box;

    if(make_box_id == 0)
    {   
        make_box_id = 1;
        make_box(str);
    }
    else
    {
        set_alarm(1.0,0.0, &command("emote chatters: I'm sorry, I only " + 
            "have two hands!"));
        set_alarm(2.0,0.0, &command("emote chatters: That would be very " + 
            "interesting to have four hands! Don't you think?"));
    }
        return;
}
   
