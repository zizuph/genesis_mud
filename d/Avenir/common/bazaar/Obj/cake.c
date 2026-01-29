#pragma strict_types
#include "/d/Avenir/common/common.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>

inherit "/std/object";
int query_amount();

int is_light = 0;  // Ready to light
int amount_left = 20;
int count_candles = 30;

public void
create_object()
{
    set_name("princess cake");
    add_name("cake");
    add_name("birthday cake");
    set_long("This cake is covered with a thin layer of light " +
        "green mazipan, powdered with vanilla sugar. Stuck in the " +
        "marzipan you can see many small candles. Most " +
        "likely one for each year the celebrate just became. Around " +
        "the bottom the cake a thin string of cream can be seen.\n");
    set_short("a princess birthday cake");
    add_item(({"candle","candles"}), "@@desc_candles");
    add_item("pieces", "@@desc_pieces");
    add_item("cream", "@@desc_cream");
    setuid();
    seteuid(getuid());
}

void
init()
{
    ::init();
        add_action("blow_lights","blow");
        add_action("light_candles","light");
        add_action("eat", "eat");
        add_action("get_cream","get");
        add_action("cut_cake","cut");
        add_action("adjust_candles","adjust");
}

int
query_candles()
{
    return count_candles;
}

string
desc_candles()
{
    if (is_light == 0)
        return "Stuck in the cake are many small unlit candles " +
            "waiting for the birthday celebrate to set light " +
            "to them. You can easily adjust the candles to get " +
            "the proper amount of them. One for each year of the " +
            "celebrate. Right now there are " +query_candles()+
            " in the cake.\n";
    if (is_light == 1)
        return "Stuck in the cake are many small candles. You see " +
            "they are all shining with a bright flare and they " +
            "spread a nice smell and a cosy atmosphere around the " +
            "room.\n";
    return "The small candles are all blown out promising the " +
        "birthday celebrate a wish!\n";
}

string
desc_cream()
{
    string text;

    text = "You look at the cream surrounding the bottom of the " +
        "cake. It looks delicious and its really inviting to get " +
        "some on your finger.\n";
    return text;
}

string
desc_pieces()
{
    string desc = "There are aproximately " +query_amount()+
        " pieces left in the cake.\n";
    return desc;
}

int
get_cream(string str)
{
    object cream;

    if (str == "cream")
    {
    TP->add_prop("_cream_on_finger", 1);
        cream = clone_object("./cream");
        cream->move(this_player(), 1);
    write("You stick out your index finger and get some " +
        "of the cream on top of it. Its very tempting to " +
        "suck it off.\n");
    say(QCTNAME(TP) + " reches forward and gets some cream " +
        "from the cake onto " + TP->query->pronoun() + " index " +
        "finger.\n");
}
}



int
blow_lights(string str)
{
    if (str == "candles" | str == "lights")
    {
        if (is_light == 1)
        {
            write("You take a deep breath and blow out all the " +
                "candles. In your head you can hear a soft voice " +
                "asking you to make a wish of luck.\n");
            say(TP->query_real_name() + " takes a deep breath " +
                "and blow out all the small candles!\n");
            (is_light = 2); // Blown out candles
            return 1;
}
else
if (is_light == 0)
{
    write("You better light the candles first!\n");
    return 1;
}
else
write("The candles have already been lit and blown out. " +
    "All that remains are small burned out candles.\n");
return 1;
}
return 0;
}

int
light_candles(string str)
{
    if (is_light == 0)
    {
        if (str == "candles")
        {
            write("You start to light up all the candles and after a " +
                "short while they shine with a bright flare!\n");
            say(TP->query_real_name() + " lights up the candles " +
                "in the green princess birthday cake!\n");
            (is_light = 1);
            return 1;
        }
    }
    write("You can only light unlit candles.\n");
    return 1;
}

int
eat(string str)
{
    if ((str == "cake") || (str == "birthday cake"))
    {
        if (query_amount())
        {
            write("You look at the cake and it looks delicious. A strong " +
                "urge to eat the whole cake comes over you, but you fight " +
                "the feeling and decide it would be better to cut a piece " +
                "instead.\n");
    return 1;
        }
}
    return 0;
}


int
cut_cake(string str)
{
    object piece;

    if ((str == "cake") || (str == "birthday cake") || ("piece"))
    {
        amount_left--;
        if (!(query_amount()))
        {
             say(QCTNAME(TP) + " took the last pice and the " +
                 "cake is no more.\n");
             write("You took the last piece and the cake. No " +
                 "need to cut that. The cake is no more.\n");
             piece = clone_object("./piece");
             piece->move(TP, 1);
             remove_object();
             return 1;
        }
        write("You cut a piece from the birthday cake.\n");
        say(QCTNAME(TP) + " cuts a piece from the birthday cake.\n");
        piece = clone_object("./piece");
        piece->move(TP, 1);
        return 1;
    }
    return 0;
}

int
query_amount()
{
    return amount_left;
}



/*

add_ask("give_cake","cake");

int
give_cake()
{
if (cake == 1)
{
        cake--;
        object cake = clone_object("/d/Avenir/common/bazaar/Obj/cake");
        cake->move(TP, 1);
        write(QCTNAME(TO) + " gives you a nice birthday cake.\n");
        return 1;
    }
}
*/
